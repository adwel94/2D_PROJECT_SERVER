#include "DungeonManager.h"
#include "Monster/Monster.h"
#include "Monster/cGiantEyes.h"
#include "Monster/cGoblin.h"
#include "CodeMaker/CodeMaker.h"
#include "XML/include/tinyxml.h"
#include "GameClient/GameClient.h"
#include "Party/PartyManager.h"
#include "MapManager.h"
#include "Math/Vector2D.h"
#include "DS/LockIterator.h"
#include "PROTOCOL.h"


GAME::Map::cDungeonManager::cDungeonManager()
{
	mLog.Connect("DUNGEON_LOG.txt");
}

GAME::Map::cDungeonManager::~cDungeonManager()
{
	mLog.Close();
}

GAME::Map::cDungeon* GAME::Map::cDungeonManager::CreateDungeon()
{

	cDungeon* dungeon = new cDungeon(mMaker.Get_Code());


	//XML 로드
	TiXmlDocument xml;
	if (xml.LoadFile("Dungeon.xml"))
	{
		//루트 <Dungeon>
		TiXmlElement* root = xml.RootElement();
		//몬스터 <Mob>
		TiXmlElement* monster = root->FirstChildElement();

		//몬스터 리스트
		while (monster)
		{
			TiXmlAttribute* attribute = monster->FirstAttribute();

			Monster::cMonster* mob = nullptr;;
			Monster::sMobStat stat;

			//몬스터의 타입
			int type = attribute->IntValue();
			attribute = attribute->Next();
			//좌표 x
			float x = attribute->DoubleValue();
			attribute = attribute->Next();
			//좌표 y
			float y = attribute->DoubleValue();
			attribute = attribute->Next();
			//Left_max
			float left_max = attribute->DoubleValue();
			attribute = attribute->Next();
			//Right_max
			float right_max = attribute->DoubleValue();
			attribute = attribute->Next();

			switch (type)
			{
			case CODE::MOB::GOBLIN_ARCHER:
				mob = new Monster::cGoblin(mMaker.Get_Code(), left_max, right_max, x, y, dungeon);
				break;
			case CODE::MOB::GIANT_EYES:
				mob = new Monster::cGiantEyes(mMaker.Get_Code(), left_max, right_max, x, y, dungeon);
				break;
			default:
				break;
			}

			dungeon->Add_Monster(mob);
			monster = monster->NextSiblingElement();
		}
	}

	//던전 스레드 시작
	dungeon->Start();
	printf_s("Create Dungeon Coed : %llu Monster Count : %d \n",dungeon->Code(),(int)dungeon->MobList().LockSize());
	mLog.Record("Create Dungeon Coed : %llu Monster Count : %d", dungeon->Code(), (int)dungeon->MobList().LockSize());
	return dungeon;
}

bool GAME::Map::cDungeonManager::Req_Enter_Dungeon(cGameClient* _client)
{
	Charactor::cCharactor* charactor = _client->Get_Charactor();

	printf_s("IP: %s Req_Enter_Dungeon Charactor Code : %llu  \n", _client->Get_IP(), charactor->Code());
	mLog.Record("IP: %s Req_Enter_Dungeon Charactor Code : %llu", _client->Get_IP(), charactor->Code());

	//가입된 파티가 있을 경우
	if (charactor->GetParty() != nullptr)
	{
		//파티장일 경우
		if (charactor == charactor->GetParty()->Host())
		{
			//던전 생성	
			cDungeon* dungeon = CreateDungeon();

			//성공 메세지
			Utilities::sBuffer buffer;
			buffer.Write(PROTOCOL::SERVER_RE_ENTER_DUNGEON);
			buffer.Write(true);

			//파티원 전부에게 전송
			Utilities::DS::cLockIterator<Charactor::cCharactor*> iter(&(charactor->GetParty()->CharList()));
			while (iter.HasNext())			
			{			
				
				Charactor::cCharactor* member = iter.Next();
				member->mActive = true;
				//던전 입장
				member->GetMap()->Out_Charactor(member);
				dungeon->In_Charactor(member);

				//상태 변경
				member->GetClient()->Set_State(STATE::E::DUNGEON);

				//전송
				member->GetClient()->Send_Packet_Push(buffer);
				member->GetClient()->WSA_Send_Packet();

			}
			return true;
		}
		//파티장이 아닐경우
		else
		{

			//실패메세지
			Utilities::sBuffer buffer;
			buffer.Write(PROTOCOL::SERVER_RE_ENTER_DUNGEON);
			buffer.Write(false);

			//실패 전송
			_client->Send_Packet_Push(buffer);
			_client->WSA_Send_Packet();
			return false;
		}

	}

	//싱글 플레이 (혼자 입장)
	cDungeon* dungeon = CreateDungeon();
	charactor->GetMap()->Out_Charactor(charactor);
	dungeon->In_Charactor(charactor);

	Utilities::sBuffer buffer;
	buffer.Write(PROTOCOL::SERVER_RE_ENTER_DUNGEON);
	buffer.Write(true);	

	charactor->mActive = true;
	_client->Set_State(STATE::E::DUNGEON);

	_client->Send_Packet_Push(buffer);
	_client->WSA_Send_Packet();

	return true;
}

//던전 정보 요청
bool GAME::Map::cDungeonManager::Req_Dungeon_Data(cGameClient* _client)
{

	Charactor::cCharactor* charactor = _client->Get_Charactor();
	Map::cDungeon* dungeon = static_cast<cDungeon*>(charactor->GetMap());



	//던전에 있을 경우
	if (dungeon != nullptr)
	{
		printf_s("IP: %s Req_Dungeon_Data Charactor Code : %llu Dungeon Code : %llu \n", _client->Get_IP(), charactor->Code(), dungeon->Code());
		mLog.Record("IP: %s Req_Dungeon_Data Charactor Code : %llu Dungeon Code : %llu", _client->Get_IP(), charactor->Code(), dungeon->Code());

		Utilities::sBuffer buffer;
		buffer.Write(PROTOCOL::SERVER_RE_DUNGEON_DATA);

		//파티가 있다면 같이 입장한 파티원 정보 패킹
		if (charactor->GetParty() != nullptr)
		{
			buffer.Write(int(charactor->GetParty()->CharList().LockSize()) - 1);
			Utilities::DS::cLockIterator<Charactor::cCharactor*> iter(&(charactor->GetParty()->CharList()));
			while (iter.HasNext())
			{
				Charactor::cCharactor* member = iter.Next();
				//자기 자신을 제외한
				if (charactor == member) continue;

				buffer.Write(member->Code());
				buffer.Write(member->NickName());
				buffer.Write(member->JobCode());
			}
		}
		else
		{
			//파티원이 없다면 파티원수 0
			buffer.Write(0);
		}



		//몬스터 수 패킹
		buffer.Write(int(dungeon->MobList().LockSize()));
		{
			Utilities::DS::cLockIterator<Monster::cMonster*> iter(&(dungeon->MobList()));
			while (iter.HasNext())
			{	
				//몬스터 정보 패킹
				Monster::cMonster* mob = iter.Next();
				buffer.Write(mob->Code());
				buffer.Write(mob->Type());
				buffer.Write(mob->mPosition.mX);
				buffer.Write(mob->mPosition.mY);
				buffer.Write(mob->Stat().MaxHp);
				buffer.Write(mob->Stat().Speed);
			}
		}

		_client->Send_Packet_Push(buffer);
		_client->WSA_Send_Packet();

		return true;
	}
	return false;
}


//플레이어가 몬스터를 공격
bool GAME::Map::cDungeonManager::Player_Atk_Monster(cGameClient* _client)
{
	Utilities::CODE mobcode;
	_client->RecvPacket().Read(mobcode);

	bool result = false;
	bool death = false;

	Charactor::cCharactor* charactor = _client->Get_Charactor();
	Map::cDungeon* dungeon = static_cast<cDungeon*>(charactor->GetMap());


	if (dungeon != nullptr)
	{
		//던전에 있는 몬스터 검색
		Utilities::DS::cLockIterator<Monster::cMonster*> iter(&(dungeon->MobList()));
		while (iter.HasNext())
		{
			Monster::cMonster* mob = iter.Next();

			//코드가 같을 경우
			if (mob->Code() == mobcode)
			{
				//캐릭터와 몬스터의 거리가 공격 범위에 들어왔을 경우
				if (Utilities::MY_Math::GetLength(mob->mPosition, charactor->mPosition) <= charactor->AtkRange() && mob->Isable())
				{
					//공격력 만큼 체력 감소
					mob->DisCountHp(charactor->Atk());			
					result = true;

					//몬스터의 hp 검사
					if (mob->Stat().NowHp == 0)
					{
						death = true; 
						mob->Disable();
						dungeon->deathcount++;
					}
					break;
				}
			}

		}
	}

	//공격성공
	if (result)
	{
		//죽었을 경우  
		if (death)
		{
			//클라에게 정보 전송 (몬스터의 코드)
			Utilities::sBuffer buffer;
			buffer.Write(PROTOCOL::SERVER_SEND_MONSTER_STATE);
			buffer.Write(GAME::Monster::DEATH);
			buffer.Write(mobcode);


			Utilities::DS::cLockIterator<Charactor::cCharactor*> iter(&dungeon->CharList());
			while (iter.HasNext())
			{
				Charactor::cCharactor* charactor = iter.Next();

				charactor->GetClient()->Send_Packet_Push(buffer);
				charactor->GetClient()->WSA_Send_Packet();
			}
		}
		else
		{
			//성공 했을 경우  클라에게 정보 전송
			Utilities::sBuffer buffer;
			buffer.Write(PROTOCOL::SERVER_SEND_MONSTER_STATE);
			buffer.Write(GAME::Monster::DAMAGE);

			//몬스터의 코드와 캐릭터의 공격력 패킹
			buffer.Write(mobcode);
			buffer.Write(charactor->Atk());

			Utilities::DS::cLockIterator<Charactor::cCharactor*> iter(&dungeon->CharList());
			while (iter.HasNext())
			{
				Charactor::cCharactor* charactor = iter.Next();

				charactor->GetClient()->Send_Packet_Push(buffer);
				charactor->GetClient()->WSA_Send_Packet();
			}
		}
	}
	return result;
}

//던전 종료 체크
bool GAME::Map::cDungeonManager::Dungeon_End(cGameClient* _client)
{
	Charactor::cCharactor* charactor = _client->Get_Charactor();
	Map::cDungeon* dungeon = static_cast<cDungeon*>(charactor->GetMap());

	//던전에 있고 죽은 몬스터의 수를 확인후 결과 전송
	if (dungeon != nullptr && 
		dungeon->deathcount == dungeon->MobList().LockSize())
	{
		//파티와 던전을 나간다.
		Party::st_cPartyManager::GetInstance()->Exit_Charactor(_client->Get_Charactor());
		Map::st_cMapManager::GetInstance()->Exit_Charactor(_client->Get_Charactor());

		//hp를 초기화 하고 마을 상태로 되돌린다.
		_client->Get_Charactor()->mNowHp = 10;
		_client->Get_Charactor()->mLevel++;
		_client->Set_State(STATE::E::TOWN);

		//클라에게 결과 전송
		Utilities::sBuffer buffer;
		buffer.Write(PROTOCOL::SERVER_SEND_DUNGEON_END);

		_client->Send_Packet_Push(buffer);
		_client->WSA_Send_Packet();

		printf_s("Dungeon_End Code : %llu\n", dungeon->Code());
		mLog.Record("Dungeon_End Code : %llu", dungeon->Code());

		return true;
	}
	return false;
}







