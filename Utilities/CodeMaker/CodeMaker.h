#pragma once
#ifndef _CODE_MAKER_H_
#define _CODE_MAKER_H_
#include <time.h>

namespace Utilities
{

	//고유 코드를 생성 
	//base(시간) + add
	class cCodeMaker
	{
		enum 
		{
			//base를 초기화할 간격 (초)
			INTERVAL = 180
		};
	protected:
		time_t mTime;
		tm mBase;
		unsigned short mAddCode;
	public:
		cCodeMaker();
		virtual ~cCodeMaker();

		unsigned __int64 Get_Code();
	};
}



#endif // !_CODE_MAKER_H_
