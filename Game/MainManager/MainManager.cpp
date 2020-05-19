#include "MainManager.h"
#include "Sock/SocketManager.h"
#include "Login/LoginManager.h"
#include "Charactor/CharactorManager.h"

using namespace Server::Socket;

GAME::cMainManager::cMainManager() : Server::cIOCP_Manager<cGameClient*>()
{
	//家南 概聪历 惑侩
	st_cSockManager::Create();
	Login::st_cLoginManger::Create();
	Charactor::st_cCharactorManager::Create();
}

GAME::cMainManager::~cMainManager()
{
	for (std::list<cGameClient*>::iterator iter = mKey_List.mList.begin(); iter != mKey_List.mList.end(); iter++)
	{
		delete (*iter);
	}

	st_cSockManager::Destroy();
	Login::st_cLoginManger::Destroy();
	Charactor::st_cCharactorManager::Destroy();
}

void GAME::cMainManager::Run()
{

	Initialize_IOCP();
	Run_IOCP();

	int num;
	while (true)
	{
		scanf_s("%d", &num);

		if (num == 0)
		{
			End_IOCP();
			break;
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
	//recv 老 版快
	if (_key->Is_Recv_Overlap(_overlap))
	{
		_key->WSA_Recv_CallBack(_trans);
	}
	//Send老 版快
	else if (_key->Is_Send_Overlap(_overlap))
	{
		_key->WSA_Send_CallBack(_trans);
	}
}

void GAME::cMainManager::ErrorProcess(cGameClient* _key, LPOVERLAPPED _overlap, DWORD _trans)
{
	//save
}

void GAME::cMainManager::DisconnectProcess(cGameClient* _key, LPOVERLAPPED _overlap, DWORD _trans)
{
	char ip[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &(_key->GetAddr().sin_addr), ip, sizeof(ip));
	printf_s("IOCP Disconnect Client IP : %s PORT : %d \n", ip, _key->GetAddr().sin_port);
	mLog.Record("IOCP Disconnect Client IP : %s PORT : %d", ip, _key->GetAddr().sin_port);
	delete _key;
}


