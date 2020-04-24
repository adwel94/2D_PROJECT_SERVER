#pragma once
#ifndef _DB_H_
#define _DB_H_
#pragma comment(lib,"libmysql.lib") 
#include "include/mysql.h"
#include <stdio.h>

namespace Utilities
{
	namespace DB
	{
		//쿼리의 결과 값을 저장
		class cDB_Result
		{
			int mCurrent_Row; //현재 행
			MYSQL_RES* mSql_Result; //쿼리의 결과를 가져올 포인터
		public:
			cDB_Result();
			~cDB_Result();

			//해당 인덱스로 열 이동
			bool Move_Row(unsigned int _index);
			//다음 열로 이동
			bool Next_Row();
			//쿼리 결과값 저장
			void Set_Result(MYSQL_RES* _result);
			//현재 행 인덱스
			int Current_Row_Index();
			//현재행의 _index열 데이터 반환
			const char* Current_Row(int _index);
			//현재행의 _index열 데이터 반환
			const char* operator [] (unsigned int _index);
			//현재행의 열 이름으로 데이터 반환
			const char* Current_Row(const char* _filed);
			//총 행 갯수
			int Row_Count();
			//총 열 갯수
			int Column_Count();
			//열 이름 반환
			const char* Flied_Name(unsigned int _index);
		};

		//데이터 베이스
		class cDatabase
		{
		protected:

			MYSQL* mConnection; //쿼리와 연결되는 포인터 
		public:
			//초기화
			cDatabase();
			//연결 해제
			~cDatabase();

			//DB접속 
			bool Conncetion(const char* _HOST, const char* _USER, const char* _PASS, const char* _NAME, unsigned int _PORT, const char* _UNIX_SOCK, unsigned  long _CLIENT_FLAG);
			//쿼리 적용
			bool Run_SQL(const char* _query);
			//결과값 반환
			bool Get_Result(OUT cDB_Result& _result);
			//DB해제
			void Close();
		};
	}
}

#endif // !_DB_H
