#pragma once
#include "gameNode.h"
#include "Player.h"
#include "Enemy.h"
#include "Friend.h"

class sceneSell : public gameNode
{
private:
	Player*		_player;	//플레이어
	Friend*		_friend;	//아군
	Enemy*		_enemy;		//적군

public:
	sceneSell();
	~sceneSell();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

public:
	void setLinkAdressPlayer(Player* player) { _player = player; }
	void setLinkAdressEnemy(Enemy* enemy) { _enemy = enemy; }
	void setLinkAdressFriend(Friend* friends) { _friend = friends; }
};

