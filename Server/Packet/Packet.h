#pragma once
#ifndef _PACKET_H_
#define _PACKET_H_
#include "Server.h"
#include "Protocol/Protocol.h"
#include"Byte/Byte.h"
#include "DS/LockQueue.h"


namespace Server
{
	
	//비동기 입출력 변수 모음
	struct WSAoverlapEX
	{
		OVERLAPPED overlapped;
		WSABUF wsabuf;

		WSAoverlapEX()
		{
			Reset();
		}

		void Reset()
		{
			ZeroMemory(&overlapped, sizeof(overlapped));
		}
	};

	//패킷 클래스 recv버퍼와 send버퍼
	class cPacket 
	{
	protected:
		Utilities::sBuffer mRecvBuf;//send버퍼 배열
		Utilities::DS::cLockQueue<Utilities::sBuffer*> mSendBuf;//send버퍼 배열
		WSAoverlapEX mRecvOverlap;
		WSAoverlapEX mSendOverlap;
	public:
		cPacket();
		virtual ~cPacket();

		Utilities::sBuffer& RecvBuf() { return mRecvBuf; }

		//패킹된 send 데이터가 있는지 확인
		bool IsPacking();

		//오버랩 준비
		void Init_Recv_Overlap();
		void Init_Send_Overlap();

		//오버랩 확인
		WSAoverlapEX& Recv_Overlap() { return mRecvOverlap; }
		WSAoverlapEX& Send_Overlap() { return mSendOverlap;}

		bool Is_Recv_Overlap(LPOVERLAPPED _overlap);
		bool Is_Send_Overlap(LPOVERLAPPED _overlap);

		//전송량 확인
		bool Is_Recv_Success(DWORD _trans);
		bool Is_Send_Success(DWORD _trans);

		//recv 사이즈 설정
		void Set_Recv_Size(int _size);
		int Get_Recv_Size();
		int Get_Recv_Trans();
		

		//send 큐에 버퍼 삽입
		void Send_Packet_Push(Utilities::sBuffer* _buffer);
	};

}





#endif // !PACKET_H
