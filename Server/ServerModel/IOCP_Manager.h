#pragma once
#ifndef _IOCP_SERVER_H_
#define _IOCP_SERVER_H_
#include "Client/Client.h"
#include "Thread/Thread.h"
#include "Log/Log.h"



namespace Server
{
	class cIOCP_Manager
	{
	protected:
		Utilities::cLog mLog;
		HANDLE mPort;
		BOOL mExit;
		int mThread_count;
		Utilities::cThread* mProcess_thread;

		static bool IOCP_Process(LPVOID _iocp); 

	public:

		cIOCP_Manager(int _thread_count = -1);
		~cIOCP_Manager();
		bool Initialize_IOCP();

		void End_IOCP();

		void AcceptProcess(Socket::cSock* _Server);
		//virtual void DisconnectProcess(cClient* _client) = 0;

		//virtual void CompleteProcess() = 0;


	};


}








#endif // !_IOCPMANAGER_H_


