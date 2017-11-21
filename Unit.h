#pragma once
#include "Item.h"

#define UNIT_ATTACK_RANGE_MAX 7

struct tagStatus
{
	TCHAR name[30];
	TCHAR family[30];	//�δ�
	TCHAR aos[30];		//����

	bool isLive;
	int enterScenario; //���� ������ �ó�����(�� ��ġ ���� �ó����� ��������)
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

	//������ �����ϴ� ��ġ
	int LvPerHPMax;
	int LvPerMPMax;
	int LvPerAtk;		//���ݷ�
	int LvPerDep;		//����
	int LvPerRes;		//���ŷ�
	int LvPerAgl;		//���߷�
	int LvPerFig;		//���
	int LvPerPwr;		//����
	int LvPerLds;		//���
	int LvPerInt;		//����
	int LvPerDex;		//��ø
	int LvPerLuk;		//��

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
	image*			_imgFace;
	image*			_imgStory;
	image*			_imgBattle;
	POINT			_pt;
	RECT			_rc;
	POINT			_tilePt;	//Ÿ�� ��ȣ

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
	inline void setImages(TCHAR* strFace, TCHAR* strNormal, TCHAR* strCombat)
	{
		_imgFace = IMAGEMANAGER->findImage(strFace);
		_imgStory = IMAGEMANAGER->findImage(strNormal);
		_imgBattle = IMAGEMANAGER->findImage(strCombat);
	}
};

typedef vector<Unit*>	vUnits;
typedef vector<Unit*>::iterator	viUnits;

