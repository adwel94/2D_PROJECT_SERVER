#pragma once
#ifndef _SOCK_H_
#define _SOCK_H_


#pragma comment(lib,"msimg32")
#pragma comment(lib,"ws2_32")
#include <winsock2.h>
#include <WS2tcpip.h>
#include <stdio.h>

namespace Server
{
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


		class cSock
		{

		protected:
			SOCKET mSock;
			SOCKADDR_IN mAddr;

		public:
			cSock()
			{
				mSock = NULL; //소켓 초기화
				ZeroMemory(&mAddr, sizeof(SOCKADDR_IN)); //주소 메모리 초기화
			}

			cSock(SOCKET _sock, const SOCKADDR_IN& _addr)
			{
				mSock = _sock;//소켓 대입
				memcpy(&mAddr, &_addr, sizeof(SOCKADDR_IN)); //주소 복사
			}

			cSock(IP_VER _af, SOCKTYPE _socktype, int _pro = 0 , int _port = 9000, const char* _addr = "\0")
			{
				mSock = socket(_af, _socktype, _pro);
				if (mSock == INVALID_SOCKET)
				{
					WSA_Err_display((TCHAR*)"Socket()");		
				}

				ZeroMemory(&mAddr, sizeof(mAddr));
				mAddr.sin_family = _af; //ip 버젼

				//주소를 따로 입력하지않으면 localhost
				if (strlen(_addr) == 0)
				{
					mAddr.sin_addr.s_addr = htonl(INADDR_ANY);
				}
				else
				{
					inet_pton(_af, _addr, &mAddr.sin_addr);
				}
				//포트 등록
				mAddr.sin_port = htons(_port);

				char addr[INET_ADDRSTRLEN];
				inet_ntop(AF_INET, &mAddr.sin_addr, addr, sizeof(addr));
				printf_s("Create Socket : IP : %s, PORT : %d \n", addr, ntohs(mAddr.sin_port));
			}

		
			virtual ~cSock()
			{
				closesocket(mSock);
			}

			const SOCKET GetSock() { return mSock; }
			const SOCKADDR_IN& GetAddr() { return mAddr; }
		};


	}
}





#endif // !SOCK_H
