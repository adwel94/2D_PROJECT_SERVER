#pragma once
#ifndef _GAMECLIENT_H_
#define _GAMECLIENT__H_
#include "Client/Client.h"
#include "State.h"
#include "User/User.h"


namespace GAME
{
	namespace STATE
	{
		class cState;
		enum class E;
	}


	//���� Ŭ���̾�Ʈ
	class cGameClient : public Server::cClient
	{

	private:
		//����
		STATE::cState* mState;
		//ID,PW
		Server::cUser mUser;

	public:

		//������
		cGameClient(SOCKET _sock, const SOCKADDR_IN& _addr);


		//���� Set,Get
		void Set_State(STATE::E _state);
		STATE::cState* Get_State() { return mState; }


		// cClient��(��) ���� ��ӵ�		
		virtual bool Recv_Process() override;
		virtual bool Send_Process() override;

	};
}





#endif // !_GAMECLIENT_H_
