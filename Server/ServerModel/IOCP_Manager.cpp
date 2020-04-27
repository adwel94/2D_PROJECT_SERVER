#include "IOCP_Manager.h"



bool Server::cIOCP_Manager::IOCP_Process(LPVOID _iocp)
{
	cIOCP_Manager* iocp = (cIOCP_Manager*)_iocp;
	DWORD transferred; //전송량
	cClient* client;//클라언트
	LPOVERLAPPED overlap;//오버랩 받을 변수
	BOOL retval = GetQueuedCompletionStatus(iocp->mPort, &transferred, (PULONG_PTR)&client, &overlap, INFINITE); //비동기 입출력이 완료되기를 기다림

	if (iocp->mExit) 
	{
		printf_s("recv exit overlap - Exit Process \n");
		return false;
	}

	if (retval == FALSE || transferred == 0) //클라이언트 강제 종료
	{

		//DWORD temp1, temp2;
		//WSAGetOverlappedResult(client->GetSock(), overlap, &temp1, FALSE, &temp2);//무슨 에러인지 확인
		//Server::WSA_Err_display((TCHAR*)"WSAGetOverlappedResult()");//에러 출력
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
		// CPU 개수 확인
		SYSTEM_INFO si;
		GetSystemInfo(&si);
		// (CPU 개수 * 2)개의 작업자 스레드 생성
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

	mPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);  // 입출력 완료 포트 생성
	if (mPort == NULL) return false;


	// i 개의 작업자 스레드 생성
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
