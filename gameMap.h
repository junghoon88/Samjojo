#pragma once
#include "gameNode.h"
#include "tileNode.h"

class Player;
class Friend;
class Enemy;

class gameMap : public gameNode
{
private:
	tagTile _tiles[TILEX * TILEY];	 // Ÿ��
	DWORD _attribute[TILEX * TILEY]; // Ÿ�� �Ӽ�

	TCHAR _strSampleImgKey[SAMPLETILEX * SAMPLETILEY][100];

	TCHAR _objImage[OBJECTSELECT_MAX][100];

	int _pos[2];

	Player*		_player;	//�÷��̾�
	Friend*		_friend;	//�Ʊ�
	Enemy*		_enemy;		//����


public:
	gameMap();
	~gameMap();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//�������� �׸� �� �ε��Լ�
	void load();

	//Ÿ�� ���� ������
	tagTile* getTile(void) { return _tiles; }
	DWORD* getAttribute(void) { return _attribute; }

	//1p, 2p ������ 
	int getPosFirst() { return _pos[0]; }
	int getPosSecond() { return _pos[1]; }

public:
	inline void setLinkAdressPlayer(Player* player) { _player = player; }
	inline void setLinkAdressFriend(Friend* friends) { _friend = friends; }
	inline void setLinkAdressEnemy(Enemy* enemy) { _enemy = enemy; }

};

