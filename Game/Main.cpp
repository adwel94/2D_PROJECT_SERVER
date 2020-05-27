#include "MainManager/MainManager.h"
#include "Map/DungeonManager.h"

int main()
{
	//GAME::Map::st_cDungeonManager::GetInstance()->CreateDungeon();
	GAME::st_cMainManager::GetInstance()->Run();
	GAME::st_cMainManager::Destroy();
}