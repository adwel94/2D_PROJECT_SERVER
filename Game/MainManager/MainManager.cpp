#include "MainManager.h"
#include "Sock/SocketManager.h"


using namespace Server::Socket;

GAME::cMainManager::cMainManager() : Server::cIOCP_Manager<cGameClient*>()
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

	Initialize_IOCP();

	int num;
	while (true)
	{
		scanf_s("%d", &num);

		if (num == 1)
		{
			Run_IOCP();
		}

		if (num == 2)
		{
			End_IOCP();
		}
	}

}

GAME::cGameClient* GAME::cMainManager::CreateKey(SOCKET _sock, const SOCKADDR_IN& _addr)
{
	return new cGameClient(_sock,_addr);
}

void GAME::cMainManager::AcceptProcess(cGameClient* _key, SOCKET _sock, const SOCKADDR_IN& _addr)
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

