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

	_imgFrameTime = 0;
	_imgFrameY = 0;

	return S_OK;
}

void Unit::release(void)
{
	_moveArea.clear();

	SAFE_DELETE(_itemW);
	SAFE_DELETE(_itemA);
	SAFE_DELETE(_itemS);

}

void Unit::update(TEAM team)
{
	expMaxCheck();	// ����ġ Ȯ��

	switch (team)
	{
		case TEAM_PLAYER:
			updateSequence(false);
		break;
		case TEAM_FRIEND:
		case TEAM_ENEMY:
			updateSequence(true);
		break;
	}

	updateImage();
}

void Unit::render(void)
{
	if (_battleState.isHiding) return;

	if (!_battleState.imgBattleAtk) return;
	if (!_battleState.imgBattleIdle) return;
	if (!_battleState.imgBattleSpc) return;

	showMoveArea();
	switch (_battleState.unitState)
	{
		case UNITSTATE_IDLE:	//�⺻����
		case UNITSTATE_TIRED:
			_battleState.imgBattleIdle->frameRender(getMemDC(), _battleState.rc.left - MAINCAMERA->getCameraX(), _battleState.rc.top - MAINCAMERA->getCameraY(), _battleState.frameIdle, _imgFrameY);
		break;
		case UNITSTATE_ATK:		//���ݻ���
			_battleState.imgBattleAtk->frameRender(getMemDC(), _battleState.rc.left - MAINCAMERA->getCameraX(), _battleState.rc.top - MAINCAMERA->getCameraY(), _battleState.frameAtk, _imgFrameY);
		break;
		case UNITSTATE_DEF:		//������
		case UNITSTATE_HIT:		//�ǰݻ���
		case UNITSTATE_VIC:		//�¸�
			_battleState.imgBattleSpc->frameRender(getMemDC(), _battleState.rc.left - MAINCAMERA->getCameraX(), _battleState.rc.top - MAINCAMERA->getCameraY(), _battleState.frameSpc, _imgFrameY);
		break;
	}

}

void Unit::updateStatus(void)
{
	if (_itemW)		_status.ItemPlusAtk = _itemW->getAtk();
	else			_status.ItemPlusAtk = 0;
	if (_itemA)		_status.ItemPlusDep = _itemA->getDep();
	else			_status.ItemPlusDep = 0;
	if (_itemS)		_status.ItemPlusHPMax = _itemS->getHP();
	else			_status.ItemPlusHPMax = 0;
		

	_status.HP = _status.HPMax = _status.InitHPMax + (_status.level * _status.LvPerHPMax) + _status.ItemPlusHPMax;
	_status.MP = _status.MPMax = _status.InitMPMax + (_status.level * _status.LvPerMPMax) + _status.ItemPlusMPMax;
	_status.Pwr = _status.InitPwr + _status.ItemPlusPwr;
	_status.Lds = _status.InitLds + _status.ItemPlusLds;
	_status.Int = _status.InitInt + _status.ItemPlusInt;
	_status.Dex = _status.InitDex + _status.ItemPlusDex;
	_status.Luk = _status.InitLuk + _status.ItemPlusLuk;

	_status.Atk = _status.InitAtk + (_status.level * _status.LvPerAtk) + _status.ItemPlusAtk;
	_status.Dep = _status.InitDep + (_status.level * _status.LvPerDep) + _status.ItemPlusDep;
	_status.Res = _status.InitRes + (_status.level * _status.LvPerRes) + _status.ItemPlusRes;
	_status.Agl = _status.InitAgl + (_status.level * _status.LvPerAgl) + _status.ItemPlusAgl;
	_status.Fig = _status.InitFig + (_status.level * _status.LvPerFig) + _status.ItemPlusFig;

	//_status.Atk = (_status.Pwr / 2) + (_status.level * _status.LvPerAtk) + _status.ItemPlusAtk;
	//_status.Dep = (_status.Lds / 2) + (_status.level * _status.LvPerDep) + _status.ItemPlusDep;
	//_status.Res = (_status.Int / 2) + (_status.level * _status.LvPerRes) + _status.ItemPlusRes;
	//_status.Agl = (_status.Dex / 2) + (_status.level * _status.LvPerAgl) + _status.ItemPlusAgl;
	//_status.Fig = (_status.Luk / 2) + (_status.level * _status.LvPerFig) + _status.ItemPlusFig;
}
void Unit::expMaxCheck(void)
{
	if (_status.expMax <= _status.exp)
	{
		_status.exp = 0;
		if (_status.level < MAXLVL)
		{
			_status.level += 1;
			updateStatus();
		}
	}
}

void Unit::useItem(Unit* unit, int type, int value)
{
	switch (type)	// TESTITEM ����� ���� �ʿ�, �Ű������� ��������
	{
		case 0:
			unit->setCurHP(unit->getCurHP() + value);
			if (unit->getCurHP() > unit->getMaxHP()) unit->setCurHP(unit->getMaxHP());
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
			else								_battleState.dir = DIRECTION_LF;

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

	setIdleState();

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


void Unit::moveTo(POINT tliePt)
{
	_battleState.tilePtNext = tliePt;
}


void Unit::attack(Unit* opponent)
{
	// ����� ���ݹ��� ���� �ڽ��� ��ġ�ϰ� ������ �ݰ� �������� ����
	//if (opponent->getStatus().atkRange[_battleState.tilePt.x][_battleState.tilePt.y] == TRUE)
	//{
	//	_battleState.squence = UNITSEQUENCE_COUNTER;
	//}
	//else _battleState.squence = UNITSEQUENCE_IDLE;

	_battleState.unitState = UNITSTATE_ATK;

	if ((opponent->getUnitState() == UNITSTATE_IDLE) || (opponent->getUnitState() == UNITSTATE_TIRED))
	{
		if (_imgFrameY >= 2)
		{
			//���� �������θ� ����Ѵ�.
			if (1) 
			{
				int damage = _status.Atk - opponent->getStatus().Dep;
				opponent->getDamage(damage);
				_battleState.attackSuccess = true;
			}
			else
			{
				_battleState.attackSuccess = false;
			}
		}
	}

	if(_imgFrameY >= 2)
	{
		if (_battleState.attackSuccess) //���� ���������� �ǰݻ��·� �ٲٰ�
		{
			opponent->setUnitState(UNITSTATE_HIT);			// �ǰ�
		}
		else //���� ��������� �����·� �ٲ۴�.
		{
			opponent->setUnitState(UNITSTATE_DEF);			// ���		
		}
	}
}

void Unit::counterAttack(Unit* opponent)
{
	_battleState.squence = UNITSEQUENCE_IDLE;

	opponent->setUnitState(UNITSTATE_ATK);

	//�ݰ��ϴ� �������� ��ȯ
	if (_battleState.tilePt.y > opponent->getBattleState().tilePt.y) opponent->setDir(DIRECTION_DN);
	if (_battleState.tilePt.y < opponent->getBattleState().tilePt.y) opponent->setDir(DIRECTION_UP);
	if (_battleState.tilePt.x < opponent->getBattleState().tilePt.x) opponent->setDir(DIRECTION_LF);
	if (_battleState.tilePt.x > opponent->getBattleState().tilePt.x) opponent->setDir(DIRECTION_RG);

	if (1)
	{
		_battleState.unitState = UNITSTATE_HIT;			// �ǰ�

		int damage;
		damage = opponent->getStatus().Atk - _status.Dep / 2;
		setCurHP(_status.HP - damage);

		return;
	}
	else	// ����ȸ�� �����ϸ� �ؿ� ��ȿ
	{
		_battleState.unitState = UNITSTATE_DEF;			// ���
		return;
	}

}

void Unit::getDamage(int damage)
{
	int curHP = _status.HP - damage;
	if (curHP <= 0)
	{
		curHP = 0;
		_status.HP = curHP;
		_status.isLive = false;
	}
	else
	{
		_status.HP = curHP;
	}
}

void Unit::setIdleState(void)
{
	//float curHPRatio = (float)_status.HP / (float)_status.HPMax;
	//if (curHPRatio < 0.3)
	//{
	//	_battleState.unitState = UNITSTATE_TIRED;
	//}
	//else
	{
		_battleState.unitState = UNITSTATE_IDLE;
	}
}


void Unit::findEnemy(TEAM myTeam, POINT closeEnemyPos)
{
	if (_battleState.squence != UNITSEQUENCE_TURNON) return;

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
				IMAGEMANAGER->findImage(L"playerMoveAreaTile")->alphaRender(getMemDC(), x * TILESIZE - MAINCAMERA->getCameraX(), y * TILESIZE - MAINCAMERA->getCameraY(), 120);
			break;
			case TEAM_FRIEND:
				IMAGEMANAGER->findImage(L"nonPlayerMoveAreaTile")->alphaRender(getMemDC(), x * TILESIZE - MAINCAMERA->getCameraX(), y * TILESIZE - MAINCAMERA->getCameraY(), 120);
			break;
			case TEAM_ENEMY:
				IMAGEMANAGER->findImage(L"nonPlayerMoveAreaTile")->alphaRender(getMemDC(), x * TILESIZE - MAINCAMERA->getCameraX(), y * TILESIZE - MAINCAMERA->getCameraY(), 120);
			break;
		}

		TCHAR str2[10];
		_stprintf(str2, L"%d", cost);
		TextOut(getMemDC(), x * TILESIZE + 20 - MAINCAMERA->getCameraX(), y * TILESIZE + 20 - MAINCAMERA->getCameraY(), str2, _tcslen(str2));
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
				IMAGEMANAGER->findImage(L"curAtkArea")->alphaRender(getMemDC(), x * TILESIZE - MAINCAMERA->getCameraX(), y * TILESIZE - MAINCAMERA->getCameraY(), 120);
			}
		}
	}
}

void Unit::clearMoveArea(void)
{
	_moveArea.clear();
}

void Unit::updateSequence(bool bAuto)
{
	if (_battleState.squence == UNITSEQUENCE_MOVE)	// findEnemy �Լ����� ��������
	{
		_battleState.isMoving = move();
		if (_battleState.isMoving == FALSE)
		{
			if (bAuto)
			{
				if (_battleState.findEnemy)
				{
					int dirX = _battleState.tilePtEnemy.x - _battleState.tilePt.x;
					int dirY = _battleState.tilePtEnemy.y - _battleState.tilePt.y;

					if (abs(dirX) >= abs(dirY))
					{
						if (dirX > 0)	_battleState.dir = DIRECTION_RG;
						else			_battleState.dir = DIRECTION_LF;
					}
					else
					{
						if (dirY > 0)	_battleState.dir = DIRECTION_DN;
						else			_battleState.dir = DIRECTION_UP;
					}

					//���������(player, friend vs enemy)
					_battleState.opponent = _map->findEnemyUnit(_status.team, _battleState.tilePtEnemy);


					_battleState.squence = UNITSEQUENCE_ATTACK;
				}
				else
				{
					_battleState.squence = UNITSEQUENCE_TURNOFF;
				}
				_moveArea.clear();
			}
			else if (!bAuto) //player
			{
				_battleState.squence = UNITSEQUENCE_TURNON;
			}
		}
		return;
	}


	if (_battleState.squence == UNITSEQUENCE_ATTACK)
	{
		if (_battleState.opponent != NULL)
		{
			attack(_battleState.opponent);
		}
		else setIdleState();

		return;
	}

	if (_battleState.squence == UNITSEQUENCE_COUNTER)
	{
		if (_battleState.opponent != NULL)
		{
			counterAttack(_battleState.opponent);
		}
		else setIdleState();
		return;
	}

	if (_battleState.squence == UNITSEQUENCE_TURNOFF)
	{
		return;
	}
}

void Unit::updateImage(void)
{
	UNITSTATE oldUnitState = _battleState.unitState;

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

	if (oldUnitState == _battleState.unitState)
	{
		float frameFPS = 5.0f;

		_imgFrameTime += TIMEMANAGER->getElapsedTime();
		if (_imgFrameTime >= (1 / frameFPS))
		{
			switch (_battleState.unitState)
			{
			case UNITSTATE_IDLE:	  //�⺻����
			case UNITSTATE_TIRED:
				_imgFrameY = _imgFrameY >= _battleState.imgBattleIdle->getMaxFrameY() ? 0 : _imgFrameY + 1;
				break;
			case UNITSTATE_ATK:	  //���ݻ���
				if (_imgFrameY >= _battleState.imgBattleAtk->getMaxFrameY())
				{
					setIdleState();
					_battleState.squence = UNITSEQUENCE_TURNOFF;
					_battleState.opponent->setIdleState();
					_battleState.opponent = NULL;
					_moveArea.clear();
					_imgFrameY = 0;
				}
				else
				{
					_imgFrameY += 1;
				}
				break;
			case UNITSTATE_DEF:	  //������
			case UNITSTATE_HIT:    //�ǰݻ���
			case UNITSTATE_VIC:    //�¸�
				_imgFrameY = 0;
				//_imgFrameY = _imgFrameY >= _battleState.imgBattleSpc->getMaxFrameY() ? 0 : _imgFrameY + 1;
				break;
			}

			_imgFrameTime -= (1 / frameFPS);
		}
	}
	else
	{
		_imgFrameTime = 0;
		_imgFrameY = 0;
	}
		
		

}

void Unit::setItemW(Item* item)
{
	SAFE_DELETE(_itemW);
	
	if (item)
	{
		_itemW = new ItemWeapon;
		_itemW->copyItem(item);
	}
}

void Unit::setItemA(Item* item)
{
	SAFE_DELETE(_itemA);

	if (item)
	{
		_itemA = new ItemArmor;
		_itemA->copyItem(item);
	}
}

void Unit::setItemS(Item* item)
{
	SAFE_DELETE(_itemS);

	if (item)
	{
		_itemS = new ItemSpecial;
		_itemS->copyItem(item);
	}
}
