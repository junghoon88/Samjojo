#pragma once
#include "gameNode.h"
#include "Item.h"
#include "aStar.h"
#include "gameMap.h"


struct tagStatus
{
	TCHAR name[32];
	TCHAR family[32];	//�δ�
	TCHAR aos[32];		//����

	TEAM team;

	//�̹���
	image*			imgFace;
	int				numImagFace;

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

	BOOL			atkRange[UNIT_ATTACK_RANGE_MAX][UNIT_ATTACK_RANGE_MAX];
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
	FRAME_SPC_DEF_DOWN,
	FRAME_SPC_DEF_UP,
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
	POINT			tilePtNext;
	POINT			tilePtEnemy;
	BOOL			findEnemy;


	DIRECTION		dir;

	UNITSTATE		unitState;
	UNITCONDITION   unitCondition;

	//�̹��� ������
	image*			imgBattleAtk;
	image*			imgBattleIdle;
	image*			imgBattleSpc;

	int				numImgBattleAtk;
	int				numImgBattleIdle;
	int				numImgBattleSpc;

	FRAME_ATK		frameAtk;
	FRAME_IDLE		frameIdle;
	FRAME_SPC		frameSpc;

	bool			isHiding;	//���Ż��� ����
	bool			isMoving;
};

//���ֿ����Ϳ��� ������ ������ ����
struct tagUnitSaveInfo
{
	//�⺻ ����
	tagStatus		status;

	//������ ��ȣ
	ITEMW_NUMBER	wNum;
	ITEMA_NUMBER	aNum;
	ITEMS_NUMBER	sNum;


	//battle ���� ����
	int				numImgBattle;
};


class Unit : public gameNode
{
private:
	typedef BOOL(*Temp)[UNIT_ATTACK_RANGE_MAX];

protected:
	tagStatus		_status;

	ItemWeapon*		_itemW;
	ItemArmor*		_itemA;
	ItemSpecial*	_itemS;


	//battle ���� ����
	tagBattleState	_battleState;

	gameMap*		_map; 
	aStar*			_astar;
	vector<tile*>	_moveArea;

public:
	Unit();
	~Unit();

	HRESULT init(gameMap* map);
	void release(void);
	void update(void);
	void render(void);

	void loadUnitData(tagUnitSaveInfo &info);
	void copyUnitData(Unit* unit);

	void move(void);
	void move(DIRECTION dir);
	void findEnemy(TEAM myTeam);
	void findMoveArea(void);
	void showMoveArea(void);

public:
	inline tagStatus getStatus(void) { return _status; }
	inline void setStatus(tagStatus status) { _status = status; }
	inline ItemWeapon* getItemW(void) { return _itemW; }
	inline void setItemW(ItemWeapon* itemw) { _itemW = itemw; }
	inline ItemArmor* getItemA(void) { return _itemA; }
	inline void setItemA(ItemArmor* itema) { _itemA = itema; }
	inline ItemSpecial*	getItemS(void) { return _itemS; }
	inline void setItemS(ItemSpecial* items) { _itemS = items; }
	inline int getImgBattleIdle(void) { return _battleState.numImgBattleAtk; }
	inline int getImgBattleAtk(void) { return _battleState.numImgBattleAtk; }
	inline int getImgBattleSpc(void) { return _battleState.numImgBattleSpc; }
	inline void setLinkAdressAStar(aStar* astar) { _astar = astar; }



	inline void setImgBattleIdle(int num)
	{
		_battleState.numImgBattleIdle = num;
		TCHAR strKey[100];
		if (num < UNIT_BATTLE_IMAGE1)
		{
			_stprintf(strKey, L"unit%d-atk", _battleState.numImgBattleIdle);
		}
		else
		{
			_stprintf(strKey, L"unit%d-%d-atk", _battleState.numImgBattleIdle, _status.team);
		}
		_battleState.imgBattleAtk = IMAGEMANAGER->findImage(strKey);
	}
	inline void setImgBattleAtk(int num)
	{
		_battleState.numImgBattleAtk = num;
		TCHAR strKey[100];
		if (num < UNIT_BATTLE_IMAGE1)
		{
			_stprintf(strKey, L"unit%d-atk", _battleState.numImgBattleAtk);
		}
		else
		{
			_stprintf(strKey, L"unit%d-%d-atk", _battleState.numImgBattleAtk, _status.team);
		}
		_battleState.imgBattleAtk = IMAGEMANAGER->findImage(strKey);
	}
	inline void setImgBattleSpc(int num)
	{
		_battleState.numImgBattleSpc = num;
		TCHAR strKey[100];
		if (num < UNIT_BATTLE_IMAGE1)
		{
			_stprintf(strKey, L"unit%d-atk", _battleState.numImgBattleSpc);
		}
		else
		{
			_stprintf(strKey, L"unit%d-%d-atk", _battleState.numImgBattleSpc, _status.team);
		}
		_battleState.imgBattleAtk = IMAGEMANAGER->findImage(strKey);
	}

	inline tagBattleState getBattleState(void) { return _battleState; }
	inline RECT getRect(void) { return _battleState.rc; }
	inline void setBattleState(tagBattleState state) { _battleState = state; }
};

typedef vector<Unit*>	vUnits;
typedef vector<Unit*>::iterator	viUnits;

