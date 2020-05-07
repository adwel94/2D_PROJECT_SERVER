#include "Packet.h"


Server::cPacket::cPacket()
{
	mRecvBuf.Reset_Buffer(0);
}

Server::cPacket::~cPacket()
{	
	while(mSendBuf.LockSize() > 0)
	{
		Utilities::sBuffer* empt = mSendBuf.LockFront();
		mSendBuf.LockPop();
		delete empt;
	}
}

bool Server::cPacket::IsPacking()
{
	return (mSendBuf.LockSize() > 0);
}

void Server::cPacket::Init_Recv_Overlap()
{
	ZeroMemory(&mRecvOverlap.overlapped, sizeof(mRecvOverlap.overlapped));
	mRecvOverlap.wsabuf.buf = (char*)(mRecvBuf.mByte + mRecvBuf.mTrans);
	mRecvOverlap.wsabuf.len = mRecvBuf.mSize - mRecvBuf.mTrans;
}

void Server::cPacket::Init_Send_Overlap()
{
	Utilities::sBuffer* sendBuf = mSendBuf.LockFront();
	ZeroMemory(&mSendOverlap.overlapped, sizeof(mSendOverlap.overlapped));
	mSendOverlap.wsabuf.buf = (char*)(sendBuf->mByte + sendBuf->mTrans);
	mSendOverlap.wsabuf.len = sendBuf->mSize - sendBuf->mTrans;
}

bool Server::cPacket::Is_Recv_Overlap(LPOVERLAPPED _overlap)
{
	return (&(mRecvOverlap.overlapped) == _overlap);
}

bool Server::cPacket::Is_Send_Overlap(LPOVERLAPPED _overlap)
{
	return  (&(mSendOverlap.overlapped) == _overlap);
}

bool Server::cPacket::Is_Recv_Success(DWORD _trans)
{
	mRecvBuf.mTrans += _trans;
	if (mRecvBuf.mSize == mRecvBuf.mTrans)//���� ���������Ϳ� �� ���� �����Ͱ� ������
	{
		return true;//������ ���� �Ϸ� ����
	}
	return false;//������ ���� ������ ����
}

bool Server::cPacket::Is_Send_Success(DWORD _trans)
{
	mSendBuf.LockFront()->mTrans += _trans;
	if (mSendBuf.LockFront()->mSize == mSendBuf.LockFront()->mTrans)//���� �۽ŵ����Ϳ� �� �������� ũ�Ⱑ ������
	{
		//ť���� �����͸� ��
		Utilities::sBuffer* empt = mSendBuf.LockFront();
		mSendBuf.LockPop();
		return true;//������ �۽� �Ϸ� ����
	}
	return false;//������ �۽� ������ ����
}

void Server::cPacket::Set_Recv_Size(int _size)
{
	mRecvBuf.Reset_Buffer(_size);
}

int Server::cPacket::Get_Recv_Size()
{
	return mRecvBuf.mSize;
}

int Server::cPacket::Get_Recv_Trans()
{
	return mRecvBuf.mTrans;
}

void Server::cPacket::Send_Packet_Push(Utilities::sBuffer* _buffer)
{
	mSendBuf.LockPush(_buffer);
}
