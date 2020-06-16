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


	//XML �ε�
	TiXmlDocument xml;
	if (xml.LoadFile("Dungeon.xml"))
	{
		//��Ʈ <Dungeon>
		TiXmlElement* root = xml.RootElement();
		//���� <Mob>
		TiXmlElement* monster = root->FirstChildElement();

		//���� ����Ʈ
		while (monster)
		{
			TiXmlAttribute* attribute = monster->FirstAttribute();

			Monster::cMonster* mob = nullptr;;
			Monster::sMobStat stat;

			//������ Ÿ��
			int type = attribute->IntValue();
			attribute = attribute->Next();
			//��ǥ x
			float x = attribute->DoubleValue();
			attribute = attribute->Next();
			//��ǥ y
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

	//���� ������ ����
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

	//���Ե� ��Ƽ�� ���� ���
	if (charactor->GetParty() != nullptr)
	{
		//��Ƽ���� ���
		if (charactor == charactor->GetParty()->Host())
		{
			//���� ����	
			cDungeon* dungeon = CreateDungeon();

			//���� �޼���
			Utilities::sBuffer buffer;
			buffer.Write(PROTOCOL::SERVER_RE_ENTER_DUNGEON);
			buffer.Write(true);

			//��Ƽ�� ���ο��� ����
			Utilities::DS::cLockIterator<Charactor::cCharactor*> iter(&(charactor->GetParty()->CharList()));
			while (iter.HasNext())			
			{			
				
				Charactor::cCharactor* member = iter.Next();
				member->mActive = true;
				//���� ����
				member->GetMap()->Out_Charactor(member);
				dungeon->In_Charactor(member);

				//���� ����
				member->GetClient()->Set_State(STATE::E::DUNGEON);

				//����
				member->GetClient()->Send_Packet_Push(buffer);
				member->GetClient()->WSA_Send_Packet();

			}
			return true;
		}
		//��Ƽ���� �ƴҰ��
		else
		{

			//���и޼���
			Utilities::sBuffer buffer;
			buffer.Write(PROTOCOL::SERVER_RE_ENTER_DUNGEON);
			buffer.Write(false);

			//���� ����
			_client->Send_Packet_Push(buffer);
			_client->WSA_Send_Packet();
			return false;
		}

	}

	//�̱� �÷��� (ȥ�� ����)
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

//���� ���� ��û
bool GAME::Map::cDungeonManager::Req_Dungeon_Data(cGameClient* _client)
{

	Charactor::cCharactor* charactor = _client->Get_Charactor();
	Map::cDungeon* dungeon = static_cast<cDungeon*>(charactor->GetMap());



	//������ ���� ���
	if (dungeon != nullptr)
	{
		printf_s("IP: %s Req_Dungeon_Data Charactor Code : %llu Dungeon Code : %llu \n", _client->Get_IP(), charactor->Code(), dungeon->Code());
		mLog.Record("IP: %s Req_Dungeon_Data Charactor Code : %llu Dungeon Code : %llu", _client->Get_IP(), charactor->Code(), dungeon->Code());

		Utilities::sBuffer buffer;
		buffer.Write(PROTOCOL::SERVER_RE_DUNGEON_DATA);

		//��Ƽ�� �ִٸ� ���� ������ ��Ƽ�� ���� ��ŷ
		if (charactor->GetParty() != nullptr)
		{
			buffer.Write(int(charactor->GetParty()->CharList().LockSize()) - 1);
			Utilities::DS::cLockIterator<Charactor::cCharactor*> iter(&(charactor->GetParty()->CharList()));
			while (iter.HasNext())
			{
				Charactor::cCharactor* member = iter.Next();
				//�ڱ� �ڽ��� ������
				if (charactor == member) continue;

				buffer.Write(member->Code());
				buffer.Write(member->NickName());
				buffer.Write(member->JobCode());
			}
		}
		else
		{
			//��Ƽ���� ���ٸ� ��Ƽ���� 0
			buffer.Write(0);
		}



		//���� �� ��ŷ
		buffer.Write(int(dungeon->MobList().LockSize()));
		{
			Utilities::DS::cLockIterator<Monster::cMonster*> iter(&(dungeon->MobList()));
			while (iter.HasNext())
			{	
				//���� ���� ��ŷ
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


//�÷��̾ ���͸� ����
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
		//������ �ִ� ���� �˻�
		Utilities::DS::cLockIterator<Monster::cMonster*> iter(&(dungeon->MobList()));
		while (iter.HasNext())
		{
			Monster::cMonster* mob = iter.Next();

			//�ڵ尡 ���� ���
			if (mob->Code() == mobcode)
			{
				//ĳ���Ϳ� ������ �Ÿ��� ���� ������ ������ ���
				if (Utilities::MY_Math::GetLength(mob->mPosition, charactor->mPosition) <= charactor->AtkRange() && mob->Isable())
				{
					//���ݷ� ��ŭ ü�� ����
					mob->DisCountHp(charactor->Atk());			
					result = true;

					//������ hp �˻�
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

	//���ݼ���
	if (result)
	{
		//�׾��� ���  
		if (death)
		{
			//Ŭ�󿡰� ���� ���� (������ �ڵ�)
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
			//���� ���� ���  Ŭ�󿡰� ���� ����
			Utilities::sBuffer buffer;
			buffer.Write(PROTOCOL::SERVER_SEND_MONSTER_STATE);
			buffer.Write(GAME::Monster::DAMAGE);

			//������ �ڵ�� ĳ������ ���ݷ� ��ŷ
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

//���� ���� üũ
bool GAME::Map::cDungeonManager::Dungeon_End(cGameClient* _client)
{
	Charactor::cCharactor* charactor = _client->Get_Charactor();
	Map::cDungeon* dungeon = static_cast<cDungeon*>(charactor->GetMap());

	//������ �ְ� ���� ������ ���� Ȯ���� ��� ����
	if (dungeon != nullptr && 
		dungeon->deathcount == dungeon->MobList().LockSize())
	{
		//��Ƽ�� ������ ������.
		Party::st_cPartyManager::GetInstance()->Exit_Charactor(_client->Get_Charactor());
		Map::st_cMapManager::GetInstance()->Exit_Charactor(_client->Get_Charactor());

		//hp�� �ʱ�ȭ �ϰ� ���� ���·� �ǵ�����.
		_client->Get_Charactor()->mNowHp = 10;
		_client->Get_Charactor()->mLevel++;
		_client->Set_State(STATE::E::TOWN);

		//Ŭ�󿡰� ��� ����
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







