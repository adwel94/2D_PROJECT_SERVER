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
				Utilities::DS::cLockIterator<__int64> iter(&mLoginList);
				while (iter.HasNext())
				{

					if (iter.Next() == atoll(db_result.Now("mCode")))
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
				mLoginList.LockAdd(atoll(db_result.Now("mCode")));
				_client->User() = Server::cUser(id, pw, (atoll(db_result.Now("mCode"))));
			}
		}
	}


	//��� ��Ŷ ����
	Utilities::sBuffer buffer;
	buffer.Write(PROTOCOL::SERVER_RE_LOGIN);
	buffer.Write(result);


	//��� ����
	printf_s("IP: %s Login_Result (%s,%s) %s \n", _client->Get_IP(), id, pw,(result ? "Success" : "Fail"));
	mLog.Record("IP: %s Login_Result (%s,%s) %s ", _client->Get_IP(), id, pw, (result ? "Success" : "Fail"));

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

	//������ ��� �ߺ��Ǹ� false
	if (!Run_SQL("insert into %s values('%s','%s',%lld)", DB_TABLE_LOGIN, id, pw, mMaker.Get_Code())) 
	{
		result = false;
	}

	printf_s("IP: %s Join_Result (%s,%s) %s \n", _client->Get_IP(), id, pw, (result ? "Success" : "Fail"));
	mLog.Record("IP: %s Join_Result (%s,%s) %s", _client->Get_IP(), id, pw, (result ? "Success" : "Fail"));

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
	if (_client->User().Code() == 0) return true;

	//�α��� ���� ����
	mLoginList.LockRemove(_client->User().Code());
	//user �ʱ�ȭ
	_client->User() = Server::cUser();

	return true;
}
