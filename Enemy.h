#pragma once
#include "gameNode.h"
#include "Unit.h"
#include "aStar.h"

class Player;
class Friend;
class gameMap;

class Enemy : public gameNode
{
private:
	vUnits _vUnits;

	Player*		_player;	//플레이어
	Friend*		_friend;	//아군
	gameMap*	_map;

public:
	Enemy();
	~Enemy();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void loadUnits(void);
	void deleteUnits(void);


public:
	inline vUnits getUnits(void) { return _vUnits; }

	inline void setLinkAdressPlayer(Player* player) { _player = player; }
	inline void setLinkAdressFriend(Friend* friends) { _friend = friends; }
	inline void setLinkAdressMap(gameMap* map) { _map = map; }
};

