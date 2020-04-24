#include "IOCP_Server.h"


Server::cIOCP_SERVER::cIOCP_SERVER()
{
	mPort = NULL;

}

Server::cIOCP_SERVER::~cIOCP_SERVER()
{
}

bool Server::cIOCP_SERVER::Create_Server()
{
	mPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);  // 입출력 완료 포트 생성
	if (mPort == NULL) return false;

	int count = IOCP_THREAD_COUNT;
	// i 개의 작업자 스레드 생성
	for (int i = 0; i < IOCP_THREAD_COUNT; i++)
	{
		mProcess_thread[i] = new Utilities::cThread(IOCP_Process, NULL);
		if (mProcess_thread[i]->Run())
		{
			mProcess_thread[j]->Destroy();
			count--;
			delete mProcess_thread[i];
		}

	
	}

	printf_s("")
	return true;

}
