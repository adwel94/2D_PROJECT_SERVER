#include "Client.h"

Server::cClient::cClient(SOCKET _sock, const SOCKADDR_IN& _addr) : cSock(_sock, _addr), cPacket()
{
	mSendEvt = CreateEvent(NULL, TRUE, TRUE, NULL);
}

Server::cClient::~cClient()
{
	CloseHandle(mSendEvt);
}

void Server::cClient::SendStart()
{
	ResetEvent(mSendEvt);
}

void Server::cClient::SendEnd()
{
	SetEvent(mSendEvt);
}

void Server::cClient::WaitSendEnd()
{
	WaitForSingleObject(mSendEvt, INFINITE);
}

bool Server::cClient::Send_ing()
{
	if (WaitForSingleObject(mSendEvt, 0) == WAIT_TIMEOUT)
	{
		//non signal
		return true;
	}
	return false;
}

bool Server::cClient::Send_Packet()
{
	//pop
	Utilities::sBuffer* sendbuf = mSendBuf.LockPop();
	//send
	bool result = Send(sendbuf->mByte, sendbuf->mSize, 0);
	//delete
	delete sendbuf;
	//return
	return result;
}

bool Server::cClient::WSA_Send_Packet()
{
	if (Send_ing()) return true;

	SendStart();

	//�̾ �����ϱ� 
	Init_Send_Overlap((char*)(mSendBuf.LockFront()->mByte + mSendBuf.LockFront()->mTrans), (mSendBuf.LockFront()->mSize - mSendBuf.LockFront()->mTrans));

	//send
	DWORD sendbytes, flags = 0;

	return WSA_Send(&mSendOverlap.wsabuf, 1, &sendbytes, flags, &mSendOverlap.overlapped, NULL);
}

void Server::cClient::WSA_Send_CallBack(DWORD _trans)
{
	SendEnd();
	//send �Ϸ� �� ���
	if (Is_Send_Success(_trans))
	{

		Send_Process();
	}
	else
	{
		//�ƴ� ��� ��� ����
		WSA_Send_Packet();
	}
}

bool Server::cClient::Recv_Packet()
{
	mRecvBuf.Reset_Buffer(sizeof(int));
	bool retval = Recv(mRecvBuf.mByte, mRecvBuf.mSize, 0);//��Ŷ�� ũ�⸦ ����
	if (retval == false)
	{
		return false;
	}

	int size;
	mRecvBuf.Read(size);

	mRecvBuf.Reset_Buffer(size);
	retval = Recv(mRecvBuf.mByte, mRecvBuf.mSize, 0); //��Ŷ�� ũ�⸸ŭ ����
	if (retval == false)
	{
		return false;
	}
	return true;
}

bool Server::cClient::WSA_Recv_Packet()
{

	Init_Recv_Overlap((char*)(mRecvBuf.mByte + mRecvBuf.mTrans),(mRecvBuf.mSize - mRecvBuf.mTrans));
	DWORD recvbytes, flags = 0;
	return WSA_Recv(&mRecvOverlap.wsabuf, 1, &recvbytes, &flags, &mRecvOverlap.overlapped, NULL);
}

void Server::cClient::WSA_Recv_CallBack(DWORD _trans)
{
	//���� �޾Ҵ��� Ȯ��
	if (Is_Recv_Success(_trans))
	{
		Recv_Process();
	}
	else
	{
		//�ƴ� ��� ��� ����
		WSA_Recv_Packet();
	}
}
