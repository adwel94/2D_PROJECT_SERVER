#pragma once
#ifndef _BYTE_H_
#define _BYTE_H_
#include <Windows.h>



namespace Utilities
{	//가변 바이트 버퍼
	struct sBuffer
	{
		BYTE* mByte;//배열
		DWORD mSize;//배열크기
		DWORD  mTrans;//데이터 포인터

		//생성자
		sBuffer(DWORD _size = 0);
		//복사 생성자
		sBuffer(sBuffer& _buffer);
		//소멸자
		~sBuffer();

		//버퍼 초기화
		void Reset_Buffer(int _size = 0);

		//이어쓰기
		template <class T>
		void Write(T* _data, int _datesize)
		{
			//기존 버퍼를 임시저장
			BYTE* empt = mByte;
			int emptsize = mSize;

			//새로운 크기 버퍼 생성
			mByte = new BYTE[emptsize + _datesize];
			mSize = emptsize + _datesize;

			//기존 버퍼 메모리를 복사
			memcpy_s(mByte, mSize, empt, emptsize);
			//기존버퍼 포인터만큼 포인터를 옴겨서 뒤에 붙임
			memcpy_s(mByte + emptsize, mSize - emptsize, _data, _datesize);

			delete empt;
		}

		//읽기 (앞부터)
		template <class T>
		bool Read(OUT T* _data, int _datesize)
		{
			//사이즈 초과시 실패
			if (mSize < _datesize) return false;

			//지정한 만큼 앞 부분 복사
			memcpy_s(_data, _datesize, mByte, _datesize);

			//기존 버퍼를 임시저장
			BYTE* empt = mByte;
			int emptsize = mSize;

			//새로운 크기 버퍼 생성
			mByte = new BYTE[emptsize - _datesize];
			mSize = emptsize - _datesize;

			//기존 버퍼 메모리를 복사(앞으로 당기는 과정)
			memcpy_s(mByte, mSize, empt + _datesize, emptsize - _datesize);

			delete empt;

			return true;
		}

		//앞부분 데이터 확인(앞부터)
		template <class T>
		bool Front(OUT T* _data, int _datesize)
		{
			//사이즈 초과시 실패
			if (mSize < _datesize) return false;

			//지정한 만큼 앞 부분 복사
			memcpy_s(_data, _datesize, mByte, _datesize);
			return true;
		}

		//데이터 결합
		void Write(const bool& _bool);
		void Write(const char& _char);
		void Write(const int& _int);
		void Write(const float& _float);
		void Write(const double& _double);
		void Write(const char* _string);
		void Write(BYTE* _byte, int _size);
		void Write(const sBuffer& _buffer);


		//데이터 분해
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
