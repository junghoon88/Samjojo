#pragma once
#include "Item.h"

#define UNIT_ATTACK_RANGE_MAX 7

struct tagStatus
{
	TCHAR name[32];
	TCHAR family[32];	//�δ�
	TCHAR aos[32];		//����

	bool isLive;
	int enterScenario; //���� ������ �ó�����(�� ��ġ ���� �ó����� ��������)
	int level;
	int exp;
	int expMax;
	int movePoint;
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

	//�⺻ ��ġ
	int InitHPMax;
	int InitMPMax;
	int InitAtk;		//���ݷ�
	int InitDep;		//����
	int InitRes;		//���ŷ�
	int InitAgl;		//���߷�
	int InitFig;		//���
	int InitPwr;		//����
	int InitLds;		//���
	int InitInt;		//����
	int InitDex;		//��ø
	int InitLuk;		//��

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

	//������ ���� ��ġ
	int ItemPlusHPMax;
	int ItemPlusMPMax;
	int ItemPlusAtk;		//���ݷ�
	int ItemPlusDep;		//����
	int ItemPlusRes;		//���ŷ�
	int ItemPlusAgl;		//���߷�
	int ItemPlusFig;		//���
	int ItemPlusPwr;		//����
	int ItemPlusLds;		//���
	int ItemPlusInt;		//����
	int ItemPlusDex;		//��ø
	int ItemPlusLuk;		//��
};

enum FRAME_ATK
{
	FRAME_ATK_DOWN,
	FRAME_ATK_UP,
	FRAME_ATK_LEFT,
	FRAME_ATK_RIGHT,

	FRAME_ATK_MAX
};

enum FRAME_IDLE
{
	FRAME_IDLE_DOWN,
	FRAME_IDLE_UP,
	FRAME_IDLE_LEFT,
	FRAME_IDLE_RIGHT,
	FRAME_IDLE_TIRED,

	FRAME_IDLE_MAX
};

enum FRAME_SPC
{
	FRAME_SPC_DEF_UP,
	FRAME_SPC_DEF_DOWN,
	FRAME_SPC_DEF_LEFT,
	FRAME_SPC_DEF_RIGHT,
	FRAME_SPC_HIT,
	FRAME_SPC_VIC,

	FRAME_SPC_MAX
};

enum UNITSTATE
{
	UNITSTATE_IDLE,	  //�⺻����
	UNITSTATE_ATK,	  //���ݻ���
	UNITSTATE_DEF,	  //������
	UNITSTATE_HIT,    //�ǰݻ���
	UNITSTATE_VIC,    //�¸�
	UNITSTATE_TIRED,  

	UNITSTATE_MAX
};

enum UNITCONDITION
{
	UNITCONDITION_NORMAL,

	UNITCONDITION_MAX
};

struct tagBattleState
{
	BOOL			valid; //�ൿ �����ϸ� true, �ൿ ������ false

	POINT			pt;
	RECT			rc;
	POINT			tilePt;	//Ÿ�� ��ȣ

	UNITSTATE		unitState;
	UNITCONDITION   unitCondition;

	//�̹��� ������
	image*			imgBattleAtk;
	image*			imgBattleIdle;
	image*			imgBattleSpc;
	FRAME_ATK		frameAtk;
	FRAME_IDLE		frameIdle;
	FRAME_SPC		frameSpc;
};

class Unit
{
private:
	typedef BOOL(*Temp)[UNIT_ATTACK_RANGE_MAX];

protected:
	tagStatus		_status;

	ItemWeapon*		_itemW;
	ItemArmor*		_itemA;
	ItemSpecial*	_itemS;

	TEAM			_team;

	//�̹���
	image*			_imgFace;

	BOOL			_atkRange[UNIT_ATTACK_RANGE_MAX][UNIT_ATTACK_RANGE_MAX];
	

	//battle ���� ����
	tagBattleState	_battleState;

public:
	Unit();
	~Unit();

	void init(void);

public:
	inline tagStatus getStatus(void) { return _status; }
	inline void setStatus(tagStatus status) { _status = status; }
	inline ItemWeapon* getItemW(void) { return _itemW; }
	inline void setItemW(ItemWeapon* itemw) { _itemW = itemw; }
	inline ItemArmor* getItemA(void) { return _itemA; }
	inline void setItemA(ItemArmor* itema) { _itemA = itema; }
	inline ItemSpecial*	getItemS(void) { return _itemS; }
	inline void setItemS(ItemSpecial* items) { _itemS = items; }
	inline TEAM getTeam(void) { return _team; }
	inline void setTeam(TEAM team) { _team = team; }
	inline void setImageFace(TCHAR* filename) { }

	inline Temp getAtkRange(void) { return _atkRange; }
	inline void setAtkRange(BOOL(*range)[UNIT_ATTACK_RANGE_MAX]) { memcpy(_atkRange, range, sizeof(BOOL) * UNIT_ATTACK_RANGE_MAX* UNIT_ATTACK_RANGE_MAX); }

	inline tagBattleState getBattleState(void) { return _battleState; }
	inline void setBattleState(tagBattleState state) { _battleState = state; }
};

typedef vector<Unit*>	vUnits;
typedef vector<Unit*>::iterator	viUnits;

