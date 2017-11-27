#pragma once
#include "gameNode.h"
#include "Player.h"
#include "Enemy.h"
#include "Friend.h"
#include "button.h"

class scenePos : public gameNode
{
private:
	image* _posImg;
	POINT _pt;

	RECT _rcCancel;
	RECT _rcOK;

	//HWND _btnOk;
	//HWND _btnCancel;

	
	Player* _player;

	bool _availableOK;
	bool _okClicking;
	bool _cancelClicking;


public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

public:
	void setLinkAdressPlayer(Player* player) { _player = player; }

	scenePos();
	~scenePos();
};

