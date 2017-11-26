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

	image*		_imgMap;		//실제 보여줄 맵
	int			_tilesizeX;		//타일크기(맵에 타일이 총 몇개인지)
	int			_tilesizeY;		//타일크기(맵에 타일이 총 몇개인지)


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
	void loadData(int num);

	//타일 정보 접근자
	tagTile* getTile(void) { return _tiles; }
	DWORD* getAttribute(void) { return _attribute; }


public:
	inline void setLinkAdressPlayer(Player* player) { _player = player; }
	inline void setLinkAdressFriend(Friend* friends) { _friend = friends; }
	inline void setLinkAdressEnemy(Enemy* enemy) { _enemy = enemy; }

	inline int getTileSizeX(void) { return _tilesizeX; }
	inline int getTileSizeY(void) { return _tilesizeY; }
};

