#include "PartyManager.h"
#include "GameClient/GameClient.h"
#include "PROTOCOL.h"

//��Ƽ ���� ��û
bool GAME::Party::cPartyManager::Req_Create_Party(cGameClient* _client)
{

	printf_s("IP: %s Charactor : %s Req_Create_Party  \n", _client->Get_IP(), _client->Get_Charactor()->NickName());

	bool result = false;	
	Charactor::cCharactor* charactor = _client->Get_Charactor();


	//���Ե� ��Ƽ�� ���ٸ�
	if (charactor->GetParty() == nullptr)
	{	
		//��Ƽ �����ϰ� ����� �߰�
		cParty* party = new cParty(mMaker.Get_Code());
		party->In_Charactor(charactor);

		result = true;	
	}

	//��� ����
	Utilities::sBuffer buffer;
	buffer.Write(PROTOCOL::SERVER_RE_CREATE_PARTY);
	buffer.Write(result);

	//���� �ϰ�� ��Ƽ ��� ���� ����
	if (result)
	{
		cParty* party = charactor->GetParty();
		buffer.Write((int)party->CharList().LockSize());

		//��Ƽ���� �̸�, �����ڵ带 ��ŷ
		Utilities::DS::cLockIterator<Charactor::cCharactor*> iter(&(party->CharList()));
		while (iter.HasNext())
		{
			Charactor::cCharactor* member = iter.Next();
			buffer.Write(member->NickName());
			buffer.Write(member->JobCode());
		}
	}

	_client->Send_Packet_Push(buffer);
	_client->WSA_Send_Packet();

	return result;
}

//��Ƽ ���� ��û
bool GAME::Party::cPartyManager::Req_Party_Info(cGameClient* _client)
{


	Charactor::cCharactor* charactor = _client->Get_Charactor();
	cParty* party = charactor->GetParty();

	//���Ե� ��Ƽ�� �ִٸ�
	if (party != nullptr)
	{

		printf_s("IP: %s Charactor : %s Req_Party_Info Code : %llu \n", _client->Get_IP(), _client->Get_Charactor()->NickName(), party->Code());


		Utilities::sBuffer buffer;
		buffer.Write(PROTOCOL::SERVER_RE_PARTY_INFO);
		buffer.Write(int(party->CharList().LockSize()));

		//��Ƽ���� �̸�, �����ڵ带 ��ŷ
		Utilities::DS::cLockIterator<Charactor::cCharactor*> iter(&(party->CharList()));
		while (iter.HasNext())
		{
			Charactor::cCharactor* member = iter.Next();

			buffer.Write(member->NickName());
			buffer.Write(member->JobCode());

		}

		//���� ����
		_client->Send_Packet_Push(buffer);
		_client->WSA_Send_Packet();

		return true;
	}
	return false;
}

//��Ƽ �ʴ� ��û
bool GAME::Party::cPartyManager::Req_Party_Invite(cGameClient* _client)
{

	//�����
	bool result = false;
	Charactor::cCharactor* charactor = _client->Get_Charactor();


	//��Ƽ�� �ִٸ� ��Ƽ ����� �˻�
	if (charactor->GetParty() != nullptr && charactor->GetParty()->CharList().LockSize() == 4)
	{
		return result;
	}

	//��Ƽ�� �ʴ��� ĳ���� �ڵ�
	Utilities::CODE code;
	_client->RecvPacket().Read(code);


	//iterator �ʿ��� �ش� �ڵ��� ĳ���͸� ã�´�.
	Map::cMap* map = charactor->GetMap();
	if (map != nullptr)
	{
		Utilities::DS::cLockIterator<Charactor::cCharactor*> iter(&(map->CharList()));
		while (iter.HasNext())
		{
			Charactor::cCharactor* invite_char = iter.Next();
			//�ڵ带 ã��
			if (invite_char->Code() == code)
			{
				//�̹� ��Ƽ�� ���Ե��� Ȯ��
				if (invite_char->GetParty() == nullptr)
				{
					//�ƴ϶�� ��Ƽ�ʴ� ����
					Utilities::sBuffer buffer;
					buffer.Write(PROTOCOL::SERVER_PARTY_INVITE_MSG);
					buffer.Write(charactor->NickName());

					invite_char->GetClient()->Send_Packet_Push(buffer);
					invite_char->GetClient()->WSA_Send_Packet();

					result = true;
					break;					
				}
			}
		}
	}
	return result;
}

//��Ƽ �ʴ� �޼���
bool GAME::Party::cPartyManager::Party_Invite_Msg(cGameClient* _client)
{

	//��Ƽ �ʴ븦 ��û�� ĳ���� �̸�, ���
	bool invite;
	_client->RecvPacket().Read(invite);

	//�����
	bool result = false;

	//������ �ߴٸ�
	if (invite)
	{
		//�ʴ븦 ��û�� ĳ���� �г���
		char name[NICK_NAME_SIZE];
		_client->RecvPacket().Read(name);

		printf_s("IP: %s Join Party Host : %s   Player : %s \n", _client->Get_IP(), name, _client->Get_Charactor()->NickName());


		//iterator �ʿ��� �ʴ븦 ��û�� ĳ���� �г����� ã�´�.
		Map::cMap* map = _client->Get_Charactor()->GetMap();
		Charactor::cCharactor* newcharactor = nullptr;
		if (map != nullptr)
		{
			Utilities::DS::cLockIterator<Charactor::cCharactor*> iter(&(map->CharList()));
			while (iter.HasNext())
			{
				newcharactor = iter.Next();
				//�̸��� ã��
				if (!strcmp(newcharactor->NickName(), name))
				{
					result = true;

					//��Ƽ�� �ִ��� Ȯ��
					if (newcharactor->GetParty() == nullptr)
					{
						//��Ƽ �����ϰ� ����� �߰�
						cParty* party = new cParty(mMaker.Get_Code());
						party->In_Charactor(newcharactor);

					}

					//������ ����� ��Ƽ�� �߰�
					newcharactor->GetParty()->In_Charactor(_client->Get_Charactor());
					break;
				}
			}


			if (result)
			{
				//���� ���� ���� ����
				Utilities::sBuffer buffer1;
				buffer1.Write(PROTOCOL::SERVER_PARTY_MEMBER_DATA);
				buffer1.Write((int)1);
				buffer1.Write(newcharactor->Code());

				//������ �־��� ���� ����
				Utilities::sBuffer buffer2;
				buffer2.Write(PROTOCOL::SERVER_PARTY_MEMBER_DATA);
				buffer2.Write(int(newcharactor->GetParty()->CharList().LockSize() - 1));
				Utilities::DS::cLockIterator<Charactor::cCharactor*> iter(&(newcharactor->GetParty()->CharList()));
				while (iter.HasNext())
				{
					//���� ���� ������ ������		
					Charactor::cCharactor* charactor = iter.Next();
					if (charactor == newcharactor) continue;

					//������ �־��� ���������� ��ŷ
					buffer2.Write(charactor->Code());

					//������ �־��� �����鿡�� ���ο� ���� ���� ����
					charactor->GetClient()->Send_Packet_Push(buffer1);
					charactor->GetClient()->WSA_Send_Packet();
				}

				//���� ���� �������� ���� ������ ���� ����
				newcharactor->GetClient()->Send_Packet_Push(buffer2);
				newcharactor->GetClient()->WSA_Send_Packet();
			}
		}	
	}

	return result;
}



//��Ƽ Ż��
void GAME::Party::cPartyManager::Exit_Charactor(Charactor::cCharactor* _char)
{
	Party::cParty* party = _char->GetParty();
	if (party != nullptr)
	{
		printf_s("IP: %s Exit_Party Charactor Code : %llu  Party Code : %llu \n", _char->GetClient()->Get_IP(), _char->Code(), party->Code());		
		party->Out_Charactor(_char);
		
		//��Ƽ������ 0�̸�
		if (party->CharList().LockSize() == 0)
		{
			//��Ƽ �Ҹ�
			delete party;
			return;
		}


		//�ƴҰ�� ����鿡�� �����ٴ� ����������
		Utilities::sBuffer buffer;
		buffer.Write(PROTOCOL::SERVER_PARTY_OUT);
		buffer.Write(_char->Code());

		Utilities::DS::cLockIterator<Charactor::cCharactor*> iter(&(party->CharList()));
		while (iter.HasNext())
		{
			//�ʿ� �ִ� ĳ���͵鿡�� ����
			Charactor::cCharactor* charactor = iter.Next();
			charactor->GetClient()->Send_Packet_Push(buffer);
			charactor->GetClient()->WSA_Send_Packet();
		}
	}
}
