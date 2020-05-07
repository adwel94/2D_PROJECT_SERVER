#include "GameClient.h"


GAME::cGameClient::cGameClient(SOCKET _sock, const SOCKADDR_IN& _addr) : cClient(_sock, _addr)
{


}

void GAME::cGameClient::Set_State(STATE::E _state)
{
	//mState = STATE::STATE_TYPE[(int)_state];
}

bool GAME::cGameClient::Recv_Process()
{
	//sizeof(int) == ��Ŷ�� ũ���� ��� 
	if (mRecvBuf.mSize == sizeof(int))
	{
		//ũ�⸸ŭ �ٽ� �д´�
		int size = 0;
		if(!mRecvBuf.Read(size)) return false;
		Set_Recv_Size(size);
		if(!WSA_Recv_Packet()) return false;
	}
	else
	{
		mState->RecvProc(this);
	}

	return true;
}

bool GAME::cGameClient::Send_Process()
{
	
	return false;
}
