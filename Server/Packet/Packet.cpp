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
	if (mRecvBuf.mSize == mRecvOverlap.trans)//현재 받은데이터와 총 받을 데이터가 같을시
	{
		return true;//데이터 수신 완료 리턴
	}
	return false;//데이터 수신 진행중 리턴
}

bool Server::cPacket::Is_Send_Success(DWORD _trans)
{
	mSendOverlap.trans += _trans;
	if (mSendBuf.front()->mSize == mSendOverlap.trans)//현재 받은데이터와 총 받을 데이터가 같을시
	{
		return true;//데이터 수신 완료 리턴
	}
	return false;//데이터 수신 진행중 리턴
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
	//문자길이 + 문자열
	int len = strlen(_string);
	Write<int>(&len, (int)sizeof(int));
	Write<const char>(_string, len);
}

void Server::cPacket::UnPack(bool& _bool)
{
	Read<bool>(&_bool, (int)sizeof(bool));
}

void Server::cPacket::UnPack(int& _int)
{
	Read<int>(&_int, (int)sizeof(int));
}

void Server::cPacket::UnPack(float& _float)
{
	Read<float>(&_float, (int)sizeof(float));
}

void Server::cPacket::UnPack(double& _double)
{
	Read<double>(&_double, (int)sizeof(double));
}

void Server::cPacket::UnPack(char* _string)
{
	int len = 0;
	Read<int>(&len, (int)sizeof(int));
	Read<char>(_string, len);
	_string[len] = '\0';
}
