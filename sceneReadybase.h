#pragma once
#include "gameNode.h"
#include "Player.h"
#include "Enemy.h"
#include "Friend.h"
#include "scanDialog.h"

class sceneReadybase : public gameNode
{
	image* _baseImg;
	image* _baseImg2;
	POINT _pt;
	RECT _rcPosUI, _rcEquipUI, _rcBuyUI, _rcSellUI;
	scanDialog* _sD;

	vUnits _vUnits;
	bool _posClicking;
	bool _equipClicking;
	bool _buyClicking;
	bool _sellClicking;
	bool _isSound;
	bool _battleStart;

public:

	Player* _player;

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

public:
	void setLinkAdressPlayer(Player* player) { _player = player; }

	sceneReadybase();
	~sceneReadybase();
};

