#pragma once
#ifndef _GAMECLIENT_H_
#define _GAMECLIENT__H_
#include "User/User.h"
#include "State.h"
#include "Client/Client.h"
namespace GAME
{
	//���� Ŭ���̾�Ʈ
	class cGameClient : public Server::cClient
	{
		static unsigned int ClientCount;
	private:
		//����
		STATE::cState* mState;
		//ID,PW
		Server::cUser mUser;

	public:

		//������
		cGameClient() {}
		cGameClient(SOCKET _sock, const SOCKADDR_IN& _addr);
		~cGameClient();

		//����
		Server::cUser& User() { return mUser; }

		//���� Set,Get
		void Set_State(STATE::E _state);
		STATE::cState* Get_State() { return mState; }


		// cClient��(��) ���� ��ӵ�		
		virtual bool Recv_Process() override;
		virtual bool Send_Process() override;

	};
}





#endif // !_GAMECLIENT_H_
