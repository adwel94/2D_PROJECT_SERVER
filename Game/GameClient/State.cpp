#include "State.h"
#include "PROTOCOL.h"
#include "Login/LoginManager.h"


void GAME::STATE::cState::SendProc(cGameClient* _client)
{
	//큐에 send할 자료가 남아있다면 send
	if (_client->IsPacking())
	{
		_client->WSA_Send_Packet();
	}
}

void GAME::STATE::cState::Create()
{
	
}

void GAME::STATE::cState::Destroy()
{
}

//----------------------------------LOGIN--------------------------------//

void GAME::STATE::cLogin_State::RecvProc(cGameClient* _client)
{
	//프로토콜을 확인
	PROTOCOL protocol;
	_client->RecvBuf().Read(protocol);
	
	//프로토콜에 따른 작업 실행
	switch (protocol)
	{
	case PROTOCOL_TYPE::CLEINT_REQ_LOGIN:
		Login::st_cLoginManger::GetInstance()->Req_Login(_client);
		break;
	default:
		break;
	}
}
