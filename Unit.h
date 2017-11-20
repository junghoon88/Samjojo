#pragma once
#include "Item.h"

#define UNIT_ATTACK_RANGE_MAX 7

struct tagStatus
{
	TCHAR name[30];
	bool isLive;
	int level;
	int exp;
	int expMax;
	int HP;
	int HPMax;
	int MP;
	int MPMax;
	int Atk;		//공격력
	int Dep;		//방어력
	int Res;		//정신력
	int Agl;		//순발력
	int Fig;		//사기
	int Pwr;		//무력
	int Lds;		//통솔
	int Int;		//지력
	int Dex;		//민첩
	int Luk;		//운

	//레벨당 증가하는 수치
	int LvPerHPMax;
	int LvPerMPMax;
	int LvPerAtk;		//공격력
	int LvPerDep;		//방어력
	int LvPerRes;		//정신력
	int LvPerAgl;		//순발력
	int LvPerFig;		//사기
	int LvPerPwr;		//무력
	int LvPerLds;		//통솔
	int LvPerInt;		//지력
	int LvPerDex;		//민첩
	int LvPerLuk;		//운

};

class Unit
{
protected:
	tagStatus		_status;
	ItemWeapon*		_itemW;
	ItemArmor*		_itemA;
	ItemSpecial*	_itemS;

	TEAM			_team;

	//이미지
	image*			_imgFace;
	image*			_imgStory;
	image*			_imgBattle;
	POINT			_pt;
	RECT			_rc;
	POINT			_tilePt;	//타일 번호

	BOOL			_atkRange[UNIT_ATTACK_RANGE_MAX][UNIT_ATTACK_RANGE_MAX];
	


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

