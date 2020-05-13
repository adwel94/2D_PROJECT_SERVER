#pragma once
#ifndef _SOCK_H_
#define _SOCK_H_
#include "Server.h"


namespace Server
{
	//소켓 에러 출력
	inline void WSA_Err_display(const char* _msg)
	{

		LPVOID lpMsgBuf;
		FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
			NULL, WSAGetLastError(),
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR)&lpMsgBuf, 0, NULL);
		printf_s("GET_LAST_ERROR MSG : %S IN %s ", (LPTSTR)lpMsgBuf, _msg);
		//MessageBox(NULL, (LPCTSTR)lpMsgBuf, msg, MB_ICONERROR);
		LocalFree(lpMsgBuf);
	}


	namespace Socket
	{

		static bool socket_start = false;

		//소켓 사용시 최초 호출
		inline bool Sock_Start()
		{
			if (socket_start == true) return true;

			WSADATA wsa;
			//윈도우 dll 초기화 윈속 할당
			if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
			{
				return false;
			}
			socket_start = true;
			return true;
		}

		//ip v4 ,v6
		enum IP_VER
		{
			IPv4 = AF_INET,
			IPv6 = AF_INET6
		};

		//소켓 타입
		enum SOCKTYPE
		{
			TCP = SOCK_STREAM,
			UDP = SOCK_DGRAM
		};

		//소켓 클래스
		class cSock
		{

		protected:
			SOCKET mSock;
			SOCKADDR_IN mAddr;
			char mIp[INET_ADDRSTRLEN];

		public:
			cSock();
			cSock(SOCKET _sock, const SOCKADDR_IN& _addr);
			virtual ~cSock();

			//Get
			const char* Get_IP();
			const SOCKET GetSock() { return mSock; }
			const SOCKADDR_IN& GetAddr() { return mAddr; }

			bool Start(IP_VER _af = IPv4, SOCKTYPE _socktype = TCP, int _pro = 0, int _port = 9000, const char* _addr = "\0");
			void End();

			//send 함수
			bool Send(BYTE* _buf, int _size, int _flag);
			bool WSA_Send(LPWSABUF _wsabuf, DWORD _buffercount, LPDWORD _sendbyte, DWORD _flag, LPWSAOVERLAPPED _overlap, LPWSAOVERLAPPED_COMPLETION_ROUTINE _routine);
			//recv 함수
			bool Recv(BYTE* _buf, int _size, int _flag);
			bool WSA_Recv(LPWSABUF _wsabuf, DWORD _buffercount, LPDWORD _recvbyte, LPDWORD _flag, LPWSAOVERLAPPED _overlap, LPWSAOVERLAPPED_COMPLETION_ROUTINE _routine);

		};


	}
}





#endif // !SOCK_H
