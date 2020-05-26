#include "State.h"
#include "PROTOCOL.h"
#include "Login/LoginManager.h"
#include "Charactor/CharactorManager.h"
#include "GameClient/GameClient.h"
#include "Map/MapManager.h"
#include "Party/PartyManager.h"

GAME::STATE::cState* GAME::STATE::cState::All_State[] = {};

void GAME::STATE::cState::Create()
{
	All_State[E::LOG_IN] = new cLogin_State();
	All_State[E::CHARACTOR] = new cCharactor_State();
	All_State[E::TOWN] = new cTown_State();
}

void GAME::STATE::cState::Destroy()
{
	for (int i = 0; i < E::STATE_COUNT; i++)
	{
		delete All_State[i];
	}
}

void GAME::STATE::cState::SendProc(cGameClient* _client)
{
	//ť�� send�� �ڷᰡ �����ִٸ� send
	if (_client->IsPacking())
	{
		_client->WSA_Send_Packet();
	}
}


//----------------------------------LOGIN--------------------------------//

void GAME::STATE::cLogin_State::RecvProc(cGameClient* _client)
{
	//���������� Ȯ��
	PROTOCOL::Protocol protocol;
	_client->RecvPacket().Read(protocol);
	//�������ݿ� ���� �۾� ����
	switch (protocol)
	{
	case PROTOCOL::CLEINT_REQ_LOGIN:
		if (Login::st_cLoginManger::GetInstance()->Req_Login(_client))
		{
			_client->Set_State(E::CHARACTOR);
		}
		break;
	case PROTOCOL::CLIENT_REQ_JOIN:
		Login::st_cLoginManger::GetInstance()->Req_Join(_client);
		break;
	case PROTOCOL::CLIENT_REQ_LOGOUT:
		Login::st_cLoginManger::GetInstance()->Req_LogOut(_client);
		break;
	default:
		break;
	}
}

//----------------------------------Charactor--------------------------------//

void GAME::STATE::cCharactor_State::RecvProc(cGameClient* _client)
{
	//���������� Ȯ��
	PROTOCOL::Protocol protocol;
	_client->RecvPacket().Read(protocol);
	//�������ݿ� ���� �۾� ����
	switch (protocol)
	{
	case PROTOCOL::CLIENT_REQ_CHAR_INFO:
		Charactor::st_cCharactorManager::GetInstance()->Req_Charactor_Info(_client);
		break;
	case PROTOCOL::CLIENT_REQ_CREATE_CHAR:
		Charactor::st_cCharactorManager::GetInstance()->Req_Create_Charactor(_client);
		break;
	case PROTOCOL::CLIENT_REQ_SELECT_CHAR:
		if (Charactor::st_cCharactorManager::GetInstance()->Req_Select_Charactor(_client))
		{
			_client->Set_State(E::TOWN);
		}
		break;
	case PROTOCOL::CLIENT_REQ_DELETE_CHAR:
		Charactor::st_cCharactorManager::GetInstance()->Req_Delete_Charactor(_client);
		break;
	default:
		break;
	}
}

void GAME::STATE::cTown_State::RecvProc(cGameClient* _client)
{
	//���������� Ȯ��
	PROTOCOL::Protocol protocol;
	_client->RecvPacket().Read(protocol);
	//�������ݿ� ���� �۾� ����
	switch (protocol)
	{
	case PROTOCOL::CLIENT_SEND_CHAT:
		Map::st_MapManager::GetInstance()->Send_Chat_Data(_client);
		break;
	case PROTOCOL::CLIENT_SEND_MOVE_DATA:
		Map::st_MapManager::GetInstance()->Send_Move_Data(_client);
		break;
	case PROTOCOL::CLIENT_REQ_MAP_ENTER:
		Map::st_MapManager::GetInstance()->Req_Enter_Map(_client);
		break;
	case PROTOCOL::CLIENT_SEND_JUMP_DATA:
		Map::st_MapManager::GetInstance()->Send_Jump_Data(_client);
		break;
	case PROTOCOL::CLIENT_REQ_PARTY_INVITE:
		Party::st_cPartyManager::GetInstance()->Req_Party_Invite(_client);
		break;
	case PROTOCOL::CLIENT_REQ_CREATE_PARTY:
		Party::st_cPartyManager::GetInstance()->Req_Create_Party(_client);
		break;
	case PROTOCOL::CLIENT_REQ_PARTY_INFO:
		Party::st_cPartyManager::GetInstance()->Req_Party_Info(_client);
		break;
	case PROTOCOL::CLIENT_PARTY_INVITE_MSG:
		Party::st_cPartyManager::GetInstance()->Party_Invite_Msg(_client);
		break;
	default:
		break;
	}
}
