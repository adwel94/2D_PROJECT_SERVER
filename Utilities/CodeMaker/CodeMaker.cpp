#include "CodeMaker.h"

Utilities::cCodeMaker::cCodeMaker()
{
	mTime = time(NULL);
	localtime_s(&mBase, &mTime);
	mAddCode = 0;
}

Utilities::cCodeMaker::~cCodeMaker()
{

}

Utilities::CODE Utilities::cCodeMaker::Get_Code()
{
	time_t t = time(NULL);

	//INTERVAL �ʰ� ������ ���
	if (t - mTime >= INTERVAL || mAddCode >= 10000)
	{
		mTime = t;
		localtime_s(&mBase, &mTime);
		mAddCode = 0;
	}

	unsigned __int64 e = 1000000000000;


	//ex 202005080818(�ð���) + 0000(mAddCode)
	unsigned __int64 code = ((__int64)mBase.tm_year - 100) * e;
	code += ((__int64)mBase.tm_mon + 1) * (e /= 100);
	code += (mBase.tm_mday) * (e /= 100);
	code += (mBase.tm_hour) * (e /= 100);
	code += (mBase.tm_min) * (e /= 100);
	code += (mAddCode++);

	return code;
}
