#include "MainManager.h"

void GAME::cMainManager::AcceptProcess(Server::cClient* _key)
{
	_key->Set_Recv_Size(PROTOCOL_SIZE);
	_key->WSA_Recv_Packet();
}

void GAME::cMainManager::CompletionProcess(Server::cClient* _key, LPOVERLAPPED _overlap, DWORD _trans)
{
	if (_key->Is_Recv_Overlap(_overlap))
	{

	}
}

void GAME::cMainManager::ErrorProcess(Server::cClient* _key, LPOVERLAPPED _overlap, DWORD _trans)
{
}

void GAME::cMainManager::DisconnectProcess(Server::cClient* _key, LPOVERLAPPED _overlap, DWORD _trans)
{
}
