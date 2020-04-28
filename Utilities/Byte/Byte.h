#pragma once
#ifndef _BYTE_H_
#define _BYTE_H_
#include <Windows.h>
#include <memory>


//�������� BYTE �迭
//template�� �̿��� ����Ʈ ������ ��ȯ ����


namespace Utilities
{
	//����Ʈ������ �迭 ������ ���� �Լ�
	template<typename T>
	struct ArrayDeleter
	{
		void operator() (T* p)
		{
			delete[] p;
		}
	};


	typedef std::shared_ptr<BYTE> sp_Byte;
#define CREATE_BUF(X) std::shared_ptr<BYTE>(new BYTE[X],ArrayDeleter<BYTE>())

	//���� ����Ʈ ����
	struct sBuffer
	{
		sp_Byte mByte;//�迭
		int mSize;//�迭ũ��

		sBuffer(int _size = 0)
		{
			mByte = CREATE_BUF(_size);
			mSize = _size;
		}

		sBuffer(sBuffer& _buffer)
		{
			mByte = CREATE_BUF(_buffer.mSize);
			mSize = _buffer.mSize;

			memcpy_s(mByte.get(), mSize, _buffer.mByte.get(), mSize);
			
		}

		~sBuffer()
		{

		}

		//���� �ʱ�ȭ
		void Reset_Buffer(int _size = 0)
		{
			mByte = CREATE_BUF(_size);
			mSize = _size;
		}

		//�����
		template <class T>
		void OverWrite(T* _data, int _datesize)
		{
			Reset_Buffer(_datesize);
			memcpy_s(mByte.get(), mSize, _data, _datesize);		
		}

		//�̾��
		template <class T>
		void Write(T* _data, int _datesize)
		{
			//���� ���۸� �ӽ�����
			sp_Byte empt = mByte;
			int emptsize = mSize;
			//���ο� ũ�� ���� ����
			Reset_Buffer(emptsize + _datesize);
			//���� ���� �޸𸮸� ����
			memcpy_s(mByte.get(), mSize, empt.get(), emptsize);
			//�������� �����͸�ŭ �����͸� �Ȱܼ� �ڿ� ����
			memcpy_s(mByte.get() + emptsize, mSize - emptsize, _data, _datesize);
		}

		//�б� (�պ���)
		template <class T>
		bool Read(OUT T* _data, int _datesize)
		{
			//������ �ʰ��� ����
			if (mSize < _datesize) return false;

			//������ ��ŭ �� �κ� ����
			memcpy_s(_data, _datesize, mByte.get(), _datesize);

			sp_Byte empt = mByte;
			int emptsize = mSize;

			//������ �ٿ��� �ʱ�ȭ
			Reset_Buffer(emptsize - _datesize);

			//���� ���� �޸𸮸� ����(������ ���� ����)
			memcpy_s(mByte.get(), mSize, empt.get() + _datesize, emptsize - _datesize);
			return true;
		}

	};
}


#endif // !_BYTE_H_
