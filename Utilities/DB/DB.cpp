#include "DB.h"
#include <cstdarg>
#include <string.h>

Utilities::DB::cDB_Result::cDB_Result()
{
	mCurrent_Row = -1;
	mSql_Result = nullptr;
}

Utilities::DB::cDB_Result::~cDB_Result()
{
	if (mSql_Result != nullptr)
	{
		//����� ������ ���� �ʱ�ȭ
		mysql_free_result(mSql_Result);
	}
}

bool Utilities::DB::cDB_Result::Move_Row(unsigned int _index)
{
	mysql_data_seek(mSql_Result, _index - 1);
	if (mysql_fetch_row(mSql_Result) == NULL)
	{
		return false;
	}
	mCurrent_Row = _index;
	return true;
}

bool Utilities::DB::cDB_Result::Next_Row()
{
	if (mysql_fetch_row(mSql_Result) == NULL)
	{
		return false;
	}
	mCurrent_Row++;
	return true;
}

void Utilities::DB::cDB_Result::Set_Result(MYSQL_RES* _result)
{
	mCurrent_Row = 0;
	mSql_Result = _result;
}

int Utilities::DB::cDB_Result::Current_Row_Index()
{
	return mCurrent_Row;
}

const char* Utilities::DB::cDB_Result::Current_Row(int _index)
{
	//index ���� �˻�
	if (mSql_Result == nullptr || mSql_Result->field_count <= _index) return nullptr;

	return mSql_Result->current_row[_index];
}

const char* Utilities::DB::cDB_Result::operator[](unsigned int _index)
{
	//index ���� �˻�
	if (mSql_Result == nullptr || mSql_Result->field_count <= _index) return nullptr;

	return mSql_Result->current_row[_index];
}

const char* Utilities::DB::cDB_Result::Current_Row(const char* _filed)
{
	//�� ���� ��ŭ �˻�
	for (int i = 0; i < (mSql_Result->field_count); i++)
	{
		//��ġ�� �ش� �ʵ尪 ��ȯ
		if (!strcmp(_filed, mSql_Result->fields[i].name))
		{
			return mSql_Result->current_row[i];
		}
	}
	return nullptr;
}

int Utilities::DB::cDB_Result::Row_Count()
{
	if (mSql_Result == nullptr) return 0;
	return mSql_Result->row_count;
}

int Utilities::DB::cDB_Result::Column_Count()
{
	if (mSql_Result == nullptr) return 0;
	return mSql_Result->field_count;
}

bool Utilities::DB::cDB_Result::Column_Check(const char* _column)
{
	if (mSql_Result == nullptr) return false;
	for (int i = 0; i < mSql_Result->field_count; i++)
	{
		if (!strcmp(mSql_Result->fields[i].name, _column))
		{
			return true;
		}
	}
	return false;
}

const char* Utilities::DB::cDB_Result::Column_Name(unsigned int _index)
{
	if (mSql_Result == nullptr || mSql_Result->field_count <= _index) return nullptr;
	return mSql_Result->fields[_index].name;
}


//-----------------------------------------------------------------------------------------------------


Utilities::DB::cDatabase::cDatabase()
{
	mConnection = mysql_init(NULL);
}

Utilities::DB::cDatabase::~cDatabase()
{
	if (mConnection != NULL)
	{
		DB::cDatabase::Close();
	}
}

bool Utilities::DB::cDatabase::Conncetion(const char* _HOST, const char* _USER, const char* _PASS, const char* _NAME, unsigned int _PORT, const char* _UNIX_SOCK, unsigned long _CLIENT_FLAG)
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

bool Utilities::DB::cDatabase::Run_SQL(const char* _query, ...)
{

	char sql[512] = "\0";


	va_list arg;
	va_start(arg, _query);
	vsprintf_s(sql, _query, arg);
	va_end(arg);



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

bool Utilities::DB::cDatabase::Get_Result(OUT cDB_Result& _result)
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

void Utilities::DB::cDatabase::Close()
{
	//DB ��������
	mysql_close(mConnection);
}
