#include "CharactorState.h"

void Charactor::cChar_State::Run(cCharactor* _char)
{

	switch (mState)
	{
	case Charactor::Move:
		Move(_char);
		break;
	default:
		break;
	}
}

void Charactor::cChar_State::Move(cCharactor* _char)
{
}
