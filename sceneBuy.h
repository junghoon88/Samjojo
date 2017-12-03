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

	ItemWeapon* _weaponList, *_weaponB;
	ItemArmor* _armorList, *_armorB;
	ItemSpecial* _specialList, *_specialB;



	Player*		_player;

	FONTVERSION _fontNum;

	button* _EXIT;
	POINT _pt;
	RECT _baseRC[2];

	RECT _listRC[12];
	
	float _messageTime;

	bool _buyed;
	bool _notbuyed;
	bool _base1;              //무기상 도구상 구분

	int _gold;
public:
	sceneBuy();
	~sceneBuy();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void setLinkAdressPlayer(Player* player) { _player = player; }

	static void selectExit(void* obj);


	inline vItems getVItems(void) { return _vItems; }
	void buyItem(void);
	void exit(void);
};

