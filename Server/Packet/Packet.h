#pragma once
#ifndef _PACKET_H_
#define _PACKET_H_
#include "Server.h"
#include "Protocol/Protocol.h"
#include"Byte/Byte.h"
#include "DS/LockQueue.h"


namespace Server
{
	
	//�񵿱� ����� ���� ����
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

	//��Ŷ Ŭ���� recv���ۿ� send����
	class cPacket 
	{
	protected:
		bool mSizeOn;
		Utilities::sBuffer mRecvBuf;//send���� �迭	
		Utilities::DS::cLockQueue<Utilities::sBuffer*> mSendBuf;//send���� �迭
		WSAoverlapEX mRecvOverlap;
		WSAoverlapEX mSendOverlap;
	public:
		cPacket();
		virtual ~cPacket();

		Utilities::sBuffer& RecvPacket() { return mRecvBuf; }

		//��ŷ�� send �����Ͱ� �ִ��� Ȯ��

		bool IsPacking();

		//������ �غ�
		void Init_Recv_Overlap(CHAR* _byte, ULONG _len);
		void Init_Send_Overlap(CHAR* _byte, ULONG _len);

		//������ Ȯ��
		WSAoverlapEX& Recv_Overlap() { return mRecvOverlap; }
		WSAoverlapEX& Send_Overlap() { return mSendOverlap;}

		bool Is_Recv_Overlap(LPOVERLAPPED _overlap);
		bool Is_Send_Overlap(LPOVERLAPPED _overlap);

		//���۷� Ȯ��
		bool Is_Recv_Success(DWORD _trans);
		bool Is_Send_Success(DWORD _trans);

		//recv ������ ����
		void Set_Recv_Size(int _size);
		int Get_Recv_Size();
		int Get_Recv_Trans();
		

		//send ť�� ���� ����,����
		void Send_Packet_Push(Utilities::sBuffer& _buffer);
		void Send_Packet_Pop();
	};

}





#endif // !PACKET_H
