#pragma once
#ifndef _STATE_H_
#define _STATE_H_
#include "GameClient.h"

namespace GAME
{
	class cGameClinet;

	class cState
	{
	public:
		enum class State
		{
			NONE = -1,
			LOG_IN,


			STATE_COUNT
		};


	private:

		cState* mState[(int)State::STATE_COUNT];
		cGameClinet* mClient;

	public:

		static void Create(cGameClinet* _clinet);
		static void Delete();

		virtual void RecvProc() = 0;
		virtual void SendProc();







	};
}



#endif // !_STATE_H_
