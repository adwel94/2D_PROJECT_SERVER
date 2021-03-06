#pragma once
#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_

namespace GAME
{
	namespace PROTOCOL
	{
		typedef int Protocol;


		 
		enum
		{
			NONE = -1,
			//클라이언트 로그인 요청 (string,string)
			CLEINT_REQ_LOGIN,
			//서버 로그 결과 (bool)
			SERVER_RE_LOGIN,
			//클라리언트 회원가입 요청(string,string)
			CLIENT_REQ_JOIN,
			//서버 회원가입 결과(bool)
			SERVER_RE_JOIN,
			//클라이언트 로그아웃 요청
			CLIENT_REQ_LOGOUT,
			//서버 로그아웃 요청 결과(bool)
			SERVER_RE_LOGOUT,
			//클라이언트 캐릭터 정보 요청
			CLIENT_REQ_CHAR_INFO,
			//서버 클라이언트 캐릭터 정보 결과 (int 캐릭터수 ,(int 직업코드, string 닉네임)...)
			SERVER_RE_CHAR_INFO,
			//클라이언트 캐릭터 생성 요청 (int 직업코드, string 닉네임)
			CLIENT_REQ_CREATE_CHAR,
			//서버 캐릭터 생성요청 결과 (bool)
			SERVER_RE_CREATE_CHAR,
			//클리아언트 캐릭터 선택(string)
			CLIENT_REQ_SELECT_CHAR,
			//서버 캐릭터 선택 결과 (bool, int 직업코드, string 닉네임)
			SERVER_RE_SELECT_CHAR,
			//클라이언트 캐릭터 삭제(string)
			CLIENT_REQ_DELETE_CHAR,
			//서버 캐릭터 삭제 결과(bool)
			SERVER_RE_DELETE_CHAR,
			//클라이언트 맵 접속 요청 (int 맵코드)
			CLIENT_REQ_MAP_ENTER,
			//서버 맵 접속 요청 결과 (int 캐릭터수, 캐릭터코드,이름,직업,좌표... int 몬스터수...)
			SERVER_RE_MAP_ENTER,
			//맵에 새로운 유저 로그인 (ulong string int)
			SERVER_PLAYER_ENTER,
			//맵에 유저가 나감 (ulong)
			SERVER_PLAYER_OUT,
			//클라이언트->서버 채팅
			CLIENT_SEND_CHAT,
			//서버->클라이언트 채팅
			SERVER_SEND_CHAT,
			//클라이언트 캐릭터 이동 데이터 (float x,float y,bool way)
			CLIENT_SEND_MOVE_DATA,
			//서버 캐릭터 이동 데이터 (float x,float y,bool way)
			SERVER_SEND_MOVE_DATA,
			//클라이언트 캐릭터 점프
			CLIENT_SEND_JUMP_DATA,
			//서버 캐릭터 점프 (ulong 
			SERVER_SEND_JUMP_DATA,
			//클라이언트 파티 생성요청
			CLIENT_REQ_CREATE_PARTY,
			//서버 파티 생성 요청 결과
			SERVER_RE_CREATE_PARTY,
			//클라이언트 파티 정보 요청
			CLIENT_REQ_PARTY_INFO,
			//서버 파티 정보 요청 결과
			SERVER_RE_PARTY_INFO,
			//서버 파티 탈퇴 (ulong
			SERVER_PARTY_OUT,
			//클라이언트 파티 초대 (ulong 
			CLIENT_REQ_PARTY_INVITE,
			//서버 파치 초대 메세지 (string id
			SERVER_PARTY_INVITE_MSG,
			//클라이언트 파티 초대 메세지 (bool , string id, 
			CLIENT_PARTY_INVITE_MSG,
			//파티 멤버 정보 (int , code, 
			SERVER_PARTY_MEMBER_DATA,
			//클라이언트 던전 입장 요청
			CLIENT_REQ_ENTER_DUNGEON,
			//서버 던전 입장 요청 결과
			SERVER_RE_ENTER_DUNGEON,
			//클라이언트 던전 정보 요청 
			CLIENT_REQ_DUNGEON_DATA,
			//서버 던전 정보 요청 결과 
			SERVER_RE_DUNGEON_DATA,
			//공격
			CLIENT_SEND_ATK_DATA,
			SERVER_SEND_ATK_DATA,
			//클라이언트 피격모션 정보
			CLIENT_SEND_DAMAGE_DATA,
			//서버 피격 모션 정보
			SERVER_SEND_DAMAGE_DATA,
			//몬스터 상태 정보
			SERVER_SEND_MONSTER_STATE,
			//플레이어 몬스터 공격 
			CLIENT_PLAYER_ATK_MONSTER,
			//몬스터 플레이어 공격(int atk
			SERVER_MONSTER_ATK_PLAYER,
			//플레이어 죽음
			CLIENT_SEND_DEATH_DATA,
			SERVER_SEND_DEATH_DATA,
			//플레이어 죽음 모션 종료
			CLIENT_SEND_DEATH_END,
			//던전 종료
			CLIENT_SNED_DUNGEON_END,
			SERVER_SEND_DUNGEON_END
		

		};
	}
	//byte


}



#endif // !_PROTOCOL_H_
