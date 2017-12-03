#pragma once
#include "gameNode.h"
#include "Player.h"
#include "button.h"
#include "Item.h"

enum BTN {
	BTN_NEXT,
	BTN_PREV,
	BTN_EXIT,

	BTN_MAXX
};

class sceneBuy;

class sceneEquip : public gameNode
{
private:
	typedef vector<Item*>	vItems;
	typedef vector<Item*>::iterator	viItems;

	sceneBuy* _sBuy;

	POINT _pt;
	
	image* _baseUI;
	image* _chosang;

	vUnits _vUnitsInFile;

	vItems _vItems;        //구매한 아이템
	//vItems _vItemsEquip;   //장착된 아이템벡터 나중에 player _vItems 로 넘겨야함

	RECT _rcItm[13];    //장비list RC
	RECT _rcItm2[13];   //장착중RC
	bool _available[13];
	bool _selectIn;
	button* _button[BTN_MAXX];

	ItemWeapon* _weapon, *_weaponU;
	ItemArmor* _armor, *_armorU;
	ItemSpecial* _special, *_specialU;
	
	TCHAR _itemClass[32];

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
	
	bool _availableEquip;
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
	void setLinkAdressSceneBuy(sceneBuy* sbuy) { _sBuy = sbuy; }
	sceneEquip();
	~sceneEquip();
};

