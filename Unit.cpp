#include "stdafx.h"
#include "Unit.h"


Unit::Unit()
{
}


Unit::~Unit()
{
}

void Unit::init(void)
{
	ZeroMemory(&_status, sizeof(tagStatus));
	_status.isLive = true;
	_status.enterScenario = 1;
	_status.level = 1;

	_itemW = NULL;
	_itemA = NULL;
	_itemS = NULL;

	_team = TEAM_NONE;

	//ÀÌ¹ÌÁö
	_imgFace = NULL;

	ZeroMemory(&_battleState, sizeof(tagBattleState));

	ZeroMemory(&_atkRange, sizeof(_atkRange));
}

void Unit::setImgFace(int num)
{
	_numImagFace = num;
	TCHAR strFaceKey[100];
	_stprintf(strFaceKey, L"face %05d", _numImagFace);
	_imgFace = IMAGEMANAGER->findImage(strFaceKey);
}
void Unit::setImgNormal(int num) {  }
void Unit::setImgBattleIdle(int num)
{
	_battleState.numImgBattleIdle = num;
	TCHAR strKey[100];
	if (num < UNIT_BATTLE_IMAGE1)
	{
		_stprintf(strKey, L"unit%d-atk", _battleState.numImgBattleIdle);
	}
	else
	{
		_stprintf(strKey, L"unit%d-%d-atk", _battleState.numImgBattleIdle, _team);
	}
	_battleState.imgBattleAtk = IMAGEMANAGER->findImage(strKey);
}
void Unit::setImgBattleAtk(int num)
{
	_battleState.numImgBattleAtk = num;
	TCHAR strKey[100];
	if (num < UNIT_BATTLE_IMAGE1)
	{
		_stprintf(strKey, L"unit%d-atk", _battleState.numImgBattleAtk);
	}
	else
	{
		_stprintf(strKey, L"unit%d-%d-atk", _battleState.numImgBattleAtk, _team);
	}
	_battleState.imgBattleAtk = IMAGEMANAGER->findImage(strKey);
}
void Unit::setImgBattleSpc(int num)
{
	_battleState.numImgBattleSpc = num;
	TCHAR strKey[100];
	if (num < UNIT_BATTLE_IMAGE1)
	{
		_stprintf(strKey, L"unit%d-atk", _battleState.numImgBattleSpc);
	}
	else
	{
		_stprintf(strKey, L"unit%d-%d-atk", _battleState.numImgBattleSpc, _team);
	}
	_battleState.imgBattleAtk = IMAGEMANAGER->findImage(strKey);
}