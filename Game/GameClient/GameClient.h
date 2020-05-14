#pragma once
#ifndef _GAMECLIENT_H_
#define _GAMECLIENT__H_
#include "User/User.h"
#include "State.h"
#include "Client/Client.h"
#include "Charactor/Charactor.h"


namespace GAME
{
	//게임 클라이언트
	class cGameClient : public Server::cClient
	{
		static unsigned int ClientCount;
	private:
		//상태
		STATE::cState* mState;
		//ID,PW
		Server::cUser mUser;
		//캐릭터
		Charactor::cCharactor* mChar;

	public:

		//생성자
		cGameClient(SOCKET _sock, const SOCKADDR_IN& _addr);
		~cGameClient();

		//유저
		Server::cUser& User() { return mUser; }

		//상태 Set,Get
		void Set_State(STATE::E _state);
		STATE::cState* Get_State() { return mState; }


		// cClient을(를) 통해 상속됨		
		virtual bool Recv_Process() override;
		virtual bool Send_Process() override;

	};
}





#endif // !_GAMECLIENT_H_
