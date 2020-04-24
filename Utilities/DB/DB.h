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
		//������ ��� ���� ����
		class cDB_Result
		{
			int mCurrent_Row; //���� ��
			MYSQL_RES* mSql_Result; //������ ����� ������ ������
		public:
			cDB_Result();
			~cDB_Result();

			//�ش� �ε����� �� �̵�
			bool Move_Row(unsigned int _index);
			//���� ���� �̵�
			bool Next_Row();
			//���� ����� ����
			void Set_Result(MYSQL_RES* _result);
			//���� �� �ε���
			int Current_Row_Index();
			//�������� _index�� ������ ��ȯ
			const char* Current_Row(int _index);
			//�������� _index�� ������ ��ȯ
			const char* operator [] (unsigned int _index);
			//�������� �� �̸����� ������ ��ȯ
			const char* Current_Row(const char* _filed);
			//�� �� ����
			int Row_Count();
			//�� �� ����
			int Column_Count();
			//�� �̸� ��ȯ
			const char* Flied_Name(unsigned int _index);
		};

		//������ ���̽�
		class cDatabase
		{
		protected:

			MYSQL* mConnection; //������ ����Ǵ� ������ 
		public:
			//�ʱ�ȭ
			cDatabase();
			//���� ����
			~cDatabase();

			//DB���� 
			bool Conncetion(const char* _HOST, const char* _USER, const char* _PASS, const char* _NAME, unsigned int _PORT, const char* _UNIX_SOCK, unsigned  long _CLIENT_FLAG);
			//���� ����
			bool Run_SQL(const char* _query);
			//����� ��ȯ
			bool Get_Result(OUT cDB_Result& _result);
			//DB����
			void Close();
		};
	}
}

#endif // !_DB_H
