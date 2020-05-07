#include "SocketManager.h"

using namespace Server::Socket;



Server::Socket::cSockManager::cSockManager()
{
	mLog.Connect("SOCKET_MANAGER.TXT");
}

Server::Socket::cSockManager::~cSockManager()
{
	mLog.Close();
}

bool Server::Socket::cSockManager::TCP_Listen_Sock(OUT cSock* _sock)
{
	if (!Bind_Socket(_sock)) return false;
	if (!Listen_Socket(_sock)) return false;
	char addr[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &_sock->GetAddr().sin_addr, addr, sizeof(addr));
	printf_s("Create Listen Socket : IP : %s, PORT : %d \n", addr, ntohs(_sock->GetAddr().sin_port));
	return true;
}
 
bool Server::Socket::cSockManager::UDP_Listen_Sock(OUT cSock* _sock)
{
	if (!Bind_Socket(_sock)) return false;
	return true;
}

bool Server::Socket::cSockManager::TCP_CLIENT_Sock(OUT cSock* _sock)
{
	if (!Connect_Socket(_sock)) return false;
	return true;
}

bool Server::Socket::cSockManager::UDP_CLIENT_Sock(OUT cSock* _sock)
{
	return true;
}

bool Server::Socket::cSockManager::Bind_Socket(OUT cSock* _sock)
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

bool Server::Socket::cSockManager::Listen_Socket(OUT cSock* _sock)
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
bool Server::Socket::cSockManager::Accept_Socket(cSock* _server, OUT SOCKET& _socket, OUT SOCKADDR_IN& addr)
{
	int addrlen = sizeof(addr);
	ZeroMemory(&addr, sizeof(addr));
	_socket = accept(_server->GetSock(), (SOCKADDR*)&addr, &addrlen);//Ŭ������ ��û ���� Ŭ�� ���ϰ� �ּҸ� �ܺη� ����
	if (_socket == INVALID_SOCKET)//��Ĺ ���� ���н�
	{
		WSA_Err_display((TCHAR*)"accept()");// �����޼��� ���
		return false; //���� ��ȯ
	}
	return true;
}

bool Server::Socket::cSockManager::Connect_Socket(OUT cSock* _sock)
{
	int retval = connect(_sock->GetSock(), (SOCKADDR*)&_sock->GetAddr(), sizeof(SOCKADDR_IN));
	if (retval == SOCKET_ERROR)
	{
		WSA_Err_display((TCHAR*)"connect()");
		return false;
	}
	return true;
}

bool Server::Socket::cSockManager::Reuse_Socket(OUT cSock* _sock)
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

