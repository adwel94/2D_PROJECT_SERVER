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
			//ũ��Ƽ�� ���� �ʱ�ȭ, ����
			cLock();
			~cLock();
			//���� Enter, Leave
			void Lock();
			void UnLock();
		};

		//�ڵ����� leave�ϴ� ũ��Ƽ�� ����
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
