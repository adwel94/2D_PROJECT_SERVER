#pragma once
#ifndef _IOCP_SERVER_H_
#define _IOCP_SERVER_H_
#pragma comment(lib,"msimg32")
#pragma comment(lib,"ws2_32")

#include <winsock2.h>
#include <WS2tcpip.h>

#include "..\Client\Client.h"
#include <Utilities/Thread\Thread.h>
#include <Utilities/Log/Log.h>


#define IOCP_THREAD_COUNT 8

namespace Server
{

	class cIOCP_SERVER
	{
	protected:
		Utilities::cLog mLog;
		HANDLE mPort;
		OVERLAPPED mExit;
		Utilities::cThread* mProcess_thread[IOCP_THREAD_COUNT];
	public:

		cIOCP_SERVER();
		virtual ~cIOCP_SERVER();

		bool Create_Server();
		void End_Server();

		static bool IOCP_Process(LPVOID _client);

		virtual void AcceptProcess(cClient* _client) = 0;
		virtual void RecvProcess(cClient* _client, DWORD _trans) = 0;
		virtual void SendProcess(cClient* _client, DWORD _trans) = 0;
		virtual void DisconnectProcess(cClient* _client) = 0;
	};


}








#endif // !_IOCPMANAGER_H_


