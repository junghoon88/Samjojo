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
	_eventAcc = 0;//�̺�Ʈ üũ��
	_astar = new aStar;
	_astar->init(_map);

	linkClass();
	setUpBattle();


	_sDL = new scanDialog;
	_sDL->init("scripts/script 05.txt");
	_sDL->setNext(9);
	ShowCursor(true);


	_isDialog[0] = true;
	for (int i = 1; i < 5; i++)
	{
		_isDialog[i] = false;
	}
	_sDL->setAddressLinkBattle(this);

	

	_phaseChanging = false;
	_phaseChangeTime = 0.0f;


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
	for (int i = 0; i < BATTLESTORY_MAX; i++)
	{
		if (_isDialog[i])
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				_sDL->loadDialog();
			}
			_sDL->update();

			return;
		}
	}
	//�׽�Ʈ�� 



	if (_phaseChanging)
	{
		_phaseChangeTime += TIMEMANAGER->getElapsedTime();
		if (_phaseChangeTime > 3.0f)
		{
			_phaseChanging = false;
			_phaseChangeTime = 0.0f;
		}
		return;
	}

	//debug
	{
		Unit* unit = _enemy->getUnits()[1];
		if (KEYMANAGER->isOnceKeyDown('5') || KEYMANAGER->isOnceKeyDown(VK_NUMPAD5))
		{
			unhideEnemy();
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

	friendAction();
	enemyAction();

	_player->update();
	_friend->update();
	_enemy->update();

	_map->update(); 
	_map->scanUnitsPos();
	_interface->update();
	if (_phase == BATTLEPHASE_PLAYER) checkEvent();
	
		

	phaseCheck();
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

	if (_phaseChanging)
	{
		TCHAR str[100];
		RECT rc =  RectMake(0, 0, 960, 960);
		RECT rc1 = RectMake(0, 0, 960, 960 - 60);
		RECT rc2 = RectMake(0, 60, 960, 960 - 60);

		HFONT hFontOld = (HFONT)SelectObject(getMemDC(), _gFont[FONTVERSION_BATTLETURN]);
		COLORREF oldcolor = GetTextColor(getMemDC());
		SetTextColor(getMemDC(), RGB(255, 255, 255));

		switch (_phase)
		{
		case BATTLEPHASE_PLAYER:
			IMAGEMANAGER->findImage(L"playerturn")->alphaRender(getMemDC(), 128);
			_stprintf(str, L"�÷��̾� ����");
			DrawText(getMemDC(), str, _tcslen(str), &rc1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			_stprintf(str, L"�� %d ��", _turn);
			DrawText(getMemDC(), str, _tcslen(str), &rc2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			break;
		case BATTLEPHASE_FRIEND:
			IMAGEMANAGER->findImage(L"friendturn")->alphaRender(getMemDC(), 128);
			_stprintf(str, L"�Ʊ� ����");
			DrawText(getMemDC(), str, _tcslen(str), &rc1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			_stprintf(str, L"�� %d ��", _turn);
			DrawText(getMemDC(), str, _tcslen(str), &rc2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			break;
		case BATTLEPHASE_ENEMY:
			IMAGEMANAGER->findImage(L"enemyturn")->alphaRender(getMemDC(), 128);
			_stprintf(str, L"���� ����");
			DrawText(getMemDC(), str, _tcslen(str), &rc1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			_stprintf(str, L"�� %d ��", _turn);
			DrawText(getMemDC(), str, _tcslen(str), &rc2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			break;
		case BATTLEPHASE_VICTORY:
			_stprintf(str, L"�¸�");
			DrawText(getMemDC(), str, _tcslen(str), &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			break;
		case BATTLEPHASE_DEFEAT:
			IMAGEMANAGER->findImage(L"defeatturn")->alphaRender(getMemDC(), 128);
			_stprintf(str, L"�й�");
			DrawText(getMemDC(), str, _tcslen(str), &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			break;
		}
		SelectObject(getMemDC(), hFontOld);
		DeleteObject(hFontOld);
		SetTextColor(getMemDC(), oldcolor);

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

// ���ൿ ����ó�..�ƹ�ư ȣ���ؼ� üũ. ��� üũ���� �ʿ�� �������
void sceneBattle::phaseCheck(void)
{
	bool isEnd = true;

	//�¸� ����
	if (_enemy->getUnits().size() == 0)
	{
		_phase = BATTLEPHASE_VICTORY;
		_phaseChanging = true;
		_phaseChangeTime = 0.0f;
		return;
	}
	//�й�����
	if (_player->getUnits().size() == 0)
	{
		_phase = BATTLEPHASE_DEFEAT;
		_phaseChanging = true;
		_phaseChangeTime = 0.0f;
		return;
	}

	//��һ��� ���� ������ ����
	if (_phase == BATTLEPHASE_NONE)
	{
		for (int i = 0; i < _player->getUnits().size(); i++)
		{
			_player->getUnits()[i]->setUnitSequnce(UNITSEQUENCE_TURNON);
			_player->getUnits()[i]->setMoveable(true);
		}
		_phase = BATTLEPHASE_PLAYER;
		_phaseChanging = true;
		_phaseChangeTime = 0.0f;
	}
	else if (_phase == BATTLEPHASE_PLAYER)
	{
		for (int i = 0; i < _player->getUnits().size(); i++)
		{
			if (_player->getUnits()[i]->getBattleState().squence != UNITSEQUENCE_TURNOFF)
			{
				isEnd = false;
				break;
			}
		}

		if (isEnd) //���� �ൿ �Ұ��� ������ �ֵ� �ൿ�������� ����� ������ �ѱ�.
		{
			_interface->dataClean();			
			if (_friend->getUnits().size() > 0)
			{
				_phase = BATTLEPHASE_FRIEND;
				for (int i = 0; i < _friend->getUnits().size(); i++)
				{
					_friend->getUnits()[i]->setUnitSequnce(UNITSEQUENCE_TURNON);
				}
			}
			else if(_enemy->getUnits().size() > 0)
			{
				_phase = BATTLEPHASE_ENEMY;
				for (int i = 0; i < _enemy->getUnits().size(); i++)
				{
					//�������϶� �������� �ʴ´�.
					if (_enemy->getUnits()[i]->getBattleState().isHiding) continue;
					if (_enemy->getUnits()[i]->getBattleState().Group == 2 && _turn < 10)//10�Ϲ̸��϶� �Ĺ��� �ֵ�
					{
						int Alive = 0;
						for (int i = 0; i < _enemy->getUnits().size(); i++)
						{
							if (_enemy->getUnits()[i]->getBattleState().Group == 2) continue;
							Alive++;
						}
						if(Alive <= 0) _enemy->getUnits()[i]->setUnitSequnce(UNITSEQUENCE_TURNON);
					}
					else _enemy->getUnits()[i]->setUnitSequnce(UNITSEQUENCE_TURNON);
				
				}
			}
			
			_phaseChanging = true;
			_phaseChangeTime = 0.0f;
		}
	}
	else if (_phase == BATTLEPHASE_FRIEND)
	{
		for (int i = 0; i < _friend->getUnits().size(); i++)
		{
			if (_friend->getUnits()[i]->getBattleState().squence != UNITSEQUENCE_TURNOFF)
			{
				isEnd = false;
				break;
			}
		}

		if (isEnd)
		{
			for (int i = 0; i < _enemy->getUnits().size(); i++)
			{
				//�������϶� �������� �ʴ´�.
				if (_enemy->getUnits()[i]->getBattleState().isHiding) continue;

				_enemy->getUnits()[i]->setUnitSequnce(UNITSEQUENCE_TURNON);
			}
			_phase = BATTLEPHASE_ENEMY;
			_phaseChanging = true;
			_phaseChangeTime = 0.0f;
		}
	}
	else if (_phase == BATTLEPHASE_ENEMY)
	{
		for (int i = 0; i < _enemy->getUnits().size(); i++)
		{
			if (_enemy->getUnits()[i]->getBattleState().squence != UNITSEQUENCE_TURNOFF)
			{
				isEnd = false;
				break;
			}
		}

		if (isEnd)
		{
			for (int i = 0; i < _player->getUnits().size(); i++)
			{
				_player->getUnits()[i]->setUnitSequnce(UNITSEQUENCE_TURNON);
				_player->getUnits()[i]->setMoveable(true);
			}
			_phase = BATTLEPHASE_PLAYER;
			_phaseChanging = true;
			_phaseChangeTime = 0.0f;

			_turn++;
		}
	}
}

void sceneBattle::friendAction(void)//�Ʊ� �� �׼�
{
	for (int i = 0; i < _friend->getUnits().size(); i++) //�ൿ ���� �ڿ� ������ ��ȣ�� �ʿ���..
	{
		if (_friend->getUnits()[i]->getBattleState().squence == UNITSEQUENCE_TURNOFF) continue; //�ൿ �Ұ����� �ֵ��� �Ÿ���
		_interface->chaseCamera(_friend->getUnits()[i]->getBattleState().tilePt);
		_interface->setUnit(TEAM_FRIEND, i);
		_friend->getUnits()[i]->findEnemy(TEAM_FRIEND, findCloseEnemyPos(_friend->getUnits()[i]));
		
		break;
	}
}
void sceneBattle::enemyAction(void) //���� �� �׼�
{

	for (int i = 0; i < _enemy->getUnits().size(); i++)
	{
		if (_enemy->getUnits()[i]->getBattleState().squence == UNITSEQUENCE_TURNOFF) continue;
		if (_turn < 10 && _enemy->getUnits()[i]->getBattleState().Group >= 2) continue;
		_interface->setUnit(TEAM_ENEMY, i);
		_interface->chaseCamera(_enemy->getUnits()[i]->getBattleState().tilePt);
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


void sceneBattle::setUpBattle(void)
{
	_turn = 1;
	_phase = BATTLEPHASE_NONE;

	RECT GroupRc2 = { 1200,432,1300,580 }; //�Ĺ� �ൿ��
	RECT GroupRc3 = { 96,576,244,768 }; //�׷� üũ�� ���� �����
	RECT GroupRc3_1 = { 576,192,768,384 }; //�ϴ� ���� �����
	RECT GroupRc4 = { 1008,336,1152,624 }; //�׷� üũ�� �Ĺ� �����


	for (int i = 0; i < _player->getUnits().size(); i++)
	{
		_player->getUnits()[i]->setUnitSequnce(UNITSEQUENCE_TURNOFF);
		_player->getUnits()[i]->setMoveable(false);
		_player->getUnits()[i]->updateStatus();
	}
	for (int i = 0; i < _friend->getUnits().size(); i++)
	{
		_friend->getUnits()[i]->setUnitSequnce(UNITSEQUENCE_TURNOFF);
		_friend->getUnits()[i]->updateStatus();
	}
	for (int i = 0; i < _enemy->getUnits().size(); i++)
	{
		_enemy->getUnits()[i]->setUnitSequnce(UNITSEQUENCE_TURNOFF);
		_enemy->getUnits()[i]->updateStatus();

		if (isCollision(GroupRc2, _enemy->getUnits()[i]->getRect()))
		{
			_enemy->getUnits()[i]->setGroup(2); // 10�� ���� �ൿ�ҳ��
			_enemy->getUnits()[i]->setHiding(false);
			continue;
		}
		else if (isCollision(GroupRc3, _enemy->getUnits()[i]->getRect()))	_enemy->getUnits()[i]->setGroup(3);
		else if (isCollision(GroupRc3_1, _enemy->getUnits()[i]->getRect()))	_enemy->getUnits()[i]->setGroup(3);
		else if (isCollision(GroupRc4, _enemy->getUnits()[i]->getRect()))	_enemy->getUnits()[i]->setGroup(4);
		else
		{
			_enemy->getUnits()[i]->setGroup(1);//ó������ �ൿ�� ���
			_enemy->getUnits()[i]->setHiding(false);
			continue;
		}
		_enemy->getUnits()[i]->setHiding(true);
	}
}

void sceneBattle::checkEvent(void)
{

	if (_eventAcc <= 0)
	{
		if (_turn >= 10)
		{
			unhideEnemy();
			_eventAcc++;
			_isDialog[1] = true;
			return;
		}

		int GroupAlive = 0;
		
		for (int i = 0; i < _player->getUnits().size(); i++)
		{
			if (_player->getUnits()[i]->getRect().left > 815)
			{
				unhideEnemy();
				_eventAcc++;
				break;
			}
		}
		for (int i = 0; i < _enemy->getUnits().size(); i++)
		{
			if (_enemy->getUnits()[i]->getBattleState().Group != 1) continue;
			GroupAlive++;
		}
		if (GroupAlive <= 0)
		{
			unhideEnemy();
			_eventAcc++;
		}
	}
	for (int i = 0; i < _player->getUnits().size(); i++)
	{
		if (_player->getUnits()[i]->getRect().left > 336)
		{
			_isDialog[1] = true;
		}
	}
}
void sceneBattle::unhideEnemy(void)
{
	if (_eventAcc == 1)
	{
		_isDialog[1] = true;
		_eventAcc++;
	}

	for (int i = 0; i < _enemy->getUnits().size(); i++)
	{
		if (!_enemy->getUnits()[i]->getHiding()) continue; //1��,2���׷��� ���� ǥ������.
		_enemy->getUnits()[i]->setHiding(false);
	}
}