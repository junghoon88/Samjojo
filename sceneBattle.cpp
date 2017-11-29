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
		if (KEYMANAGER->isOnceKeyDown('3'))
		{
			unit->move(DIRECTION_UP);
		}
		if (KEYMANAGER->isOnceKeyDown('5'))
		{
			unit->move(DIRECTION_DN);
		}
		if (KEYMANAGER->isOnceKeyDown('4'))
		{
			unit->move(DIRECTION_LF);
		}
		if (KEYMANAGER->isOnceKeyDown('6'))
		{
			unit->move(DIRECTION_RG);
		}
		if (KEYMANAGER->isOnceKeyDown('7'))
		{
			_map->scanUnitsPos();
			unit->findMoveArea();
		}
		if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD9))
		{
			_map->scanUnitsPos();
			unit->findEnemy(TEAM_ENEMY, findCloseEnemyPos(unit));
		}
	}

	_player->update();
	_friend->update();
	_enemy->update();

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