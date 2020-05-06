#pragma once
#ifndef _CLIENT_H_
#define _CLIENT_H_
#include "Sock/Sock.h"
#include "Packet/Packet.h"
#include "User/User.h"

namespace Server
{

	class cClient :public Server::Socket::cSock, public Server::cPacket, public Server::cUser
	{

	protected:



	public:

		cClient() {}
		~cClient() {}


		bool Send_Packet();
		bool WSA_Send_Packet();


		bool Recv_Packet();
		bool WSA_Recv_Packet();


		virtual bool Recv_Process() = 0;
		virtual bool Send_Process() = 0;
	};

}



#endif // !_CLIENT_H_
