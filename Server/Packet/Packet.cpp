#include "Packet.h"


Server::cPacket::cPacket()
{

}

Server::cPacket::~cPacket()
{	

}

bool Server::cPacket::IsPacking()
{
	return (mSendBuf.LockSize() > 0);
}

void Server::cPacket::Init_Recv_Overlap(CHAR* _byte, ULONG _len)
{
	ZeroMemory(&mRecvOverlap.overlapped, sizeof(mRecvOverlap.overlapped));
	mRecvOverlap.wsabuf.buf = _byte;
	mRecvOverlap.wsabuf.len = _len;
}

void Server::cPacket::Init_Send_Overlap(CHAR* _byte, ULONG _len)
{
	ZeroMemory(&mSendOverlap.overlapped, sizeof(mSendOverlap.overlapped));
	mSendOverlap.wsabuf.buf = _byte;
	mSendOverlap.wsabuf.len = _len;
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

void Server::cPacket::Send_Packet_Push(Utilities::sBuffer& _buffer)
{
	Utilities::sBuffer* sendbuffer = new Utilities::sBuffer();
	sendbuffer->Write(_buffer.mByte, _buffer.mSize);
	mSendBuf.LockPush(sendbuffer);
}

void Server::cPacket::Send_Packet_Pop()
{
	Utilities::sBuffer* empt = mSendBuf.LockPop();
	delete empt;
}
