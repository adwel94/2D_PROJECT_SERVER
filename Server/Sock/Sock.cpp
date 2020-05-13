#include "Sock.h"


Server::Socket::cSock::cSock()
{
	mSock = NULL; //소켓 초기화
	ZeroMemory(&mAddr, sizeof(SOCKADDR_IN)); //주소 메모리 초기화
	mIp[0] = '\0';
}

Server::Socket::cSock::cSock(SOCKET _sock, const SOCKADDR_IN& _addr)
{
	mSock = _sock;//소켓 대입
	memcpy(&mAddr, &_addr, sizeof(SOCKADDR_IN)); //주소 복사

	//결과 메세지
	inet_ntop(AF_INET, &mAddr.sin_addr, mIp, sizeof(mIp));
	printf_s("Create Socket : IP : %s, PORT : %d \n", mIp, ntohs(mAddr.sin_port));
}

Server::Socket::cSock::~cSock()
{
	if (mSock != NULL)closesocket(mSock);
	
}

const char* Server::Socket::cSock::Get_IP()
{
	return mIp;
}

bool Server::Socket::cSock::Start(IP_VER _af, SOCKTYPE _socktype, int _pro, int _port , const char* _addr)
{
	if (mSock != NULL)
	{
		printf_s("Socket already create()\n");
		return false;
	}

	mSock = socket(_af, _socktype, _pro);

	if (mSock == INVALID_SOCKET)
	{
		WSA_Err_display("Socket()");
	}

	ZeroMemory(&mAddr, sizeof(mAddr));
	mAddr.sin_family = _af; //ip 버젼

	//주소를 따로 입력하지않으면 localhost
	if (strlen(_addr) == 0)
	{
		mAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	}
	else
	{
		inet_pton(_af, _addr, &mAddr.sin_addr);
	}
	//포트 등록
	mAddr.sin_port = htons(_port);

	//결과 메세지
	inet_ntop(AF_INET, &mAddr.sin_addr, mIp, sizeof(mIp));
	printf_s("Create Socket : IP : %s, PORT : %d \n", mIp, ntohs(mAddr.sin_port));

	return true;
}

void Server::Socket::cSock::End()
{
	closesocket(mSock);
	mSock = NULL;

	printf_s("Close Socket : IP : %s, PORT : %d \n", mIp, ntohs(mAddr.sin_port));
	
}

bool Server::Socket::cSock::Send(BYTE* _buf, int _size, int _flag)
{
	int sendbyte;
	char* ptr = (char*)_buf;
	int left = _size;

	while (left > 0) {//보낸 메모리가 남아있으면
		sendbyte = send(mSock, ptr, left, _flag);//send
		if (sendbyte == SOCKET_ERROR)//에러체크
		{
			WSA_Err_display("send()");
			return false;//에러반환
		}
		else if (sendbyte == 0)
		{
			break;//반복문 탈출
		}

		left -= sendbyte;//목표 메모리에서 실제가져온 용량만큼 빼서 저장
		ptr += sendbyte;//받음만큼 주소를 이동시킴 데이터를 이어받기 위해
	}

	return true;
}

bool Server::Socket::cSock::WSA_Send(LPWSABUF _wsabuf, DWORD _buffercount, LPDWORD _sendbyte, DWORD _flag, LPWSAOVERLAPPED _overlap, LPWSAOVERLAPPED_COMPLETION_ROUTINE _routine)
{

	int retval = WSASend(mSock, _wsabuf, _buffercount, _sendbyte, _flag, _overlap, _routine);
	if (retval == SOCKET_ERROR) {
		if (WSAGetLastError() != WSA_IO_PENDING) {
			WSA_Err_display("WSA_Send() WSA_IO_PENDING");
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

	while (left > 0) {//받을 메모리가 남아있다면
		received = recv(mSock, ptr, left, _flag);//데이터를 수신버퍼에서 가져옴
		if (received == SOCKET_ERROR)//에러체크
		{
			WSA_Err_display("recv()");
			return false;//에러반환
		}			
		else if (received == 0)//종료체크
		{
			break;//반복문 탈출
		}
			
		left -= received;//목표 메모리에서 실제가져온 용량만큼 빼서 저장
		ptr += received;//받음만큼 주소를 이동시킴 데이터를 이어받기 위해
	}

	return true;
}

bool Server::Socket::cSock::WSA_Recv(LPWSABUF _wsabuf, DWORD _buffercount, LPDWORD _recvbyte, LPDWORD _flag, LPWSAOVERLAPPED _overlap, LPWSAOVERLAPPED_COMPLETION_ROUTINE _routine)
{
	DWORD recvbytes, flags = 0;
	int retval = WSARecv(mSock, _wsabuf, _buffercount, _recvbyte, _flag, _overlap, NULL);
	if (retval == SOCKET_ERROR) {
		if (WSAGetLastError() != WSA_IO_PENDING) {
			WSA_Err_display("WSA_Recv() WSA_IO_PENDING");
		}
		return false;
	}
	return true;
}
