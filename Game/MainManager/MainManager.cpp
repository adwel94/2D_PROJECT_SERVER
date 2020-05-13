#include "MainManager.h"
#include "Sock/SocketManager.h"


using namespace Server::Socket;

GAME::cMainManager::cMainManager() : Server::cIOCP_Manager<cGameClient*>()
{
	//���� �Ŵ��� ���
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
	//recv �� ���
	if (_key->Is_Recv_Overlap(_overlap))
	{
		//���� �޾Ҵ��� Ȯ��
		if (_key->Is_Recv_Success(_trans))
		{
			_key->Recv_Process();
		}
		else
		{
			//�ƴ� ��� ��� ����
			_key->WSA_Recv_Packet();
		}

	}
	//Send�� ���
	else if (_key->Is_Send_Overlap(_overlap))
	{
		//send �Ϸ� �� ���
		if (_key->Is_Send_Success(_trans))
		{
			_key->Send_Process();
		}
		else
		{
			//�ƴ� ��� ��� ����
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

