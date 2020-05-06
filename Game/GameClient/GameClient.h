#pragma once
#ifndef _GAMECLIENT_H_
#define _GAMECLIENT__H_
#include "Client/Client.h"
#include "User/User.h"


namespace GAME
{
	class cState;


	class cGameClinet : public Server::cClient
	{

	private:

		cState* mState;
		Server::cUser mUser;

	public:




	};
}





#endif // !_GAMECLIENT_H_
