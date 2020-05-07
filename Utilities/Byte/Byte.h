#pragma once
#ifndef _BYTE_H_
#define _BYTE_H_
#include <Windows.h>



namespace Utilities
{	//���� ����Ʈ ����
	struct sBuffer
	{
		BYTE* mByte;//�迭
		DWORD mSize;//�迭ũ��
		DWORD  mTrans;//������ ������

		//������
		sBuffer(DWORD _size = 0);
		//���� ������
		sBuffer(sBuffer& _buffer);
		//�Ҹ���
		~sBuffer();

		//���� �ʱ�ȭ
		void Reset_Buffer(int _size = 0);

		//�̾��
		template <class T>
		void Write(T* _data, int _datesize)
		{
			//���� ���۸� �ӽ�����
			BYTE* empt = mByte;
			int emptsize = mSize;

			//���ο� ũ�� ���� ����
			mByte = new BYTE[emptsize + _datesize];
			mSize = emptsize + _datesize;

			//���� ���� �޸𸮸� ����
			memcpy_s(mByte, mSize, empt, emptsize);
			//�������� �����͸�ŭ �����͸� �Ȱܼ� �ڿ� ����
			memcpy_s(mByte + emptsize, mSize - emptsize, _data, _datesize);

			delete empt;
		}

		//�б� (�պ���)
		template <class T>
		bool Read(OUT T* _data, int _datesize)
		{
			//������ �ʰ��� ����
			if (mSize < _datesize) return false;

			//������ ��ŭ �� �κ� ����
			memcpy_s(_data, _datesize, mByte, _datesize);

			//���� ���۸� �ӽ�����
			BYTE* empt = mByte;
			int emptsize = mSize;

			//���ο� ũ�� ���� ����
			mByte = new BYTE[emptsize - _datesize];
			mSize = emptsize - _datesize;

			//���� ���� �޸𸮸� ����(������ ���� ����)
			memcpy_s(mByte, mSize, empt + _datesize, emptsize - _datesize);

			delete empt;

			return true;
		}

		//�պκ� ������ Ȯ��(�պ���)
		template <class T>
		bool Front(OUT T* _data, int _datesize)
		{
			//������ �ʰ��� ����
			if (mSize < _datesize) return false;

			//������ ��ŭ �� �κ� ����
			memcpy_s(_data, _datesize, mByte, _datesize);
			return true;
		}

		//������ ����
		void Write(const bool& _bool);
		void Write(const char& _char);
		void Write(const int& _int);
		void Write(const float& _float);
		void Write(const double& _double);
		void Write(const char* _string);
		void Write(BYTE* _byte, int _size);
		void Write(const sBuffer& _buffer);


		//������ ����
		bool Read(OUT bool& _bool);
		bool Read(OUT int& _int);
		bool Read(OUT char& _char);
		bool Read(OUT float& _float);
		bool Read(OUT double& _double);
		bool Read(OUT char* _string);
		bool Read(OUT BYTE* _byte, int _size);
		bool Read(OUT sBuffer& _buffer);




	};
}


#endif // !_BYTE_H_
