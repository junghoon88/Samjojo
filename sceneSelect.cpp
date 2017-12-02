#include "stdafx.h"
#include "sceneSelect.h"


sceneSelect::sceneSelect()
	: _map(NULL)
{
	_background = NULL;
	for (int i = 0; i < BTNSELECT1_MAX; i++)
	{
		_button1[i] = NULL;
	}
	for (int i = 0; i < SCENARIO_MAX + 1; i++)
	{
		_button2[i] = NULL;
	}
	
	//debug
	for (int i = 0; i < BTNTEST_MAX; i++)
	{
		_buttonTest[i] = NULL;
	}

	_player = NULL;
	_friend = NULL;
	_enemy = NULL;
}


sceneSelect::~sceneSelect()
{
}

HRESULT sceneSelect::init(void)
{
	//_background = IMAGEMANAGER->addImage(L"�������", L"image/logo/Logo 00006.bmp", WINSIZEX, WINSIZEY);
	_background = IMAGEMANAGER->findImage(L"logo 06");

	_selectLevel = SELECTLEVEL1;

	setuptButtons();

	//����� ���� �����͵��� �ҷ��´�.
	_player->loadUnits();
	_friend->loadUnits();
	_enemy->loadUnits();


	return S_OK;
}


void sceneSelect::release(void)
{
	for (int i = 0; i < BTNSELECT1_MAX; i++)
	{
		_button1[i]->release();
		SAFE_DELETE(_button1[i]);
	}
	for (int i = 0; i < SCENARIO_MAX + 1; i++)
	{
		_button2[i]->release();
		SAFE_DELETE(_button2[i]);
	}

	//debug
	for (int i = 0; i < BTNTEST_MAX; i++)
	{
		_buttonTest[i]->release();
		SAFE_DELETE(_buttonTest[i]);
	}
}

void sceneSelect::update(void)
{
	switch (_selectLevel)
	{
	case SELECTLEVEL1:
		for (int i = 0; i < BTNSELECT1_MAX; i++)
		{
			if (_button1[i]) _button1[i]->update();
		}

		//debug
		for (int i = 0; i < BTNTEST_MAX; i++)
		{
			if (_buttonTest[i]) _buttonTest[i]->update();
		}
		break;
	case SELECTLEVEL2:
		for (int i = 0; i < SCENARIO_MAX + 1; i++)
		{
			if(_button2[i]) _button2[i]->update();
		}
		break;
	}

}

void sceneSelect::render(void)
{
	if (_background)
	{
		_background->render(getMemDC());
	}

	switch (_selectLevel)
	{
	case SELECTLEVEL1:
		for (int i = 0; i < BTNSELECT1_MAX; i++)
		{
			if (_button1[i] == NULL) continue;
			_button1[i]->render();
		}

		//debug
		for (int i = 0; i < BTNTEST_MAX; i++)
		{
			if (_buttonTest[i] == NULL) continue;
			_buttonTest[i]->render();
		}
		break;
	case SELECTLEVEL2:
		for (int i = 0; i < SCENARIO_MAX + 1; i++)
		{
			if(_button2[i] == NULL) continue;
			_button2[i]->render();
		}
		break;
	}

}

void sceneSelect::setuptButtons(void)
{
	for (int i = 0; i < BTNSELECT1_MAX; i++)
	{
		switch (i)
		{
			case BTNSELECT1_GAMESTART:
				_button1[i] = new button;
				//_button1[i]->init(L"SELECT-���ù�ư", L"���ӽ���", 50, 150, { 0,0 }, { 0,1 }, cbFuncGameStart, this);
				_button1[i]->init(L"SELECT-���ù�ư", L"���ӽ���", 150, 150, { 0,0 }, { 0,1 }, cbFuncSelect, this);
			break;
			case BTNSELECT1_MAPTOOL:
				_button1[i] = new button;
				_button1[i]->init(L"SELECT-���ù�ư", L"������", 150, 200, { 0,0 }, { 0,1 }, cbFuncMaptool, this);
			break;
			case BTNSELECT1_UNITEDITOR:
				_button1[i] = new button;
				_button1[i]->init(L"SELECT-���ù�ư", L"��������", 150, 250, { 0,0 }, { 0,1 }, cbFuncUnitEditor, this);
			break;
			case BTNSELECT1_EXIT:
				_button1[i] = new button;
				_button1[i]->init(L"SELECT-���ù�ư", L"��������", 150, 300, { 0,0 }, { 0,1 }, cbFuncGameExit, this);
			break;
		}
	}

	for (int i = 0; i < SCENARIO_MAX; i++)
	{
		_button2[i] = new button;
		TCHAR strText[30];
		_stprintf(strText, L"�� %d ��", i);
		_button2[i]->init(L"SELECT-���ù�ư", strText, 50 + (i % 5) * 130, 50 + (i / 5) * 60, { 0, 0 }, { 0, 1 }, cbFuncSelect, this);
	}
	_button2[SCENARIO_MAX] = new button;
	_button2[SCENARIO_MAX]->init(L"SELECT-���ù�ư", L"��������", WINSIZEX2 / 2 - 400, 500, { 0,0 }, { 0,1 }, cbFuncPrev, this);

	//debugt
	for (int i = 0; i < BTNTEST_MAX; i++)
	{
		switch (i)
		{
			case BTNTEST_STORY:
				_buttonTest[i] = new button;
				_buttonTest[i]->init(L"SELECT-���ù�ư", L"���丮��", 300, 100, { 0,0 }, { 0,1 }, cbFuncDebug1, this);
				break;
			case BTNTEST_READYBASE:
				_buttonTest[i] = new button;
				_buttonTest[i]->init(L"SELECT-���ù�ư", L"�غ�⺻��", 300, 150, { 0,0 }, { 0,1 }, cbFuncDebug2, this);
				break;
			case BTNTEST_POS:
				_buttonTest[i] = new button;
				_buttonTest[i]->init(L"SELECT-���ù�ư", L"����", 300, 200, { 0,0 }, { 0,1 }, cbFuncDebug3, this);
				break;
			case BTNTEST_BUY:
				_buttonTest[i] = new button;
				_buttonTest[i]->init(L"SELECT-���ù�ư", L"���Ż���", 300, 250, { 0,0 }, { 0,1 }, cbFuncDebug4, this);
				break;
			case BTNTEST_SELL:
				_buttonTest[i] = new button;
				_buttonTest[i]->init(L"SELECT-���ù�ư", L"�ǸŻ���", 300, 300, { 0,0 }, { 0,1 }, cbFuncDebug5, this);
				break;
			case BTNTEST_BATTLE:
				_buttonTest[i] = new button;
				_buttonTest[i]->init(L"SELECT-���ù�ư", L"����", 300, 350, { 0,0 }, { 0,1 }, cbFuncDebug6, this);
				break;

		}
		
	}
}

void sceneSelect::selectScenario(void)
{
	//for (int i = 0; i < SCENARIO_MAX; i++)
	{
		//if (PtInRect(&_button2[i]->getRect(), _ptMouse))
		{
			//debug
			int i = 3;

			DATABASE->setSlectScenario(i);

			_map->loadData(i);
			_map->scanUnitsPos();
			//test
			//_player->registUnitAll();
			_player->registUnitBasic();   //���� ���ĵ��� ��Ͽ�
			_player->locateUnits();

			_friend->locateUnits();
			_enemy->locateUnits();

			//SCENEMANAGER->changeScene(L"��ȭ��");
			//SCENEMANAGER->changeScene(L"�غ�⺻��");
			SCENEMANAGER->changeScene(L"������");

			//break;
		}
	}
}

void sceneSelect::selectScenario(BTNTEST test)
{
	//debug
	int i = 3;

	DATABASE->setSlectScenario(i);

	_map->loadData(i);
	_map->scanUnitsPos();
	//test
	//_player->registUnitAll();
	_player->registUnitBasic();   //���� ���ĵ��� ��Ͽ�
	_player->locateUnits();

	_friend->locateUnits();
	_enemy->locateUnits();

	switch (test)
	{
	case BTNTEST_STORY:
		SCENEMANAGER->changeScene(L"��ȭ��");
		break;
	case BTNTEST_READYBASE:
		SCENEMANAGER->changeScene(L"�غ�⺻��");
		break;
	case BTNTEST_POS:
		SCENEMANAGER->changeScene(L"������");
		break;
	case BTNTEST_BUY:
		SCENEMANAGER->changeScene(L"���Ż�����");
		break;
	case BTNTEST_SELL:
		SCENEMANAGER->changeScene(L"�ǸŻ�����");
		break;
	case BTNTEST_BATTLE:
		SCENEMANAGER->changeScene(L"������");
		break;
	}
}


//-----------------------------------------------------------------------------------------
//callback functions
void sceneSelect::cbFuncGameStart(void* obj)
{
	sceneSelect* ss = (sceneSelect*)obj;
	ss->setNextLevel();
}
void sceneSelect::cbFuncMaptool(void* obj)
{
	sceneSelect* ss = (sceneSelect*)obj;
	SCENEMANAGER->changeScene(L"������");
}
void sceneSelect::cbFuncUnitEditor(void* obj)
{
	sceneSelect* ss = (sceneSelect*)obj;
	SCENEMANAGER->changeScene(L"���ֿ�����");
}
void sceneSelect::cbFuncGameExit(void* obj)
{
	sceneSelect* ss = (sceneSelect*)obj;
	PostQuitMessage(0);
}
void sceneSelect::cbFuncSelect(void * obj)
{
	sceneSelect* ss = (sceneSelect*)obj;
	ss->selectScenario();
}
void sceneSelect::cbFuncPrev(void * obj)
{
	sceneSelect* ss = (sceneSelect*)obj;
	ss->setPrevLevel();
}

//debug
void sceneSelect::cbFuncDebug1(void* obj)
{
	sceneSelect* ss = (sceneSelect*)obj;
	ss->selectScenario(BTNTEST_STORY);
}
void sceneSelect::cbFuncDebug2(void* obj)
{
	sceneSelect* ss = (sceneSelect*)obj;
	ss->selectScenario(BTNTEST_READYBASE);
}
void sceneSelect::cbFuncDebug3(void* obj)
{
	sceneSelect* ss = (sceneSelect*)obj;
	ss->selectScenario(BTNTEST_POS);
}
void sceneSelect::cbFuncDebug4(void* obj)
{
	sceneSelect* ss = (sceneSelect*)obj;
	ss->selectScenario(BTNTEST_BUY);
}
void sceneSelect::cbFuncDebug5(void* obj)
{
	sceneSelect* ss = (sceneSelect*)obj;
	ss->selectScenario(BTNTEST_SELL);
}
void sceneSelect::cbFuncDebug6(void* obj)
{
	sceneSelect* ss = (sceneSelect*)obj;
	ss->selectScenario(BTNTEST_BATTLE);
}


//~callback functions
//-----------------------------------------------------------------------------------------
