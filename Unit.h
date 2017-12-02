#pragma once
#include "gameNode.h"
#include "Item.h"
#include "aStar.h"
#include "gameMap.h"

#define MAXDEF 100
#define MAXLVL 50

#define TESTITEM 1

struct tagStatus //�⺻���� (������������)
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
	int Fig;		//���		�躯ȭ����
	int Pwr;		//����		���������
	int Lds;		//���
	int Int;		//����
	int Dex;		//��ø
	int Luk;		//��	

	//�⺻ ��ġ
	int InitHPMax;
	int InitMPMax;
	int InitAtk;		//���ݷ� = ����/2
	int InitDep;		//���� = ���/2
	int InitRes;		//���ŷ� = ����/2
	int InitAgl;		//���߷� = ��ø/2
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
	UNITSTATE_TIRED,  
	UNITSTATE_ATK,	  //���ݻ���
	UNITSTATE_DEF,	  //������
	UNITSTATE_HIT,    //�ǰݻ���
	UNITSTATE_VIC,    //�¸�

	UNITSTATE_MAX
};

enum UNITCONDITION
{
	UNITCONDITION_NORMAL,

	UNITCONDITION_MAX
};

enum UNITSEQUENCE
{
	UNITSEQUENCE_TURNON,
	UNITSEQUENCE_MOVE,
	UNITSEQUENCE_ATTACK,
	UNITSEQUENCE_COUNTER,
	UNITSEQUENCE_IDLE,
	UNITSEQUENCE_TURNOFF,


};

struct tagBattleState
{
	BOOL			valid; //�ൿ �����ϸ� true, �ൿ ������ false
	BOOL			moved;//�÷��̾��. �������� �ȿ������� üũ -> ���������� �߰� ��� ���ɻ��� ���п�.

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

	UNITSEQUENCE	squence;
	bool			isHiding;	//���Ż��� ����
	bool			isMoving;	//�����̴���
	bool			isAtking;	//������
	bool			isHiting;	//�ǰ���
};

//���ֿ����Ϳ��� ������ ������ ���� (������������)
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

	float _imgFrameTime;
	int _imgFrameY;

	UNITSEQUENCE _oldSeq;

	int _delayTime;

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
	void update(TEAM team);
	void render(void);

	void loadUnitData(tagUnitSaveInfo &info);
	void copyUnitData(Unit* unit);

	bool move(void);
	void move(DIRECTION dir);
	void moveTo(POINT tliePt);
	void attack(Unit* opponent);
	void counterAttack(Unit* opponent);
	void findEnemy(TEAM myTeam, POINT closeEnemyPos);
	void findMoveArea(void);
	void showMoveArea(void);
	void clearMoveArea(void);

	void updateSequence(bool bAuto);
	void updateImage(void);
public:
	inline void updateStatus(void);
	inline void earnExp(int exp) { _status.exp += exp; };
	inline void	expMaxCheck(void);
	inline void useItem(Unit* unit);

public:
	inline tagStatus getStatus(void) { return _status; }
	inline void setStatus(tagStatus status) { _status = status; }
	inline ItemWeapon* getItemW(void) { return _itemW; }
	inline void setItemW(ItemWeapon* itemw) { _itemW = itemw; }
	inline ItemArmor* getItemA(void) { return _itemA; }
	inline void setItemA(ItemArmor* itema) { _itemA = itema; }
	inline ItemSpecial*	getItemS(void) { return _itemS; }
	inline void setItemS(ItemSpecial* items) { _itemS = items; }
	inline int getImgBattleIdle(void) { return _battleState.numImgBattleIdle; }
	inline int getImgBattleAtk(void) { return _battleState.numImgBattleAtk; }
	inline int getImgBattleSpc(void) { return _battleState.numImgBattleSpc; }
	inline void setLinkAdressAStar(aStar* astar) { _astar = astar; }
	inline bool isMovableArea(int index)
	{
		for (int i = 0; i < _moveArea.size(); i++)
		{
			if (_moveArea[i] == NULL) continue;

			int x = _moveArea[i]->getIdX();
			int y = _moveArea[i]->getIdY();

			if (x + y * TILEX == index)
			{
				//����ٰ� �ش� �ε����� ����� ��ȣ�� �־��ָ� �ǰ���??
				return true;
				break;
			}
		}
		return false;
	};//�ε��� �޾Ƽ� �ε����� �ش�Ÿ�� ������ Ʈ�簪 ��ȯ ������ ������ ����

	inline void setUnitState(UNITSTATE state) { _battleState.unitState = state; }
	inline UNITSTATE getUnitState(void) { return _battleState.unitState; }

	inline void setMaxHP(int val) { _status.HPMax = val; }
	inline int getMaxHP(void) { return _status.HPMax; }
	inline void setCurHP(int val) { _status.HP = val; }
	inline int getCurHP(void) { return _status.HP; }

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
	inline void setVaild(bool val) { _battleState.valid = val; }
	inline void setMoved(bool val) { _battleState.moved = val; }
	inline void setDir(DIRECTION dir) { _battleState.dir = dir; }
	inline void moveBack(POINT backPT) // �̵��Ѱ� ��ҿ�.
	{
		_battleState.pt = backPT;
		_battleState.rc = RectMake(_battleState.pt.x - TILESIZE / 2, _battleState.pt.y - TILESIZE / 2, TILESIZE, TILESIZE);
		_battleState.tilePt = { (LONG)(_battleState.pt.x / TILESIZE), (LONG)(_battleState.pt.y / TILESIZE) };
	}
	inline UNITSEQUENCE getUnitSequnce(void) { return _battleState.squence; }
	inline void setUnitSequnce(UNITSEQUENCE squence) { _battleState.squence = squence; }
};

typedef vector<Unit*>	vUnits;
typedef vector<Unit*>::iterator	viUnits;

