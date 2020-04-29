#pragma once
#ifndef _USER_H_
#define _USER_H_
#include <string.h>



namespace Server
{
	class cUser
	{
	public:
		enum
		{
			ID_SIZE = 30,
			PW_SIZE = 30
		};
	protected:

		unsigned __int64 mCode;
		char mId[30];
		char mPw[30];

	public:

		cUser()
		{
			mCode = 0;
			mId[0] = '\0';
			mPw[0] = '\0';
		}

		cUser(const char* _id, const char* _pw, unsigned __int64 _code = 0)
		{
			mCode = _code;
			strcpy_s(mId, ID_SIZE, _id);
			strcpy_s(mPw, PW_SIZE, _pw);
		}

		cUser(const cUser& _user)
		{
			mCode = _user.mCode;
			strcpy_s(mId, ID_SIZE, _user.mId);
			strcpy_s(mPw, PW_SIZE, _user.mPw);
		}


		const unsigned __int64& Code() const { return mCode; }
		const char* Id() const { return mId; } 
		const char* Pw() const { return mPw; }

	};

}




#endif // !_USER_H_
