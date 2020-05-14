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
			SERVER_REQ_LOGOUT
		};
	}
	//byte


}



#endif // !_PROTOCOL_H_
