#include "LoginManager.h"
#include "Game.h"
bool GAME::Login::cLoginManger::Req_Login(Server::cClient* _client)
{
	char id[ID_SIZE];
	char pw[PW_SIZE];



	_client->RecvBuf().Read(id);
	_client->RecvBuf().Read(pw);

	//DB 데이터 확인



	//결과 전송



	return false;
}
