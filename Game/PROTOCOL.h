#pragma once
#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_

namespace GAME
{
	namespace PROTOCOL
	{
		typedef int P;

		enum TYPE
		{
			//Ŭ���̾�Ʈ �α��� ��û (string,string)
			CLEINT_REQ_LOGIN,
			//���� �α� ��� (bool)
			SERVER_RE_LOGIN,
			//Ŭ�󸮾�Ʈ ȸ������ ��û(string,string)
			CLIENT_REQ_JOIN,
			//���� ȸ������ ���(bool)
			SERVER_RE_JOIN
		};
	}
	//byte


}



#endif // !_PROTOCOL_H_
