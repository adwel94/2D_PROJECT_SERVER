#pragma once
#ifndef _SOCK_H_
#define _SOCK_H_


#pragma comment(lib,"msimg32")
#pragma comment(lib,"ws2_32")
#include <winsock2.h>
#include <WS2tcpip.h>

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
			virtual ~cSock()
			{

			}

			const SOCKET GetSock() { return mSock; }
			const SOCKADDR_IN& GetAddr() { return mAddr; }
		};


	}
}





#endif // !SOCK_H
