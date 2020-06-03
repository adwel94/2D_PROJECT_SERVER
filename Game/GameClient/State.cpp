#include "State.h"
#include "PROTOCOL.h"
#include "Login/LoginManager.h"
#include "Charactor/CharactorManager.h"
#include "GameClient/GameClient.h"
#include "Map/MapManager.h"
#include "Party/PartyManager.h"
#include "Map/DungeonManager.h"
#include "PlayerManager/PlayerManager.h"

GAME::STATE::cState* GAME::STATE::cState::All_State[] = {};

void GAME::STATE::cState::Create()
{
	All_State[E::LOG_IN] = new cLogin_State();
	All_State[E::CHARACTOR] = new cCharactor_State();
	All_State[E::TOWN] = new cTown_State();
	All_State[E::DUNGEON] = new cDungeon_State();
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
	//큐에 send할 자료가 남아있다면 send
	if (_client->IsPacking())
	{
		_client->WSA_Send_Packet();
	}
}


//----------------------------------LOGIN--------------------------------//

void GAME::STATE::cLogin_State::RecvProc(cGameClient* _client)
{
	//프로토콜을 확인
	PROTOCOL::Protocol protocol;
	_client->RecvPacket().Read(protocol);
	//프로토콜에 따른 작업 실행
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
		printf_s("IP: %s Login State Error %d \n", _client->Get_IP(), protocol);
		break;
	}
}

//----------------------------------Charactor--------------------------------//

void GAME::STATE::cCharactor_State::RecvProc(cGameClient* _client)
{
	//프로토콜을 확인
	PROTOCOL::Protocol protocol;
	_client->RecvPacket().Read(protocol);
	//프로토콜에 따른 작업 실행
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
		printf_s("IP: %s Charactor State Error %d \n", _client->Get_IP(), protocol);
		break;
	}
}

void GAME::STATE::cTown_State::RecvProc(cGameClient* _client)
{
	//프로토콜을 확인
	PROTOCOL::Protocol protocol;
	_client->RecvPacket().Read(protocol);
	//프로토콜에 따른 작업 실행
	switch (protocol)
	{
	case PROTOCOL::CLIENT_SEND_CHAT:
		Map::st_cMapManager::GetInstance()->Send_Chat_Data(_client);
		break;
	case PROTOCOL::CLIENT_SEND_MOVE_DATA:
		st_cPlayerManager::GetInstance()->Send_Move_Data(_client);
		break;
	case PROTOCOL::CLIENT_REQ_MAP_ENTER:
		Map::st_cMapManager::GetInstance()->Req_Enter_Map(_client);
		break;
	case PROTOCOL::CLIENT_SEND_JUMP_DATA:
		st_cPlayerManager::GetInstance()->Send_Jump_Data(_client);
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
	case PROTOCOL::CLIENT_SEND_ATK_DATA:
		st_cPlayerManager::GetInstance()->Send_Atk_Data(_client);
		break;
	case PROTOCOL::CLIENT_SEND_DAMAGE_DATA:
		st_cPlayerManager::GetInstance()->Send_Damage_Data(_client);
		break;
	case PROTOCOL::CLIENT_REQ_ENTER_DUNGEON:
		Map::st_cDungeonManager::GetInstance()->Req_Enter_Dungeon(_client);
		break;
	default:
		printf_s("IP: %s Town State Error %d \n", _client->Get_IP(), protocol);
		break;
	}
}

void GAME::STATE::cDungeon_State::RecvProc(cGameClient* _client)
{
	//프로토콜을 확인
	PROTOCOL::Protocol protocol;
	_client->RecvPacket().Read(protocol);
	//프로토콜에 따른 작업 실행
	switch (protocol)
	{
	case PROTOCOL::CLIENT_SEND_CHAT:
		Map::st_cMapManager::GetInstance()->Send_Chat_Data(_client);
		break;
	case PROTOCOL::CLIENT_SEND_MOVE_DATA:
		st_cPlayerManager::GetInstance()->Send_Move_Data(_client);
		break;
	case PROTOCOL::CLIENT_SEND_JUMP_DATA:
		st_cPlayerManager::GetInstance()->Send_Jump_Data(_client);
		break;
	case PROTOCOL::CLIENT_REQ_DUNGEON_DATA:
		Map::st_cDungeonManager::GetInstance()->Req_Dungeon_Data(_client);
		break;
	case PROTOCOL::CLIENT_REQ_PARTY_INFO:
		Party::st_cPartyManager::GetInstance()->Req_Party_Info(_client);
		break;
	case PROTOCOL::CLIENT_SEND_ATK_DATA:
		st_cPlayerManager::GetInstance()->Send_Atk_Data(_client);
		break;
	case PROTOCOL::CLIENT_SEND_DAMAGE_DATA:
		st_cPlayerManager::GetInstance()->Send_Damage_Data(_client);
		break;
	case PROTOCOL::CLIENT_PLAYER_ATK_MONSTER:
		Map::st_cDungeonManager::GetInstance()->Player_Atk_Monster(_client);
		break;
	case PROTOCOL::CLIENT_SEND_DEATH_DATA:
		st_cPlayerManager::GetInstance()->Send_Death_Data(_client);
		break;
	case PROTOCOL::CLIENT_SEND_DEATH_END:
		st_cPlayerManager::GetInstance()->Send_Death_End(_client);
		break;
	default:
		printf_s("IP: %s Dungeon State Error %d \n", _client->Get_IP(), protocol);
		break;
	}
}
