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
	int retval; //결과값 저장
	DWORD transferred; //전송량
	cClient* client;//클라언트
	LPOVERLAPPED overlap;//오버랩 받을 변수
	while (true)
	{
		retval = GetQueuedCompletionStatus(server->mPort, &transferred, (PULONG_PTR)&client, &overlap, INFINITE); //비동기 입출력이 완료되기를 기다림

		if (overlap == &server->mExit) return 1;

		if (retval == 0 || transferred == 0) //클라이언트 강제 종료
		{
			if (retval == 0)//비정상 종료
			{
				DWORD temp1, temp2;
				//WSAGetOverlappedResult(client->GetSock(), overlap, &temp1, FALSE, &temp2);//무슨 에러인지 확인
				Server::WSA_Err_display((TCHAR*)"WSAGetOverlappedResult()");//에러 출력
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

	mPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);  // 입출력 완료 포트 생성
	if (mPort == NULL) return false;

	int count = IOCP_THREAD_COUNT;
	// i 개의 작업자 스레드 생성
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
