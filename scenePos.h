#pragma once
#include "gameNode.h"
#include "Player.h"
#include "Enemy.h"
#include "Friend.h"
#include "button.h"
struct tagPos {
	TCHAR name[32];
	RECT posRC;
	bool isPos;
};

class scenePos : public gameNode
{
private:
	image* _posImg;
	POINT _pt;

	RECT _rcCancel;
	RECT _rcOK;

	vUnits _vUnits;
	vUnits _vUnitsInFile;

	tagPos _posUnits[7];
	RECT posRC2[7];  //출진리스트에서 제거하기위한 클릭용 rect

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

