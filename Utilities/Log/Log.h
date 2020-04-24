#pragma once
#ifndef _LOG_H_
#define _LOG_H_
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

namespace Utilities
{
	class cLog
	{
	public:

		enum
		{
			NAME_LEN = 32,//���� �ִ� �̸�
			MAX_LEN=128//�ִ�� ����Ҽ� �ִ� ���� ����
		};

	protected:
		FILE* mFp;//���� ������
		char mName[NAME_LEN] = "\0";//���� �̸�	
	public:

		cLog()
		{
			mFp = nullptr;
		}

		//�����̸�,���
		bool Connect(const char* _name, const char* _path = "\0");
		//���
		bool Record(const char* _msg);
		//����
		bool Close();


	};

}


#endif // !_LOG_H_
