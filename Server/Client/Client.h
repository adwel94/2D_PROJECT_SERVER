#pragma once
#ifndef _CLIENT_H_
#define _CLIENT_H_
#include "Sock/Sock.h"
#include "Packet/Packet.h"


namespace Server
{

	class cClient :public Server::Socket::cSock, public Server::cPacket
	{

	protected:



	public:

		cClient(SOCKET _sock, const SOCKADDR_IN& _addr) : cSock(_sock, _addr) {}
		cClient() {}
		~cClient() {}

		//send
		bool Send_Packet();
		bool WSA_Send_Packet();

		//recv
		bool Recv_Packet();
		bool WSA_Recv_Packet();

		//recv,send 완료시 처리 함수
		virtual bool Recv_Process() = 0;
		virtual bool Send_Process() = 0;
	};

}



#endif // !_CLIENT_H_
