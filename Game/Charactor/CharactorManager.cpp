#include "CharactorManager.h"
#include "GameClient/GameClient.h"
#include "PROTOCOL.h"

using namespace Utilities::DB;

GAME::Charactor::cCharactorManager::cCharactorManager()
{
	Conncetion(DB_HOST, DB_ID, DB_PW, DB_NAME, DB_PORT);
	mLog.Connect("CHARACTOR_LOG.txt");
}

GAME::Charactor::cCharactorManager::~cCharactorManager()
{
	mLog.Close();
}

void GAME::Charactor::cCharactorManager::Req_Charactor_Info(GAME::cGameClient* _client)
{

	printf_s("IP: %s Req_Charactor_Info User_Code : %lld \n", _client->Get_IP(), _client->User().Code());

	cDB_Result db_result;

	//��� ��Ŷ ����
	Utilities::sBuffer buffer;
	buffer.Write(PROTOCOL::SERVER_RE_CHAR_INFO);

	if (Run_SQL("select * from %s where mUser_Code = %lld", DB_TABLE_CHAR, _client->User().Code()))
	{
		//����� ����
		Get_Result(db_result);
		buffer.Write(db_result.Row_Count());

		while (db_result.MoveNext())
		{
			//�����ڵ�, �г���
			buffer.Write(atoi(db_result.Now("mJob")));
			buffer.Write(db_result.Now("mName"));
		}		
	}

	_client->Send_Packet_Push(buffer);
	_client->WSA_Send_Packet();
}

void GAME::Charactor::cCharactorManager::Req_Create_Charactor(GAME::cGameClient* _client)
{

	printf_s("IP: %s Req_Create_Charactor User_Code : %lld \n", _client->Get_IP(), _client->User().Code());

	int jobcode;
	char nickname[NICK_NAME_SIZE];


	//�����ڵ�,�г���
	_client->RecvPacket().Read(jobcode);
	_client->RecvPacket().Read(nickname);



	bool result = false;

	//db�� ĳ���� insert
	Utilities::CODE code = mMaker.Get_Code();
	if (Run_SQL("insert into %s values(%lld,%lld,'%s',%d)", DB_TABLE_CHAR, code,_client->User().Code(),nickname,jobcode))
	{
		mLog.Record("IP: %s Create_Charactor User_Code : %lld Charactor(%lld,%d,%s)", _client->Get_IP(), _client->User().Code(), code, jobcode, nickname);
		result = true;
	}

	//��� ��Ŷ ����
	Utilities::sBuffer buffer;
	buffer.Write(PROTOCOL::SERVER_RE_CREATE_CHAR);
	buffer.Write(result);

	_client->Send_Packet_Push(buffer);
	_client->WSA_Send_Packet();

}

void GAME::Charactor::cCharactorManager::Req_Select_Charactor(GAME::cGameClient* _client)
{

	printf_s("IP: %s Req_Select_Charactor User_Code : %lld \n", _client->Get_IP(), _client->User().Code());

	//������ ĳ���� �̸�
	char nickname[NICK_NAME_SIZE];
	_client->RecvPacket().Read(nickname);

	bool result = false;




	//db��ȸ
	cDB_Result db_result;
	if (Run_SQL("select * from %s where mUser_Code = %lld and mName = '%s'", DB_TABLE_CHAR, _client->User().Code(), nickname))
	{

		Get_Result(db_result);

		//�����ڵ�,�г��� 
		db_result.MoveNext();


		mLog.Record("IP: %s Select_Charactor User_Code : %lld Charactor : %s)", _client->Get_IP(), _client->User().Code(), nickname);


		cCharactor* charactor = nullptr;

		switch (atoi(db_result.Now("mJob")))
		{
		case GAME::WARRIOR:
			charactor = new cWarrior(_client, atoll(db_result.Now("mCode")), nickname);
			break;
		case GAME::ARCHER:
			charactor = new cArcher(_client, atoll(db_result.Now("mCode")), nickname);
			break;
		case GAME::MAGICIAN:
			charactor = new cMagician(_client, atoll(db_result.Now("mCode")), nickname);
			break;
		}


		result = true;
	}


	Utilities::sBuffer buffer;
	buffer.Write(PROTOCOL::SERVER_RE_SELECT_CHAR);
	buffer.Write(result);
	if (result)
	{
		buffer.Write(atoi(db_result.Now("mJob")));
		buffer.Write(nickname);
	}

	//send
	_client->Send_Packet_Push(buffer);
	_client->WSA_Send_Packet();

}

void GAME::Charactor::cCharactorManager::Req_Delete_Charactor(GAME::cGameClient* _client)
{

	printf_s("IP: %s Req_Delete_Charactor User_Code : %lld \n", _client->Get_IP(), _client->User().Code());

	//������ ĳ���� �̸�
	char nickname[NICK_NAME_SIZE];
	_client->RecvPacket().Read(nickname);


	bool result = false;
	if (Run_SQL("delete from %s where mName='%s'",DB_TABLE_CHAR, nickname))
	{
		mLog.Record("IP: %s Delect_Charactor User_Code : %lld Charactor : %s)", _client->Get_IP(), _client->User().Code(), nickname);
		result = true;
	}


	Utilities::sBuffer buffer;
	buffer.Write(PROTOCOL::SERVER_RE_DELETE_CHAR);
	buffer.Write(result);

	//send
	_client->Send_Packet_Push(buffer);
	_client->WSA_Send_Packet();


}

void GAME::Charactor::cCharactorManager::Req_Out_Charactor(GAME::cGameClient* _client)
{
}
