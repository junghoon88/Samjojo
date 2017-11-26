#include "stdafx.h"
#include "Unit.h"


Unit::Unit()
{
}


Unit::~Unit()
{
}

HRESULT Unit::init(void)
{
	ZeroMemory(&_status, sizeof(tagStatus));
	_status.isLive = true;
	_status.enterScenario = 1;
	_status.level = 1;

	_itemW = NULL;
	_itemA = NULL;
	_itemS = NULL;

	_team = TEAM_NONE;

	//이미지
	_imgFace = NULL;

	ZeroMemory(&_battleState, sizeof(tagBattleState));

	ZeroMemory(&_atkRange, sizeof(_atkRange));

	return S_OK;
}

void Unit::release(void)
{
}

void Unit::update(void)
{
	switch (_battleState.unitState)
	{
	case UNITSTATE_IDLE:	  //기본상태
		_battleState.frameIdle = (FRAME_IDLE)_battleState.dir;
		break;
	case UNITSTATE_ATK:	  //공격상태
		_battleState.frameAtk = (FRAME_ATK)_battleState.dir;
		break;
	case UNITSTATE_DEF:	  //방어상태
		_battleState.frameSpc = (FRAME_SPC)_battleState.dir;
		break;
	case UNITSTATE_HIT:    //피격상태
		_battleState.frameSpc = FRAME_SPC_HIT;
		break;
	case UNITSTATE_VIC:    //승리
		_battleState.frameSpc = FRAME_SPC_VIC;
		break;
	case UNITSTATE_TIRED:
		_battleState.frameIdle = FRAME_IDLE_TIRED;
		break;
	}
}

void Unit::render(void)
{
	if (!_battleState.imgBattleAtk) return;
	if (!_battleState.imgBattleIdle) return;
	if (!_battleState.imgBattleSpc) return;


	switch (_battleState.unitState)
	{
		case UNITSTATE_IDLE:	  //기본상태
		case UNITSTATE_TIRED:
			_battleState.imgBattleIdle->frameRender(getMemDC(), _battleState.rc.left, _battleState.rc.top, _battleState.frameIdle, 0);
		break;
		case UNITSTATE_ATK:	  //공격상태
			_battleState.imgBattleAtk->frameRender(getMemDC(), _battleState.rc.left, _battleState.rc.top, _battleState.frameAtk, 0);
		break;
		case UNITSTATE_DEF:	  //방어상태
		case UNITSTATE_HIT:    //피격상태
		case UNITSTATE_VIC:    //승리
			_battleState.imgBattleSpc->frameRender(getMemDC(), _battleState.rc.left, _battleState.rc.top, _battleState.frameSpc, 0);
		break;
	}
}
