#include "IOCP_Manager.h"



bool Server::cIOCP_Manager::IOCP_Process(LPVOID _iocp)
{
	cIOCP_Manager* iocp = (cIOCP_Manager*)_iocp;
	DWORD transferred; //���۷�
	cClient* client;//Ŭ���Ʈ
	LPOVERLAPPED overlap;//������ ���� ����
	BOOL retval = GetQueuedCompletionStatus(iocp->mPort, &transferred, (PULONG_PTR)&client, &overlap, INFINITE); //�񵿱� ������� �Ϸ�Ǳ⸦ ��ٸ�

	if (iocp->mExit) 
	{
		printf_s("recv exit overlap - Exit Process \n");
		return false;
	}

	if (retval == FALSE || transferred == 0) //Ŭ���̾�Ʈ ���� ����
	{

		//DWORD temp1, temp2;
		//WSAGetOverlappedResult(client->GetSock(), overlap, &temp1, FALSE, &temp2);//���� �������� Ȯ��
		//Server::WSA_Err_display((TCHAR*)"WSAGetOverlappedResult()");//���� ���
		return false;
		///*server->DisconnectProcess(client);*/
	}

	//if (client->IsRecvOverLap(overlap)) RecvProcess(client, cbTransferred);
	//if (client->IsSendOverLap(overlap)) SendProcess(client, cbTransferred);

	return true;
}

Server::cIOCP_Manager::cIOCP_Manager(int _thread_count)
{

	mPort = NULL;
	mExit = FALSE;
	if (_thread_count < 0)
	{
		// CPU ���� Ȯ��
		SYSTEM_INFO si;
		GetSystemInfo(&si);
		// (CPU ���� * 2)���� �۾��� ������ ����
		mThread_count = (int)(si.dwNumberOfProcessors * 2);
	}
	else
	{
		mThread_count = _thread_count;
	}
	mProcess_thread = new Utilities::cThread[mThread_count];
}

Server::cIOCP_Manager::~cIOCP_Manager()
{
	mLog.Close();
	delete[] mProcess_thread;
}

bool Server::cIOCP_Manager::Initialize_IOCP()
{
	mLog.Connect("IOCP_MANAGER.TXT");

	mPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);  // ����� �Ϸ� ��Ʈ ����
	if (mPort == NULL) return false;


	// i ���� �۾��� ������ ����
	for (int i = 0; i < mThread_count; i++)
	{
		mProcess_thread[i].Create(IOCP_Process, this,true,false);
	}

	mLog.Record("CREATE IOCP PORT THREAD : %d", mThread_count);

	return true;


}

void Server::cIOCP_Manager::End_IOCP()
{
	mExit = TRUE;
	PostQueuedCompletionStatus(mPort, 1, NULL, 0);
	CloseHandle(mPort);
	mPort = NULL;
}

void Server::cIOCP_Manager::AcceptProcess(Socket::cSock* _Server)
{
}
