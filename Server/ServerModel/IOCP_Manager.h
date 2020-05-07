#pragma once
#ifndef _IOCP_SERVER_H_
#define _IOCP_SERVER_H_
#include "Server.h"
#include "Thread/Thread.h"
#include "Log/Log.h"
#include "DS/LockList.h"


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
		BOOL mExit;
		//������ ����
		int mThread_count;
		//��Ʈ�� ���� ������ �迭
		Utilities::cThread* mProcess_thread;
		//Ű�� ������ ����Ʈ
		Utilities::DS::cLockList<T> mKey_List;

	public:

		//�� �Է½� cpu ������ �°� ����
		cIOCP_Manager(int _thread_count = -1);
		~cIOCP_Manager();

		//����,���� �Լ�
		bool Initialize_IOCP();
		void End_IOCP();

		//��Ʈ ���
		void Accpet_Port(SOCKET _sock, T _key = NULL);

		//GetQueuedCompletionStatus �۵��� �۵��� �Լ�
		virtual void AcceptProcess(T _key) = 0;
		virtual void CompletionProcess(T _key,LPOVERLAPPED _overlap = NULL,DWORD _trans = 0) = 0;
		virtual void ErrorProcess(T _key, LPOVERLAPPED _overlap = NULL, DWORD _trans = 0) = 0;
		virtual void DisconnectProcess(T _key, LPOVERLAPPED _overlap = NULL, DWORD _trans = 0) = 0;


	protected:

		static bool IOCP_Process(LPVOID _iocp);
	};

	template<class T>
	inline Server::cIOCP_Manager<T>::cIOCP_Manager(int _thread_count)
	{
		mPort = NULL;
		mExit = FALSE;
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

		mProcess_thread = new Utilities::cThread[mThread_count];
	}

	template<class T>
	inline Server::cIOCP_Manager<T>::~cIOCP_Manager()
	{
		mLog.Close();

	}

	template<class T>
	inline bool cIOCP_Manager<T>::Initialize_IOCP()
	{
		mLog.Connect("IOCP_MANAGER.TXT");

		mPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);  // ����� �Ϸ� ��Ʈ ����
		if (mPort == NULL) return false;


		// i ���� �۾��� ������ ����
		for (int i = 0; i < mThread_count; i++)
		{
			mProcess_thread[i].Create(IOCP_Process, this, true, false);
		}

		mLog.Record("CREATE IOCP PORT THREAD : %d", mThread_count);

		return true;
	}

	template<class T>
	inline void cIOCP_Manager<T>::End_IOCP()
	{
		//��Ʈ ���� 
		mExit = TRUE;
		
		//��Ʈ�� ť �ֱ�
		PostQueuedCompletionStatus(mPort, 1, NULL, 0);
		CloseHandle(mPort);
		mPort = NULL;
		mLog.Record("END IOCP -------------------");


		delete[] mProcess_thread;
	}

	template<class T>
	inline void Server::cIOCP_Manager<T>::Accpet_Port(SOCKET _sock, T _key)
	{
		//��Ʈ ���
		CreateIoCompletionPort((HANDLE)_sock, mPort, (ULONG_PTR)_key, 0);//��Ʈ�� Ŭ���̾�Ʈ ���� ���ø���Ű�� Ŭ���̾�Ʈ ��ü��
	}




	template<class T>
	inline bool cIOCP_Manager<T>::IOCP_Process(LPVOID _iocp)
	{
		cIOCP_Manager* iocp = (cIOCP_Manager*)_iocp;
		DWORD transferred; //���۷�
		T key;//Ŭ���Ʈ
		LPOVERLAPPED overlap;//������ ���� ����	
		while (true)
		{
			//wsa�Ϸ� ���
			BOOL retval = GetQueuedCompletionStatus(iocp->mPort, &transferred, (PULONG_PTR)&key, &overlap, INFINITE); 
			if (retval == FALSE) //Ŭ���̾�Ʈ ���� ����
			{
				//���� ó��
				iocp->ErrorProcess(key, overlap, transferred);

				//���� on
				if (iocp->mExit)
				{
					printf_s("recv exit overlap - Exit Process \n");
					return true;
				}
			}
			else if (transferred == 0) //���� ��Ŷ
			{
				//���� ó��
				iocp->DisconnectProcess(key, overlap, transferred);
			}

			//���� ó��
			iocp->CompletionProcess(key, overlap, transferred);
		}

		return true;

	}



}



#endif // !_IOCPMANAGER_H_


