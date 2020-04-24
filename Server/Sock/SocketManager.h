#pragma once
#ifndef _SOCKET_MANAGER_H_
#define _SOCKET_MANAGER_H_
#include "Sock.h"
#include <Singleton/SingleTon.h>



namespace Server
{
	namespace Socket
	{
		enum IP_VER
		{
			IPv4 = AF_INET,
			IPv6 = AF_INET6
		};

		enum SOCKTYPE
		{
			TCP = SOCK_STREAM,
			UDP = SOCK_DGRAM
		};


		//소켓 사용시 최초 호출
		inline bool Sock_Start()
		{
			WSADATA wsa;
			//윈도우 dll 초기화 윈속 할당
			if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
			{
				return false;
			}
			return true;
		}

		class cSockManager
		{

		public:

			//기본 소켓 생성 함수
			cSock* Create_Socket(IP_VER _af, SOCKTYPE _socktype, int _pro, int _port, const char* _addr = "\0");
			
			//소켓 변경
			bool TCP_Listen_Sock(cSock* _sock);
			bool UDP_Listen_Sock(cSock* _sock);
			bool TCP_CLIENT_Sock(cSock* _sock);
			bool UDP_CLIENT_Sock(cSock* _sock);
			//소켓함수

			//bind()
			bool Bind_Socket(cSock* _sock);
			//listen()
			bool Listen_Socket(cSock* _sock);
			//accpet()
			cSock* Accept_Socket(cSock* _sock);
			//connect()
			bool Connect_Socket(cSock* _sock);
			//reuseaddr -bind 재사용 
			bool Reuse_Socket(cSock* _sock);
		};

		typedef Utilities::cSingleTon<cSockManager> st_cSockManager;
	}
}






#endif // !_SOCKET_MANAGER_H_
