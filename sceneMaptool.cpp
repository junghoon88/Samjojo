#include "stdafx.h"
#include "sceneMaptool.h"


sceneMaptool::sceneMaptool()
{
}


sceneMaptool::~sceneMaptool()
{

}

HRESULT sceneMaptool::init(void)
{
	setup();

	_selectSampleIndex = 0;
	
	_countMapX = _countMapY = 0;

	for (int i = 0; i < 6; i++)
	{
		_tileSizeX[i] = _tileSizeY[i] = 20 + i * 4;
	}

	_selectSizeX = _selectSizeY = 5;

	_alphaValue = 128;

	_mapView = false;
	_viewTERRAIN = false;
	_isMapLoad = false;

	_editBox = new editbox;
	_editBox->init();
	_editBox->setRect(RectMake(WINSIZEX - 3 * TILESIZE + 20, 755, 100, 30));
	_editBox->setOnlyNum(TRUE);

	_alphaValueBox = new editbox;
	_alphaValueBox->init();
	_alphaValueBox->setRect(RectMake(WINSIZEX - 3 * TILESIZE + 20, 810, 100, 30));
	_alphaValueBox->setOnlyNum(TRUE);

	_tileObj = new editbox;
	_tileObj->init();
	_tileObj->setRect(RectMake(WINSIZEX - 3 * TILESIZE, 13 * TILESIZE - 14, 100, 30));

	_alphaValueBox->setStrNum(_alphaValue / 255 * 100);

	_stprintf(_saveSize, L"0 x 0");
	_stprintf(_fileName, L"빈공간");

	return S_OK;
}

void sceneMaptool::release(void)
{

}

void sceneMaptool::update(void)
{
	//맵이름 정하기 or 불러오는 맵 이름 쓰기
	_editBox->update();
	if (_editBox->getStrNum() > 57)	_editBox->setStrNum(57);
	else if (_editBox->getStrNum() < 0) _editBox->setStrNum(0);

	_tileObj->update();

	for (int i = 0; i < CTRL_END; i++)
	{
		_ctrlButton[i]->update();
	}
	_exit->update();

	if (PtInRect(&RectMake(WINSIZEX - 3 * TILESIZE, 20, 3 * TILESIZE, 10 * TILESIZE + 20), _ptMouse)
		|| PtInRect(&RectMake(WINSIZEX - 3 * TILESIZE, TILESIZE * 10 + 41, TILESIZE * 3, TILESIZE), _ptMouse)
		|| PtInRect(&RectMake(0, 0, 20 * TILESIZE, 20 * TILESIZE), _ptMouse))
		if (KEYMANAGER->isOnceKeyDown(MK_LBUTTON) || KEYMANAGER->isStayKeyDown(MK_LBUTTON))	setMap();

	if (KEYMANAGER->isOnceKeyUp(MK_LBUTTON))
	{
		if (PtInRect(&RectMake(0, 0, TILEVIEWX * TILESIZE, TILEVIEWY * TILESIZE), _ptMouse))
		{
			for (int i = 0; i < TILEX * TILEY; i++)
			{
				_tiles[i].isClick = false;
			}
			if (_ctrSelect == CTRL_OBJDRAW)
				for (int i = 0; i < TILEVIEWX; i++)
				{
					for (int j = 0; j < TILEVIEWY; j++)
					{
						if (PtInRect(&_tiles[i * TILEVIEWY * (TILEX / TILEVIEWY) + j].rc, _ptMouse)
							&& _tiles[(i + _countMapY) * 20 * (TILEX / 20) + j + _countMapX].sampleObjectSelectIdx != OBJECTSELECT_NONE)
						{
							_tiles[(i + _countMapY) * 20 * (TILEX / 20) + j + _countMapX].isClick = true;
							_tileObj->setStr(_tiles[(i + _countMapY) * 20 * (TILEX / 20) + j + _countMapX].obj);
						}
					}
				}
		}
	}

	if (PtInRect(&RectMake(0, 0, TILEVIEWX * TILESIZE, TILEVIEWY * TILESIZE), _ptMouse))
	{
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			_countMapX--;
			if (_countMapX < 0) _countMapX = 0;
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			_countMapX++;
			if (_countMapX + 20 > _tileSizeX[_selectSizeX]) _countMapX = _tileSizeX[_selectSizeX] - 20;
		}
		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			_countMapY--;
			if (_countMapY < 0) _countMapY = 0;
		}
		if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			_countMapY++;
			if (_countMapY + 20 > _tileSizeY[_selectSizeY]) _countMapY = _tileSizeY[_selectSizeY] - 20;
		}
	}

	if (PtInRect(&RectMake(0, 0, 20 * TILESIZE, 20 * TILESIZE), _ptMouse))
	{
		//맵사이즈 변경(X축)
		if (!KEYMANAGER->isStayKeyDown(VK_SHIFT))
		{
			if (KEYMANAGER->isOnceKeyDown('0'))
			{
				_selectSizeX = 0;
				if (_countMapX + 20 > _tileSizeX[_selectSizeX]) _countMapX = _tileSizeX[_selectSizeX] - 20;
			}
			else if (KEYMANAGER->isOnceKeyDown('1'))
			{
				_selectSizeX = 1;
				if (_countMapX + 20 > _tileSizeX[_selectSizeX]) _countMapX = _tileSizeX[_selectSizeX] - 20;
			}
			else if (KEYMANAGER->isOnceKeyDown('2'))
			{
				_selectSizeX = 2;
				if (_countMapX + 20 > _tileSizeX[_selectSizeX]) _countMapX = _tileSizeX[_selectSizeX] - 20;
			}
			else if (KEYMANAGER->isOnceKeyDown('3'))
			{
				_selectSizeX = 3;
				if (_countMapX + 20 > _tileSizeX[_selectSizeX]) _countMapX = _tileSizeX[_selectSizeX] - 20;
			}
			else if (KEYMANAGER->isOnceKeyDown('4'))
			{
				_selectSizeX = 4;
				if (_countMapX + 20 > _tileSizeX[_selectSizeX]) _countMapX = _tileSizeX[_selectSizeX] - 20;
			}
			else if (KEYMANAGER->isOnceKeyDown('5'))
			{
				_selectSizeX = 5;
				if (_countMapX + 20 > _tileSizeX[_selectSizeX]) _countMapX = _tileSizeX[_selectSizeX] - 20;
			}
		}

		//맵사이즈 변경(Y축)
		else
		{
			if (KEYMANAGER->isOnceKeyDown('0'))
			{
				_selectSizeY = 0;
				if (_countMapY + 20 > _tileSizeY[_selectSizeY]) _countMapY = _tileSizeY[_selectSizeY] - 20;
			}
			else if (KEYMANAGER->isOnceKeyDown('1'))
			{
				_selectSizeY = 1;
				if (_countMapY + 20 > _tileSizeY[_selectSizeY]) _countMapY = _tileSizeY[_selectSizeY] - 20;
			}
			else if (KEYMANAGER->isOnceKeyDown('2'))
			{
				_selectSizeY = 2;
				if (_countMapY + 20 > _tileSizeY[_selectSizeY]) _countMapY = _tileSizeY[_selectSizeY] - 20;
			}
			else if (KEYMANAGER->isOnceKeyDown('3'))
			{
				_selectSizeY = 3;
				if (_countMapY + 20 > _tileSizeY[_selectSizeY]) _countMapY = _tileSizeY[_selectSizeY] - 20;
			}
			else if (KEYMANAGER->isOnceKeyDown('4'))
			{
				_selectSizeY = 4;
				if (_countMapY + 20 > _tileSizeY[_selectSizeY]) _countMapY = _tileSizeY[_selectSizeY] - 20;
			}
			else if (KEYMANAGER->isOnceKeyDown('5'))
			{
				_selectSizeY = 5;
				if (_countMapY + 20 > _tileSizeY[_selectSizeY]) _countMapY = _tileSizeY[_selectSizeY] - 20;
			}
		}
	}

	//원본 맵 보기 on/off && 그림에 맞게 _selectSize맞추기
	if (KEYMANAGER->isOnceKeyDown(VK_TAB))
	{
		if (_mapView)	_mapView = false;
		else			_mapView = true;
	}

	//TERRAIN 보기 on/off
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		if (_viewTERRAIN)	_viewTERRAIN = false;
		else				_viewTERRAIN = true;
	}

	//원본맵그림 X, Y 업데이트하기
	if (IMAGEMANAGER->findImage(_fileName) != NULL)
	{
		IMAGEMANAGER->findImage(_fileName)->setX(-(_countMapX * TILESIZE));
		IMAGEMANAGER->findImage(_fileName)->setY(-(_countMapY * TILESIZE));
	}

	_alphaValueBox->update();
	if (_alphaValueBox->getStrNum() > 100) _alphaValueBox->setStrNum(100);
	else if (_alphaValueBox->getStrNum() < 0) _alphaValueBox->setStrNum(0);
	_alphaValue = (int)(((100 - (float)_alphaValueBox->getStrNum()) / 100) * (float)255);

	//오브젝트에 값넣기
	if (KEYMANAGER->isOnceKeyDown(MK_LBUTTON)
		&& PtInRect(&RectMake(WINSIZEX - 37, 672 - 58, 34, 18), _ptMouse))
	{
		for (int i = 0; i < TILEVIEWX; i++)
		{
			for (int j = 0; j < TILEVIEWY; j++)
			{
				if (_tiles[(i + _countMapY) * TILEVIEWY * (TILEX / TILEVIEWY) + j + _countMapX].isClick)
					_stprintf(_tiles[(i + _countMapY) * TILEVIEWY * (TILEX / TILEVIEWY) + j + _countMapX].obj, _tileObj->getStr());
			}
		}
	}
}

void sceneMaptool::render(void)	
{
	SetBkMode(getMemDC(), TRANSPARENT);

	//샘플타일
	RectangleMake(getMemDC(), WINSIZEX - 3 * TILESIZE - 1, 0, TILESIZE * 3 + 1, TILESIZE * 10 + 21);
	TextOut(getMemDC(), WINSIZEX - (3 * TILESIZE) / 2 - 20, 1, L"지형", _tcslen(L"지형"));

	for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
	{
		if (_sampleTiles[i].img == NULL) continue;
		_sampleTiles[i].img->render(getMemDC(), _sampleTiles[i].rcTile.left, _sampleTiles[i].rcTile.top);
	}

	//샘플 오브젝트 타일
	RectangleMake(getMemDC(), WINSIZEX - 3 * TILESIZE - 1, TILESIZE * 10 + 21, TILESIZE * 3 + 1, TILESIZE + 41);
	RectangleMake(getMemDC(), WINSIZEX - 3 * TILESIZE - 1, TILESIZE * 10 + 40, TILESIZE + 1, TILESIZE + 22);
	RectangleMake(getMemDC(), WINSIZEX - 2 * TILESIZE - 1, TILESIZE * 10 + 40, TILESIZE + 1, TILESIZE + 22);
	RectangleMake(getMemDC(), WINSIZEX - 1 * TILESIZE - 1, TILESIZE * 10 + 40, TILESIZE + 1, TILESIZE + 22);

	TextOut(getMemDC(), WINSIZEX - (3 * TILESIZE) / 2 - 20, TILESIZE * 10 + 22, L"유닛", _tcslen(L"유닛"));
	TextOut(getMemDC(), WINSIZEX - 3 * TILESIZE + 6, TILESIZE * 10 + 22 + TILESIZE + 20, L"아군", _tcslen(L"아군"));
	TextOut(getMemDC(), WINSIZEX - (3 * TILESIZE) / 2 - 20, TILESIZE * 10 + 22 + TILESIZE + 20, L"적군", _tcslen(L"적군"));
	TextOut(getMemDC(), WINSIZEX - TILESIZE + 2, TILESIZE * 10 + 22 + TILESIZE + 20, L"player", _tcslen(L"player"));

	for (int i = 0; i < OBJECTSELECT_MAX; i++)
	{
		_objTiles[i].img->render(getMemDC(), _objTiles[i].rcTile.left, _objTiles[i].rcTile.top);
	}


	//에딧박스 및 정보
	TCHAR text[128];
	_stprintf(text, L"맵 크기");
	TextOut(getMemDC(), WINSIZEX - 3 * TILESIZE + 45, 680, text, wcslen(text));
	RectangleMake(getMemDC(), WINSIZEX - 3 * TILESIZE + 20, 700, 100, 30);

	if (_isMapLoad)
	{
		_stprintf(_saveSize, L"%d x %d", (int)IMAGEMANAGER->findImage(_fileName)->getWidth(), (int)IMAGEMANAGER->findImage(_fileName)->getHeight());
	}
	TextOut(getMemDC(), WINSIZEX - 3 * TILESIZE + 25, 703, _saveSize, wcslen(_saveSize));

	_stprintf(text, L"맵 번호(0-57)");
	TextOut(getMemDC(), WINSIZEX - 3 * TILESIZE + 25, 735, text, wcslen(text));
	_editBox->render();

	_stprintf(text, L"투명도(0-100(%%))");
	TextOut(getMemDC(), WINSIZEX - 3 * TILESIZE + 15, 790, text, wcslen(text));
	_alphaValueBox->render();

	_stprintf(text, L"유닛 이름");
	TextOut(getMemDC(), WINSIZEX - 3 * TILESIZE, 592, text, wcslen(text));
	_tileObj->render();

	IMAGEMANAGER->findImage(L"맵툴버튼")->render(getMemDC(), WINSIZEX - 37, 672 - 58, 0, 0, 34, 18);
	_stprintf(text, L"save");
	TextOut(getMemDC(), WINSIZEX - 36, 673 - 58, text, wcslen(text));

	//지형
	for (int i = 0; i < TILEVIEWX; i++)
	{
		for (int j = 0; j < TILEVIEWY; j++)
		{
			IMAGEMANAGER->render(_sampleTiles[_tiles[(i + _countMapY) * TILEVIEWY * (TILEX / TILEVIEWY) + j + _countMapX].sampleTerrainIdx].strImgKey, getMemDC(), _tiles[i * TILEVIEWY * (TILEX / TILEVIEWY) + j].rc.left, _tiles[i * TILEVIEWY * (TILEX / TILEVIEWY) + j].rc.top);
		}
	}

	//오브젝트
	for (int i = 0; i < TILEVIEWX; i++)
	{
		for (int j = 0; j < TILEVIEWY; j++)
		{
			if (_tiles[(i + _countMapY) * TILEVIEWY * (TILEX / TILEVIEWY) + j + _countMapX].sampleObjectSelectIdx == OBJECTSELECT_NONE) continue;

			IMAGEMANAGER->alphaRender(_objTiles[_tiles[(i + _countMapY) * TILEVIEWY * (TILEX / TILEVIEWY) + j + _countMapX].sampleObjectSelectIdx].strImgKey, getMemDC(), _tiles[i * TILEVIEWY * (TILEX / TILEVIEWY) + j].rc.left, _tiles[i * TILEVIEWY * (TILEX / TILEVIEWY) + j].rc.top, 128);
			if (_tiles[(i + _countMapY) * TILEVIEWY * (TILEX / TILEVIEWY) + j + _countMapX].isClick) 
				IMAGEMANAGER->findImage(L"타일선택")->render(getMemDC(), _tiles[i * TILEVIEWY * (TILEX / TILEVIEWY) + j].rc.left, _tiles[i * TILEVIEWY * (TILEX / TILEVIEWY) + j].rc.top);
			TextOut(getMemDC(), _tiles[i * TILEVIEWY * (TILEX / TILEVIEWY) + j].rc.left, _tiles[i * TILEVIEWY * (TILEX / TILEVIEWY) + j].rc.bottom - 18, _tiles[(i + _countMapY) * TILEVIEWY * (TILEX / TILEVIEWY) + j + _countMapX].obj, _tcslen(_tiles[(i + _countMapY) * TILEVIEWY * (TILEX / TILEVIEWY) + j + _countMapX].obj));
		}
	}

	//맵툴 기능 버튼
	for (int i = 0; i < CTRL_END; i++)
	{
		_ctrlButton[i]->render();
		TextOut(getMemDC(), _ctrlButton[i]->getRect().left, _ctrlButton[i]->getRect().top, _strButton[i], _tcslen(_strButton[i]));
	}
	_exit->render();
	TextOut(getMemDC(), _exit->getRect().left, _exit->getRect().top, _strExit, _tcslen(_strExit));

	//스페이스바 누르면 TERRAIN 번호 보여주기
	if (_viewTERRAIN)
	{
		for (int i = 0; i < TILEVIEWX; i++)
		{
			for (int j = 0; j < TILEVIEWY; j++)
			{
				TCHAR text[128];
				_stprintf_s(text, L"%d", _tiles[(i + _countMapY) * TILEVIEWY * (TILEX / TILEVIEWY) + j + _countMapX].terrain);
				TextOut(getMemDC(), _tiles[i * TILEVIEWY * (TILEX / TILEVIEWY) + j].rc.left, _tiles[i * TILEVIEWY * (TILEX / TILEVIEWY) + j].rc.top, text, wcslen(text));
			}
		}
	}

	//원본 맵 탭누르면 보게하기
	if (_mapView)
	{
		if (_isMapLoad)
		{
			IMAGEMANAGER->findImage(_fileName)->alphaRender(getMemDC(), 0, 0, _countMapX * 48, _countMapY * 48, 960, 960, _alphaValue);
		}
	}
}

void sceneMaptool::getChar(WPARAM wParam)
{
	_editBox->getChar(wParam);
	_alphaValueBox->getChar(wParam);
	_tileObj->getChar(wParam);
}

//-----------------------------------------------------------------------------------------
//callback functions
void sceneMaptool::ctrlSelectSave(void* obj)
{
	sceneMaptool* maptool = (sceneMaptool*)obj;

	maptool->save();
}

void sceneMaptool::ctrlSelectLoad(void* obj)
{
	sceneMaptool* maptool = (sceneMaptool*)obj;

	maptool->load();
}

void sceneMaptool::ctrlSelectTerrain(void* obj)
{
	sceneMaptool* maptool = (sceneMaptool*)obj;

	maptool->setCtrlSelect(CTRL_TERRAINDRAW);
}

void sceneMaptool::ctrlSelectObject(void* obj)
{
	sceneMaptool* maptool = (sceneMaptool*)obj;

	maptool->setCtrlSelect(CTRL_OBJDRAW);
}

void sceneMaptool::ctrlSelectEraser(void* obj)
{
	sceneMaptool* maptool = (sceneMaptool*)obj;

	maptool->setCtrlSelect(CTRL_ERASER);
}
void sceneMaptool::exit(void * obj)
{
	SCENEMANAGER->changeScene(L"선택씬");
}
//~callback functions
//-----------------------------------------------------------------------------------------

void sceneMaptool::setup(void)
{
	//기능 버튼 생성
	_ctrlButton[CTRL_SAVE] = new button;
	_ctrlButton[CTRL_LOAD] = new button;
	_ctrlButton[CTRL_ERASER] = new button;
	
	_ctrlButton[CTRL_SAVE]->init(L"맵툴버튼",	WINSIZEX - (3 * TILESIZE) / 2, WINSIZEY - 100, { 0, 0 }, { 0, 1 }, ctrlSelectSave, this);
	_ctrlButton[CTRL_LOAD]->init(L"맵툴버튼",	WINSIZEX - (3 * TILESIZE) / 2, WINSIZEY - 60, { 0, 0 }, { 0, 1 }, ctrlSelectLoad, this);
	_ctrlButton[CTRL_ERASER]->init(L"맵툴버튼",	WINSIZEX - (3 * TILESIZE) / 2, TILESIZE * 14 - 10, { 0, 0 }, { 0, 1 }, ctrlSelectEraser, this);
	
	_stprintf(_strButton[CTRL_SAVE], L"SAVE");
	_stprintf(_strButton[CTRL_LOAD], L"LOAD");
	_stprintf(_strButton[CTRL_ERASER], L"ERASER");

	_exit = new button;
	_exit->init(L"맵툴버튼", WINSIZEX - (3 * TILESIZE) / 2, WINSIZEY - 20, { 0, 0 }, { 0, 1 }, exit, this);
	_stprintf(_strExit, L"EXIT");

	_ctrSelect = CTRL_TERRAINDRAW;

	_ctrObjectSelect = OBJECTSELECT_PLAYER;

	//샘플타일 시작점
	POINT ptSampleStart = { WINSIZEX - TILESIZE * SAMPLETILEX, 20 };

	//샘플 타일셋 셋팅
	for (int i = 0; i < SAMPLETILEY; i++)
	{
		for (int j = 0; j < SAMPLETILEX; j++)
		{
			int index = i * SAMPLETILEX + j;
			_stprintf(_sampleTiles[index].strImgKey, L"tile (%02d)", index + 1);

			_sampleTiles[index].img = IMAGEMANAGER->findImage(_sampleTiles[index].strImgKey);
			_sampleTiles[index].rcTile = RectMake(ptSampleStart.x + j*TILESIZE, ptSampleStart.y + i * TILESIZE, TILESIZE, TILESIZE);
		}
	}

	//샘플 오브젝트타일 시작점
	POINT ptSampleObjStart = { WINSIZEX - TILESIZE * 3, TILESIZE * 10 + 41 };

	//오브젝트 타일셋 셋팅
	_objTiles[OBJECTSELECT_AILY].img = IMAGEMANAGER->findImage(L"objAliy");
	_objTiles[OBJECTSELECT_AILY].rcTile = RectMake(ptSampleObjStart.x, ptSampleObjStart.y, TILESIZE, TILESIZE);
	_stprintf(_objTiles[OBJECTSELECT_AILY].strImgKey, L"objAliy");

	_objTiles[OBJECTSELECT_ENEMY].img = IMAGEMANAGER->findImage(L"objEnemy");
	_objTiles[OBJECTSELECT_ENEMY].rcTile = RectMake(ptSampleObjStart.x + TILESIZE, ptSampleObjStart.y, TILESIZE, TILESIZE);
	_stprintf(_objTiles[OBJECTSELECT_ENEMY].strImgKey, L"objEnemy");

	_objTiles[OBJECTSELECT_PLAYER].img = IMAGEMANAGER->findImage(L"objPlayer");
	_objTiles[OBJECTSELECT_PLAYER].rcTile = RectMake(ptSampleObjStart.x + TILESIZE * 2, ptSampleObjStart.y, TILESIZE, TILESIZE);
	_stprintf(_objTiles[OBJECTSELECT_PLAYER].strImgKey, L"objPlayer");
	
	//샘플타일 시작점
	POINT ptTileStart = { 0, 0 };

	//타일 영역 셋팅
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			int index = i * TILEX + j;

			_tiles[index].rc = RectMake(ptTileStart.x + j * TILESIZE, ptTileStart.y + i * TILESIZE, TILESIZE, TILESIZE);
		}
	}

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		_tiles[i].sampleTerrainIdx = 0;
		_tiles[i].sampleObjectSelectIdx = OBJECTSELECT_NONE;
		_tiles[i].terrain = terrainSelect(_tiles[i].sampleTerrainIdx);
		_tiles[i].isClick = false;
		_stprintf(_tiles[i].obj, L"");
	}
}

void sceneMaptool::setMap(void)
{
	if (PtInRect(&RectMake(WINSIZEX - 3 * TILESIZE, 20, 3 * TILESIZE, 10 * TILESIZE + 20), _ptMouse))
	{
		_ctrSelect = CTRL_TERRAINDRAW;
		for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
		{
			if (PtInRect(&_sampleTiles[i].rcTile, _ptMouse))
			{
				_selectSampleIndex = i;
				break;
			}
		}
	}

	if (PtInRect(&RectMake(WINSIZEX - 3 * TILESIZE, TILESIZE * 10 + 41, TILESIZE * 3, TILESIZE), _ptMouse))
	{
		_ctrSelect = CTRL_OBJDRAW;
		for (int i = 0; i < OBJECTSELECT_MAX; i++)
		{
			if (PtInRect(&_objTiles[i].rcTile, _ptMouse))	_ctrObjectSelect = i;
		}
	}

	if (PtInRect(&RectMake(0, 0, 20 * TILESIZE, 20 * TILESIZE), _ptMouse))
	{
		for (int i = 0; i < TILEX; i++)
		{
			for (int j = 0; j < TILEY; j++)
			{
				if (PtInRect(&_tiles[i * 20 * (TILEX / 20) + j].rc, _ptMouse))
				{
					if (_ctrSelect == CTRL_TERRAINDRAW)
					{
						_tiles[(i + _countMapY) * 20 * (TILEX / 20) + j + _countMapX].sampleTerrainIdx = _selectSampleIndex;
						_tiles[(i + _countMapY) * 20 * (TILEX / 20) + j + _countMapX].terrain = (TERRAIN)_selectSampleIndex;
					}
					else if (_ctrSelect == CTRL_OBJDRAW)
					{
						if (_tiles[(i + _countMapY) * 20 * (TILEX / 20) + j + _countMapX].sampleObjectSelectIdx != OBJECTSELECT_NONE) continue;
						_tiles[(i + _countMapY) * 20 * (TILEX / 20) + j + _countMapX].sampleObjectSelectIdx = _ctrObjectSelect;
					}
					else if (_ctrSelect == CTRL_ERASER)
					{
						_stprintf(_tiles[(i + _countMapY) * 20 * (TILEX / 20) + j + _countMapX].obj, L"");
						_tiles[(i + _countMapY) * 20 * (TILEX / 20) + j + _countMapX].sampleObjectSelectIdx = OBJECTSELECT_NONE;
					}

					break;
				}
			}
		}
	}
}
					
void sceneMaptool::save(void)
{
	HANDLE file;
	DWORD write;

	int num = _editBox->getStrNum();
	TCHAR strFile[100];
	_stprintf(strFile, L"MapData/M%03d.map", num);

	file = CreateFile(strFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &write, NULL);

	CloseHandle(file);

}

void sceneMaptool::load(void)
{
	HANDLE file;
	DWORD read;

	int num = _editBox->getStrNum();
	TCHAR strFile[100];
	_stprintf(strFile, L"MapData/M%03d.map", num);

	file = CreateFile(strFile, GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);

	_stprintf(_fileName, L"M%03d", num);

	//맵사이즈 그림에 맞게 변경
	for (int i = 0; i < 6; i++)
	{
		if (IMAGEMANAGER->findImage(_fileName)->getWidth() / TILESIZE == _tileSizeX[i])		_selectSizeX = i;
		if (IMAGEMANAGER->findImage(_fileName)->getHeight() / TILESIZE == _tileSizeY[i])	_selectSizeY = i;
	}

	if (_countMapX + 20 > _tileSizeX[_selectSizeX]) _countMapX = _tileSizeX[_selectSizeX] - 20;
	if (_countMapY + 20 > _tileSizeY[_selectSizeY]) _countMapY = _tileSizeY[_selectSizeY] - 20;

	_isMapLoad = true;
	_mapView = false;

	CloseHandle(file);
}

TERRAIN sceneMaptool::terrainSelect(int index)
{

	return TERRAIN_RIVER;
}
