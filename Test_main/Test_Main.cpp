#include "ServerModel/IOCP_Manager.h"
#include "Sock/SocketManager.h"

int main()
{
	Server::Socket::Sock_Start();
	Server::Socket::cSock server(Server::Socket::IPv4, Server::Socket::TCP);
	Server::Socket::st_cSockManager::GetInstance()->TCP_Listen_Sock(server);
	Server::Socket::Sock_Start();
	Server::cIOCP_Manager sp(4);
	sp.Initialize_IOCP();


}