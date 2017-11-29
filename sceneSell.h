#pragma once
#include "gameNode.h"
#include "Player.h"
#include "Enemy.h"
#include "Friend.h"

class sceneSell : public gameNode
{
private:
	Player* _player;


public:
	sceneSell();
	~sceneSell();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void setLinkAdressPlayer(Player* player) { _player = player; }
};

