#include "CharactorManager.h"
#include "GameClient/GameClient.h"
#include "PROTOCOL.h"
#include"Map/Town.h"
#include "Map/MapManager.h"
#include "Party/PartyManager.h"

using namespace Utilities::DB;

GAME::Charactor::cCharactorManager::cCharactorManager()
{
	//캐릭터 DB, 로그 연결
	Conncetion(DB_HOST, DB_ID, DB_PW, DB_NAME, DB_PORT);
	mLog.Connect("CHARACTOR_LOG.txt");
}

GAME::Charactor::cCharactorManager::~cCharactorManager()
{
	//DB, 로그 커넥션 해제
	Close();
	mLog.Close();
}


//캐릭터 정보 요청
bool GAME::Charactor::cCharactorManager::Req_Charactor_Info(GAME::cGameClient* _client)
{

	printf_s("IP: %s Req_Charactor_Info User_Code : %llu \n", _client->Get_IP(), _client->User().Code());
	mLog.Record("IP: %s Req_Charactor_Info User_Code : %llu", _client->Get_IP(), _client->User().Code());

	cDB_Result db_result;

	//결과 패킷 생성
	Utilities::sBuffer buffer;
	buffer.Write(PROTOCOL::SERVER_RE_CHAR_INFO);

	//유저 정보로 캐릭터 조회
	if (Run_SQL("select * from %s where mUser_Code = %llu", DB_TABLE_CHAR, _client->User().Code()))
	{
		//결과값 저장
		Get_Result(db_result);
		buffer.Write(db_result.Row_Count());

		
		while (db_result.MoveNext())
		{
			//직업코드, 닉네임, 레벨
			buffer.Write(db_result.Now("mName"));
			buffer.Write(atoi(db_result.Now("mJob")));
			buffer.Write(atoi(db_result.Now("mLevel")));
		}		
	}
	else
	{
		return false;
	}

	_client->Send_Packet_Push(buffer);
	_client->WSA_Send_Packet();

	return true;
}


//캐릭터 생성
bool GAME::Charactor::cCharactorManager::Req_Create_Charactor(GAME::cGameClient* _client)
{

	printf_s("IP: %s Req_Create_Charactor User_Code : %llu \n", _client->Get_IP(), _client->User().Code());
	mLog.Record("IP: %s Req_Create_Charactor User_Code : %llu", _client->Get_IP(), _client->User().Code());

	int jobcode;
	char nickname[NICK_NAME_SIZE];


	//직업코드,닉네임
	_client->RecvPacket().Read(jobcode);
	_client->RecvPacket().Read(nickname);



	bool result = false;

	//db에 캐릭터 insert
	Utilities::CODE code = mMaker.Get_Code();
	if (Run_SQL("insert into %s values(%llu,%llu,'%s',%d,1)", DB_TABLE_CHAR, code,_client->User().Code(),nickname,jobcode))
	{
		printf_s("IP: %s Create_Charactor User_Code : %llu Charactor(%llu,%d,%s) \n", _client->Get_IP(), _client->User().Code(), code, jobcode, nickname);
		mLog.Record("IP: %s Create_Charactor User_Code : %llu Charactor(%llu,%d,%s)", _client->Get_IP(), _client->User().Code(), code, jobcode, nickname);
		result = true;
	}


	//결과 패킷 생성
	Utilities::sBuffer buffer;
	buffer.Write(PROTOCOL::SERVER_RE_CREATE_CHAR);
	buffer.Write(result);

	_client->Send_Packet_Push(buffer);
	_client->WSA_Send_Packet();

	return result;
}

bool GAME::Charactor::cCharactorManager::Req_Select_Charactor(GAME::cGameClient* _client)
{

	printf_s("IP: %s Req_Select_Charactor User_Code : %llu \n", _client->Get_IP(), _client->User().Code());
	mLog.Record("IP: %s Req_Select_Charactor User_Code : %llu", _client->Get_IP(), _client->User().Code());

	//선택한 캐릭터 이름
	char nickname[NICK_NAME_SIZE];
	_client->RecvPacket().Read(nickname);

	bool result = false;


	//db조회
	cDB_Result db_result;
	if (Run_SQL("select * from %s where mUser_Code = %llu and mName = '%s'", DB_TABLE_CHAR, _client->User().Code(), nickname))
	{

		Get_Result(db_result);

		//직업코드,닉네임 
		db_result.MoveNext();


		mLog.Record("IP: %s Select_Charactor User_Code : %llu Charactor : %s)", _client->Get_IP(), _client->User().Code(), nickname);


		cCharactor* charactor = nullptr;

		//코드에 따라 캐릭터 생성
		switch (atoi(db_result.Now("mJob")))
		{
		case GAME::CODE::JOB::WARRIOR:
			charactor = new cWarrior(_client, strtoull(db_result.Now("mCode"),NULL,10), nickname);
			break;
		case GAME::CODE::JOB::ARCHER:
			//charactor = new cArcher(_client, strtoull(db_result.Now("mCode"), NULL, 10), nickname);
			break;
		case GAME::CODE::JOB::MAGICIAN:
			//charactor = new cMagician(_client, strtoull(db_result.Now("mCode"), NULL, 10), nickname);
			break;
		default:
			charactor = new cWarrior(_client, strtoull(db_result.Now("mCode"), NULL, 10), nickname);
			break;
		}
		

		charactor->mLevel = atoi(db_result.Now("mLevel"));
		_client->Set_Charactor(charactor);
		result = true;
	}

	//결과 패킹
	Utilities::sBuffer buffer;
	buffer.Write(PROTOCOL::SERVER_RE_SELECT_CHAR);
	buffer.Write(result);
	if (result)
	{
		buffer.Write(_client->Get_Charactor()->Code());
		buffer.Write(_client->Get_Charactor()->JobCode());
		buffer.Write(_client->Get_Charactor()->mLevel);
	}

	//send
	_client->Send_Packet_Push(buffer);
	_client->WSA_Send_Packet();


	return result;
}

bool GAME::Charactor::cCharactorManager::Req_Delete_Charactor(GAME::cGameClient* _client)
{

	printf_s("IP: %s Req_Delete_Charactor User_Code : %llu \n", _client->Get_IP(), _client->User().Code());

	//삭제할 캐릭터 이름
	char nickname[NICK_NAME_SIZE];
	_client->RecvPacket().Read(nickname);


	bool result = false;
	if (Run_SQL("delete from %s where mName='%s'",DB_TABLE_CHAR, nickname))
	{
		mLog.Record("IP: %s Delect_Charactor User_Code : %llu Charactor : %s)", _client->Get_IP(), _client->User().Code(), nickname);
		result = true;
	}


	Utilities::sBuffer buffer;
	buffer.Write(PROTOCOL::SERVER_RE_DELETE_CHAR);
	buffer.Write(result);


	//send
	_client->Send_Packet_Push(buffer);
	_client->WSA_Send_Packet();

	return result;


}

//bool GAME::Charactor::cCharactorManager::Req_Out_Charactor(GAME::cGameClient* _client)
//{
//	//세이브
//	//파티 out
//	//맵 out
//
//	return true;
//}

void GAME::Charactor::cCharactorManager::Exit_Charactor(cCharactor* _char)
{
	//자신이 있던 파티에서 나옴
	Party::st_cPartyManager::GetInstance()->Exit_Charactor(_char);
	//자신이있던 맵에서 나옴
	Map::st_cMapManager::GetInstance()->Exit_Charactor(_char);
	//레벨 업데이트
	Run_SQL("update %s set mLevel = %d where mCode = %llu", DB_TABLE_CHAR, _char->mLevel, _char->Code());
}

void GAME::Charactor::cCharactorManager::Save_Charactor(cCharactor* _char)
{
	Run_SQL("update %s set mLevel = %d where mCode = %llu", DB_TABLE_CHAR, _char->mLevel, _char->Code());
}

