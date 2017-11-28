#pragma once
#include "gameNode.h"
#include "Unit.h"

class Friend;
class Enemy;
class gameMap;
class infoCursor;

class Player : public gameNode
{
private:
	vUnits		_vUnitsInFile;		//폴더 내 유닛데이터들 전체
	vUnits		_vUnits;			//전투에 출전되는 유닛들

	Friend*		_friend;	//아군
	Enemy*		_enemy;		//적군
	gameMap*	_map;

	infoCursor* info;

public:
	Player();
	~Player();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void loadUnits(void);
	void deleteUnits(void);

public:
	inline vUnits getUnits(void) { return _vUnits; }
	inline void setUnits(vUnits vunits) { _vUnits = vunits; }
	inline vUnits getUnitsInFile(void) { return _vUnitsInFile; }

	inline void setLinkAdressFriend(Friend* friends) { _friend = friends; }
	inline void setLinkAdressEnemy(Enemy* enemy) { _enemy = enemy; }
	inline void setLinkAdressMap(gameMap* map) { _map = map; }
	inline void setLinkCursor(infoCursor* cursor) { info = cursor; }
};

