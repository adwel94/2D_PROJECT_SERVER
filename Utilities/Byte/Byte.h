#pragma once
#ifndef _BYTE_H_
#define _BYTE_H_
#include <Windows.h>
#include <memory>


//가변길이 BYTE 배열


namespace Utilities
{
	//스마트포인터 배열 삭제를 위한 함수
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

	//가변 바이트 버퍼
	struct sBuffer
	{
		sp_Byte mByte;//배열
		int mSize;//배열크기
		int mTrans;//전송량

		sBuffer(int _size = 0)
		{
			mByte = CREATE_BUF(_size);
			mSize = _size;
			mTrans = 0;		
		}

		sBuffer(sBuffer& _buffer)
		{
			mByte = CREATE_BUF(_buffer.mSize);
			mSize = _buffer.mSize;
			mTrans = _buffer.mTrans;

			memcpy_s(mByte.get(), mSize, _buffer.mByte.get(), mSize);
			
		}

		~sBuffer()
		{

		}

		//버퍼 초기화
		void Reset(int _size = 0)
		{
			mByte = CREATE_BUF(_size);
			mSize = _size;
			mTrans = 0;
		}

		//앞부터 덮어쓰기
		template <class T>
		void OverWrite(T* _data, int _datesize)
		{
			mByte = Reset(_datesize);
			memcpy_s(mByte.get(), mSize, _data, _datesize);		
		}

		//이어쓰기
		template <class T>
		void Write(T* _data, int _datesize)
		{
			//기존 버퍼를 임시저장
			sp_Byte empt = mByte;
			int emptsize = mSize;
			//새로운 크기 버퍼 생성
			mByte = Reset(emptsize + _datesize);
			//기존 버퍼 메모리를 복사
			memcpy_s(mByte.get(), mSize, empt.get(), emptsize);
			//기존버퍼 포인터만큼 포인터를 옴겨서 뒤에 붙임
			memcpy_s(mByte.get() + emptsize, mSize - emptsize, _data, _datesize);
		}

		//읽기 (앞부터)
		template <class T>
		bool Read(OUT T* _data, int _datesize)
		{
			//사이즈 초과시 실패
			if (mSize < _datesize) return false;

			//지정한 만큼 앞 부분 복사
			memcpy_s(_data, _datesize, mByte.get(), _datesize);

			sp_Byte empt = mByte;
			int emptsize = mSize;

			//사이즈 줄여서 초기화
			Reset(emptsize - _datesize);

			//기존 버퍼 메모리를 복사(앞으로 당기는 과정)
			memcpy_s(mByte.get(), mSize, empt.get() + _datesize, emptsize - _datesize);
			return true;
		}

	};
}


#endif // !_BYTE_H_
