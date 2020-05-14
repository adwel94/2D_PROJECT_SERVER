#include <iostream>
#include "MainManager/MainManager.h"

using namespace std;

int main()
{
	GAME::st_cMainManager::GetInstance()->Run();
	GAME::st_cMainManager::Destroy();
	while (1)
	{

	}
}