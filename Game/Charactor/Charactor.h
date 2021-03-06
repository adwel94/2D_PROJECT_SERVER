#pragma once
#ifndef _CHARACTOR_H_
#define _CHARACTOR_H_
#include "Game.h"
#include "Math/Vector2D.h"
#include "CodeMaker/CodeMaker.h"
#include "Map/Map.h"
#include "Party/Party.h"
#include "CharactorState.h"
#include "Math/Vector2D.h"

namespace GAME
{
	class cGameClient;

	namespace Charactor
	{
		class cCharactor
		{
		protected:
			//코드
			Utilities::CODE mCode;
			//닉네임
			char mNickName[NICK_NAME_SIZE];
			//클라이언트
			cGameClient* mClient;
			//접속 맵
			Map::cMap* mMap;	
			//파티
			Party::cParty* mParty;
			//최대체력
			int mMaxHp;
		public:


			//캐릭터 방향, 위치
			bool mDirection;
			Utilities::MY_Math::cVector2D mPosition;

			//상태값
			bool mActive; //죽었는지 살았는지
			int mNowHp; //현재 체력
			int mLevel; //레벨

			//생성자, 소멸자
			cCharactor(cGameClient* _client, Utilities::CODE _code, const char* _name, Map::cMap* _map = nullptr);
			virtual ~cCharactor();


			//직업코드, 공격력, 공격 범위
			virtual int JobCode() = 0;
			virtual int Atk() = 0;
			virtual float AtkRange() = 0;

			//GET ,SET
			Utilities::CODE Code() 
			{ return mCode; }

			cGameClient* GetClient()
			{
				return mClient;
			}

			const char* NickName()
			{
				return mNickName;
			}

			void SetMap(Map::cMap* _map)
			{
				mMap = _map;
			}

			Map::cMap* GetMap()
			{
				return mMap;
			}

			void SetParty(Party::cParty* _party)
			{
				mParty = _party;
			}

			Party::cParty* GetParty() 
			{ return mParty; }

			//virtual void Update() = 0;
		};

		class cWarrior : public cCharactor
		{
		public:
			cWarrior(cGameClient* _client, Utilities::CODE _code, const char* _name, Map::cMap* _map = nullptr)
				: cCharactor(_client, _code, _name, _map)
			{
				mMaxHp = 10;
				mNowHp = mMaxHp;
			}


			// cCharactor을(를) 통해 상속됨
			//virtual void Update() override;


			// cCharactor을(를) 통해 상속됨
			virtual int JobCode() override
			{
				return  CODE::JOB::WARRIOR;
			}


			// cCharactor을(를) 통해 상속됨
			virtual int Atk() override
			{
				return 1;
			}


			// cCharactor을(를) 통해 상속됨
			virtual float AtkRange() override
			{
				return 3.6f;
			}

		};

		class cArcher : public cCharactor
		{
		public:
			cArcher(cGameClient* _client, Utilities::CODE _code, const char* _name, Map::cMap* _map = nullptr)
				: cCharactor(_client, _code, _name, _map)
			{

			}

			// cCharactor을(를) 통해 상속됨
			//virtual void Update() override;

			virtual int JobCode() override
			{
				return CODE::JOB::ARCHER;
			}

			// cCharactor을(를) 통해 상속됨
			virtual int Atk() override
			{
				return 1;
			}
		};

	}

}






#endif // !_CHARACTOR_H_
