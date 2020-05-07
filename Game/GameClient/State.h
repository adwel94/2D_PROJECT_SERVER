#pragma once
#ifndef _STATE_H_
#define _STATE_H_
#include "GameClient.h"

namespace GAME
{

	class cGameClient;

	//상태 패턴
	namespace STATE
	{

		//상태 종류
		enum class E
		{
			NONE = -1,
			LOG_IN,


			STATE_COUNT
		};


		//상태 - 부모클래스
		class cState
		{
		public:
			virtual void RecvProc(cGameClient* _client) = 0;
			virtual void SendProc(cGameClient* _client);

			static void Create();
			static void Destroy();
		};

		////상태 갯수
		//const int STATE_COUNT = (int)E::STATE_COUNT;

		////모든 상태를 저장해놓을 배열
		//cState* STATE_TYPE[STATE_COUNT];







		//로그인 페이지 상태
		class cLogin_State : public cState
		{
		public:
			// cState을(를) 통해 상속됨
			virtual void RecvProc(cGameClient* _client) override;
		};


	}


	
}



#endif // !_STATE_H_
