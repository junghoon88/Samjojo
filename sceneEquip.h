#pragma once
#include "gameNode.h"
#include "Player.h"

class sceneEquip : public gameNode
{
private:
	Player*	_player;
public:

	void setLinkAdressPlayer(Player* player) { _player = player; }
	sceneEquip();
	~sceneEquip();
};

