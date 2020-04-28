#pragma once
#ifndef _IOCP_SERVER_H_
#define _IOCP_SERVER_H_
#include "Thread/Thread.h"
#include "Log/Log.h"
#include "Server.h"
#include <list>


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
		std::list<T> mKey_List;

		//iocp ���μ���
		static bool IOCP_Process(LPVOID _iocp); 

	public:

		//�� �Է½� cpu ������ �°� ����
		cIOCP_Manager(int _thread_count = -1);
		~cIOCP_Manager();
		bool Initialize_IOCP();

		void End_IOCP();

		//��Ʈ ����� ȣ��� �Լ�
		void Accpet_Port(SOCKET _sock, T _key);
		virtual void AcceptProcess(T _key) = 0;

		//GetQueuedCompletionStatus �۵��� �۵��� �Լ�
		virtual void CompletionProcess(T _key,LPOVERLAPPED _overlap = NULL,DWORD _trans = 0) = 0;
		virtual void ErrorProcess(T _key, LPOVERLAPPED _overlap = NULL, DWORD _trans = 0) = 0;
		virtual void DisconnectProcess(T _key, LPOVERLAPPED _overlap = NULL, DWORD _trans = 0) = 0;
	};

}








#endif // !_IOCPMANAGER_H_


