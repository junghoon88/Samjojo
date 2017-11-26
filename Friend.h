#pragma once
#include "gameNode.h"
#include "Unit.h"

class Player;
class Enemy;
class gameMap;

class Friend : public gameNode
{
private:
	vUnits _vUnits;

	Player*		_player;	//플레이어
	Enemy*		_enemy;		//적군
	gameMap*	_map;

public:
	Friend();
	~Friend();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void loadUnits(void);
	void deleteUnits(void);


public:
	inline vUnits getUnits(void) { return _vUnits; }

	inline void setLinkAdressPlayer(Player* player) { _player = player; }
	inline void setLinkAdressEnemy(Enemy* enemy) { _enemy = enemy; }
	inline void setLinkAdressMap(gameMap* map) { _map = map; }
};

