#pragma once
#ifndef _SOCKET_MANAGER_H_
#define _SOCKET_MANAGER_H_
#include "Sock.h"
#include "Singleton/SingleTon.h"
#include "Log/Log.h"
 
namespace Server
{
	namespace Socket
	{
		class cSockManager
		{
			Utilities::cLog mLog;
		public:
			cSockManager();
			~cSockManager();

			//���� ����
			bool TCP_Listen_Sock(OUT cSock*_sock);
			bool UDP_Listen_Sock(OUT cSock* _sock);
			bool TCP_CLIENT_Sock(OUT cSock* _sock);
			bool UDP_CLIENT_Sock(OUT cSock* _sock);
			//�����Լ�

			//bind()
			bool Bind_Socket(OUT cSock* _sock);
			//listen()
			bool Listen_Socket(OUT cSock* _sock);
			//accpet()
			bool Accept_Socket(cSock* _server, OUT SOCKET& _socket, OUT SOCKADDR_IN& addr);
			//connect()
			bool Connect_Socket(OUT cSock* _sock);
			//reuseaddr -bind ���� 
			bool Reuse_Socket(OUT cSock* _sock);
		};

		//�̱��� ���� �Ŵ���
		typedef Utilities::cSingleTon<cSockManager> st_cSockManager;
	}
}






#endif // !_SOCKET_MANAGER_H_
