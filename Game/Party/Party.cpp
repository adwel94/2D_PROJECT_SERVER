#include "Party.h"
#include "Charactor/Charactor.h"

GAME::Party::cParty::cParty(Utilities::CODE _code)
{
	mCode = _code;
	printf_s("Create_Party Code : %llu \n", mCode);
}

GAME::Party::cParty::~cParty()
{
	printf_s("Destroy_Party Code : %llu \n", mCode);
}

bool GAME::Party::cParty::In_Charactor(Charactor::cCharactor* _char)
{
	_char->SetParty(this);
	mChar_List.LockAdd(_char);
	return false;
}

bool GAME::Party::cParty::Out_Charactor(Charactor::cCharactor* _char)
{
	_char->SetParty(nullptr);
	mChar_List.LockRemove(_char);
	return false;
}

