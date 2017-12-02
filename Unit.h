#pragma once
#include "gameNode.h"
#include "Item.h"
#include "aStar.h"
#include "gameMap.h"

#define MAXDEF 100
#define MAXLVL 50

#define TESTITEM 1

struct tagStatus //기본정보 (수정하지말것)
{
	TCHAR name[32];
	TCHAR family[32];	//부대
	TCHAR aos[32];		//병과

	TEAM team;

	//이미지
	image*			imgFace;
	int				numImagFace;

	bool isLive;
	int enterScenario; //출전 가능한 시나리오(이 수치 이후 시나리오 출전가능)
	int level;
	int exp;
	int expMax;
	int movePoint;
	int HP;
	int HPMax;
	int MP;
	int MPMax;
	int Atk;		//공격력
	int Dep;		//방어력
	int Res;		//정신력
	int Agl;		//순발력
	int Fig;		//사기		↑변화스탯
	int Pwr;		//무력		↓고정스탯
	int Lds;		//통솔
	int Int;		//지력
	int Dex;		//민첩
	int Luk;		//운	

	//기본 수치
	int InitHPMax;
	int InitMPMax;
	int InitAtk;		//공격력 = 무력/2
	int InitDep;		//방어력 = 통솔/2
	int InitRes;		//정신력 = 지력/2
	int InitAgl;		//순발력 = 민첩/2
	int InitFig;		//사기
	int InitPwr;		//무력
	int InitLds;		//통솔
	int InitInt;		//지력
	int InitDex;		//민첩
	int InitLuk;		//운

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

	//아이템 증가 수치
	int ItemPlusHPMax;
	int ItemPlusMPMax;
	int ItemPlusAtk;		//공격력
	int ItemPlusDep;		//방어력
	int ItemPlusRes;		//정신력
	int ItemPlusAgl;		//순발력
	int ItemPlusFig;		//사기
	int ItemPlusPwr;		//무력
	int ItemPlusLds;		//통솔
	int ItemPlusInt;		//지력
	int ItemPlusDex;		//민첩
	int ItemPlusLuk;		//운

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
	UNITSTATE_IDLE,	  //기본상태
	UNITSTATE_TIRED,  
	UNITSTATE_ATK,	  //공격상태
	UNITSTATE_DEF,	  //방어상태
	UNITSTATE_HIT,    //피격상태
	UNITSTATE_VIC,    //승리

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
	BOOL			valid; //행동 가능하면 true, 행동 했으면 false
	BOOL			moved;//플레이어용. 움직였나 안움직였나 체크 -> 움직였지만 추가 명령 가능상태 구분용.

	POINT			pt;
	RECT			rc;
	POINT			tilePt;	//타일 번호
	POINT			tilePtNext;
	POINT			tilePtEnemy;
	BOOL			findEnemy;


	DIRECTION		dir;

	UNITSTATE		unitState;
	UNITCONDITION   unitCondition;

	//이미지 프레임
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
	bool			isHiding;	//은신상태 여부
	bool			isMoving;	//움직이는중
	bool			isAtking;	//공격중
	bool			isHiting;	//피격중
};

//유닛에디터에서 저장할 정보들 모음 (수정하지말것)
struct tagUnitSaveInfo
{
	//기본 정보
	tagStatus		status;

	//아이템 번호
	ITEMW_NUMBER	wNum;
	ITEMA_NUMBER	aNum;
	ITEMS_NUMBER	sNum;


	//battle 관련 변수
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


	//battle 관련 변수
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
				//여기다가 해당 인덱스로 가라고 신호를 넣어주면 되겠죠??
				return true;
				break;
			}
		}
		return false;
	};//인덱스 받아서 인덱스로 해당타일 있으면 트루값 반환 해주자 없으면 빠꾸

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
	inline void moveBack(POINT backPT) // 이동한거 취소용.
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

