#include "State.h"
#include "PROTOCOL.h"
#include "Login/LoginManager.h"
#include "Charactor/CharactorManager.h"
#include "GameClient/GameClient.h"

GAME::STATE::cState* GAME::STATE::cState::All_State[] = {};

void GAME::STATE::cState::Create()
{
	All_State[E::LOG_IN] = new cLogin_State();
	All_State[E::CHARACTOR] = new cCharactor_State();
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
		Charactor::st_cCharactorManager::GetInstance()->Req_Select_Charactor(_client);
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
}
