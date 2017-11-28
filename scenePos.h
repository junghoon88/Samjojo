#pragma once
#include "sceneReadybase.h"
#include "Player.h"
#include "Enemy.h"
#include "Friend.h"
#include "button.h"
struct tagPOS {
	image* _readyImg;  //장수 기본이미지




};
class scenePos : public sceneReadybase
{
private:
	image* _posImg;
	POINT _pt;

	RECT _rcCancel;
	RECT _rcOK;

	

	
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

