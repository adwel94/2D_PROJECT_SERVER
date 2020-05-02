//#include "ServerModel/IOCP_Manager.h"
//#include "Sock/SocketManager.h"
//#include "Client/Client.h"
#include "User/UserManager.h"
//using namespace Server;


//
//class cMainManger : cIOCP_Manager<cClient*>
//{
//public:
//	// cIOCP_Manager을(를) 통해 상속됨
//	virtual void AcceptProcess(cClient* _key) override
//	{
//		_key->Set_Recv_Size(sizeof(int));
//		_key->WSA_Recv_Packet();
//		
//	}
//	virtual void CompletionProcess(cClient* _key , LPOVERLAPPED _overlap, DWORD _trans) override
//	{
//		//클라이언트 recv 오버랩과 같을시
//		if (_key->Is_Recv_Overlap(_overlap))
//		{			
//			if (_key->Is_Recv_Success(_trans))
//			{
//				if (_key->Recv_Overlap().trans == sizeof(int))
//				{
//
//				}
//			}
//
//		}
//
//	}
//	virtual void ErrorProcess(cClient* _key) override
//	{
//
//	}
//	virtual void DisconnectProcess(cClient* _key) override
//	{
//
//	}
//};

int main()
{


	//time_t t = time(NULL);
	//tm m;




	//time_t t2 = time(NULL);
	//localtime_s(&m, &t);


	////unsigned __int64 n1 =20042911040000;
	//unsigned short s1 = 0;
	//unsigned __int64 e = 1000000000000;
	//unsigned __int64 _n1 = ((__int64)m.tm_year - 100) * e;
	//_n1 += ((__int64)m.tm_mon + 1) * (e /=100);
	//_n1 += (m.tm_mday) * (e/=100);
	//_n1 += (m.tm_hour) * (e /= 100);
	//_n1 +=  (m.tm_min) * (e /= 100);
	//_n1 += (++s1);

	





	   
}