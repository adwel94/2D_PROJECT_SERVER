#include "Dungeon.h"

bool GAME::Map::cDungeon::FrameProc()
{
	return false;
}

GAME::Map::cDungeon::cDungeon(Utilities::CODE _code) : cMap(_code)
{
	mDeltaTime = 1.0f / (float)GAME_FRAME;
	mThread.Create(FrameThread, this, true, true);
}
