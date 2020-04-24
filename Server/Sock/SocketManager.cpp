#include "SocketManager.h"

using namespace Server::Socket;




cSock* cSockManager::Create_Socket(IP_VER _af, SOCKTYPE _socktype, int _pro, int _port, const char* _addr)
{
	//소켓 생성
	SOCKET sock = socket(_af, _socktype, _pro);
	if (sock == INVALID_SOCKET)
	{
		WSA_Err_display((TCHAR*)"Socket()");
		return nullptr;
	}

	//주소 등록 
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = _af; //ip 버젼

	//주소를 따로 입력하지않으면 localhost
	if (strlen(_addr) == 0)
	{
		serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	}
	else
	{		
		inet_pton(_af, _addr, &serveraddr.sin_addr);
	}

	//포트 등록
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
	//소켓 bind()
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
	// listen 소켓으로 등록
	int retval = listen(_sock->GetSock(), SOMAXCONN);
	if (retval == SOCKET_ERROR)
	{
		WSA_Err_display((TCHAR*)"listen()");
		return false;
	}
	return true;
}

//accept 해서 받은 소켓을 반환
cSock* Server::Socket::cSockManager::Accept_Socket(cSock* _serversock)
{
	SOCKADDR_IN clientaddr;
	int addrlen = sizeof(clientaddr);
	ZeroMemory(&clientaddr, sizeof(clientaddr));
	SOCKET socket = accept(_serversock->GetSock(), (SOCKADDR*)&clientaddr, &addrlen);//클라접속 요청 받음 클라 소켓과 주소를 외부로 전달
	if (socket == INVALID_SOCKET)//소캣 생성 실패시
	{
		WSA_Err_display((TCHAR*)"accept()");// 에러메세지 출력
		return nullptr; //실패 반환
	}
	return new cSock(socket,clientaddr); //성공 반환
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
	int retval = setsockopt(_sock->GetSock(), SOL_SOCKET, // REUSEADDR 설정
		SO_REUSEADDR, (char*)&optval, sizeof(optval));
	if (retval == SOCKET_ERROR)
	{
		WSA_Err_display((TCHAR*)"reuse()");
		return false;
	}
	return true;
}

