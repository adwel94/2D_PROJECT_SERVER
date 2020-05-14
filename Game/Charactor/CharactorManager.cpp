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

	//결과 패킷 생성
	Utilities::sBuffer buffer;
	buffer.Write(PROTOCOL::SERVER_RE_CHAR_INFO);

	if (Run_SQL("select * from %s where mUser_Code = %lld", DB_TABLE_CHAR, _client->User().Code()))
	{
		//결과값 저장
		Get_Result(db_result);
		buffer.Write(db_result.Row_Count());

		while (db_result.MoveNext())
		{
			//직업코드, 닉네임
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


	//직업코드,닉네임
	_client->RecvPacket().Read(jobcode);
	_client->RecvPacket().Read(nickname);


	bool result = false;

	if (Run_SQL("insert into %s values(%lld,%lld,'%s',%d)", DB_TABLE_CHAR, mMaker.Get_Code(),_client->User().Code(),nickname,jobcode))
	{
		result = true;
	}

	//결과 패킷 생성
	Utilities::sBuffer buffer;
	buffer.Write(PROTOCOL::SERVER_RE_CREATE_CHAR);
	buffer.Write(result);

	_client->Send_Packet_Push(buffer);
	_client->WSA_Send_Packet();

}

void GAME::Charactor::cCharactorManager::Req_Select_Charactor(GAME::cGameClient* _client)
{
}

void GAME::Charactor::cCharactorManager::Req_Delete_Charactor(GAME::cGameClient* _client)
{
}

void GAME::Charactor::cCharactorManager::Req_Out_Charactor(GAME::cGameClient* _client)
{
}
