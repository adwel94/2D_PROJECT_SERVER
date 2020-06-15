#include "MapManager.h"
#include "GameClient/GameClient.h"
#include "DS/LockList.h"
#include "DS/LockIterator.h"
#include "PROTOCOL.h"
#include "Map/Town.h"




bool GAME::Map::cMapManager::Req_Enter_Map(cGameClient* _client)
{



	int mapcode;
	_client->RecvPacket().Read(mapcode);

	printf_s("IP: %s Req_Enter_Map Charactor Code : %llu  Map Code : %llu \n", _client->Get_IP(), _client->Get_Charactor()->Code(), mapcode);
	mLog.Record("IP: %s Req_Enter_Map Charactor Code : %llu  Map Code : %llu", _client->Get_IP(), _client->Get_Charactor()->Code(), mapcode);


	switch (mapcode)
	{
	case CODE::MAP::TOWN:
		st_cTown::GetInstance()->In_Charactor(_client->Get_Charactor());
		break;
	default:
		break;
	}


	cMap* map = _client->Get_Charactor()->GetMap();

	if (map != nullptr)
	{
		//자신의 정보 패킹
		Utilities::sBuffer buffer1;

		buffer1.Write(PROTOCOL::SERVER_PLAYER_ENTER);
		buffer1.Write(_client->Get_Charactor()->Code());
		buffer1.Write(_client->Get_Charactor()->NickName());
		buffer1.Write(_client->Get_Charactor()->JobCode());

		//맵에 정보 패킹
		Utilities::sBuffer buffer2;
		buffer2.Write(PROTOCOL::SERVER_RE_MAP_ENTER);
		buffer2.Write(int(map->CharList().LockSize() - 1));
		Utilities::DS::cLockIterator<Charactor::cCharactor*> iter(&(map->CharList()));
		while (iter.HasNext())
		{
			//자신을 제외한
			Charactor::cCharactor* charactor = iter.Next();
			if (charactor == _client->Get_Charactor()) continue;

			//맵에 있는 캐릭터들정보를 패킹
			buffer2.Write(charactor->Code());
			buffer2.Write(charactor->NickName());
			buffer2.Write(charactor->JobCode());
			buffer2.Write(charactor->mPosition.mX);
			buffer2.Write(charactor->mPosition.mY);
	


			//맵에 있던 캐릭터들에게 나의정보를 전송
			charactor->GetClient()->Send_Packet_Push(buffer1);
			charactor->GetClient()->WSA_Send_Packet();
		}

		//맵에 있던 캐릭터들 정보 전송
		_client->Send_Packet_Push(buffer2);
		_client->WSA_Send_Packet();
	}
	return true;
}

GAME::Map::cMapManager::cMapManager()
{
	mLog.Connect("MAP_LOG.txt");
}

GAME::Map::cMapManager::~cMapManager()
{
	mLog.Close();
}

bool GAME::Map::cMapManager::Send_Chat_Data(cGameClient* _client)
{

	//채팅 내역 추출
	char msg[255];
	_client->RecvPacket().Read(msg);

	//iterator
	cMap* map = _client->Get_Charactor()->GetMap();
	if (map != nullptr)
	{
		//채팅 보낸사람 + 채팅 내용
		Utilities::sBuffer buffer;

		buffer.Write(PROTOCOL::SERVER_SEND_CHAT);
		buffer.Write(_client->Get_Charactor()->NickName());
		buffer.Write(msg);

		Utilities::DS::cLockIterator<Charactor::cCharactor*> iter(&(map->CharList()));
		while (iter.HasNext())
		{

			//맵에 있는 캐릭터들에게 전송
			Charactor::cCharactor* charactor = iter.Next();
			charactor->GetClient()->Send_Packet_Push(buffer);
			charactor->GetClient()->WSA_Send_Packet();
		}
	}
	return true;
}

bool GAME::Map::cMapManager::Send_Move_Data(cGameClient* _client)
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
	cMap* map = _client->Get_Charactor()->GetMap();
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

bool GAME::Map::cMapManager::Send_Jump_Data(cGameClient* _client)
{
	cMap* map = _client->Get_Charactor()->GetMap();
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

void GAME::Map::cMapManager::Exit_Charactor(Charactor::cCharactor* _char)
{
	Map::cMap* map = _char->GetMap();
	if (map != nullptr)
	{
		printf_s("IP: %s Exit_Map Charactor Code : %llu  Map Code : %llu \n", _char->GetClient()->Get_IP(), _char->Code(), map->Code());
		mLog.Record("IP: %s Exit_Map Charactor Code : %llu  Map Code : %llu", _char->GetClient()->Get_IP(), _char->Code(), map->Code());
		Utilities::sBuffer buffer;
		buffer.Write(PROTOCOL::SERVER_PLAYER_OUT);
		buffer.Write(_char->Code());

		map->Out_Charactor(_char);
		{
			Utilities::DS::cLockIterator<Charactor::cCharactor*> iter(&(map->CharList()));
			while (iter.HasNext())
			{
				//맵에 있는 캐릭터들에게 전송
				Charactor::cCharactor* charactor = iter.Next();
				charactor->GetClient()->Send_Packet_Push(buffer);
				charactor->GetClient()->WSA_Send_Packet();
			}
		}

		if (map != st_cTown::GetInstance() && map->CharList().LockSize() == 0)
		{
			delete map;
		}
	}
}
