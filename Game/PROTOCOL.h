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
			//Ŭ���̾�Ʈ �α��� ��û (string,string)
			CLEINT_REQ_LOGIN,
			//���� �α� ��� (bool)
			SERVER_RE_LOGIN,
			//Ŭ�󸮾�Ʈ ȸ������ ��û(string,string)
			CLIENT_REQ_JOIN,
			//���� ȸ������ ���(bool)
			SERVER_RE_JOIN,
			//Ŭ���̾�Ʈ �α׾ƿ� ��û
			CLIENT_REQ_LOGOUT,
			//���� �α׾ƿ� ��û ���(bool)
			SERVER_REQ_LOGOUT
		};
	}
	//byte


}



#endif // !_PROTOCOL_H_
