#pragma once
#include "gameNode.h"
#include "Unit.h"

class Player;
class Enemy;
class gameMap;
class infoCursor;

class Friend : public gameNode
{
private:
	vUnits		_vUnitsInFile;		//폴더 내 유닛데이터들 전체
	vUnits		_vUnits;			//전투에 출전되는 유닛들

	Player*		_player;	//플레이어
	Enemy*		_enemy;		//적군
	gameMap*	_map;
	infoCursor* info;
public:
	Friend();
	~Friend();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void loadUnits(void);
	void locateUnits(void);
	void deleteUnits(void);


public:
	inline vUnits getUnits(void) { return _vUnits; }

	inline void setLinkAdressPlayer(Player* player) { _player = player; }
	inline void setLinkAdressEnemy(Enemy* enemy) { _enemy = enemy; }
	inline void setLinkAdressMap(gameMap* map) { _map = map; }
	inline void setLinkCursor(infoCursor* cursor) { info = cursor; }
};

