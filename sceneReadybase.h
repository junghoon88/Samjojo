#pragma once
#include "gameNode.h"
#include "Player.h"
#include "Enemy.h"
#include "Friend.h"
class sceneReadybase : public gameNode
{
	image* _baseImg;
	POINT _pt;
	RECT _rcPosUI, _rcEquipUI, _rcBuyUI, _rcSellUI;
	Player* _player;

	bool _posClicking;
public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

public:
	void setLinkAdressPlayer(Player* player) { _player = player; }

	sceneReadybase();
	~sceneReadybase();
};

