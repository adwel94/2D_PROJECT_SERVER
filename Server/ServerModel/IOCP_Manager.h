#pragma once
#ifndef _IOCP_SERVER_H_
#define _IOCP_SERVER_H_
#include "Thread/Thread.h"
#include "Log/Log.h"
#include "Server.h"
#include <list>


namespace Server
{
	//iocp매니저
	//T는 completionkey
	template <class T>
	class cIOCP_Manager
	{
	protected:
		//로그 기록
		Utilities::cLog mLog;
		//포트
		HANDLE mPort;
		//종료 
		BOOL mExit;
		//스레드 갯수
		int mThread_count;
		//포트를 받을 스레드 배열
		Utilities::cThread* mProcess_thread;
		//키를 보관할 리스트
		std::list<T> mKey_List;

		//iocp 프로세스
		static bool IOCP_Process(LPVOID _iocp); 

	public:

		//미 입력시 cpu 갯수에 맞게 설정
		cIOCP_Manager(int _thread_count = -1);
		~cIOCP_Manager();
		bool Initialize_IOCP();

		void End_IOCP();

		//포트 등록후 호출될 함수
		void Accpet_Port(SOCKET _sock, T _key);
		virtual void AcceptProcess(T _key) = 0;

		//GetQueuedCompletionStatus 작동후 작동할 함수
		virtual void CompletionProcess(T _key,LPOVERLAPPED _overlap = NULL,DWORD _trans = 0) = 0;
		virtual void ErrorProcess(T _key, LPOVERLAPPED _overlap = NULL, DWORD _trans = 0) = 0;
		virtual void DisconnectProcess(T _key, LPOVERLAPPED _overlap = NULL, DWORD _trans = 0) = 0;
	};

}








#endif // !_IOCPMANAGER_H_


