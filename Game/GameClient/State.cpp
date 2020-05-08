#include "State.h"
#include "PROTOCOL.h"
#include "Login/LoginManager.h"
#include "GameClient/GameClient.h"

GAME::STATE::cState* GAME::STATE::cState::All_State[] = {};

void GAME::STATE::cState::Create()
{
	All_State[E::LOG_IN] = new cLogin_State();
	All_State[0];
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


//void GAME::STATE::cState::Create(cState** _state)
//{
//	
//}
//
//void GAME::STATE::cState::Destroy(cState** _state)
//{
//}

//----------------------------------LOGIN--------------------------------//

void GAME::STATE::cLogin_State::RecvProc(cGameClient* _client)
{
	//프로토콜을 확인
	PROTOCOL::P protocol;
	_client->RecvBuf().Read(protocol);
	
	//프로토콜에 따른 작업 실행
	switch (protocol)
	{
	case PROTOCOL::CLEINT_REQ_LOGIN:
		Login::st_cLoginManger::GetInstance()->Req_Login(_client);
		break;
	case PROTOCOL::CLIENT_REQ_JOIN:
		Login::st_cLoginManger::GetInstance()->Req_Join(_client);
		break;
	default:
		break;
	}
}

