#pragma once
#ifndef _DB_H_
#define _DB_H_
#include <WinSock2.h>
#include "include/mysql.h"



namespace Utilities
{
	namespace DB
	{
		//������ ��� ���� ����
		class cDB_Result
		{
			MYSQL_RES* mSql_Result; //������ ����� ������ ������
		public:
			cDB_Result();
			virtual ~cDB_Result();

			//���� ����� ����
			void Set_Result(MYSQL_RES* _result);
			//�ش� �ε����� �� �̵�
			void Move_Row(unsigned int _index);
			//���� ���� �̵�
			bool MoveNext();
			//�� �����Ͱ�
			const char* Now(int _index);
			const char* Now(const char* _field);
			//�� �� ����
			int Row_Count();
			//�� �� ����
			int Column_Count();
			//�ش� �� �ִ��� Ȯ��
			bool Column_Check(const char* _column);
			//�� �̸� ��ȯ
			const char* Column_Name(unsigned int _index);
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
			virtual ~cDatabase();

			//DB���� 
			bool Conncetion(const char* _HOST, const char* _USER, const char* _PASS, const char* _DB_NAME, unsigned int _PORT, const char* _UNIX_SOCK = NULL, unsigned  long _CLIENT_FLAG = NULL);
			//���� ����
			bool Run_SQL(const char* _query, ...);
			//����� ��ȯ
			bool Get_Result(OUT cDB_Result& _result);
			//DB����
			void Close();
		};
	}
}

#endif // !_DB_H
