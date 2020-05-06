#include "IOCP_Manager.h"


template <class T>
bool Server::cIOCP_Manager<T>::IOCP_Process(LPVOID _iocp)
{
	cIOCP_Manager* iocp = (cIOCP_Manager*)_iocp;
	DWORD transferred; //���۷�
	T key;//Ŭ���Ʈ
	LPOVERLAPPED overlap;//������ ���� ����	
	while (true)
	{
		BOOL retval = GetQueuedCompletionStatus(iocp->mPort, &transferred, (PULONG_PTR)&key, &overlap, INFINITE); //�񵿱� ������� �Ϸ�Ǳ⸦ ��ٸ�
		if (retval == FALSE) //Ŭ���̾�Ʈ ���� ����
		{
			iocp->ErrorProcess(key, overlap,transferred);
			//���� on
			if (iocp->mExit)
			{
				printf_s("recv exit overlap - Exit Process \n");
				return true;
			}
		}
		else if (transferred == 0) //���� ��Ŷ
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

template<class T>
void Server::cIOCP_Manager<T>::Accpet_Port(SOCKET _sock, T _key)
{
	CreateIoCompletionPort((HANDLE)_sock, mPort, (ULONG_PTR)_key, 0);//��Ʈ�� Ŭ���̾�Ʈ ���� ���ø���Ű�� Ŭ���̾�Ʈ ��ü��
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
