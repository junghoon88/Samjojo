#pragma once
#include "gameNode.h"
#include "Player.h"
#include "Enemy.h"
#include "Friend.h"
#include "gameMap.h"

class sceneBattle : public gameNode
{
private:
	Player*		_player;	//플레이어
	Friend*		_friend;	//아군
	Enemy*		_enemy;		//적군

	gameMap*	_map;		//게임 맵

private:
	void initImage(void);
	void initSound(void);

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);


	sceneBattle();
	~sceneBattle();

public:
	inline void setLinkAdressPlayer(Player* player) { _player = player; }
	inline void setLinkAdressEnemy(Enemy* enemy) { _enemy = enemy; }
	inline void setLinkAdressFriend(Friend* friends) { _friend = friends; }
	inline void setLinkAdressMap(gameMap* map) { _map = map; }

};

