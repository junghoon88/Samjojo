#include "stdafx.h"
#include "sceneBattle.h"


sceneBattle::sceneBattle()
	: _map(NULL)
{


}


sceneBattle::~sceneBattle()
{

}

HRESULT sceneBattle::init(void)
{
	DATABASE->getSlectScenario();

	_cursor = new infoCursor;
	_cursor->init();
	_turn = 1;

	_astar = new aStar;
	_astar->init(_map);

	linkClass();

	_phase = PLAYERPHASE;


	return S_OK;
}


void sceneBattle::release(void)
{
	_cursor->release();
	SAFE_DELETE(_cursor);

	_astar->release();
	SAFE_DELETE(_astar);
}

void sceneBattle::update(void)
{
	//debug
	{
		Unit* unit = _enemy->getUnits()[0];
		if (KEYMANAGER->isOnceKeyDown('3') || KEYMANAGER->isOnceKeyDown(VK_NUMPAD8))
		{
			unit->move(DIRECTION_UP);
		}
		if (KEYMANAGER->isOnceKeyDown('5') || KEYMANAGER->isOnceKeyDown(VK_NUMPAD5))
		{
			unit->move(DIRECTION_DN);
		}
		if (KEYMANAGER->isOnceKeyDown('4') || KEYMANAGER->isOnceKeyDown(VK_NUMPAD4))
		{
			unit->move(DIRECTION_LF);
		}
		if (KEYMANAGER->isOnceKeyDown('6') || KEYMANAGER->isOnceKeyDown(VK_NUMPAD6))
		{
			unit->move(DIRECTION_RG);
		}
		if (KEYMANAGER->isOnceKeyDown('7') || KEYMANAGER->isOnceKeyDown(VK_NUMPAD7))
		{
			_map->scanUnitsPos();
			unit->findMoveArea();
		}
		if (KEYMANAGER->isOnceKeyDown('8') || KEYMANAGER->isOnceKeyDown(VK_NUMPAD9))
		{
			unit->setUnitSequnce(UNITSEQUENCE_TURNON);
			_map->scanUnitsPos();
			unit->findEnemy(TEAM_ENEMY, findCloseEnemyPos(unit));
		}
	}

	_player->update();
	_friend->update(); 
	_enemy->update();
	_map->scanUnitsPos();
	_map->update(); 
	if(_phase == PLAYERPHASE)_cursor->update();
	else if (_phase == FRIENDPHASE); //friendAction();
	else if (_phase == ENEMYPHASE); //enemyAction();

}

void sceneBattle::render(void)
{
	_map->render();

	_player->render();
	_friend->render(); 
	_enemy->render();
	_astar->render();
	_cursor->render();
	
}

POINT sceneBattle::findCloseEnemyPos(Unit* unit)
{
	float distMin = 1000.0f;
	POINT myPt = unit->getBattleState().tilePt;
	POINT tarPt = myPt;

	switch (unit->getStatus().team)
	{
	case TEAM_PLAYER:
		break;
	case TEAM_FRIEND:
		for (int i = 0; i < _enemy->getUnits().size(); i++)
		{
			POINT ePt = _enemy->getUnits()[i]->getBattleState().tilePt;

			float dist = getDistance(myPt.x, myPt.y, ePt.x, ePt.y);
			if (distMin > dist)
			{
				tarPt = ePt;
				distMin = dist;
			}
		}
		break;
	case TEAM_ENEMY:
		for (int i = 0; i < _player->getUnits().size(); i++)
		{
			POINT ePt = _player->getUnits()[i]->getBattleState().tilePt;

			float dist = getDistance(myPt.x, myPt.y, ePt.x, ePt.y);
			if (distMin > dist)
			{
				tarPt = ePt;
				distMin = dist;
			}
		}
		for (int i = 0; i < _friend->getUnits().size(); i++)
		{
			POINT ePt = _friend->getUnits()[i]->getBattleState().tilePt;

			float dist = getDistance(myPt.x, myPt.y, ePt.x, ePt.y);
			if (distMin > dist)
			{
				tarPt = ePt;
				distMin = dist;
			}
		}
		break;
	}

	return tarPt;
}

void sceneBattle::initImage(void)
{

}

void sceneBattle::initSound(void)
{

}


// ���ൿ ����ó�..�ƹ�ư ȣ���ؼ� üũ. ��� üũ���� �ʿ�� �������
void sceneBattle::phaseCheck(void)
{
	int _Active = 0;
	if (_phase == PLAYERPHASE)
	{
		for (int i = 0; i < _player->getUnits().size(); i++)
		{
			if (!_player->getUnits()[i]->getBattleState().valid) continue;
			_Active++;
		}
		if (_Active == 0)//���� �ൿ �Ұ��� ������ �ֵ� �ൿ�������� ����� ������ �ѱ�.
		{
			for (int i = 0; i < _friend->getUnits().size(); i++)
			{
				_friend->getUnits()[i]->setVaild(true);
			}
			_phase = FRIENDPHASE;
		}
	}
	else if (_phase == FRIENDPHASE)
	{
		for (int i = 0; i < _friend->getUnits().size(); i++)
		{
			if (!_friend->getUnits()[i]->getBattleState().valid) continue;
		}
		if (_Active == 0)
		{
			for (int i = 0; i < _enemy->getUnits().size(); i++)
			{
				_enemy->getUnits()[i]->setVaild(true);
			}
			_phase = ENEMYPHASE;
		}
	}
	else if (_phase == ENEMYPHASE)
	{
		for (int i = 0; i < _enemy->getUnits().size(); i++)
		{
			if (!_enemy->getUnits()[i]->getBattleState().valid) continue;
		}
		if (_Active == 0)
		{
			for (int i = 0; i < _player->getUnits().size(); i++)
			{
				_player->getUnits()[i]->setVaild(true);
			}
			_phase = PLAYERPHASE;
		}
	}
}

void sceneBattle::phaseControl(void) //ȣ���ؼ� ���� �����ϰ� �ൿ�� �� �ִ� �� ������ ������ ��ȯ
{
	
}

void sceneBattle::friendAction(void)//�Ʊ� �� �׼�
{ 
	for (int i = 0; i < _friend->getUnits().size(); i++) //�ൿ ���� �ڿ� ������ ��ȣ�� �ʿ���..
	{
		if (!_friend->getUnits()[i]->getBattleState().valid) continue; //�ൿ �Ұ����� �ֵ��� �Ÿ���
	}

}
void sceneBattle::enemyAction(void) //���� �� �׼�
{
	for (int i = 0; i < _enemy->getUnits().size(); i++)
	{
		if (!_enemy->getUnits()[i]->getBattleState().valid) continue;
	}
}

void sceneBattle::linkClass(void)
{
	_cursor->setLinkPlyer(_player);
	_cursor->setLinkFriend(_friend);
	_cursor->setLinkEnemy(_enemy);
	_cursor->setLinkAdressMap(_map);

	_player->setLinkCursor(_cursor);
	_friend->setLinkCursor(_cursor);
	_enemy->setLinkCursor(_cursor);
	_map->setLinkAdressCursor(_cursor);

	//��� ���ֿ� a* �������ֱ�
	for (int i = 0; i < _player->getUnits().size(); i++)
	{
		_player->getUnits()[i]->setLinkAdressAStar(_astar);
	}

	for (int i = 0; i < _friend->getUnits().size(); i++)
	{
		_friend->getUnits()[i]->setLinkAdressAStar(_astar);
	}

	for (int i = 0; i < _enemy->getUnits().size(); i++)
	{
		_enemy->getUnits()[i]->setLinkAdressAStar(_astar);
	}
}

Unit* sceneBattle::findUnit(TEAM team, POINT pt)
{
	switch (team)
	{
	case TEAM_PLAYER:
		for (int i = 0; i < _player->getUnits().size(); i++)
		{
			POINT unitPt = _player->getUnits()[i]->getBattleState().tilePt;

			if (pt.x == unitPt.x && pt.y == unitPt.y)
			{
				return _player->getUnits()[i];
			}
		}
		break;
	case TEAM_FRIEND:
		for (int i = 0; i < _friend->getUnits().size(); i++)
		{
			POINT unitPt = _friend->getUnits()[i]->getBattleState().tilePt;

			if (pt.x == unitPt.x && pt.y == unitPt.y)
			{
				return _friend->getUnits()[i];
			}
		}
		break;
	case TEAM_ENEMY:
		for (int i = 0; i < _enemy->getUnits().size(); i++)
		{
			POINT unitPt = _enemy->getUnits()[i]->getBattleState().tilePt;

			if (pt.x == unitPt.x && pt.y == unitPt.y)
			{
				return _enemy->getUnits()[i];
			}
		}
		break;
	}

	return NULL;
}
