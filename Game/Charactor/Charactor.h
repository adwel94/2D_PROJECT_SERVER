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

		public:

			//ĳ���� ��ġ
			WAY mWay;
			Utilities::MY_Math::cVector2D mPosition;



			cCharactor(cGameClient* _client, Utilities::CODE _code, const char* _name, Map::cMap* _map = nullptr)
			{
				mCode = _code;
				strcpy_s(mNickName, _name);
				mClient = _client;
				mMap = _map;
				mParty = nullptr;

				mWay = LEFT;
				mPosition = Utilities::MY_Math::cVector2D(0, 0);
			}

			Utilities::CODE Code() 
			{ return mCode; }

			virtual int JobCode() =0;

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
			static const int mJob_Code = JOB::WARRIOR;
		public:
			cWarrior(cGameClient* _client, Utilities::CODE _code, const char* _name, Map::cMap* _map = nullptr)
				: cCharactor(_client, _code, _name, _map)
			{

			}


			// cCharactor��(��) ���� ��ӵ�
			virtual void Update() override;


			// cCharactor��(��) ���� ��ӵ�
			virtual int JobCode() override
			{
				return mJob_Code;
			}

		};

		class cArcher : public cCharactor
		{
			static const int mJob_Code = JOB::ARCHER;
		public:
			cArcher(cGameClient* _client, Utilities::CODE _code, const char* _name, Map::cMap* _map = nullptr)
				: cCharactor(_client, _code, _name, _map)
			{

			}

			// cCharactor��(��) ���� ��ӵ�
			virtual void Update() override;

			virtual int JobCode() override
			{
				return mJob_Code;
			}
		};

		class cMagician : public cCharactor
		{
			static const int mJob_Code = JOB::MAGICIAN;
		public:
			cMagician(cGameClient* _client, Utilities::CODE _code, const char* _name, Map::cMap* _map = nullptr)
				: cCharactor(_client, _code, _name, _map)
			{

			}

			// cCharactor��(��) ���� ��ӵ�
			virtual void Update() override;

			virtual int JobCode() override
			{
				return mJob_Code;
			}
		};
	}

}






#endif // !_CHARACTOR_H_
