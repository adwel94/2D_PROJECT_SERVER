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

	//INTERVAL 초가 지났을 경우
	if (t - mTime >= INTERVAL)
	{
		mTime = t;
		localtime_s(&mBase, &mTime);
		mAddCode = 0;
	}

	unsigned __int64 e = 1000000000000;

	unsigned __int64 code = ((__int64)mBase.tm_year - 100) * e;
	code += ((__int64)mBase.tm_mon + 1) * (e /= 100);
	code += (mBase.tm_mday) * (e /= 100);
	code += (mBase.tm_hour) * (e /= 100);
	code += (mBase.tm_min) * (e /= 100);
	code += (mAddCode++);

	return code;
}
