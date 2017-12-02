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

	_interface = new battleSceneInterface;
	_interface->init();
	_turn = 1;

	_astar = new aStar;
	_astar->init(_map);

	linkClass();
	setUpBattle();
	setUpPlayer();//

	_phase = PLAYERPHASE;
	
	_sDL = new scanDialog;
	_sDL->init("scripts/script 05.txt");
	_sDL->setNext(9);
	ShowCursor(true);

	_isDialog = false;


	return S_OK;
}


void sceneBattle::release(void)
{
	_interface->release();
	SAFE_DELETE(_interface);

	_astar->release();
	SAFE_DELETE(_astar);

	_sDL->release();
	SAFE_DELETE(_sDL);
}

void sceneBattle::update(void)
{
	if (_isDialog)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_sDL->loadDialog();
		}
		_sDL->update();

		return;
	}





	//debug
	{
		Unit* unit = _enemy->getUnits()[1];
		if (KEYMANAGER->isOnceKeyDown('3') || KEYMANAGER->isOnceKeyDown(VK_NUMPAD8))
		{
			debug_enemyturn();
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

	_map->update(); 
	friendAction();
	enemyAction();
	_map->scanUnitsPos();
	if(_phase == PLAYERPHASE)_interface->update();
//	else if (_phase == FRIENDPHASE); //friendAction();
//	else if (_phase == ENEMYPHASE); //enemyAction();

}

void sceneBattle::render(void)
{
	_map->render();

	_player->render();
	_friend->render(); 
	_enemy->render();
	_astar->render();
	_interface->render();


	if (_isDialog)
	{
		_sDL->render();
	}
	
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
			if (_player->getUnits()[i]->getBattleState().squence != UNITSEQUENCE_TURNOFF) continue;
			_Active++;
		}
		if (_Active == 0)//���� �ൿ �Ұ��� ������ �ֵ� �ൿ�������� ����� ������ �ѱ�.
		{
			for (int i = 0; i < _friend->getUnits().size(); i++)
			{
				_friend->getUnits()[i]->setUnitSequnce(UNITSEQUENCE_TURNON);
			}
			_phase = FRIENDPHASE;
		}
	}
	else if (_phase == FRIENDPHASE)
	{
		for (int i = 0; i < _friend->getUnits().size(); i++)
		{
			if (_friend->getUnits()[i]->getBattleState().squence != UNITSEQUENCE_TURNOFF) continue;
			_Active++;
		}
		if (_Active == 0)
		{
			for (int i = 0; i < _enemy->getUnits().size(); i++)
			{
				_enemy->getUnits()[i]->setUnitSequnce(UNITSEQUENCE_TURNON);
			}
			_phase = ENEMYPHASE;
		}
	}
	else if (_phase == ENEMYPHASE)
	{
		for (int i = 0; i < _enemy->getUnits().size(); i++)
		{
			if (_enemy->getUnits()[i]->getBattleState().squence != UNITSEQUENCE_TURNOFF) continue;
			_Active++;
		}
		if (_Active == 0)
		{
			_turn++;
			setUpPlayer();
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
		if (_friend->getUnits()[i]->getBattleState().squence == UNITSEQUENCE_TURNOFF) continue; //�ൿ �Ұ����� �ֵ��� �Ÿ���
		_friend->getUnits()[i]->findEnemy(TEAM_FRIEND, findCloseEnemyPos(_friend->getUnits()[i]));
		break;
	}
}
void sceneBattle::enemyAction(void) //���� �� �׼�
{

	for (int i = 0; i < _enemy->getUnits().size(); i++)
	{
		if (_enemy->getUnits()[i]->getBattleState().squence == UNITSEQUENCE_TURNOFF) continue;
		_enemy->getUnits()[i]->findEnemy(TEAM_ENEMY, findCloseEnemyPos(_enemy->getUnits()[i]));
		break;
	}
}

void sceneBattle::linkClass(void)
{
	_interface->setLinkPlyer(_player);
	_interface->setLinkFriend(_friend);
	_interface->setLinkEnemy(_enemy);
	_interface->setLinkAdressMap(_map);

	_player->setLinkAdressUI(_interface);
	_friend->setLinkAdressUI(_interface);
	_enemy->setLinkAdressUI(_interface);
	_map->setLinkAdressUI(_interface);

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


void sceneBattle::setUpPlayer(void)
{
	_phase = PLAYERPHASE;
	for (int i = 0; i < _player->getUnits().size(); i++)
	{
		_player->getUnits()[i]->setUnitSequnce(UNITSEQUENCE_TURNON);
		_player->getUnits()[i]->setMoved(true);
	}
}


void sceneBattle::setUpBattle(void)
{
	for (int i = 0; i < _enemy->getUnits().size(); i++)
	{
		_enemy->getUnits()[i]->setUnitSequnce(UNITSEQUENCE_TURNOFF);
	}
	for (int i = 0; i < _friend->getUnits().size(); i++)
	{
		_friend->getUnits()[i]->setUnitSequnce(UNITSEQUENCE_TURNOFF);
	}
}

void sceneBattle::debug_enemyturn(void)
{
	for (int i = 0; i < _enemy->getUnits().size(); i++)
	{
		_enemy->getUnits()[i]->setUnitSequnce(UNITSEQUENCE_TURNON);
	}
}