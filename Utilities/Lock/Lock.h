#ifndef _LOCK_H_
#define _LOCK_H_
#include <Windows.h>

namespace Utilities
{
	namespace Lock
	{
		class cLock
		{
		protected:
			CRITICAL_SECTION mCS;

		public:
			//크리티컬 섹션 초기화, 삭제
			cLock();
			~cLock();
			//섹션 Enter, Leave
			void Lock();
			void UnLock();
		};

		//자동으로 leave하는 크리티컬 섹션
		class cAutoUnLock
		{
		protected:
			cLock* mLock;
		public:
			cAutoUnLock(cLock* _lock);
			~cAutoUnLock();

		};





		
	}
}






#endif // !_LOCK_H_
