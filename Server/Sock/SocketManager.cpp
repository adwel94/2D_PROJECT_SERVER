#include "SocketManager.h"

using namespace Server::Socket;




cSock* cSockManager::Create_Socket(IP_VER _af, SOCKTYPE _socktype, int _pro, int _port, const char* _addr)
{
	//���� ����
	SOCKET sock = socket(_af, _socktype, _pro);
	if (sock == INVALID_SOCKET)
	{
		WSA_Err_display((TCHAR*)"Socket()");
		return nullptr;
	}

	//�ּ� ��� 
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = _af; //ip ����

	//�ּҸ� ���� �Է����������� localhost
	if (strlen(_addr) == 0)
	{
		serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	}
	else
	{		
		inet_pton(_af, _addr, &serveraddr.sin_addr);
	}

	//��Ʈ ���
	serveraddr.sin_port = htons(_port);

	return new cSock(sock, serveraddr);
}

bool Server::Socket::cSockManager::TCP_Listen_Sock(cSock* _sock)
{
	if (!Bind_Socket(_sock)) return false;
	if (!Listen_Socket(_sock)) return false;
	return true;
}
 
bool Server::Socket::cSockManager::UDP_Listen_Sock(cSock* _sock)
{
	if (!Bind_Socket(_sock)) return false;
	return true;
}

bool Server::Socket::cSockManager::TCP_CLIENT_Sock(cSock* _sock)
{
	if (!Connect_Socket(_sock)) return false;
	return true;
}

bool Server::Socket::cSockManager::UDP_CLIENT_Sock(cSock* _sock)
{
	return true;
}

bool Server::Socket::cSockManager::Bind_Socket(cSock* _sock)
{
	//���� bind()
	int retval = bind(_sock->GetSock(), (SOCKADDR*)&_sock->GetAddr(), sizeof(SOCKADDR_IN));
	if (retval == SOCKET_ERROR)
	{
		WSA_Err_display((TCHAR*)"Bind()");
		return false;
	}
	return true;
}

bool Server::Socket::cSockManager::Listen_Socket(cSock* _sock)
{
	// listen �������� ���
	int retval = listen(_sock->GetSock(), SOMAXCONN);
	if (retval == SOCKET_ERROR)
	{
		WSA_Err_display((TCHAR*)"listen()");
		return false;
	}
	return true;
}

//accept �ؼ� ���� ������ ��ȯ
cSock* Server::Socket::cSockManager::Accept_Socket(cSock* _serversock)
{
	SOCKADDR_IN clientaddr;
	int addrlen = sizeof(clientaddr);
	ZeroMemory(&clientaddr, sizeof(clientaddr));
	SOCKET socket = accept(_serversock->GetSock(), (SOCKADDR*)&clientaddr, &addrlen);//Ŭ������ ��û ���� Ŭ�� ���ϰ� �ּҸ� �ܺη� ����
	if (socket == INVALID_SOCKET)//��Ĺ ���� ���н�
	{
		WSA_Err_display((TCHAR*)"accept()");// �����޼��� ���
		return nullptr; //���� ��ȯ
	}
	return new cSock(socket,clientaddr); //���� ��ȯ
}

bool Server::Socket::cSockManager::Connect_Socket(cSock* _sock)
{
	int retval = connect(_sock->GetSock(), (SOCKADDR*)&_sock->GetAddr(), sizeof(SOCKADDR_IN));
	if (retval == SOCKET_ERROR)
	{
		WSA_Err_display((TCHAR*)"connect()");
		return false;
	}
	return true;
}

bool Server::Socket::cSockManager::Reuse_Socket(cSock* _sock)
{
	BOOL optval = TRUE;
	int retval = setsockopt(_sock->GetSock(), SOL_SOCKET, // REUSEADDR ����
		SO_REUSEADDR, (char*)&optval, sizeof(optval));
	if (retval == SOCKET_ERROR)
	{
		WSA_Err_display((TCHAR*)"reuse()");
		return false;
	}
	return true;
}

