#pragma once
#ifndef _PACKET_H_
#define _PACKET_H_
#include"Byte/Byte.h"
#include <queue>
#include "Server.h"
#include "Protocol/Protocol.h"


namespace Server
{
	
	//비동기 입출력 변수 모음
	struct WSAoverlapEX
	{
		OVERLAPPED overlapped;
		WSABUF wsabuf;
		DWORD trans;

		WSAoverlapEX()
		{
			Reset();
		}

		void Reset()
		{
			ZeroMemory(&overlapped, sizeof(overlapped));
			trans = 0;
		}
	};

	//패킷 클래스
	class cPacket : public Utilities::sBuffer
	{
	protected:
		Utilities::sBuffer mRecvBuf;//send버퍼 배열
		std::queue<Utilities::sBuffer*> mSendBuf;//send버퍼 배열
		WSAoverlapEX mRecvOverlap;
		WSAoverlapEX mSendOverlap;
	public:
		cPacket();
		virtual ~cPacket();

		//패킹된 데이터가 있는지 확인
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

		//패킷 결합
		void Pack(const bool& _bool);
		void Pack(const int& _int);
		void Pack(const float& _float);
		void Pack(const double& _double);
		void Pack(const char* _string);
		void Pack(const sBuffer& _buffer);


		//패킷 분해
		void UnPack(OUT bool& _bool);
		void UnPack(OUT int& _int);
		void UnPack(OUT float& _float);
		void UnPack(OUT double& _double);
		void UnPack(OUT char* _string);
		void UnPack(OUT sBuffer& _buffer);

	};

}





#endif // !PACKET_H
