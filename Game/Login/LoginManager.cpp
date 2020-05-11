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

	//DB Ȯ��
	if (!Run_SQL("select * from %s where mId = '%s' and mPw = '%s'", DB_TABLE_LOGIN, id, pw)) return false;
	//����� ����
	Get_Result(db_result);

	//������� �ϳ��� �ִٸ� �α��� ����
	if (db_result.Row_Count() > 0)
	{
		//true
		result = true;

		//���� ���(id,pw,code)
		_client->User() = Server::cUser(id, pw, (atoll(db_result.Current_Row("mCode"))));

	}

	//��� ��Ŷ ����
	Utilities::sBuffer buffer;
	buffer.Write(PROTOCOL::SERVER_RE_LOGIN);
	buffer.Write(result);


	//��� ����
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

	//DB id�ߺ� Ȯ��
	if (!Run_SQL("select * from %s where mId = '%s'", DB_TABLE_LOGIN, id)) result = false;
	//����� ����
	if(!Get_Result(db_result)) result = false;

	//�ߺ����� ������ ����
	if (db_result.Row_Count() == 0)
	{
		//������ ���
		if (!Run_SQL("insert into %s values('%s','%s',%lld)", DB_TABLE_LOGIN, id, pw, mMaker.Get_Code())) result = false;

	}

	//��� ��Ŷ ����
	Utilities::sBuffer buffer;
	buffer.Write(PROTOCOL::SERVER_RE_JOIN);
	buffer.Write(result);

	//��� ����
	_client->Send_Packet_Push(buffer);

	return result;
}

bool GAME::Login::cLoginManger::Req_LogOut(cGameClient* _client)
{
	return false;
}
