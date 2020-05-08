#pragma once
#ifndef _GAMECLIENT_H_
#define _GAMECLIENT__H_
#include "Client/Client.h"
#include "User/User.h"
#include "State.h"

namespace GAME
{
	namespace STATE
	{
		class cState;
		enum class E;
	}


	//게임 클라이언트
	class cGameClient : public Server::cClient
	{

	private:
		//상태
		STATE::cState* mState;
		//ID,PW
		Server::cUser mUser;

	public:

		//생성자
		cGameClient() {}
		cGameClient(SOCKET _sock, const SOCKADDR_IN& _addr);

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
