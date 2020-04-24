#include "IOCP_Server.h"
#include"../Sock/SocketManager.h"

//Server::cIOCP_SERVER::cIOCP_SERVER()
//{
//	mPort = NULL;
//
//}
//
//Server::cIOCP_SERVER::~cIOCP_SERVER()
//{
//}

bool Server::cIOCP_SERVER::IOCP_Process(LPVOID _iocp)
{
	cIOCP_SERVER* server = (cIOCP_SERVER*)_iocp;
	int retval; //����� ����
	DWORD transferred; //���۷�
	cClient* client;//Ŭ���Ʈ
	LPOVERLAPPED overlap;//������ ���� ����
	while (true)
	{
		retval = GetQueuedCompletionStatus(server->mPort, &transferred, (PULONG_PTR)&client, &overlap, INFINITE); //�񵿱� ������� �Ϸ�Ǳ⸦ ��ٸ�

		if (overlap == &server->mExit) return 1;

		if (retval == 0 || transferred == 0) //Ŭ���̾�Ʈ ���� ����
		{
			if (retval == 0)//������ ����
			{
				DWORD temp1, temp2;
				//WSAGetOverlappedResult(client->GetSock(), overlap, &temp1, FALSE, &temp2);//���� �������� Ȯ��
				Server::WSA_Err_display((TCHAR*)"WSAGetOverlappedResult()");//���� ���
			}
			server->DisconnectProcess(client);
			continue;
		}

		//if (client->IsRecvOverLap(overlap)) RecvProcess(client, cbTransferred);
		//if (client->IsSendOverLap(overlap)) SendProcess(client, cbTransferred);
	}

	return false;
}

bool Server::cIOCP_SERVER::Initialize_Server()
{
	if (!(Socket::st_cSockManager::GetInstance()->TCP_Listen_Sock(&mServer)))
	{
		return false;
	}

	mPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);  // ����� �Ϸ� ��Ʈ ����
	if (mPort == NULL) return false;

	int count = IOCP_THREAD_COUNT;
	// i ���� �۾��� ������ ����
	for (int i = 0; i < IOCP_THREAD_COUNT; i++)
	{
		mProcess_thread[i] = new Utilities::cThread(IOCP_Process, this);
		if (mProcess_thread[i]->Run())
		{
			mProcess_thread[i]->Destroy();
			count--;
			delete mProcess_thread[i];
		}	
	}
	mLog.Record("CREATE IOCP PORT THREAD : ", count);

	return true;


}

void Server::cIOCP_SERVER::AcceptProcess(Socket::cSock* _Server)
{
}
