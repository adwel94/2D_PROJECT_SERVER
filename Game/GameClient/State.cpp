#include "State.h"
#include "PROTOCOL.h"
#include "Login/LoginManager.h"


void GAME::STATE::cState::SendProc(cGameClient* _client)
{
	//ť�� send�� �ڷᰡ �����ִٸ� send
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
	//���������� Ȯ��
	PROTOCOL protocol;
	_client->RecvBuf().Read(protocol);
	
	//�������ݿ� ���� �۾� ����
	switch (protocol)
	{
	case PROTOCOL_TYPE::CLEINT_REQ_LOGIN:
		Login::st_cLoginManger::GetInstance()->Req_Login(_client);
		break;
	default:
		break;
	}
}
