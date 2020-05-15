#include <iostream>
#include "MainManager/MainManager.h"
#include "GameClient/GameClient.h"
#include "Charactor/Charactor.h"
#include "DB/DB.h"
using namespace std;

int main()
{

	GAME::st_cMainManager::GetInstance()->Run();
	GAME::st_cMainManager::Destroy();
}