#pragma once
#ifndef _MAINMANAGER_H_
#define _MAINMANAGER_H_
#include "Game.h"
#include "Singleton/SingleTon.h"
#include "ServerModel/IOCP_Manager.h"
#include "GameClient/GameClient.h"

namespace GAME
{
	class cMainManager : public Server::cIOCP_Manager<cGameClient*>
	{
	public:

		cMainManager();
		~cMainManager();

		void Run();

		// cIOCP_Manager을(를) 통해 상속됨
		virtual cGameClient* CreateKey(SOCKET _sock, const SOCKADDR_IN& _addr) override;
		
		virtual void AcceptProcess(cGameClient* _key, SOCKET _sock, const SOCKADDR_IN& _addr) override;

		virtual void CompletionProcess(cGameClient* _key, LPOVERLAPPED _overlap = NULL, DWORD _trans = 0) override;

		virtual void ErrorProcess(cGameClient* _key, LPOVERLAPPED _overlap = NULL, DWORD _trans = 0) override;

		virtual void DisconnectProcess(cGameClient* _key, LPOVERLAPPED _overlap = NULL, DWORD _trans = 0) override;




	};

	typedef Utilities::cSingleTon<cMainManager> st_cMainManager;
}



#endif // !_MAINMANAGER_H_
