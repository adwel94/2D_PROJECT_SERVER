#include "Sock.h"


Server::Socket::cSock::cSock()
{
	mSock = NULL; //���� �ʱ�ȭ
	ZeroMemory(&mAddr, sizeof(SOCKADDR_IN)); //�ּ� �޸� �ʱ�ȭ
}

Server::Socket::cSock::cSock(SOCKET _sock, const SOCKADDR_IN& _addr)
{
	mSock = _sock;//���� ����
	memcpy(&mAddr, &_addr, sizeof(SOCKADDR_IN)); //�ּ� ����
}

Server::Socket::cSock::cSock(IP_VER _af, SOCKTYPE _socktype, int _pro, int _port, const char* _addr)
{
	mSock = socket(_af, _socktype, _pro);
	if (mSock == INVALID_SOCKET)
	{
		WSA_Err_display((TCHAR*)"Socket()");
	}

	ZeroMemory(&mAddr, sizeof(mAddr));
	mAddr.sin_family = _af; //ip ����

	//�ּҸ� ���� �Է����������� localhost
	if (strlen(_addr) == 0)
	{
		mAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	}
	else
	{
		inet_pton(_af, _addr, &mAddr.sin_addr);
	}
	//��Ʈ ���
	mAddr.sin_port = htons(_port);

	char addr[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &mAddr.sin_addr, addr, sizeof(addr));
	printf_s("Create Socket : IP : %s, PORT : %d \n", addr, ntohs(mAddr.sin_port));
}

Server::Socket::cSock::~cSock()
{
	closesocket(mSock);
}

bool Server::Socket::cSock::Send(BYTE* _buf, int _size, int _flag)
{
	int sendbyte;
	char* ptr = (char*)_buf;
	int left = _size;

	while (left > 0) {//���� �޸𸮰� ����������
		sendbyte = send(mSock, ptr, left, _flag);//send
		if (sendbyte == SOCKET_ERROR)//����üũ
		{
			WSA_Err_display((TCHAR*)"send()");
			return false;//������ȯ
		}
		else if (sendbyte == 0)
		{
			break;//�ݺ��� Ż��
		}

		left -= sendbyte;//��ǥ �޸𸮿��� ���������� �뷮��ŭ ���� ����
		ptr += sendbyte;//������ŭ �ּҸ� �̵���Ŵ �����͸� �̾�ޱ� ����
	}

	return true;
}

bool Server::Socket::cSock::WSA_Send(LPWSABUF _wsabuf, DWORD _buffercount, LPDWORD _sendbyte, DWORD _flag, LPWSAOVERLAPPED _overlap, LPWSAOVERLAPPED_COMPLETION_ROUTINE _routine)
{

	int retval = WSASend(mSock, _wsabuf, _buffercount, _sendbyte, _flag, _overlap, _routine);
	if (retval == SOCKET_ERROR) {
		if (WSAGetLastError() != WSA_IO_PENDING) {
			WSA_Err_display((TCHAR*)"WSA_Send() WSA_IO_PENDING");
		}
		return false;
	}
	return true;
}

bool Server::Socket::cSock::Recv(BYTE* _buf, int _size, int _flag)
{
	int received;
	char* ptr = (char*)_buf;
	int left = _size;

	while (left > 0) {//���� �޸𸮰� �����ִٸ�
		received = recv(mSock, ptr, left, _flag);//�����͸� ���Ź��ۿ��� ������
		if (received == SOCKET_ERROR)//����üũ
		{
			WSA_Err_display((TCHAR*)"recv()");
			return false;//������ȯ
		}			
		else if (received == 0)//����üũ
		{
			break;//�ݺ��� Ż��
		}
			
		left -= received;//��ǥ �޸𸮿��� ���������� �뷮��ŭ ���� ����
		ptr += received;//������ŭ �ּҸ� �̵���Ŵ �����͸� �̾�ޱ� ����
	}

	return true;
}

bool Server::Socket::cSock::WSA_Recv(LPWSABUF _wsabuf, DWORD _buffercount, LPDWORD _recvbyte, LPDWORD _flag, LPWSAOVERLAPPED _overlap, LPWSAOVERLAPPED_COMPLETION_ROUTINE _routine)
{
	DWORD recvbytes, flags = 0;
	int retval = WSARecv(mSock, _wsabuf, _buffercount, _recvbyte, _flag, _overlap, NULL);
	if (retval == SOCKET_ERROR) {
		if (WSAGetLastError() != WSA_IO_PENDING) {
			WSA_Err_display((TCHAR*)"WSA_Recv() WSA_IO_PENDING");
		}
		return false;
	}
	return true;
}