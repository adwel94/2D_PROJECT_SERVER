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

		};
	}
	//byte


}



#endif // !_PROTOCOL_H_
