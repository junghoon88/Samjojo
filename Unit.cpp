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

	//이미지
	_status.imgFace = NULL;

	_itemW = NULL;
	_itemA = NULL;
	_itemS = NULL;


	ZeroMemory(&_battleState, sizeof(tagBattleState));

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

void Unit::loadUnitData(tagUnitSaveInfo &info)
{
	//기본 정보
	memcpy(&_status, &info.status, sizeof(tagStatus));

	TCHAR strFaceKey[100];
	_stprintf(strFaceKey, L"face %05d", _status.numImagFace);
	_status.imgFace = IMAGEMANAGER->findImage(strFaceKey);

	//아이템 번호
	_itemW = NULL; //wNum 으로 로딩하도록 변경
	_itemA = NULL; //aNum 으로 로딩하도록 변경
	_itemS = NULL; //sNum 으로 로딩하도록 변경

	//battle 관련 변수
	TCHAR strKey[100];
	if (info.numImgBattle < UNIT_BATTLE_IMAGE1)
	{
		_stprintf(strKey, L"unit%d-atk", info.numImgBattle);
		_battleState.imgBattleAtk = IMAGEMANAGER->findImage(strKey);
		_stprintf(strKey, L"unit%d-idle", info.numImgBattle);
		_battleState.imgBattleIdle = IMAGEMANAGER->findImage(strKey);
		_stprintf(strKey, L"unit%d-spc", info.numImgBattle);
		_battleState.imgBattleSpc = IMAGEMANAGER->findImage(strKey);
	}
	else
	{
		_stprintf(strKey, L"unit%d-%d-atk", info.numImgBattle, _status.team);
		_battleState.imgBattleAtk = IMAGEMANAGER->findImage(strKey);
		_stprintf(strKey, L"unit%d-%d-idle", info.numImgBattle, _status.team);
		_battleState.imgBattleIdle = IMAGEMANAGER->findImage(strKey);
		_stprintf(strKey, L"unit%d-%d-spc", info.numImgBattle, _status.team);
		_battleState.imgBattleSpc = IMAGEMANAGER->findImage(strKey);
	}
}

void Unit::copyUnitData(Unit* unit)
{
	//기본 정보
	memcpy(&_status, &unit->getStatus(), sizeof(tagStatus));

	//아이템 번호
	_itemW = unit->getItemW();
	_itemA = unit->getItemA();
	_itemS = unit->getItemS();

	//battle 관련 변수
	memcpy(&_battleState, &unit->getBattleState(), sizeof(tagBattleState));
}

void Unit::move(gameMap* map, DIRECTION dir)
{
	_battleState.dir = dir;

	//move
	switch (dir)
	{
	case DIRECTION_DN:
		_battleState.tilePt.y += 1;
		break;
	case DIRECTION_UP:
		_battleState.tilePt.y -= 1;
		break;
	case DIRECTION_LF:
		_battleState.tilePt.x -= 1;
		break;
	case DIRECTION_RG:
		_battleState.tilePt.x += 1;
		break;
	}

	//collision check
	switch (dir)
	{
	case DIRECTION_DN:
		if (_battleState.tilePt.y >= map->getTileSizeY())
		{
			_battleState.tilePt.y -= 1;
		}
		break;
	case DIRECTION_UP:
		if (_battleState.tilePt.y < 0)
		{
			_battleState.tilePt.y += 1;
		}
		break;
	case DIRECTION_LF:
		if (_battleState.tilePt.x < 0)
		{
			_battleState.tilePt.x += 1;
		}
		break;
	case DIRECTION_RG:
		if (_battleState.tilePt.x >= map->getTileSizeX())
		{
			_battleState.tilePt.x -= 1;
		}
		break;
	}
}
