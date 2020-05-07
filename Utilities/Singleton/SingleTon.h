#pragma once
#ifndef _SINGLE_TON_H_
#define _SINGLE_TON_H

namespace Utilities
{

	//ΩÃ±€≈Ê ∆–≈œ

	template <class T>
	class cSingleTon
	{
		cSingleTon<T>()
		{

		}

		~cSingleTon<T>()
		{

		}

		static T* mInstance;
	public:
		
		static void Create()
		{
			if (mInstance == nullptr)
			{
				mInstance = new T();
			}
		}

		static T* GetInstance()
		{
			if (mInstance == nullptr)
			{
				mInstance = new T();
			}
			return mInstance;
		}

		static void Destroy()
		{
			if (mInstance != nullptr)
			{
				delete mInstance;
				mInstance = nullptr;
			}
		}
	};

	template<class T>
	T* cSingleTon<T>::mInstance = nullptr;

}
#endif // !_SINGLE_TON_H_