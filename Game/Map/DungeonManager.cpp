#include "DungeonManager.h"
#include "Monster/Monster.h"
#include "Monster/cGiantEyes.h"
#include "Monster/cGoblin.h"
#include "CodeMaker/CodeMaker.h"
#include "XML/include/tinyxml.h"
#include "GameClient/GameClient.h"
#include "Math/Vector2D.h"
#include "PROTOCOL.h"


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

	dungeon->Start();
	printf_s("Create Dungeon Coed : %llu Monster Count : %d \n",dungeon->Code(),(int)dungeon->MobList().LockSize());
	return dungeon;
}

bool GAME::Map::cDungeonManager::Req_Enter_Dungeon(cGameClient* _client)
{
	Charactor::cCharactor* charactor = _client->Get_Charactor();

	printf_s("IP: %s Req_Enter_Dungeon Charactor Code : %llu  \n", _client->Get_IP(), charactor->Code());
	//가입된 파티가 있을 경우
	if (charactor->GetParty() != nullptr)
	{
		//파티장일 경우
		if (charactor == charactor->GetParty()->Host())
		{


			//던전 생성
			charactor->GetMap()->Out_Charactor(charactor);
			cDungeon* dungeon = CreateDungeon();

			//성공 메세지
			Utilities::sBuffer buffer;
			buffer.Write(PROTOCOL::SERVER_RE_ENTER_DUNGEON);
			buffer.Write(true);

			//파티원 전부에게 전송
			Utilities::DS::cLockIterator<Charactor::cCharactor*> iter(&(charactor->GetParty()->CharList()));
			while (iter.HasNext())			{			
				
				Charactor::cCharactor* member = iter.Next();
				//던전 입장
				member->GetMap()->Out_Charactor(member);
				dungeon->In_Charactor(member);
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

	//싱글 플레이

	cDungeon* dungeon = CreateDungeon();
	charactor->GetMap()->Out_Charactor(charactor);
	dungeon->In_Charactor(charactor);

	Utilities::sBuffer buffer;
	buffer.Write(PROTOCOL::SERVER_RE_ENTER_DUNGEON);
	buffer.Write(true);	

	_client->Send_Packet_Push(buffer);
	_client->WSA_Send_Packet();

	return true;
}

bool GAME::Map::cDungeonManager::Req_Dungeon_Data(cGameClient* _client)
{

	Charactor::cCharactor* charactor = _client->Get_Charactor();
	Map::cDungeon* dungeon = static_cast<cDungeon*>(charactor->GetMap());
	printf_s("IP: %s Req_Dungeon_Data Charactor Code : %llu Dungeon Code : %llu \n", _client->Get_IP(), charactor->Code(), dungeon->Code());

	Utilities::sBuffer buffer;
	buffer.Write(PROTOCOL::SERVER_RE_DUNGEON_DATA);


	if (dungeon != nullptr)
	{
		//맵에 있는 파티원 정보 패킹
		buffer.Write(int(dungeon->CharList().LockSize()) -1);
		{
			Utilities::DS::cLockIterator<Charactor::cCharactor*> iter(&(dungeon->CharList()));
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

		//몬스터 정보 패킹
		buffer.Write(int(dungeon->MobList().LockSize()));
		{
			Utilities::DS::cLockIterator<Monster::cMonster*> iter(&(dungeon->MobList()));
			while (iter.HasNext())
			{
				Monster::cMonster* mob = iter.Next();
				buffer.Write(mob->Code());
				buffer.Write(mob->Type());
				buffer.Write(mob->mPosition.mX);
				buffer.Write(mob->mPosition.mY);
			}
		}

		_client->Send_Packet_Push(buffer);
		_client->WSA_Send_Packet();

		return true;
	}
	return false;
}

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
		Utilities::DS::cLockIterator<Monster::cMonster*> iter(&(dungeon->MobList()));
		while (iter.HasNext())
		{
			Monster::cMonster* mob = iter.Next();
			if (mob->Code() == mobcode)
			{
				//캐릭터와 몬스터의 거리가 공격 범위에 들어왔을 경우
				if (Utilities::MY_Math::GetLength(mob->mPosition, charactor->mPosition) <= charactor->AtkRange() && mob->Isable())
				{
					//공격력 만큼 체력 감소
					printf_s("공격 성공 \n");
					mob->DisCountHp(charactor->Atk());			
					result = true;
					if (mob->Stat().NowHp == 0)
					{
						printf_s("뒤짐 \n");
						death = true; 
						mob->Disable();
					}
					break;
				}
			}

		}
	}

	if (result)
	{
		if (death)
		{
			//죽었을 경우  클라에게 정보 전송
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







