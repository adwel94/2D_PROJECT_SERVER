#pragma once
#ifndef _DB_H_
#define _DB_H_
#include <WinSock2.h>
#include "include/mysql.h"



namespace Utilities
{
	namespace DB
	{
		//쿼리의 결과 값을 저장
		class cDB_Result
		{
			MYSQL_RES* mSql_Result; //쿼리의 결과를 가져올 포인터
		public:
			cDB_Result();
			virtual ~cDB_Result();

			//쿼리 결과값 저장
			void Set_Result(MYSQL_RES* _result);
			//해당 인덱스로 열 이동
			void Move_Row(unsigned int _index);
			//다음 열로 이동
			bool MoveNext();
			//열 데이터값
			const char* Now(int _index);
			const char* Now(const char* _field);
			//총 행 갯수
			int Row_Count();
			//총 열 갯수
			int Column_Count();
			//해당 열 있는지 확인
			bool Column_Check(const char* _column);
			//열 이름 반환
			const char* Column_Name(unsigned int _index);
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
			virtual ~cDatabase();

			//DB접속 
			bool Conncetion(const char* _HOST, const char* _USER, const char* _PASS, const char* _DB_NAME, unsigned int _PORT, const char* _UNIX_SOCK = NULL, unsigned  long _CLIENT_FLAG = NULL);
			//쿼리 적용
			bool Run_SQL(const char* _query, ...);
			//결과값 반환
			bool Get_Result(OUT cDB_Result& _result);
			//DB해제
			void Close();
		};
	}
}

#endif // !_DB_H
