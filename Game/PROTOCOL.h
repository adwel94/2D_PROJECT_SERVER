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
			SERVER_RE_LOGOUT,
			//Ŭ���̾�Ʈ ĳ���� ���� ��û
			CLIENT_REQ_CHAR_INFO,
			//���� Ŭ���̾�Ʈ ĳ���� ���� ��� (int ĳ���ͼ� ,(int �����ڵ�, string �г���)...)
			SERVER_RE_CHAR_INFO,
			//Ŭ���̾�Ʈ ĳ���� ���� ��û (int �����ڵ�, string �г���)
			CLIENT_REQ_CREATE_CHAR,
			//���� ĳ���� ������û ��� (bool)
			SERVER_RE_CREATE_CHAR,
			//Ŭ���ƾ�Ʈ ĳ���� ����(string)
			CLIENT_REQ_SELECT_CHAR,
			//���� ĳ���� ���� ��� (bool, int �����ڵ�, string �г���)
			SERVER_RE_SELECT_CHAR,
			//Ŭ���̾�Ʈ ĳ���� ����(string)
			CLIENT_REQ_DELETE_CHAR,
			//���� ĳ���� ���� ���(bool)
			SERVER_RE_DELETE_CHAR,

		};
	}
	//byte


}



#endif // !_PROTOCOL_H_
