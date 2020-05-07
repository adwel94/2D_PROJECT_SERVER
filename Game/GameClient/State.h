#pragma once
#ifndef _STATE_H_
#define _STATE_H_
#include "GameClient.h"

namespace GAME
{

	class cGameClient;

	//���� ����
	namespace STATE
	{

		//���� ����
		enum class E
		{
			NONE = -1,
			LOG_IN,


			STATE_COUNT
		};


		//���� - �θ�Ŭ����
		class cState
		{
		public:
			virtual void RecvProc(cGameClient* _client) = 0;
			virtual void SendProc(cGameClient* _client);

			static void Create();
			static void Destroy();
		};

		////���� ����
		//const int STATE_COUNT = (int)E::STATE_COUNT;

		////��� ���¸� �����س��� �迭
		//cState* STATE_TYPE[STATE_COUNT];







		//�α��� ������ ����
		class cLogin_State : public cState
		{
		public:
			// cState��(��) ���� ��ӵ�
			virtual void RecvProc(cGameClient* _client) override;
		};


	}


	
}



#endif // !_STATE_H_
