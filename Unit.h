#pragma once
#include "Item.h"


struct tagStatus
{
	TCHAR name[30];
	int level;
	int exp;
	int expMax;
	int HP;
	int HPMax;
	int MP;
	int MPMax;
	int Atk;		//���ݷ�
	int Dep;		//����
	int Res;		//���ŷ�
	int Agl;		//���߷�
	int Fig;		//���
	int Pwr;		//����
	int Lds;		//���
	int Int;		//����
	int Dex;		//��ø
	int Luk;		//��
};

class Unit
{
protected:
	tagStatus		_status;
	ItemWeapon*		_itemW;
	ItemArmor*		_itemA;
	ItemSpecial*	_itemS;

	TEAM			_team;

	//�̹���
	image*			_img;
	POINT			_pt;
	RECT			_rc;
	POINT			_tilePt;	//Ÿ�� ��ȣ

	


public:
	Unit();
	~Unit();

public:
	inline tagStatus getStatus(void) { return _status; }
	inline void setStatus(tagStatus status) { _status = status; }
	inline ItemWeapon* getItemW(void) { return _itemW; }
	inline void setItemW(ItemWeapon* itemw) { _itemW = itemw; }
	inline ItemArmor* getItemA(void) { return _itemA; }
	inline void setItemA(ItemArmor* itema) { _itemA = itema; }
	inline ItemSpecial*	getItemS(void) { return _itemS; }
	inline void setItemS(ItemSpecial* items) { _itemS = items; }
};

typedef vector<Unit*>	vUnits;
typedef vector<Unit*>::iterator	viUnits;

