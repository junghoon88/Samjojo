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

	//�̹���
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
	case UNITSTATE_IDLE:	  //�⺻����
		_battleState.frameIdle = (FRAME_IDLE)_battleState.dir;
		break;
	case UNITSTATE_ATK:	  //���ݻ���
		_battleState.frameAtk = (FRAME_ATK)_battleState.dir;
		break;
	case UNITSTATE_DEF:	  //������
		_battleState.frameSpc = (FRAME_SPC)_battleState.dir;
		break;
	case UNITSTATE_HIT:    //�ǰݻ���
		_battleState.frameSpc = FRAME_SPC_HIT;
		break;
	case UNITSTATE_VIC:    //�¸�
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
		case UNITSTATE_IDLE:	  //�⺻����
		case UNITSTATE_TIRED:
			_battleState.imgBattleIdle->frameRender(getMemDC(), _battleState.rc.left - MAINCAMERA->getCameraX(), _battleState.rc.top - MAINCAMERA->getCameraY(), _battleState.frameIdle, 0);
		break;
		case UNITSTATE_ATK:	  //���ݻ���
			_battleState.imgBattleAtk->frameRender(getMemDC(), _battleState.rc.left, _battleState.rc.top, _battleState.frameAtk, 0);
		break;
		case UNITSTATE_DEF:	  //������
		case UNITSTATE_HIT:    //�ǰݻ���
		case UNITSTATE_VIC:    //�¸�
			_battleState.imgBattleSpc->frameRender(getMemDC(), _battleState.rc.left, _battleState.rc.top, _battleState.frameSpc, 0);
		break;
	}
}

void Unit::loadUnitData(tagUnitSaveInfo &info)
{
	//�⺻ ����
	memcpy(&_status, &info.status, sizeof(tagStatus));

	TCHAR strFaceKey[100];
	_stprintf(strFaceKey, L"face %05d", _status.numImagFace);
	_status.imgFace = IMAGEMANAGER->findImage(strFaceKey);

	//������ ��ȣ
	_itemW = NULL; //wNum ���� �ε��ϵ��� ����
	_itemA = NULL; //aNum ���� �ε��ϵ��� ����
	_itemS = NULL; //sNum ���� �ε��ϵ��� ����

	//battle ���� ����
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
	//�⺻ ����
	memcpy(&_status, &unit->getStatus(), sizeof(tagStatus));

	//������ ��ȣ
	_itemW = unit->getItemW();
	_itemA = unit->getItemA();
	_itemS = unit->getItemS();

	//battle ���� ����
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
