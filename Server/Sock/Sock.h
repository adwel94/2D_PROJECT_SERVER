#pragma once
#ifndef _SOCK_H_
#define _SOCK_H_
#include "Server.h"


namespace Server
{
	//소켓 에러 출력
	inline void WSA_Err_display(const TCHAR* msg)
	{
		LPVOID lpMsgBuf;
		FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
			NULL, WSAGetLastError(),
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR)&lpMsgBuf, 0, NULL);
		MessageBox(NULL, (LPCTSTR)lpMsgBuf, msg, MB_ICONERROR);
		LocalFree(lpMsgBuf);
	}


	namespace Socket
	{

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
			cSock(IP_VER _af, SOCKTYPE _socktype, int _pro = 0, int _port = 9000, const char* _addr = "\0");
			virtual ~cSock();

			//Get
			const char* Get_IP();
			const SOCKET GetSock() { return mSock; }
			const SOCKADDR_IN& GetAddr() { return mAddr; }

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
