#include "ServerModel/IOCP_Manager.h"
#include "Sock/SocketManager.h"
#include "Client/Client.h"

using namespace Server;

class cMainManger : cIOCP_Manager<cClient*>
{
public:
	// cIOCP_Manager을(를) 통해 상속됨
	virtual void AcceptProcess(cClient* _key) override
	{
		_key->Set_Recv_Size(sizeof(int));
		_key->WSA_Recv_Packet();
		
	}
	virtual void CompletionProcess(cClient* _key , LPOVERLAPPED _overlap, DWORD _trans) override
	{
		//클라이언트 recv 오버랩과 같을시
		if (_key->Is_Recv_Overlap(_overlap))
		{			
			if (_key->Is_Recv_Success(_trans))
			{
				if (_key->Recv_Overlap().trans == sizeof(int))
				{

				}
			}

		}

	}
	virtual void ErrorProcess(cClient* _key) override
	{

	}
	virtual void DisconnectProcess(cClient* _key) override
	{

	}
};

int main()
{





}