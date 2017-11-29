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

	_phase = playerPhase;


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
		if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD8))
		{
			unit->move(DIRECTION_UP);
		}
		if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD5))
		{
			unit->move(DIRECTION_DN);
		}
		if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD4))
		{
			unit->move(DIRECTION_LF);
		}
		if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD6))
		{
			unit->move(DIRECTION_RG);
		}
		if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD7))
		{
			_map->scanUnitsPos();
			unit->findMoveArea();
			//unit->findEnemy();
		}
	}

	_player->update();
	_friend->update();
	_enemy->update();
	_map->scanUnitsPos();
	_map->update(); 
	if(_phase == playerPhase)_cursor->update();

}

void sceneBattle::render(void)
{
	_map->render();

	_player->render();
	_friend->render();
	_enemy->render();

	_cursor->render();
	_astar->render();
}

void sceneBattle::initImage(void)
{

}

void sceneBattle::initSound(void)
{

}



void sceneBattle::phaseControl(void)
{

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

	//모든 유닛에 a* 연결해주기
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
