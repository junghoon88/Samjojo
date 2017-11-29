#include "stdafx.h"
#include "Unit.h"


Unit::Unit()
	: _map(NULL), _astar(NULL)
{
}


Unit::~Unit()
{
}

HRESULT Unit::init(gameMap* map)
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

	_map = map;

	return S_OK;
}

void Unit::release(void)
{
	_moveArea.clear();
}

void Unit::update(void)
{
	if (_battleState.squence == UNITSEQUENCE_MOVE)
	{
		_battleState.isMoving = move();
		if (_battleState.isMoving == FALSE)
		{
			if (_battleState.findEnemy)
			{
				_battleState.squence = UNITSEQUENCE_ATTACK;
			}
			else
			{
				_battleState.squence = UNITSEQUENCE_TURNOFF;
			}
		}
	}

	
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
			_battleState.imgBattleIdle->frameRender(getMemDC(), _battleState.rc.left, _battleState.rc.top, _battleState.frameIdle, 0);
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

	showMoveArea();
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

bool Unit::move(void)
{
	int moveSpeed = TILESIZE / 16;

	POINT ptNext = { (_battleState.tilePtNext.x + 0.5) * TILESIZE,
						(_battleState.tilePtNext.y + 0.5) * TILESIZE };

	if (_battleState.tilePt.x != _battleState.tilePtNext.x)
	{
		if(_battleState.tilePt.x < _battleState.tilePtNext.x)	_battleState.dir = DIRECTION_RG;
		else													_battleState.dir = DIRECTION_LF;
	}
	else if (_battleState.tilePt.y != _battleState.tilePtNext.y)
	{
		if (_battleState.tilePt.y < _battleState.tilePtNext.y)	_battleState.dir = DIRECTION_DN;
		else													_battleState.dir = DIRECTION_UP;
	}
	else //�Ѵ� ������
	{
		if (_battleState.pt.x != ptNext.x)
		{
			if (_battleState.pt.x < ptNext.x)	_battleState.dir = DIRECTION_RG;
			else									_battleState.dir = DIRECTION_LF;

			moveSpeed = moveSpeed < abs(_battleState.pt.x - ptNext.x) ? moveSpeed : abs(_battleState.pt.x - ptNext.x);
		}
		else if (_battleState.pt.y != ptNext.y)
		{
			if (_battleState.pt.y < ptNext.y)	_battleState.dir = DIRECTION_DN;
			else									_battleState.dir = DIRECTION_UP;

			moveSpeed = moveSpeed < abs(_battleState.pt.y - ptNext.y) ? moveSpeed : abs(_battleState.pt.y - ptNext.y);
		}
		else
		{
			return FALSE;
		}
	}

	switch (_battleState.dir)
	{
	case DIRECTION_LF:
		_battleState.pt.x -= moveSpeed;
		break;
	case DIRECTION_RG:
		_battleState.pt.x += moveSpeed;
		break;
	case DIRECTION_UP:
		_battleState.pt.y -= moveSpeed;
		break;
	case DIRECTION_DN:
		_battleState.pt.y += moveSpeed;
		break;
	}

	_battleState.rc = RectMake(_battleState.pt.x - TILESIZE / 2, _battleState.pt.y - TILESIZE / 2, TILESIZE, TILESIZE);
	_battleState.tilePt = { (LONG)(_battleState.pt.x / TILESIZE), (LONG)(_battleState.pt.y / TILESIZE) };

	_battleState.unitState = UNITSTATE_IDLE;

	return TRUE;
}

void Unit::move(DIRECTION dir)
{
	POINT maxTile = { (LONG)_map->getTileSizeX(), (LONG)_map->getTileSizeY() };

	POINT targetTilePt = _battleState.tilePt;

	//move
	switch (dir)
	{
	case DIRECTION_DN:
		_battleState.tilePtNext.y += 1;
		break;
	case DIRECTION_UP:
		_battleState.tilePtNext.y -= 1;
		break;
	case DIRECTION_LF:
		_battleState.tilePtNext.x -= 1;
		break;
	case DIRECTION_RG:
		_battleState.tilePtNext.x += 1;
		break;
	}

	//collision check
	switch (dir)
	{
	case DIRECTION_DN:
		if (_battleState.tilePtNext.y >= maxTile.y)
		{
			_battleState.tilePtNext.y -= 1;
		}
		break;
	case DIRECTION_UP:
		if (_battleState.tilePtNext.y < 0)
		{
			_battleState.tilePtNext.y += 1;
		}
		break;
	case DIRECTION_LF:
		if (_battleState.tilePtNext.x < 0)
		{
			_battleState.tilePtNext.x += 1;
		}
		break;
	case DIRECTION_RG:
		if (_battleState.tilePtNext.x >= maxTile.x)
		{
			_battleState.tilePtNext.x -= 1;
		}
		break;
	}

}


void Unit::findEnemy(TEAM myTeam, POINT closeEnemyPos)
{
	//1. ���� ���� �ְ�
	_astar->resetAtkRange();
	for (int i = 0; i < UNIT_ATTACK_RANGE_MAX; i++)
	{
		for (int j = 0; j < UNIT_ATTACK_RANGE_MAX; j++)
		{
			_astar->setAtkRange(_status.atkRange[j][i], j, i);
		}
	}

	//2. �̵����� ���� ����ϰ�
	findMoveArea();

	//3. ���� ������ ��ġ�� ����.
	POINT myPos = _battleState.tilePt;
	POINT enemyPos = _battleState.tilePt;
	if (_astar->findAtkPos(myTeam, &myPos, &enemyPos))
	{
		_battleState.findEnemy = true;
		_battleState.tilePtNext = myPos;
		_battleState.tilePtEnemy = enemyPos;
	}
	else
	{
		//4. ������ �Ұ����� �����̸� ���� ����� ���� ���� ����.
		_battleState.findEnemy = false;
		_battleState.tilePtNext = _astar->findCloseTile(_battleState.tilePt, closeEnemyPos);
	}

	_battleState.squence = UNITSEQUENCE_MOVE;
}

//�̵������� ������ ����Ѵ�.
void Unit::findMoveArea(void)
{
	_moveArea.clear();
	_astar->clearTiles();

	POINT curTilePt = _battleState.tilePt;
	_astar->setTiles(curTilePt, _status.movePoint);
	if (_astar->getTile(curTilePt))
	{
		_astar->findOpenList(_astar->getTile(curTilePt));

		for (int i = 0; i < _astar->getOpenList().size(); i++)
		{
			_moveArea.push_back(_astar->getOpenList()[i]);
		}
	}
}

void Unit::showMoveArea(void)
{
	if (_moveArea.size() == 0)
		return;


	for (int i = 0; i < _moveArea.size(); i++)
	{
		if (_moveArea[i] == NULL) continue;

		int x = _moveArea[i]->getIdX();
		int y = _moveArea[i]->getIdY();

		int cost = (int)_moveArea[i]->getTotalCost();
		//RECT rc;
		//rc = RectMake(x * TILESIZE , y * TILESIZE, 48, 48);
		//Rectangle(getMemDC(), rc.left, rc.top, rc.right, rc.bottom);
		switch (_status.team)
		{
			case TEAM_PLAYER:
				IMAGEMANAGER->findImage(L"playerMoveAreaTile")->alphaRender(getMemDC(), x * TILESIZE, y * TILESIZE, 120);
			break;
			case TEAM_FRIEND:
				IMAGEMANAGER->findImage(L"nonPlayerMoveAreaTile")->alphaRender(getMemDC(), x * TILESIZE, y * TILESIZE, 120);
			break;
			case TEAM_ENEMY:
				IMAGEMANAGER->findImage(L"nonPlayerMoveAreaTile")->alphaRender(getMemDC(), x * TILESIZE, y * TILESIZE, 120);
			break;
		}

		TCHAR str[10];
		_stprintf(str, L"%d", cost);
		TextOut(getMemDC(), x * TILESIZE + 20, y * TILESIZE + 20, str, _tcslen(str));

	}
	
	for (int i = 0; i < UNIT_ATTACK_RANGE_MAX; i++) // y
	{
		for (int j = 0; j < UNIT_ATTACK_RANGE_MAX; j++) // x
		{
			if (_status.atkRange[j][i] == true)
			{
				int x = _battleState.tilePt.x + j - int(UNIT_ATTACK_RANGE_MAX / 2);
				int y = _battleState.tilePt.y + i - int(UNIT_ATTACK_RANGE_MAX / 2);

				if (x < 0) continue;
				if (y < 0) continue;
				if (x >= _map->getTileSizeX()) continue;
				if (y >= _map->getTileSizeY()) continue;
				IMAGEMANAGER->findImage(L"curAtkArea")->alphaRender(getMemDC(), x * TILESIZE, y * TILESIZE, 120);
			}
		}
	}
}
