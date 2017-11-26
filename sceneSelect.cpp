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
	_player = NULL;
	_friend = NULL;
	_enemy = NULL;
}


sceneSelect::~sceneSelect()
{
}

HRESULT sceneSelect::init(void)
{
	_background = IMAGEMANAGER->findImage(L"logo 06");

	_selectLevel = SELECTLEVEL1;

	setuptButtons();

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
			TextOut(getMemDC(), _button1[i]->getRect().left, _button1[i]->getRect().top, _strButton1[i], _tcslen(_strButton1[i]));
		}
		break;
	case SELECTLEVEL2:
		for (int i = 0; i < SCENARIO_MAX + 1; i++)
		{
			if(_button2[i] == NULL) continue;
			_button2[i]->render();
			TextOut(getMemDC(), _button2[i]->getRect().left, _button2[i]->getRect().top, _strButton2[i], _tcslen(_strButton2[i]));
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
				_button1[i]->init(L"SELECT-선택버튼", WINSIZEX / 2 - 400, 300 + i * 100, { 0,0 }, { 0,1 }, cbFuncGameStart, this);
				_stprintf(_strButton1[i], L"게임시작");
			break;
			case BTNSELECT1_MAPTOOL:
				_button1[i] = new button;
				_button1[i]->init(L"SELECT-선택버튼", WINSIZEX / 2 - 400, 300 + i * 100, { 0,0 }, { 0,1 }, cbFuncMaptool, this);
				_stprintf(_strButton1[i], L"맵편집");
			break;
			case BTNSELECT1_UNITEDITOR:
				_button1[i] = new button;
				_button1[i]->init(L"SELECT-선택버튼", WINSIZEX / 2 - 400, 300 + i * 100, { 0,0 }, { 0,1 }, cbFuncUnitEditor, this);
				_stprintf(_strButton1[i], L"유닛편집");
			break;
			case BTNSELECT1_EXIT:
				_button1[i] = new button;
				_button1[i]->init(L"SELECT-선택버튼", WINSIZEX / 2 - 400, 300 + i * 100, { 0,0 }, { 0,1 }, cbFuncGameExit, this);
				_stprintf(_strButton1[i], L"게임종료");
			break;
		}
	}

	for (int i = 0; i < SCENARIO_MAX; i++)
	{
		_button2[i] = new button;
		_button2[i]->init(L"SELECT-선택버튼", 50 + (i % 5) * 130, 50 + (i/5) * 60, { 0,0 }, { 0,1 }, cbFuncSelect, this);
		_stprintf(_strButton2[i], L"제 %d 장", i);
	}
	_button2[SCENARIO_MAX] = new button;
	_button2[SCENARIO_MAX]->init(L"SELECT-선택버튼", WINSIZEX / 2 - 400, 500, { 0,0 }, { 0,1 }, cbFuncPrev, this);
	_stprintf(_strButton2[SCENARIO_MAX], L"이전으로");
}

void sceneSelect::selectScenario(void)
{
	for (int i = 0; i < SCENARIO_MAX; i++)
	{
		if (PtInRect(&_button2[i]->getRect(), _ptMouse))
		{
			//debug
			i = 3;

			DATABASE->setSlectScenario(i);

			_map->loadData(i);
			_player->loadUnits();
			_friend->loadUnits();
			_enemy->loadUnits();
			


			//SCENEMANAGER->changeScene(L"대화씬");
			//SCENEMANAGER->changeScene(L"상점씬");
			SCENEMANAGER->changeScene(L"전투씬");
			break;
		}
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
	SCENEMANAGER->changeScene(L"맵툴씬");
}
void sceneSelect::cbFuncUnitEditor(void* obj)
{
	sceneSelect* ss = (sceneSelect*)obj;
	SCENEMANAGER->changeScene(L"유닛에디터");
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
//~callback functions
//-----------------------------------------------------------------------------------------
