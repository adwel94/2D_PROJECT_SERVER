#pragma once
#ifndef _CLIENT_H_
#define _CLIENT_H_
#include "Sock/Sock.h"

namespace Server
{
	struct WSAoverlapEX
	{
		OVERLAPPED overlapped;
		WSABUF wsabuf;
	};

	class cClient : public Socket::cSock
	{
		WSAoverlapEX mRecvOverlap;
		WSAoverlapEX mSendOverlap;
	protected:

	public:
		//cClient() {}
		//~cClient() {}
		//bool SendPacket();
		//bool RecvPacket();
		//bool WSArecvPacket();
		//bool WSAsendPacket();
	};

}



#endif // !_CLIENT_H_
