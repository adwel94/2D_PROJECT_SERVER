#include "MainManager/MainManager.h"

int main()
{
	GAME::st_cMainManager::GetInstance()->Run();
	GAME::st_cMainManager::Destroy();
}