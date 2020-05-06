#pragma once
#ifndef _CODE_MAKER_H_
#define _CODE_MAKER_H_
#include <time.h>

namespace Utilities
{



	typedef unsigned __int64 CODE;
	//���� �ڵ带 ���� 
	//base(�ð�) + add
	class cCodeMaker
	{
		enum 
		{
			//base�� �ʱ�ȭ�� ���� (��)
			INTERVAL = 180
		};
	protected:
		time_t mTime;
		tm mBase;
		unsigned short mAddCode;
	public:
		cCodeMaker();
		virtual ~cCodeMaker();

		CODE Get_Code();
	};
}



#endif // !_CODE_MAKER_H_