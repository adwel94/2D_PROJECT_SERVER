#pragma once
#ifndef _SOCK_H_
#define _SOCK_H_
#include "Server.h"


namespace Server
{
	//���� ���� ���
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

		//���� ���� ���� ȣ��
		inline bool Sock_Start()
		{
			WSADATA wsa;
			//������ dll �ʱ�ȭ ���� �Ҵ�
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

		//���� Ÿ��
		enum SOCKTYPE
		{
			TCP = SOCK_STREAM,
			UDP = SOCK_DGRAM
		};

		//���� Ŭ����
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

			//send �Լ�
			bool Send(BYTE* _buf, int _size, int _flag);
			bool WSA_Send(LPWSABUF _wsabuf, DWORD _buffercount, LPDWORD _sendbyte, DWORD _flag, LPWSAOVERLAPPED _overlap, LPWSAOVERLAPPED_COMPLETION_ROUTINE _routine);
			//recv �Լ�
			bool Recv(BYTE* _buf, int _size, int _flag);
			bool WSA_Recv(LPWSABUF _wsabuf, DWORD _buffercount, LPDWORD _recvbyte, LPDWORD _flag, LPWSAOVERLAPPED _overlap, LPWSAOVERLAPPED_COMPLETION_ROUTINE _routine);

		};


	}
}





#endif // !SOCK_H
