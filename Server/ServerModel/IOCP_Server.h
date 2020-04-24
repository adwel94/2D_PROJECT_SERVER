#pragma once
#ifndef _IOCP_SERVER_H_
#define _IOCP_SERVER_H_
#include "../Client/Client.h"
#include <Thread/Thread.h>
#include <Log/Log.h>


#define IOCP_THREAD_COUNT 8

namespace Server
{
	class cIOCP_SERVER
	{
	protected:
		Socket::cSock mServer;
		Utilities::cLog mLog;
		HANDLE mPort;
		OVERLAPPED mExit;
		Utilities::cThread* mProcess_thread[IOCP_THREAD_COUNT];

		static bool IOCP_Process(LPVOID _iocp);

	public:
		bool Initialize_Server();

		//void End_Server();	

		void AcceptProcess(Socket::cSock* _Server);
		virtual void DisconnectProcess(cClient* _client) = 0;

		virtual void CompleteProcess() = 0;


	};


}








#endif // !_IOCPMANAGER_H_


