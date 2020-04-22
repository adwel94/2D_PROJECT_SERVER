#pragma once
#pragma comment(lib,"libmysql.lib") 
#include "include/mysql.h"
#include <stdio.h>

namespace DB
{
	//������ ��� ���� ����
	class cDB_Result
	{
		int mCurrent_Row; //���� ��
		MYSQL_RES* mSql_Result; //������ ����� ������ ������
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
				//����� ������ ���� �ʱ�ȭ
				mysql_free_result(mSql_Result);
			}
		}

		//�ش� �ε����� �� �̵�
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
		
		//���� ���� �̵�
		bool Next_Row()
		{
			if (mysql_fetch_row(mSql_Result) == NULL)
			{		
				return false;
			}
			mCurrent_Row++;
			return true;
		}

		//���� ����� ����
		void Set_Result(MYSQL_RES* _result)
		{
			mCurrent_Row = 0;
			mSql_Result = _result;
		}		

		//���� �� �ε���
		int Current_Row_Index()
		{
			return mCurrent_Row;
		}

		//�������� _index�� ������ ��ȯ
		const char* Current_Row(int _index)
		{
			//index ���� �˻�
			if (mSql_Result == nullptr || mSql_Result->field_count <= _index) return "��Flied_index_Err��";

			return mSql_Result->current_row[_index];
		}

		//�������� _index�� ������ ��ȯ
		const char* operator [] (unsigned int _index)
		{
			//index ���� �˻�
			if (mSql_Result == nullptr || mSql_Result->field_count <= _index) return "��Flied_index_Err��";

			return mSql_Result->current_row[_index];
		}

		//�������� �� �̸����� ������ ��ȯ
		const char* Current_Row(const char* _filed)
		{
			//�� ���� ��ŭ �˻�
			for (int i = 0; i < (mSql_Result->field_count); i++)
			{
				//��ġ�� �ش� �ʵ尪 ��ȯ
				if(!strcmp(_filed, mSql_Result->fields[i].name))
				{
					return mSql_Result->current_row[i];
				}
			}
			return "��Flied_index_Err��";		}

		//�� �� ����
		int Row_Count() 
		{
			if (mSql_Result == nullptr) return 0;
			return mSql_Result->row_count;
		}

		//�� �� ����
		int Column_Count() 
		{ 
			if (mSql_Result == nullptr) return 0;
			return mSql_Result->field_count;
		}

		//�� �̸� ��ȯ
		const char* Flied_Name(unsigned int _index)
		{
			if (mSql_Result == nullptr || mSql_Result->field_count <= _index) return "��Flied_Name_Err��";
			return mSql_Result->fields[_index].name;
		}
	};

	//������ ���̽�
	class cDatabase
	{
	protected:

		MYSQL* mConnection; //������ ����Ǵ� ������ 
	public:

		cDatabase()
		{
			//�ʱ�ȭ
			mConnection = mysql_init(NULL);
		}

		//DB���� 
		bool Conncetion(const char* _HOST, const char* _USER, const char* _PASS, const char* _NAME, unsigned int _PORT, const char* _UNIX_SOCK, unsigned  long _CLIENT_FLAG)
		{
			//DB���� 
			if (mysql_real_connect(mConnection, _HOST, _USER, _PASS, _NAME, _PORT, (char*)NULL, 0) == NULL)
			{
				//���н� ���� ���
				fprintf_s(stderr, "Mysql connection error : %s \n", mysql_error(mConnection));
				return false;
			}

			printf_s("Mysql connection Success DB NAME : %s \n", _NAME);
			return true;
		}

		//���� ����
		bool Run_SQL(const char* _query)
		{
			//���� ����
			int retval = mysql_query(mConnection, _query);
			if (retval != 0)
			{
				//���н� ���� ���
				fprintf(stderr, "Mysql query error : %s", mysql_error(mConnection));
				return false;
			}

			//���� ���� ����� ����
			
			return true; 
		}

		bool Get_Result(OUT cDB_Result& _result)
		{
			MYSQL_RES* result = nullptr;
			//������� �����Ѵ�.
			if ((result = mysql_store_result(mConnection)) != NULL)
			{
				_result.Set_Result(result);
				return true;
			}
			return false;
		}

		void Close()
		{
			//DB ��������
			mysql_close(mConnection);
		}
	};
}
