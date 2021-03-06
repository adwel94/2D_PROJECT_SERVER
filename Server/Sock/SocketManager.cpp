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
	printf_s("Create Listen Socket : IP : %s, PORT : %d \n", _sock->Get_IP(), ntohs(_sock->GetAddr().sin_port));
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
	//소켓 bind()
	int retval = bind(_sock->GetSock(), (SOCKADDR*)&_sock->GetAddr(), sizeof(SOCKADDR_IN));
	if (retval == SOCKET_ERROR)
	{
		WSA_Err_display("Bind()");
		return false;
	}

	mLog.Record("Socket Bind : IP : %s, PORT : %d", _sock->Get_IP(), ntohs(_sock->GetAddr().sin_port));
	return true;
}

bool Server::Socket::cSockManager::Listen_Socket(OUT cSock* _sock)
{
	// listen 소켓으로 등록
	int retval = listen(_sock->GetSock(), SOMAXCONN);
	if (retval == SOCKET_ERROR)
	{
		WSA_Err_display("listen()");
		return false;
	}

	mLog.Record("Socket Listen : IP : %s, PORT : %d", _sock->Get_IP(), ntohs(_sock->GetAddr().sin_port));
	return true;
}

//accept 해서 받은 소켓을 반환
bool Server::Socket::cSockManager::Accept_Socket(cSock* _server, OUT SOCKET& _socket, OUT SOCKADDR_IN& _addr)
{
	int addrlen = sizeof(_addr);
	ZeroMemory(&_addr, sizeof(_addr));
	_socket = accept(_server->GetSock(), (SOCKADDR*)&_addr, &addrlen);//클라접속 요청 받음 클라 소켓과 주소를 외부로 전달
	if (_socket == INVALID_SOCKET)//소캣 생성 실패시
	{
		WSA_Err_display("accept()");// 에러메세지 출력
		return false; //실패 반환
	}

	char addr[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &_addr.sin_addr, addr, sizeof(addr));

	printf_s("Socket Accept : IP : %s, PORT : %d \n", addr, ntohs(_addr.sin_port));
	mLog.Record("Socket Accept : IP : %s, PORT : %d", addr, ntohs(_addr.sin_port));

	return true;
}

bool Server::Socket::cSockManager::Connect_Socket(OUT cSock* _sock)
{
	int retval = connect(_sock->GetSock(), (SOCKADDR*)&_sock->GetAddr(), sizeof(SOCKADDR_IN));
	if (retval == SOCKET_ERROR)
	{
		WSA_Err_display("connect()");
		return false;
	}
	return true;
}

bool Server::Socket::cSockManager::Reuse_Socket(OUT cSock* _sock)
{
	BOOL optval = TRUE;
	int retval = setsockopt(_sock->GetSock(), SOL_SOCKET, // REUSEADDR 설정
		SO_REUSEADDR, (char*)&optval, sizeof(optval));
	if (retval == SOCKET_ERROR)
	{
		WSA_Err_display("reuse()");
		return false;
	}
	return true;
}

