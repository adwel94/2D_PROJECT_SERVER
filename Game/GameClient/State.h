#pragma once
#ifndef _STATE_H_
#define _STATE_H_

namespace GAME
{
	class cGameClient;


	//상태 패턴
	namespace STATE
	{

		//상태 종류
		enum E
		{
			NONE = -1,
			LOG_IN,
			CHARACTOR,
			TOWN,
			DUNGEON,


			STATE_COUNT
		};



		//상태 - 부모클래스
		class cState
		{

		public:

			static cState* All_State[STATE_COUNT];
			static void Create(); 
			static void Destroy();
			virtual void RecvProc(cGameClient* _client) = 0;
			virtual void SendProc(cGameClient* _client);	
		};



		//로그인 페이지 상태
		class cLogin_State : public cState
		{
		public:
			// cState을(를) 통해 상속됨
			virtual void RecvProc(cGameClient* _client) override;
		};

		//캐릭터 페이지 상태
		class cCharactor_State : public cState
		{
		public:
			// cState을(를) 통해 상속됨
			virtual void RecvProc(cGameClient* _client) override;
		};

		//마을에 있는 상태
		class cTown_State : public cState
		{
		public:
			// cState을(를) 통해 상속됨
			virtual void RecvProc(cGameClient* _client) override;

		};

		class cDungeon_State : public cState
		{
		public:
			// cState을(를) 통해 상속됨
			virtual void RecvProc(cGameClient* _client) override;
		};




	}


	
}



#endif // !_STATE_H_
