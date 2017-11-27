#pragma once
#include "gameNode.h"
#include "Player.h"
#include "Enemy.h"
#include "Friend.h"

class sceneBuy : public gameNode
{
private:
	Player*		_player;


public:
	sceneBuy();
	~sceneBuy();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);


};

