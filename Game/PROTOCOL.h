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
			//Ŭ���̾�Ʈ �� ���� ��û (int ���ڵ�)
			CLIENT_REQ_MAP_ENTER,
			//���� �� ���� ��û ��� (int ĳ���ͼ�, ĳ�����ڵ�,�̸�,����,��ǥ... int ���ͼ�...)
			SERVER_RE_MAP_ENTER,
			//�ʿ� ���ο� ���� �α��� (ulong string int)
			SERVER_PLAYER_ENTER,
			//�ʿ� ������ ���� (ulong)
			SERVER_PLAYER_OUT,
			//Ŭ���̾�Ʈ->���� ä��
			CLIENT_SEND_CHAT,
			//����->Ŭ���̾�Ʈ ä��
			SERVER_SEND_CHAT,
			//Ŭ���̾�Ʈ ĳ���� �̵� ������ (float x,float y,bool way)
			CLIENT_SEND_MOVE_DATA,
			//���� ĳ���� �̵� ������ (float x,float y,bool way)
			SERVER_SEND_MOVE_DATA,
			//Ŭ���̾�Ʈ ĳ���� ����
			CLIENT_SEND_JUMP_DATA,
			//���� ĳ���� ���� (ulong 
			SERVER_SEND_JUMP_DATA,
			//Ŭ���̾�Ʈ ��Ƽ ������û
			CLIENT_REQ_CREATE_PARTY,
			//���� ��Ƽ ���� ��û ���
			SERVER_RE_CREATE_PARTY,
			//Ŭ���̾�Ʈ ��Ƽ ���� ��û
			CLIENT_REQ_PARTY_INFO,
			//���� ��Ƽ ���� ��û ���
			SERVER_RE_PARTY_INFO,
			//���� ��Ƽ Ż�� (ulong
			SERVER_PARTY_OUT,
			//Ŭ���̾�Ʈ ��Ƽ �ʴ� (ulong 
			CLIENT_REQ_PARTY_INVITE,
			//���� ��ġ �ʴ� �޼��� (string id
			SERVER_PARTY_INVITE_MSG,
			//Ŭ���̾�Ʈ ��Ƽ �ʴ� �޼��� (bool , string id, 
			CLIENT_PARTY_INVITE_MSG,
			//��Ƽ ��� ���� (int , code, 
			SERVER_PARTY_MEMBER_DATA,
			//Ŭ���̾�Ʈ ���� ���� ��û
			CLIENT_REQ_ENTER_DUNGEON,
			//���� ���� ���� ��û ���
			SERVER_RE_ENTER_DUNGEON,
			//Ŭ���̾�Ʈ ���� ���� ��û 
			CLIENT_REQ_DUNGEON_DATA,
			//���� ���� ���� ��û ��� 
			SERVER_RE_DUNGEON_DATA,
		};
	}
	//byte


}



#endif // !_PROTOCOL_H_
