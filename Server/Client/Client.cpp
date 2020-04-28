#include "Client.h"

bool Server::cClient::Send_Packet()
{	
	sBuffer* sendBuf = mSendBuf.front();
	mSendBuf.pop();
	return Send(sendBuf->mByte.get(), sendBuf->mSize, 0);
}

bool Server::cClient::WSA_Send_Packet()
{
	Init_Send_Overlap();
	DWORD sendbytes, flags = 0;
	bool retval = WSA_Send(&mSendOverlap.wsabuf, 1, &sendbytes, flags, &mSendOverlap.overlapped, NULL);
	return retval;
}

bool Server::cClient::Recv_Packet()
{
	mRecvBuf.Reset_Buffer(sizeof(int));
	bool retval = Recv(mRecvBuf.mByte.get(), mRecvBuf.mSize, 0);//패킷의 크기를 받음
	if (retval == false)
	{
		return false;
	}

	int size;
	UnPack(size);

	mRecvBuf.Reset_Buffer(size);
	retval = Recv(mRecvBuf.mByte.get(), mRecvBuf.mSize, 0); //패킷의 크기만큼 받음
	if (retval == false)
	{
		return false;
	}
	return true;
}

bool Server::cClient::WSA_Recv_Packet()
{
	Init_Recv_Overlap();
	DWORD recvbytes, flags = 0;
	bool retval = WSA_Recv(&mRecvOverlap.wsabuf, 1, &recvbytes, &flags, &mRecvOverlap.overlapped, NULL);
	return retval;
}
