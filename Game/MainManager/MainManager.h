#pragma once
#ifndef _MAINMANAGER_H_
#define _MAINMANAGER_H_
#include "ServerModel/IOCP_Manager.h"
#include "Singleton/SingleTon.h"
#include "Game.h"

namespace GAME
{
	class cMainManager 
	{
	public:

	};


	typedef Utilities::cSingleTon<cMainManager> st_cMainManger;


}



#endif // !_MAINMANAGER_H_
