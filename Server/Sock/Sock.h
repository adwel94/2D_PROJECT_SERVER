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
				mSock = NULL; //���� �ʱ�ȭ
				ZeroMemory(&mAddr, sizeof(SOCKADDR_IN)); //�ּ� �޸� �ʱ�ȭ
			}

			cSock(SOCKET _sock, const SOCKADDR_IN& _addr)
			{
				mSock = _sock;//���� ����
				memcpy(&mAddr, &_addr, sizeof(SOCKADDR_IN)); //�ּ� ����
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
