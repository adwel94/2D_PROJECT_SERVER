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
		
		HANDLE mSendEvt;
		//HANDLE mRecvEvt;
	public:

		cClient(SOCKET _sock, const SOCKADDR_IN& _addr);
		//cClient() {}
		virtual ~cClient();


		//중복 send 막기위함
		void SendStart();
		void SendEnd();
		void WaitSendEnd();
		bool Send_ing();

		//void RecvStart();
		//void RecvEnd();
		//void WaitRecvEnd();
		//bool Recv_ing();

		//send
		bool Send_Packet();
		bool WSA_Send_Packet();
		void WSA_Send_CallBack(DWORD _trans);

		//recv
		bool Recv_Packet();
		bool WSA_Recv_Packet();
		void WSA_Recv_CallBack(DWORD _trans);

		//recv,send 완료시 처리 함수
		virtual bool Recv_Process() = 0;
		virtual bool Send_Process() = 0;
	};

}



#endif // !_CLIENT_H_
