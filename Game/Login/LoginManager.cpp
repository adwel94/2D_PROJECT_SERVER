#include "LoginManager.h"
#include "Game.h"
#include "PROTOCOL.h"


using namespace Utilities::DB;

GAME::Login::cLoginManger::cLoginManger()
{
	Conncetion(DB_HOST, DB_ID, DB_PW, DB_NAME, DB_PORT);
	mLog.Connect("LOGIN_LOG.txt");
}

GAME::Login::cLoginManger::~cLoginManger()
{
	Close();
	mLog.Close();
}

bool GAME::Login::cLoginManger::Req_Login(cGameClient* _client)
{
	char id[ID_SIZE];
	char pw[PW_SIZE];

	_client->RecvPacket().Read(id);
	_client->RecvPacket().Read(pw);

	printf_s("IP: %s Req_Login (%s,%s) \n", _client->Get_IP(), id, pw);

	bool result = false;
	cDB_Result db_result;

	//DB 확인
	if (!Run_SQL("select * from %s where mId = '%s' and mPw = '%s'", DB_TABLE_LOGIN, id, pw)) return false;
	//결과값 저장
	Get_Result(db_result);

	//결과값이 하나라도 있다면 로그인 성공
	if (db_result.Row_Count() > 0)
	{
		//true
		result = true;

		//유저 등록(id,pw,code)
		_client->User() = Server::cUser(id, pw, (atoll(db_result.Current_Row("mCode"))));

	}

	//결과 패킷 생성
	Utilities::sBuffer buffer;
	buffer.Write(PROTOCOL::SERVER_RE_LOGIN);
	buffer.Write(result);


	//결과 전송
	if (result) printf_s("IP: %s Login_Success (%s,%s) \n", _client->Get_IP(), id, pw);
	_client->Send_Packet_Push(buffer);
	_client->WSA_Send_Packet();

	
	return result;
}

bool GAME::Login::cLoginManger::Req_Join(cGameClient* _client)
{
	char id[ID_SIZE];
	char pw[PW_SIZE];

	_client->RecvPacket().Read(id);
	_client->RecvPacket().Read(pw);

	printf_s("IP: %s Req_Join (%s,%s) \n", _client->Get_IP(), id, pw);

	bool result = true;
	cDB_Result db_result;

	//DB id중복 확인
	if (!Run_SQL("select * from %s where mId = '%s'", DB_TABLE_LOGIN, id)) result = false;
	//결과값 저장
	if(!Get_Result(db_result)) result = false;

	//중복값이 없으면 성공
	if (db_result.Row_Count() == 0)
	{
		//쿼리에 등록
		if (!Run_SQL("insert into %s values('%s','%s',%lld)", DB_TABLE_LOGIN, id, pw, mMaker.Get_Code())) result = false;

	}

	//결과 패킷 생성
	Utilities::sBuffer buffer;
	buffer.Write(PROTOCOL::SERVER_RE_JOIN);
	buffer.Write(result);

	//결과 전송
	_client->Send_Packet_Push(buffer);

	return result;
}

bool GAME::Login::cLoginManger::Req_LogOut(cGameClient* _client)
{
	return false;
}
