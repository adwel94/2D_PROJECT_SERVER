#pragma once
#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_
#include <math.h>

namespace Server
{

	class cProtocol
	{
	public:		

		static const int PROTOCOL_SIZE = 128;
		virtual enum class P;
	private:
		//2��  p���� ��ȯ�Ͽ� ��Ʈ������ �����ϰ� ��
		int ToBit(P _p)
		{
			return pow(2,(int)_p);
		}
	protected:

		__int64 mProtocol[PROTOCOL_SIZE/64];

	public:


		const BYTE* Get() const
		{
		}

		void Add(P _p)
		{

		}

		bool In(P _p)
		{

		}
	};
}






#endif // !_PROTOCOL_H_
