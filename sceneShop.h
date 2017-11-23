#pragma once
#include "gameNode.h"
#include "Player.h"
#include "Enemy.h"
#include "Friend.h"

class sceneShop : public gameNode
{
private:
	Player*		_player;	//�÷��̾�
	Friend*		_friend;	//�Ʊ�
	Enemy*		_enemy;		//����

public:
	sceneShop();
	~sceneShop();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

public:
	void setLinkAdressPlayer(Player* player) { _player = player; }
	void setLinkAdressEnemy(Enemy* enemy) { _enemy = enemy; }
	void setLinkAdressFriend(Friend* friends) { _friend = friends; }

};

