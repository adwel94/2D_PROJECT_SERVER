#pragma once
#pragma comment(lib,"libmysql.lib") 
#include "include/mysql.h"
#include <stdio.h>

namespace DB
{
	//쿼리의 결과 값을 저장
	class cDB_Result
	{
		int mCurrent_Row; //현재 행
		MYSQL_RES* mSql_Result; //쿼리의 결과를 가져올 포인터
	public:
		

		cDB_Result()
		{
			mCurrent_Row = -1;
			mSql_Result = nullptr;
		}

		~cDB_Result()
		{
			if (mSql_Result != nullptr)
			{
				//결과값 저장한 변수 초기화
				mysql_free_result(mSql_Result);
			}
		}

		//해당 인덱스로 열 이동
		bool Move_Row(unsigned int _index)
		{			
			mysql_data_seek(mSql_Result, _index-1);
			if (mysql_fetch_row(mSql_Result) == NULL)
			{
				return false;
			}
			mCurrent_Row = _index;
			return true;
		}
		
		//다음 열로 이동
		bool Next_Row()
		{
			if (mysql_fetch_row(mSql_Result) == NULL)
			{		
				return false;
			}
			mCurrent_Row++;
			return true;
		}

		//쿼리 결과값 저장
		void Set_Result(MYSQL_RES* _result)
		{
			mCurrent_Row = 0;
			mSql_Result = _result;
		}		

		//현재 행 인덱스
		int Current_Row_Index()
		{
			return mCurrent_Row;
		}

		//현재행의 _index열 데이터 반환
		const char* Current_Row(int _index)
		{
			//index 범위 검사
			if (mSql_Result == nullptr || mSql_Result->field_count <= _index) return "★Flied_index_Err★";

			return mSql_Result->current_row[_index];
		}

		//현재행의 _index열 데이터 반환
		const char* operator [] (unsigned int _index)
		{
			//index 범위 검사
			if (mSql_Result == nullptr || mSql_Result->field_count <= _index) return "★Flied_index_Err★";

			return mSql_Result->current_row[_index];
		}

		//현재행의 열 이름으로 데이터 반환
		const char* Current_Row(const char* _filed)
		{
			//열 갯수 만큼 검사
			for (int i = 0; i < (mSql_Result->field_count); i++)
			{
				//일치시 해당 필드값 반환
				if(!strcmp(_filed, mSql_Result->fields[i].name))
				{
					return mSql_Result->current_row[i];
				}
			}
			return "★Flied_index_Err★";		}

		//총 행 갯수
		int Row_Count() 
		{
			if (mSql_Result == nullptr) return 0;
			return mSql_Result->row_count;
		}

		//총 열 갯수
		int Column_Count() 
		{ 
			if (mSql_Result == nullptr) return 0;
			return mSql_Result->field_count;
		}

		//열 이름 반환
		const char* Flied_Name(unsigned int _index)
		{
			if (mSql_Result == nullptr || mSql_Result->field_count <= _index) return "★Flied_Name_Err★";
			return mSql_Result->fields[_index].name;
		}
	};

	//데이터 베이스
	class cDatabase
	{
	protected:

		MYSQL* mConnection; //쿼리와 연결되는 포인터 
	public:

		cDatabase()
		{
			//초기화
			mConnection = mysql_init(NULL);
		}

		//DB접속 
		bool Conncetion(const char* _HOST, const char* _USER, const char* _PASS, const char* _NAME, unsigned int _PORT, const char* _UNIX_SOCK, unsigned  long _CLIENT_FLAG)
		{
			//DB접속 
			if (mysql_real_connect(mConnection, _HOST, _USER, _PASS, _NAME, _PORT, (char*)NULL, 0) == NULL)
			{
				//실패시 에러 출력
				fprintf_s(stderr, "Mysql connection error : %s \n", mysql_error(mConnection));
				return false;
			}

			printf_s("Mysql connection Success DB NAME : %s \n", _NAME);
			return true;
		}

		//쿼리 적용
		bool Run_SQL(const char* _query)
		{
			//쿼리 적용
			int retval = mysql_query(mConnection, _query);
			if (retval != 0)
			{
				//실패시 에러 출력
				fprintf(stderr, "Mysql query error : %s", mysql_error(mConnection));
				return false;
			}

			//쿼리 적용 결과값 저장
			
			return true; 
		}

		bool Get_Result(OUT cDB_Result& _result)
		{
			MYSQL_RES* result = nullptr;
			//결과값을 저장한다.
			if ((result = mysql_store_result(mConnection)) != NULL)
			{
				_result.Set_Result(result);
				return true;
			}
			return false;
		}

		void Close()
		{
			//DB 연결해제
			mysql_close(mConnection);
		}
	};
}
