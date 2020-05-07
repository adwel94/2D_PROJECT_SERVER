#include "MainManager.h"
#include "Sock/SocketManager.h"


using namespace Server::Socket;

GAME::cMainManager::cMainManager(int _count = -1) : Server::cIOCP_Manager<cGameClient*>(_count)
{
	//소켓 매니저 상용
	st_cSockManager::Create();
}

GAME::cMainManager::~cMainManager()
{
	st_cSockManager::Destroy();
}

void GAME::cMainManager::Run()
{
	//소켓
	cSock server;

	//서버 소켓으로 설정
	st_cSockManager::GetInstance()->TCP_Listen_Sock(&server);

	//accept 받을 변수
	SOCKET client_socket = NULL;
	SOCKADDR_IN client_addr;

	//클라이언트 accept
	while (st_cSockManager::GetInstance()->Accept_Socket(&server, client_socket, client_addr))
	{
		//클라이언트 생성
		cGameClient* client = new cGameClient(client_socket, client_addr);
		
		//포트 등록, 초기작업
		Accpet_Port(client_socket, client);
		AcceptProcess(client);
	}

}

//초기 작업
void GAME::cMainManager::AcceptProcess(cGameClient* _key)
{
	_key->Set_State(GAME::STATE::E::LOG_IN);
	_key->Set_Recv_Size(sizeof(int));
	_key->WSA_Recv_Packet();
}

void GAME::cMainManager::CompletionProcess(cGameClient* _key, LPOVERLAPPED _overlap, DWORD _trans)
{
	//recv 일 경우
	if (_key->Is_Recv_Overlap(_overlap))
	{
		//전부 받았는지 확인
		if (_key->Is_Recv_Success(_trans))
		{
			_key->Recv_Process();
		}
		else
		{
			//아닐 경우 계속 받음
			_key->WSA_Recv_Packet();
		}

	}
	//Send일 경우
	else if (_key->Is_Send_Overlap(_overlap))
	{
		//send 완료 일 경우
		if (_key->Is_Send_Success(_trans))
		{
			_key->Send_Process();
		}
		else
		{
			//아닐 경우 계속 받음
			_key->WSA_Send_Packet();
		}
	}
}

void GAME::cMainManager::ErrorProcess(cGameClient* _key, LPOVERLAPPED _overlap, DWORD _trans)
{
}

void GAME::cMainManager::DisconnectProcess(cGameClient* _key, LPOVERLAPPED _overlap, DWORD _trans)
{
}

