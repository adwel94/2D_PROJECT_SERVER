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
	//sizeof(int) == 패킷의 크기일 경우 
	if (mRecvBuf.mSize == sizeof(int))
	{
		//크기만큼 다시 읽는다
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
