
#include <stdlib.h>
#include <string.h>
#include <cstdarg>
#include <time.h>


#include "Log.h"

bool Utilities::cLog::Connect(const char* _name, const char* _path)
{
	//�̸� ���� + ��� ���� >= MAX_LEN
	if ((strlen(_name) + strlen(_path)) > MAX_LEN)
	{
		printf_s("Name Size Over \n");
		return false;
	}

	char mMsg[MAX_LEN] = "\0";
	
	//��ΰ� �ԷµǸ� ���+
	if (strlen(_path) > 0)
	{
		strcat_s(mMsg, _path);
		mMsg[strlen(_path)] = '\\';
		mMsg[strlen(_path) + 1] = '\0';
	}

	//���� �̸�+
	strcat_s(mMsg, _name);	

	//���� �̾� ����� ����
	if (fopen_s(&mFp, mMsg, "a") != 0)
	{
		printf_s("Log Connect Fail Name : %s \n", _name);
		return false;
	}

	printf_s("Log Connect Success Name : %s \n", _name);
	return true;
}

bool Utilities::cLog::Record(const char* _msg, ...)
{
	if (mFp == nullptr) return false;

	if (strlen(_msg) >= MAX_LEN) return false;

	//�ð� ���ϴ� ����, �Լ�
	time_t timer = time(NULL);
	tm now;

	//�ִ����+ �ð��� ����
	char log[MAX_LEN +1 ] = "\0";
	char timeinfo[30] = "\0";

	if (localtime_s(&now, &timer) != 0)
	{
		//����ð��� �˼� ���� ���
		sprintf_s(timeinfo, "Unknown Time - ");
	}
	else
	{	//�ð��� �̾� ����
		sprintf_s(timeinfo, "%d-%d-%d %d:%d:%d - ", now.tm_year+1900, now.tm_mon+1, now.tm_mday, now.tm_hour, now.tm_min, now.tm_sec);
	}

	//���� �μ� Ȯ��
	va_list arg;
	va_start(arg, _msg); 
	vsprintf_s(log, _msg, arg);
	va_end(arg);

	log[strlen(log) + 1] = '\0';
	log[strlen(log)] = '\n';


	fputs(timeinfo, mFp);
	fputs(log, mFp);
	return true;	
}

bool Utilities::cLog::Close()
{
	//���� �ݱ�
	return (fclose(mFp) == 0) ? true : false;
}
