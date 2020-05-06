#include "Packet.h"


Server::cPacket::cPacket()
{
	mRecvBuf.Reset_Buffer(0);
}

Server::cPacket::~cPacket()
{	
	while(mSendBuf.size() > 0)
	{
		Utilities::sBuffer* empt = mSendBuf.front();
		mSendBuf.pop();
		delete empt;
	}
}

bool Server::cPacket::IsPacking()
{
	return (mSendBuf.size() > 0);
}

void Server::cPacket::Init_Recv_Overlap()
{
	ZeroMemory(&mRecvOverlap.overlapped, sizeof(mRecvOverlap.overlapped));
	mRecvOverlap.wsabuf.buf = (char*)(mRecvBuf.mByte.get() + mRecvOverlap.trans);
	mRecvOverlap.wsabuf.len = mRecvBuf.mSize - mRecvOverlap.trans;
}

void Server::cPacket::Init_Send_Overlap()
{
	sBuffer* sendBuf = mSendBuf.front();
	ZeroMemory(&mSendOverlap.overlapped, sizeof(mSendOverlap.overlapped));
	mSendOverlap.wsabuf.buf = (char*)(sendBuf->mByte.get() + mSendOverlap.trans);
	mSendOverlap.wsabuf.len = sendBuf->mSize - mSendOverlap.trans;
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
	mRecvOverlap.trans += _trans;
	if (mRecvBuf.mSize == mRecvOverlap.trans)//���� ���������Ϳ� �� ���� �����Ͱ� ������
	{
		return true;//������ ���� �Ϸ� ����
	}
	return false;//������ ���� ������ ����
}

bool Server::cPacket::Is_Send_Success(DWORD _trans)
{
	mSendOverlap.trans += _trans;
	if (mSendBuf.front()->mSize == mSendOverlap.trans)//���� ���������Ϳ� �� ���� �����Ͱ� ������
	{
		return true;//������ ���� �Ϸ� ����
	}
	return false;//������ ���� ������ ����
}

void Server::cPacket::Set_Recv_Size(int _size)
{
	mRecvBuf.Reset_Buffer(_size);
}

void Server::cPacket::Pack(const bool& _bool)
{
	Write<const bool>(&_bool, (int)sizeof(bool));
}

void Server::cPacket::Pack(const int& _int)
{
	Write<const int>(&_int, (int)sizeof(int));
}

void Server::cPacket::Pack(const float& _float)
{
	Write<const float>(&_float, (int)sizeof(float));
}

void Server::cPacket::Pack(const double& _double)
{
	Write<const double>(&_double, (int)sizeof(double));
}

void Server::cPacket::Pack(const char* _string)
{
	//���ڱ��� + ���ڿ�
	int len = 0;
	len = strlen(_string) + 1;
	Write<int>(&len, (int)sizeof(int));
	Write<const char>(_string, len);
}

void Server::cPacket::Pack(const sBuffer& _buffer)
{
	int size = _buffer.mSize;
	Write<int>(&size, (int)sizeof(int));
	Write<const BYTE>(_buffer.mByte.get(), _buffer.mSize);
}

void Server::cPacket::UnPack(OUT bool& _bool)
{
	Read<bool>(&_bool, (int)sizeof(bool));
}

void Server::cPacket::UnPack(OUT int& _int)
{
	Read<int>(&_int, (int)sizeof(int));
}

void Server::cPacket::UnPack(OUT float& _float)
{
	Read<float>(&_float, (int)sizeof(float));
}

void Server::cPacket::UnPack(OUT double& _double)
{
	Read<double>(&_double, (int)sizeof(double));
}

void Server::cPacket::UnPack(OUT char* _string)
{
	int len = 0;
	Read<int>(&len, (int)sizeof(int));
	Read<char>(_string, len);
}

void Server::cPacket::UnPack(OUT sBuffer& _buffer)
{
	int size = 0;
	Read<int>(&size, (int)sizeof(int));
	_buffer.Reset_Buffer(size);
	Read<BYTE>(_buffer.mByte.get(), size);
}
