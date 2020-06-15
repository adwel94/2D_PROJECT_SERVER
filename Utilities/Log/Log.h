#pragma once
#ifndef _LOG_H_
#define _LOG_H_
#include <stdio.h>



namespace Utilities
{
	//로그 기록
	class cLog
	{
	public:

		enum
		{
			NAME_LEN = 32,//파일 최대 이름
			MAX_LEN=256,//최대로 기록할수 있는 글자 길이
			TIME_LEN =30
		};

	protected:
		//파일 포인터
		FILE* mFp;
		//파일 이름	
		char mName[NAME_LEN] = "\0";
	public:

		cLog()
		{
			mFp = nullptr;
		}

		//파일이름,경로 연결
		bool Connect(const char* _name, const char* _path = "..\\LogFile");
		//기록
		bool Record(const char* _msg, ...);
		//해제
		bool Close();


	};

}


#endif // !_LOG_H_
