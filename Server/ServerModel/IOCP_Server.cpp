#include "IOCP_Server.h"


bool Server::cIOCP_SERVER::Create_Server()
{
	mPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);  // 입출력 완료 포트 생성
	if (mPort == NULL) return false;

	// i 개의 작업자 스레드 생성
jp	for (int i = 0; i < IOCP_THREAD_COUNT; i++)
	{
		mProcess_thread[i] = new Utilities::cThread(IOCP_Process, NULL);
		if (mProcess_thread[i] == NULL)
		{
			for (int j = i; j < 0; j--)
			{
				mProcess_thread[j]->Destroy();
				return false;
			}
		}
	}
	return true;

}
