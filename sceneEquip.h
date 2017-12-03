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

	vItems _vItems;        //������ ������
	//vItems _vItemsEquip;   //������ �����ۺ��� ���߿� player _vItems �� �Ѱܾ���

	RECT _rcItm[13];    //���list RC
	RECT _rcItm2[13];   //������RC
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

	int _atk;		//���ݷ�
	int _dep;		//����
	int _res;		//���ŷ�
	int _agl;		//���߷�
	int _fig;		//���
	int _move;      //�̵���
	
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

