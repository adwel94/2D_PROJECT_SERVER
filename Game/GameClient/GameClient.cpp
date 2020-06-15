#include "GameClient.h"
#include "State.h"
#include "Login/LoginManager.h"
#include "Charactor/CharactorManager.h"

unsigned int GAME::cGameClient::ClientCount = 0;

GAME::cGameClient::cGameClient(SOCKET _sock, const SOCKADDR_IN& _addr) : cClient(_sock, _addr)
{
	if (ClientCount == 0)
	{
		GAME::STATE::cState::Create();
	}
	ClientCount++;

	mState = nullptr;
	mChar = nullptr;
}

GAME::cGameClient::~cGameClient()
{
	ClientCount--;
	if (ClientCount == 0)
	{
		//GAME::STATE::cState::Destroy();
	}

	if (mChar != nullptr)
	{
		Charactor::st_cCharactorManager::GetInstance()->Exit_Charactor(mChar);
		delete mChar;
	}

	Login::st_cLoginManger::GetInstance()->LogOut(this);

}


bool GAME::cGameClient::Recv_Process()
{
	//mSizeOn = ��Ŷ�� ũ�⸦ �޴����ϰ��
	if (mSizeOn == true)
	{
		//ũ�⸸ŭ �ٽ� �д´�
		int size = 0;
		if(!mRecvBuf.Read(size)) return false;
		Set_Recv_Size(size);
		mSizeOn = false;
		if(!WSA_Recv_Packet()) return false;

	}
	else
	{
		mState->RecvProc(this);
		Set_Recv_Size(sizeof(int));
		mSizeOn = true;
		if (!WSA_Recv_Packet()) return false;
	}

	return true;
}

bool GAME::cGameClient::Send_Process()
{
	Send_Packet_Pop();
	//ť�� send�� �����Ͱ� �����ִٸ� send
	if (IsPacking())
	{
		WSA_Send_Packet();
	}
	return false;
}
