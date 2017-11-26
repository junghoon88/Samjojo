#pragma once
#include "Item.h"

#define UNIT_ATTACK_RANGE_MAX 7

struct tagStatus
{
	TCHAR name[32];
	TCHAR family[32];	//부대
	TCHAR aos[32];		//병과

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
	int Fig;		//사기
	int Pwr;		//무력
	int Lds;		//통솔
	int Int;		//지력
	int Dex;		//민첩
	int Luk;		//운

	//기본 수치
	int InitHPMax;
	int InitMPMax;
	int InitAtk;		//공격력
	int InitDep;		//방어력
	int InitRes;		//정신력
	int InitAgl;		//순발력
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
	UNITSTATE_IDLE,	  //기본상태
	UNITSTATE_ATK,	  //공격상태
	UNITSTATE_DEF,	  //방어상태
	UNITSTATE_HIT,    //피격상태
	UNITSTATE_VIC,    //승리
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
	BOOL			valid; //행동 가능하면 true, 행동 했으면 false

	POINT			pt;
	RECT			rc;
	POINT			tilePt;	//타일 번호

	UNITSTATE		unitState;
	UNITCONDITION   unitCondition;

	//이미지 프레임
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

	//이미지
	image*			_imgFace;

	BOOL			_atkRange[UNIT_ATTACK_RANGE_MAX][UNIT_ATTACK_RANGE_MAX];
	

	//battle 관련 변수
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

