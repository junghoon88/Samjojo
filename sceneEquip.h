#pragma once
#include "gameNode.h"
#include "Player.h"
#include "button.h"
enum BTN {
	BTN_NEXT,
	BTN_PREV,
	BTN_EXIT,

	BTN_MAXX
};
class sceneEquip : public gameNode
{
private:
	image* _baseUI;
	image* _chosang;

	vUnits _vUnitsInFile;

	button* _button[BTN_MAXX];

	TCHAR _name[32];
	TCHAR _aos[32];

	FONTVERSION _fontNum;

	TCHAR _name2[7][32];


	int _index;

	int _level;
	int _hpMax;
	int _mpMax;

	int _atk;		//공격력
	int _dep;		//방어력
	int _res;		//정신력
	int _agl;		//순발력
	int _fig;		//사기
	int _move;      //이동력
	
	Player*	_player;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	static void selectNext(void* obj);
	static void selectPrev(void* obj);
	static void selectExit(void* obj);

	void next(void);
	void prev(void);
	void exit(void);

	void setLinkAdressPlayer(Player* player) { _player = player; }
	sceneEquip();
	~sceneEquip();
};

