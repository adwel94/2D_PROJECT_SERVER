#include "Map.h"
#include "Charactor/Charactor.h"

GAME::Map::cMap::cMap(Utilities::CODE _code)
{
	mCode = _code;
	printf_s("Create_Map Code : %llu \n", mCode);
}

GAME::Map::cMap::~cMap()
{
	printf_s("Destroy_Map Code : %llu \n", mCode);
}

bool GAME::Map::cMap::In_Charactor(Charactor::cCharactor* _char)
{
	_char->SetMap(this);
	mChar_List.LockAdd(_char);
	return true;
}


bool GAME::Map::cMap::Out_Charactor(Charactor::cCharactor* _char)
{
	_char->SetMap(nullptr);
	mChar_List.LockRemove(_char);
	return true;
}
