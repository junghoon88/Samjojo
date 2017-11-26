#pragma once
#include "gameNode.h"
#include "Unit.h"

class Friend;
class Enemy;
class gameMap;

class Player : public gameNode
{
private:
	vUnits _vUnits;

	Friend*		_friend;	//�Ʊ�
	Enemy*		_enemy;		//����
	gameMap*	_map;


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

	inline void setLinkAdressFriend(Friend* friends) { _friend = friends; }
	inline void setLinkAdressEnemy(Enemy* enemy) { _enemy = enemy; }
	inline void setLinkAdressMap(gameMap* map) { _map = map; }

};

