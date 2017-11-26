#pragma once
#include "gameNode.h"
#include "tileNode.h"

class Player;
class Friend;
class Enemy;

class gameMap : public gameNode
{
private:
	tagTile _tiles[TILEX * TILEY];	 // 타일
	DWORD _attribute[TILEX * TILEY]; // 타일 속성

	TCHAR _strSampleImgKey[SAMPLETILEX * SAMPLETILEY][100];

	TCHAR _objImage[OBJECTSELECT_MAX][100];

	int _pos[2];

	Player*		_player;	//플레이어
	Friend*		_friend;	//아군
	Enemy*		_enemy;		//적군


public:
	gameMap();
	~gameMap();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//맵툴에서 그린 맵 로드함수
	void load();

	//타일 정보 접근자
	tagTile* getTile(void) { return _tiles; }
	DWORD* getAttribute(void) { return _attribute; }

	//1p, 2p 포지션 
	int getPosFirst() { return _pos[0]; }
	int getPosSecond() { return _pos[1]; }

public:
	inline void setLinkAdressPlayer(Player* player) { _player = player; }
	inline void setLinkAdressFriend(Friend* friends) { _friend = friends; }
	inline void setLinkAdressEnemy(Enemy* enemy) { _enemy = enemy; }

};

