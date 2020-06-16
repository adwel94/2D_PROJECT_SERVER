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
			//�ڵ�
			Utilities::CODE mCode;
			//�г���
			char mNickName[NICK_NAME_SIZE];
			//Ŭ���̾�Ʈ
			cGameClient* mClient;
			//���� ��
			Map::cMap* mMap;	
			//��Ƽ
			Party::cParty* mParty;

			int mMaxHp;


		public:


			//ĳ���� ��ġ
			bool mDirection;
			Utilities::MY_Math::cVector2D mPosition;



			cCharactor(cGameClient* _client, Utilities::CODE _code, const char* _name, Map::cMap* _map = nullptr);
			virtual ~cCharactor();


			Utilities::CODE Code() 
			{ return mCode; }

			bool mActive;
			int mNowHp;
			int mLevel;

			virtual int JobCode() =0;
			virtual int Atk() = 0;
			virtual float AtkRange() = 0;

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


			virtual void Update() = 0;
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


			// cCharactor��(��) ���� ��ӵ�
			virtual void Update() override;


			// cCharactor��(��) ���� ��ӵ�
			virtual int JobCode() override
			{
				return  CODE::JOB::WARRIOR;
			}


			// cCharactor��(��) ���� ��ӵ�
			virtual int Atk() override
			{
				return 1;
			}


			// cCharactor��(��) ���� ��ӵ�
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

			// cCharactor��(��) ���� ��ӵ�
			virtual void Update() override;

			virtual int JobCode() override
			{
				return CODE::JOB::ARCHER;
			}

			// cCharactor��(��) ���� ��ӵ�
			virtual int Atk() override
			{
				return 1;
			}
		};

	}

}






#endif // !_CHARACTOR_H_
