#pragma once
#include "gameNode.h"
#include "Player.h"
#include "Enemy.h"
#include "Friend.h"
#include "button.h"
#include "Item.h"

class sceneBuy : public gameNode
{
private:
	typedef vector<Item*>	vItems;
	typedef vector<Item*>::iterator	viItems;

	image* _baseUI;
	image* _baseUI2;

	vItems _vItemlist;        //상점목록
	vItems _vItems;           //구매한놈들

	Player*		_player;

	button* _EXIT;
	button* _OK;
	button* _CANCEL;
	bool _base1;              //무기상 도구상 구분
public:
	sceneBuy();
	~sceneBuy();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void setLinkAdressPlayer(Player* player) { _player = player; }

	static void selectExit(void* obj);
	static void selectOK(void* obj);
	static void selectCancel(void* obj);

	inline vItems getVItems(void) { return _vItems; }
	void buyItem(void);
	void cancel(void);
	void exit(void);
};

