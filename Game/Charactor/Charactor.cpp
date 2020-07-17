#include "Charactor.h"
#include "GameClient/GameClient.h"

//void GAME::Charactor::cWarrior::Update()
//{
//}
//
//
//
//
//void GAME::Charactor::cArcher::Update()
//{
//}

GAME::Charactor::cCharactor::cCharactor(cGameClient* _client, Utilities::CODE _code, const char* _name, Map::cMap* _map)
{
	mCode = _code;
	strcpy_s(mNickName, _name);
	mClient = _client;
	mMap = _map;
	mParty = nullptr;
	mActive = true;

	mDirection = LEFT;
	mPosition = Utilities::MY_Math::cVector2D(0, 0);

	printf_s("IP: %s Enter Charactor Code : %llu \n", GetClient()->Get_IP(), mCode);
}

GAME::Charactor::cCharactor::~cCharactor()
{
	printf_s("IP: %s Exit Charactor Code : %llu \n", GetClient()->Get_IP(), mCode);
}
