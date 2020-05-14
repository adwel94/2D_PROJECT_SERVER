#pragma once
#ifndef _GAMECLIENT_H_
#define _GAMECLIENT__H_
#include "User/User.h"
#include "State.h"
#include "Client/Client.h"
#include "Charactor/Charactor.h"


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
		//ĳ����
		Charactor::cCharactor* mChar;

	public:

		//������
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
