#pragma once
#ifndef _STATE_H_
#define _STATE_H_

namespace GAME
{
	class cGameClient;


	//���� ����
	namespace STATE
	{

		//���� ����
		enum E
		{
			NONE = -1,
			LOG_IN,


			STATE_COUNT
		};



		//���� - �θ�Ŭ����
		class cState
		{

		public:

			static cState* All_State[STATE_COUNT];
			static void Create(); 
			static void Destroy();
			virtual void RecvProc(cGameClient* _client) = 0;
			virtual void SendProc(cGameClient* _client);	
		};



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
