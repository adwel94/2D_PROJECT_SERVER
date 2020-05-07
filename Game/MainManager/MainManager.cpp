#include "MainManager.h"
#include "Sock/SocketManager.h"


using namespace Server::Socket;

GAME::cMainManager::cMainManager(int _count = -1) : Server::cIOCP_Manager<cGameClient*>(_count)
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
	//����
	cSock server;

	//���� �������� ����
	st_cSockManager::GetInstance()->TCP_Listen_Sock(&server);

	//accept ���� ����
	SOCKET client_socket = NULL;
	SOCKADDR_IN client_addr;

	//Ŭ���̾�Ʈ accept
	while (st_cSockManager::GetInstance()->Accept_Socket(&server, client_socket, client_addr))
	{
		//Ŭ���̾�Ʈ ����
		cGameClient* client = new cGameClient(client_socket, client_addr);
		
		//��Ʈ ���, �ʱ��۾�
		Accpet_Port(client_socket, client);
		AcceptProcess(client);
	}

}

//�ʱ� �۾�
void GAME::cMainManager::AcceptProcess(cGameClient* _key)
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

