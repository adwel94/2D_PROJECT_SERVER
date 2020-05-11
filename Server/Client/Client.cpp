#include "Client.h"

bool Server::cClient::Send_Packet()
{
	//lock
	Utilities::Lock::cAutoUnLock a(&mSendLock);
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
	Utilities::Lock::cAutoUnLock a(&mSendLock);

	//이어서 전송하기 
	char* buf = (char*)(mSendBuf.LockFront()->mByte + mSendBuf.LockFront()->mTrans);
	int size = (mSendBuf.LockFront()->mSize - mSendBuf.LockFront()->mTrans);

	//overap
	Init_Send_Overlap(buf, size);

	//send
	DWORD sendbytes, flags = 0;
	return WSA_Send(&mSendOverlap.wsabuf, 1, &sendbytes, flags, &mSendOverlap.overlapped, NULL);
}

bool Server::cClient::Recv_Packet()
{
	mRecvBuf.Reset_Buffer(sizeof(int));
	bool retval = Recv(mRecvBuf.mByte, mRecvBuf.mSize, 0);//패킷의 크기를 받음
	if (retval == false)
	{
		return false;
	}

	int size;
	mRecvBuf.Read(size);

	mRecvBuf.Reset_Buffer(size);
	retval = Recv(mRecvBuf.mByte, mRecvBuf.mSize, 0); //패킷의 크기만큼 받음
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
