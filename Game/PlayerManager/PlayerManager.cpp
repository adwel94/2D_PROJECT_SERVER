#include "PlayerManager.h"
#include "PROTOCOL.h"
#include "Map/Map.h"
#include "Map/MapManager.h"
#include "Party/PartyManager.h"
#include "GameClient/State.h"

bool GAME::cPlayerManager::Send_Move_Data(cGameClient* _client)
{
	//좌표, 방향값
	float x, y;
	bool is_left;

	_client->RecvPacket().Read(x);
	_client->RecvPacket().Read(y);
	_client->RecvPacket().Read(is_left);

	//캐릭터값에 입력
	//printf_s("캐릭터 좌표 (%f,%f) 방향 %s \n", x, y, (is_left ? "left" : "right"));
	_client->Get_Charactor()->mPosition.SetXY(x, y);
	_client->Get_Charactor()->mDirection = is_left;

	//iterator
	Map::cMap* map = _client->Get_Charactor()->GetMap();
	if (map != nullptr)
	{

		Utilities::sBuffer buffer;

		//정보 패킹
		buffer.Write(PROTOCOL::SERVER_SEND_MOVE_DATA);
		buffer.Write(_client->Get_Charactor()->Code());
		buffer.Write(x);
		buffer.Write(y);
		buffer.Write(is_left);

		Utilities::DS::cLockIterator<Charactor::cCharactor*> iter(&(map->CharList()));
		while (iter.HasNext())
		{
			//맵에 있는 캐릭터들에게 전송
			Charactor::cCharactor* charactor = iter.Next();
			//자신 제외
			if (charactor == _client->Get_Charactor()) continue;

			charactor->GetClient()->Send_Packet_Push(buffer);
			charactor->GetClient()->WSA_Send_Packet();
		}
	}
	return true;
}

bool GAME::cPlayerManager::Send_Jump_Data(cGameClient* _client)
{
	Map::cMap* map = _client->Get_Charactor()->GetMap();
	if (map != nullptr)
	{
		Utilities::sBuffer buffer;

		buffer.Write(PROTOCOL::SERVER_SEND_JUMP_DATA);
		buffer.Write(_client->Get_Charactor()->Code());

		Utilities::DS::cLockIterator<Charactor::cCharactor*> iter(&(map->CharList()));
		while (iter.HasNext())
		{
			//맵에 있는 캐릭터들에게 전송
			Charactor::cCharactor* charactor = iter.Next();
			//자신 제외
			if (charactor == _client->Get_Charactor()) continue;

			charactor->GetClient()->Send_Packet_Push(buffer);
			charactor->GetClient()->WSA_Send_Packet();
		}
	}
	return true;
}

bool GAME::cPlayerManager::Send_Atk_Data(cGameClient* _client)
{
	Map::cMap* map = _client->Get_Charactor()->GetMap();
	if (map != nullptr)
	{
		Utilities::sBuffer buffer;

		buffer.Write(PROTOCOL::SERVER_SEND_ATK_DATA);
		buffer.Write(_client->Get_Charactor()->Code());

		Utilities::DS::cLockIterator<Charactor::cCharactor*> iter(&(map->CharList()));
		while (iter.HasNext())
		{
			//맵에 있는 캐릭터들에게 전송
			Charactor::cCharactor* charactor = iter.Next();
			//자신 제외
			if (charactor == _client->Get_Charactor()) continue;

			charactor->GetClient()->Send_Packet_Push(buffer);
			charactor->GetClient()->WSA_Send_Packet();
		}
	}
	return true;
}

bool GAME::cPlayerManager::Send_Damage_Data(cGameClient* _client)
{
	Map::cMap* map = _client->Get_Charactor()->GetMap();
	if (map != nullptr)
	{
		Utilities::sBuffer buffer;

		buffer.Write(PROTOCOL::SERVER_SEND_DAMAGE_DATA);
		buffer.Write(_client->Get_Charactor()->Code());

		Utilities::DS::cLockIterator<Charactor::cCharactor*> iter(&(map->CharList()));
		while (iter.HasNext())
		{
			//맵에 있는 캐릭터들에게 전송
			Charactor::cCharactor* charactor = iter.Next();
			//자신 제외
			if (charactor == _client->Get_Charactor()) continue;

			charactor->GetClient()->Send_Packet_Push(buffer);
			charactor->GetClient()->WSA_Send_Packet();
		}
	}
	return true;
}

bool GAME::cPlayerManager::Send_Death_Data(cGameClient* _client)
{
	Map::cMap* map = _client->Get_Charactor()->GetMap();
	if (map != nullptr)
	{
		Utilities::sBuffer buffer;

		buffer.Write(PROTOCOL::SERVER_SEND_DEATH_DATA);
		buffer.Write(_client->Get_Charactor()->Code());

		Utilities::DS::cLockIterator<Charactor::cCharactor*> iter(&(map->CharList()));
		while (iter.HasNext())
		{
			//맵에 있는 캐릭터들에게 전송
			Charactor::cCharactor* charactor = iter.Next();
			//자신 제외
			if (charactor == _client->Get_Charactor()) continue;

			charactor->GetClient()->Send_Packet_Push(buffer);
			charactor->GetClient()->WSA_Send_Packet();
		}
	}
	return true;
}

void GAME::cPlayerManager::Death_Player(Charactor::cCharactor* _char)
{
	//Party::st_cPartyManager::GetInstance()->Exit_Charactor(_char);
	//Map::st_cMapManager::GetInstance()->Exit_Charactor(_char);
	//_char->GetClient()->Set_State(STATE::E::TOWN);

	//Utilities::sBuffer buffer;
	//buffer.Write(PROTOCOL::SERVER_PLAYER_DEATH);

	//_char->GetClient()->Send_Packet_Push(buffer);
	//_char->GetClient()->WSA_Send_Packet();

	printf_s("Death_Send\n");

}
