#pragma once
#ifndef _PACKET_H_
#define _PACKET_H_
#include"Byte/Byte.h"
#include <queue>
#include "Server.h"


namespace Server
{

	//�񵿱� ����� ���� ����
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

	//��Ŷ Ŭ����
	class cPacket : public Utilities::sBuffer
	{
	protected:
		Utilities::sBuffer mRecvBuf;//send���� �迭
		std::queue<Utilities::sBuffer*> mSendBuf;//send���� �迭
		WSAoverlapEX mRecvOverlap;
		WSAoverlapEX mSendOverlap;
	public:
		cPacket();
		virtual ~cPacket();

		//��ŷ�� �����Ͱ� �ִ��� Ȯ��
		bool IsPacking();

		//������ �غ�
		void Init_Recv_Overlap();
		void Init_Send_Overlap();

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

		//��Ŷ ����
		void Pack(const bool& _bool);
		void Pack(const int& _int);
		void Pack(const float& _float);
		void Pack(const double& _double);
		void Pack(const char* _string);

		//��Ŷ ����
		void UnPack(bool& _bool);
		void UnPack(int& _int);
		void UnPack(float& _float);
		void UnPack(double& _double);
		void UnPack(char* _string);

	};

}





#endif // !PACKET_H
