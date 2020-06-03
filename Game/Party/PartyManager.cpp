#include "PartyManager.h"
#include "GameClient/GameClient.h"
#include "PROTOCOL.h"

//파티 생성 요청
bool GAME::Party::cPartyManager::Req_Create_Party(cGameClient* _client)
{

	printf_s("IP: %s Charactor : %s Req_Create_Party  \n", _client->Get_IP(), _client->Get_Charactor()->NickName());

	bool result = false;	
	Charactor::cCharactor* charactor = _client->Get_Charactor();


	//가입된 파티가 없다면
	if (charactor->GetParty() == nullptr)
	{	
		//파티 생성하고 멤버로 추가
		cParty* party = new cParty(mMaker.Get_Code());
		party->In_Charactor(charactor);

		result = true;	
	}

	//결과 전송
	Utilities::sBuffer buffer;
	buffer.Write(PROTOCOL::SERVER_RE_CREATE_PARTY);
	buffer.Write(result);

	//성공 일경우 파티 멤버 정보 전송
	if (result)
	{
		cParty* party = charactor->GetParty();
		buffer.Write((int)party->CharList().LockSize());

		//파티원들 이름, 직업코드를 패킹
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

//파티 정보 요청
bool GAME::Party::cPartyManager::Req_Party_Info(cGameClient* _client)
{


	Charactor::cCharactor* charactor = _client->Get_Charactor();
	cParty* party = charactor->GetParty();

	//가입된 파티가 있다면
	if (party != nullptr)
	{

		printf_s("IP: %s Charactor : %s Req_Party_Info Code : %llu \n", _client->Get_IP(), _client->Get_Charactor()->NickName(), party->Code());


		Utilities::sBuffer buffer;
		buffer.Write(PROTOCOL::SERVER_RE_PARTY_INFO);
		buffer.Write(int(party->CharList().LockSize()));

		//파티원들 이름, 직업코드를 패킹
		Utilities::DS::cLockIterator<Charactor::cCharactor*> iter(&(party->CharList()));
		while (iter.HasNext())
		{
			Charactor::cCharactor* member = iter.Next();

			buffer.Write(member->NickName());
			buffer.Write(member->JobCode());

		}

		//정보 전송
		_client->Send_Packet_Push(buffer);
		_client->WSA_Send_Packet();

		return true;
	}
	return false;
}

//파티 초대 요청
bool GAME::Party::cPartyManager::Req_Party_Invite(cGameClient* _client)
{

	//결과값
	bool result = false;
	Charactor::cCharactor* charactor = _client->Get_Charactor();


	//파티가 있다면 파티 멤버수 검사
	if (charactor->GetParty() != nullptr && charactor->GetParty()->CharList().LockSize() == 4)
	{
		return result;
	}

	//파티를 초대할 캐릭터 코드
	Utilities::CODE code;
	_client->RecvPacket().Read(code);


	//iterator 맵에서 해당 코드의 캐릭터를 찾는다.
	Map::cMap* map = charactor->GetMap();
	if (map != nullptr)
	{
		Utilities::DS::cLockIterator<Charactor::cCharactor*> iter(&(map->CharList()));
		while (iter.HasNext())
		{
			Charactor::cCharactor* invite_char = iter.Next();
			//코드를 찾고
			if (invite_char->Code() == code)
			{
				//이미 파티에 가입된지 확인
				if (invite_char->GetParty() == nullptr)
				{
					//아니라면 파티초대 보냄
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

//파티 초대 메세지
bool GAME::Party::cPartyManager::Party_Invite_Msg(cGameClient* _client)
{

	//파티 초대를 요청한 캐릭터 이름, 결과
	bool invite;
	_client->RecvPacket().Read(invite);

	//결과값
	bool result = false;

	//수락을 했다면
	if (invite)
	{
		//초대를 요청한 캐릭터 닉네임
		char name[NICK_NAME_SIZE];
		_client->RecvPacket().Read(name);

		printf_s("IP: %s Join Party Host : %s   Player : %s \n", _client->Get_IP(), name, _client->Get_Charactor()->NickName());


		//iterator 맵에서 초대를 요청한 캐릭터 닉네임을 찾는다.
		Map::cMap* map = _client->Get_Charactor()->GetMap();
		Charactor::cCharactor* newcharactor = nullptr;
		if (map != nullptr)
		{
			Utilities::DS::cLockIterator<Charactor::cCharactor*> iter(&(map->CharList()));
			while (iter.HasNext())
			{
				newcharactor = iter.Next();
				//이름을 찾고
				if (!strcmp(newcharactor->NickName(), name))
				{
					result = true;

					//파티가 있는지 확인
					if (newcharactor->GetParty() == nullptr)
					{
						//파티 생성하고 멤버로 추가
						cParty* party = new cParty(mMaker.Get_Code());
						party->In_Charactor(newcharactor);

					}

					//수락한 멤버도 파티에 추가
					newcharactor->GetParty()->In_Charactor(_client->Get_Charactor());
					break;
				}
			}


			if (result)
			{
				//새로 들어온 유저 정보
				Utilities::sBuffer buffer1;
				buffer1.Write(PROTOCOL::SERVER_PARTY_MEMBER_DATA);
				buffer1.Write((int)1);
				buffer1.Write(newcharactor->Code());

				//기존에 있었던 유저 정보
				Utilities::sBuffer buffer2;
				buffer2.Write(PROTOCOL::SERVER_PARTY_MEMBER_DATA);
				buffer2.Write(int(newcharactor->GetParty()->CharList().LockSize() - 1));
				Utilities::DS::cLockIterator<Charactor::cCharactor*> iter(&(newcharactor->GetParty()->CharList()));
				while (iter.HasNext())
				{
					//새로 들어온 유저를 제외한		
					Charactor::cCharactor* charactor = iter.Next();
					if (charactor == newcharactor) continue;

					//기존에 있었던 유저정보를 패킹
					buffer2.Write(charactor->Code());

					//기존에 있었던 유저들에게 새로운 유저 정보 전송
					charactor->GetClient()->Send_Packet_Push(buffer1);
					charactor->GetClient()->WSA_Send_Packet();
				}

				//새로 들어온 유저에게 기존 유저들 정보 전송
				newcharactor->GetClient()->Send_Packet_Push(buffer2);
				newcharactor->GetClient()->WSA_Send_Packet();
			}
		}	
	}

	return result;
}



//파티 탈퇴
void GAME::Party::cPartyManager::Exit_Charactor(Charactor::cCharactor* _char)
{
	Party::cParty* party = _char->GetParty();
	if (party != nullptr)
	{
		printf_s("IP: %s Exit_Party Charactor Code : %llu  Party Code : %llu \n", _char->GetClient()->Get_IP(), _char->Code(), party->Code());		
		party->Out_Charactor(_char);
		
		//파티원수가 0이면
		if (party->CharList().LockSize() == 0)
		{
			//파티 소멸
			delete party;
			return;
		}


		//아닐경우 멤버들에게 나갔다는 데이터전송
		Utilities::sBuffer buffer;
		buffer.Write(PROTOCOL::SERVER_PARTY_OUT);
		buffer.Write(_char->Code());

		Utilities::DS::cLockIterator<Charactor::cCharactor*> iter(&(party->CharList()));
		while (iter.HasNext())
		{
			//맵에 있는 캐릭터들에게 전송
			Charactor::cCharactor* charactor = iter.Next();
			charactor->GetClient()->Send_Packet_Push(buffer);
			charactor->GetClient()->WSA_Send_Packet();
		}
	}
}
