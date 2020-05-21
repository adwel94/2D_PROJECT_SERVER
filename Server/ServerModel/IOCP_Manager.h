#pragma once
#ifndef _IOCP_SERVER_H_
#define _IOCP_SERVER_H_
#include "Server.h"
#include "Thread/Thread.h"
#include "Log/Log.h"
#include "DS/LockList.h"

#include "Sock/SocketManager.h"


namespace Server
{
	//iocp�Ŵ���
	//T�� completionkey
	template <class T>
	class cIOCP_Manager
	{
	protected:

		//�α� ���
		Utilities::cLog mLog;
		//��Ʈ
		HANDLE mPort;
		//����
		Socket::cSock mServer;
		//���� 
		BOOL mExit;
		//������ ����
		int mThread_count;
		//accept�� �� ������
		Utilities::cThread mAccept_thread;
		//��Ʈ�� ���� ������ �迭
		Utilities::cThread* mProcess_thread;
		//Ű�� ������ ����Ʈ
		Utilities::DS::cLockList<T> mKey_List;

	public:

		//�� �Է½� cpu ������ �°� ����
		cIOCP_Manager();
		virtual ~cIOCP_Manager();

		//����,���� �Լ�
		bool Initialize_IOCP(const char* _addr = "\0", int _port = 9000, int _thread_count = -1);
		bool Run_IOCP();
		void End_IOCP();

	protected:

		//GetQueuedCompletionStatus �۵��� �۵��� �Լ�
		virtual T CreateKey(SOCKET _sock, const SOCKADDR_IN& _addr) = 0;
		virtual void AcceptProcess(T _key, SOCKET _sock = NULL, const SOCKADDR_IN& _addr = NULL) = 0;
		virtual void CompletionProcess(T _key, LPOVERLAPPED _overlap = NULL, DWORD _trans = 0) = 0;
		virtual void ErrorProcess(T _key, LPOVERLAPPED _overlap = NULL, DWORD _trans = 0) = 0;
		virtual void DisconnectProcess(T _key, LPOVERLAPPED _overlap = NULL, DWORD _trans = 0) = 0;

		//accept ��
		virtual void AcceptProcess_IN(SOCKET _sock,SOCKADDR_IN& _addr);
		//������
		static Utilities::cThread::T_retval Accept_Process_thread(LPVOID _iocp);
		static Utilities::cThread::T_retval IOCP_Process_thread(LPVOID _iocp);
	};

	template<class T>
	inline Server::cIOCP_Manager<T>::cIOCP_Manager()
	{
		mThread_count = -1;
		mLog.Connect("IOCP_MANAGER.txt");
		mPort = NULL;
		mExit = FALSE;
	}

	template<class T>
	inline Server::cIOCP_Manager<T>::~cIOCP_Manager()
	{
		mLog.Close();
		mServer.End();

		//������ ����
		delete[] mProcess_thread;
	}

	template<class T>
	inline bool cIOCP_Manager<T>::Initialize_IOCP(const char* _addr, int _port, int _thread_count)
	{

		//wsa_start
		if (Socket::Sock_Start() == false) return false;

		//���ϻ���
		if (mServer.Start() == false)
		{
			printf_s("IOCP Create Server Error  \n");
			return false;

		}

		//tcp listen �������� ����
		if (Socket::st_cSockManager::GetInstance()->TCP_Listen_Sock(&mServer) == false) return false;

		mPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);  // ����� �Ϸ� ��Ʈ ����
		if (mPort == NULL) return false;


		//�۾��� ������ ����

		//default
		if (_thread_count < 0)
		{
			// CPU ���� Ȯ��
			SYSTEM_INFO si;
			GetSystemInfo(&si);
			// (CPU ���� * 2)���� �۾��� ������ ����
			mThread_count = (int)(si.dwNumberOfProcessors * 2);
		}
		else
		{
			mThread_count = _thread_count;
		}

		//������ �迭 �Ҵ�
		mProcess_thread = new Utilities::cThread[mThread_count];
		for (int i = 0; i < mThread_count; i++)
		{
			mProcess_thread[i].Create(IOCP_Process_thread, this);
		}

		//acppet ������ �Ҵ�
		mAccept_thread.Create(Accept_Process_thread, this);

		printf_s("IOCP CREATE PORT THREAD : %d\n", mThread_count);
		mLog.Record("IOCP CREATE PORT THREAD : %d", mThread_count);

		return true;
	}

	template<class T>
	inline bool cIOCP_Manager<T>::Run_IOCP()
	{

		//������ ����
		for (int i = 0; i < mThread_count; i++)
		{
			mProcess_thread[i].Run();
		}

		mAccept_thread.Run();

		printf_s("IOCP RUN Server IP : %s PORT : %d \n", mServer.Get_IP(), mServer.GetAddr().sin_port);
		mLog.Record("IOCP RUN Server IP : %s PORT : %d",mServer.Get_IP(),mServer.GetAddr().sin_port);

		return false;
	}

	template<class T>
	inline void cIOCP_Manager<T>::End_IOCP()
	{
		mServer.End();
		CloseHandle(mPort);
		mPort = NULL;


		// ������ join
		for (int i = 0; i < mThread_count; i++)
		{
			mProcess_thread[i].Join();
		}

		mAccept_thread.Join();

		mLog.Record("------------------- END IOCP -------------------");
	}	


	template<class T>
	inline void cIOCP_Manager<T>::AcceptProcess_IN(SOCKET _sock, SOCKADDR_IN& _addr)
	{
		//key ����
		T key = CreateKey(_sock, _addr);
		mKey_List.LockAdd(key);
		//��Ʈ ����
		CreateIoCompletionPort((HANDLE)_sock, mPort, (ULONG_PTR)key, 0);
		//accpet�� �۾�
		AcceptProcess(key, _sock, _addr);


		char ip[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &_addr.sin_addr, ip, sizeof(ip));
		printf_s("IOCP Connect Client IP : %s PORT : %d \n", ip, _addr.sin_port);
		mLog.Record("IOCP Connect Client IP : %s PORT : %d", ip, _addr.sin_port);
	}

	template<class T>
	inline Utilities::cThread::T_retval cIOCP_Manager<T>::Accept_Process_thread(LPVOID _iocp)
	{
		cIOCP_Manager* iocp = (cIOCP_Manager*)_iocp;
		if (iocp->mPort == NULL)
		{
			printf_s("PORT Not Create \n");
			return Utilities::cThread::T_retval::ERROR_EXIT;
		}

		//accept ���� ����
		SOCKET client_socket = NULL;
		SOCKADDR_IN client_addr;

		//Ŭ���̾�Ʈ accept
		while (true)
		{
			if (Socket::st_cSockManager::GetInstance()->Accept_Socket(&(iocp->mServer), client_socket, client_addr))
			{
				iocp->AcceptProcess_IN(client_socket, client_addr);
			}
		}
		return Utilities::cThread::T_retval::EXIT;
	}

	template<class T>
	inline Utilities::cThread::T_retval cIOCP_Manager<T>::IOCP_Process_thread(LPVOID _iocp)
	{
		cIOCP_Manager* iocp = (cIOCP_Manager*)_iocp;
		DWORD transferred; //���۷�
		T key;//Ŭ���Ʈ
		LPOVERLAPPED overlap;//������ ���� ����	

		while (true)
		{
			//wsa�Ϸ� ���
			BOOL retval = GetQueuedCompletionStatus(iocp->mPort, &transferred, (PULONG_PTR)&key, &overlap, INFINITE); 
			if (retval == FALSE) //Ŭ���̾�Ʈ ����
			{
				//Ŭ���̾�Ʈ ������ ����
				if (transferred == 0)
				{
					//���� ó��
					iocp->mKey_List.LockRemove(key);
					iocp->DisconnectProcess(key, overlap, transferred);
					continue;

				}	
				else 
				{
					//���� ó��
					iocp->ErrorProcess(key, overlap, transferred);
					WSA_Err_display("IOCP_Process_thread");
					return Utilities::cThread::T_retval::ERROR_EXIT;

				}
			}
			//���� ���� ��Ŷ
			else if (transferred == 0)
			{
				//���� ó��
				iocp->mKey_List.LockRemove(key);
				iocp->DisconnectProcess(key, overlap, transferred);
				continue;

			}
			//���� ó��
			iocp->CompletionProcess(key, overlap, transferred);
		}

		return Utilities::cThread::T_retval::EXIT;

	}



}



#endif // !_IOCPMANAGER_H_


