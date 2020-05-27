#include "Dungeon.h"
#include "Monster/Monster.h"

bool GAME::Map::cDungeon::FrameProc()
{
	Utilities::DS::cLockIterator<GAME::Monster::cMonster*> iter(&mMob_List);
	while (iter.HasNext())
	{
		iter.Next()->Update();
	}

	return true;
}

GAME::Map::cDungeon::cDungeon(Utilities::CODE _code) : cMap(_code)
{
	mDeltaTime = 1.0f / (float)GAME_FRAME;
	mThread.Create(FrameThread, this, false, true);
}

void GAME::Map::cDungeon::Add_Monster(Monster::cMonster* _mob)
{
	mMob_List.LockAdd(_mob);
}

void GAME::Map::cDungeon::Start()
{
	mThread.Run();
}
