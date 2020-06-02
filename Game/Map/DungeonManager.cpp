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

	dungeon->Start();
	printf_s("Create Dungeon Coed : %llu Monster Count : %d \n",dungeon->Code(),(int)dungeon->MobList().LockSize());
	return dungeon;
}

bool GAME::Map::cDungeonManager::Req_Enter_Dungeon(cGameClient* _client)
{
	Charactor::cCharactor* charactor = _client->Get_Charactor();

	printf_s("IP: %s Req_Enter_Dungeon Charactor Code : %llu  \n", _client->Get_IP(), charactor->Code());
	//���Ե� ��Ƽ�� ���� ���
	if (charactor->GetParty() != nullptr)
	{
		//��Ƽ���� ���
		if (charactor == charactor->GetParty()->Host())
		{


			//���� ����
			charactor->GetMap()->Out_Charactor(charactor);
			cDungeon* dungeon = CreateDungeon();

			//���� �޼���
			Utilities::sBuffer buffer;
			buffer.Write(PROTOCOL::SERVER_RE_ENTER_DUNGEON);
			buffer.Write(true);

			//��Ƽ�� ���ο��� ����
			Utilities::DS::cLockIterator<Charactor::cCharactor*> iter(&(charactor->GetParty()->CharList()));
			while (iter.HasNext())			{			
				
				Charactor::cCharactor* member = iter.Next();
				//���� ����
				member->GetMap()->Out_Charactor(member);
				dungeon->In_Charactor(member);
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

	//�̱� �÷���

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
		//�ʿ� �ִ� ��Ƽ�� ���� ��ŷ
		buffer.Write(int(dungeon->CharList().LockSize()) -1);
		{
			Utilities::DS::cLockIterator<Charactor::cCharactor*> iter(&(dungeon->CharList()));
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

		//���� ���� ��ŷ
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
				//ĳ���Ϳ� ������ �Ÿ��� ���� ������ ������ ���
				if (Utilities::MY_Math::GetLength(mob->mPosition, charactor->mPosition) <= charactor->AtkRange() && mob->Isable())
				{
					//���ݷ� ��ŭ ü�� ����
					printf_s("���� ���� \n");
					mob->DisCountHp(charactor->Atk());			
					result = true;
					if (mob->Stat().NowHp == 0)
					{
						printf_s("���� \n");
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
			//�׾��� ���  Ŭ�󿡰� ���� ����
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







