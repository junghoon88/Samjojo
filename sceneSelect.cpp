#include "stdafx.h"
#include "sceneSelect.h"


sceneSelect::sceneSelect()
{
	_background = NULL;
	for (int i = 0; i < BTNSELECT1_MAX; i++)
	{
		_button1[i] = NULL;
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

	_selectLevel = 0;

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

}

void sceneSelect::update(void)
{

	for (int i = 0; i < BTNSELECT1_MAX; i++)
	{
		if(_button1[i]) _button1[i]->update();
	}

}

void sceneSelect::render(void)
{
	if (_background)
	{
		_background->render(getMemDC());
	}

	for (int i = 0; i < BTNSELECT1_MAX; i++)
	{
		_button1[i]->render();
		TextOut(getMemDC(), _button1[i]->getRect().left, _button1[i]->getRect().top, _strButton1[i], _tcslen(_strButton1[i]));
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
}


//-----------------------------------------------------------------------------------------
//callback functions
void sceneSelect::cbFuncGameStart(void* obj)
{
	sceneSelect* ss = (sceneSelect*)obj;
}
void sceneSelect::cbFuncMaptool(void* obj)
{
	sceneSelect* ss = (sceneSelect*)obj;
}
void sceneSelect::cbFuncUnitEditor(void* obj)
{
	sceneSelect* ss = (sceneSelect*)obj;
}
void sceneSelect::cbFuncGameExit(void* obj)
{
	sceneSelect* ss = (sceneSelect*)obj;
}
//~callback functions
//-----------------------------------------------------------------------------------------
