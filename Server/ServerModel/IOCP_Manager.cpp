#include "IOCP_Manager.h"


template <class T>
bool Server::cIOCP_Manager<T>::IOCP_Process(LPVOID _iocp)
{
	cIOCP_Manager* iocp = (cIOCP_Manager*)_iocp;
	DWORD transferred; //전송량
	T key;//클라언트
	LPOVERLAPPED overlap;//오버랩 받을 변수	
	while (true)
	{
		BOOL retval = GetQueuedCompletionStatus(iocp->mPort, &transferred, (PULONG_PTR)&key, &overlap, INFINITE); //비동기 입출력이 완료되기를 기다림
		if (retval == FALSE) //클라이언트 강제 종료
		{
			iocp->ErrorProcess(key, overlap,transferred);
			//종료 on
			if (iocp->mExit)
			{
				printf_s("recv exit overlap - Exit Process \n");
				return true;
			}
		}
		else if (transferred == 0) //종료 패킷
		{
			iocp->DisconnectProcess(key, overlap, transferred);
		}

		iocp->CompletionProcess(key, overlap, transferred);
	}
	return true;
}

template<class T>
Server::cIOCP_Manager<T>::cIOCP_Manager(int _thread_count)
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

template<class T>
Server::cIOCP_Manager<T>::~cIOCP_Manager()
{
	mLog.Close();
	delete[] mProcess_thread;
}

template<class T>
bool Server::cIOCP_Manager<T>::Initialize_IOCP()
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

template<class T>
void Server::cIOCP_Manager<T>::Accpet_Port(SOCKET _sock, T _key)
{
	CreateIoCompletionPort((HANDLE)_sock, mPort, (ULONG_PTR)_key, 0);//포트에 클라이언트 연결 컴플리션키는 클라이언트 객체로
	AcceptProcess(_key);
}

template<class T>
void Server::cIOCP_Manager<T>::End_IOCP()
{
	mExit = TRUE;
	PostQueuedCompletionStatus(mPort, 1, NULL, 0);
	CloseHandle(mPort);
	mPort = NULL;

	mLog.Record("END IOCP -------------------");
}
