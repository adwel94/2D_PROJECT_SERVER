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
	//ť�� send�� �ڷᰡ �����ִٸ� send
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
	//���������� Ȯ��
	PROTOCOL::P protocol;
	_client->RecvBuf().Read(protocol);
	
	//�������ݿ� ���� �۾� ����
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

