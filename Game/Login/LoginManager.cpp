#include "LoginManager.h"
#include "Game.h"
#include "DS/LockIterator.h"
#include "PROTOCOL.h"


using namespace Utilities::DB;

GAME::Login::cLoginManger::cLoginManger()
{
	Conncetion(DB_HOST, DB_ID, DB_PW, DB_NAME, DB_PORT);
	mLog.Connect("LOGIN_LOG.txt");
}

GAME::Login::cLoginManger::~cLoginManger()
{
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
	if (Run_SQL("select * from %s where mId = '%s' and mPw = '%s'", DB_TABLE_LOGIN, id, pw))
	{
		//����� ����
		Get_Result(db_result);
		//������� �ִٸ�
		if (db_result.Row_Count() > 0)
		{
			db_result.MoveNext();
			bool overlap = false;//�α����ߺ�

			{
				//�̹� �α��� �������� Ȯ��
				Utilities::DS::cLockIterator<Utilities::CODE> iter(&mLoginList);
				while (iter.HasNext())
				{

					if (iter.Next() == strtoull(db_result.Now("mCode"),NULL,0))
					{
						overlap = true;
						break;
					}
				}
			}//lock������ ��ȣ

			//�α��ε� ������ ���ٸ�
			if (overlap == false)
			{
				result = true;

				//���� ���(id,pw,code)
				mLoginList.LockAdd(strtoull(db_result.Now("mCode"), NULL, 0));
				_client->User() = Server::cUser(id, pw, (strtoull(db_result.Now("mCode"), NULL, 0)));
				mLog.Record("IP: %s Login (%s,%s)", _client->Get_IP(), id, pw);
			}
		}
	}


	//��� ��Ŷ ����
	Utilities::sBuffer buffer;
	buffer.Write(PROTOCOL::SERVER_RE_LOGIN);
	buffer.Write(result);


	//��� ����
	printf_s("IP: %s Login_Result (%s,%s) %s \n", _client->Get_IP(), id, pw,(result ? "Success" : "Fail"));


	_client->Send_Packet_Push(buffer);
	_client->WSA_Send_Packet();

	
	return result;
}

//ȸ������ ��û
bool GAME::Login::cLoginManger::Req_Join(cGameClient* _client)
{
	char id[ID_SIZE];
	char pw[PW_SIZE];

	_client->RecvPacket().Read(id);
	_client->RecvPacket().Read(pw);

	printf_s("IP: %s Req_Join (%s,%s) \n", _client->Get_IP(), id, pw);

	bool result = false;
	cDB_Result db_result;

	//������ ��� �ߺ��Ǹ� false
	if (Run_SQL("insert into %s values(%llu,'%s','%s')", DB_TABLE_LOGIN, mMaker.Get_Code(),id, pw))
	{
		result = true;
		mLog.Record("IP: %s Join (%s,%s)", _client->Get_IP(), id, pw);
	}

	printf_s("IP: %s Join_Result (%s,%s) %s \n", _client->Get_IP(), id, pw, (result ? "Success" : "Fail"));


	//��� ��Ŷ ����
	Utilities::sBuffer buffer;
	buffer.Write(PROTOCOL::SERVER_RE_JOIN);
	buffer.Write(result);

	//��� ����
	_client->Send_Packet_Push(buffer);
	_client->WSA_Send_Packet();

	return result;
}

bool GAME::Login::cLoginManger::Req_LogOut(cGameClient* _client)
{
	LogOut(_client);
	return true;
}

void GAME::Login::cLoginManger::LogOut(cGameClient* _client)
{
	if (_client->User().Code() == 0) return;

	printf_s("IP: %s LogOut (%s,%s)\n", _client->Get_IP(), _client->User().Id(), _client->User().Pw());
	mLog.Record("IP: %s LogOut (%s,%s)", _client->Get_IP(), _client->User().Id(), _client->User().Pw());
	//�α��� ���� ����
	mLoginList.LockRemove(_client->User().Code());
	//user �ʱ�ȭ
	_client->User() = Server::cUser();
}
