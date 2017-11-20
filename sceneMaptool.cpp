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
	
	_countX = _countY = 0;

	for (int i = 0; i < 9; i++)
	{
		_tileSizeX[i] = _tileSizeY[i] = 20 + i * 5;
	}

	_selectSize = 8;

	return S_OK;
}
void sceneMaptool::release(void)
{

}

void sceneMaptool::update(void)	
{
	for (int i = 0; i < CTRL_END; i++)
	{
		_ctrlButton[i]->update();
	}

	if (KEYMANAGER->isOnceKeyDown(MK_LBUTTON) || KEYMANAGER->isStayKeyDown(MK_LBUTTON))	setMap();

	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_countX--;
		if (_countX < 0) _countX = 0;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_countX++;
		if (_countX + 20 > _tileSizeX[_selectSize]) _countX = _tileSizeX[_selectSize] - 20;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_countY--;
		if (_countY < 0) _countY = 0;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_countY++;
		if (_countY + 20 > _tileSizeY[_selectSize]) _countY = _tileSizeY[_selectSize] - 20;
	}
}

void sceneMaptool::render(void)	
{
	for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
	{
		if (_sampleTiles[i].img == NULL) continue;
		_sampleTiles[i].img->render(getMemDC(), _sampleTiles[i].rcTile.left, _sampleTiles[i].rcTile.top);
	}


	//지형
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			IMAGEMANAGER->render(_sampleTiles[_tiles[(i + _countY) * 20 * (TILEX / 20) + j + _countX].sampleTerrainIdx].strImgKey, getMemDC(), _tiles[i * 20 * (TILEX / 20) + j].rc.left, _tiles[i * 20 * (TILEX / 20) + j].rc.top);
		}
	}

	//오브젝트
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_tiles[i].obj == OBJECT_NONE) continue;
	}

	for (int i = 0; i < CTRL_END; i++)
	{
		_ctrlButton[i]->render();
		TextOut(getMemDC(), _ctrlButton[i]->getRect().left, _ctrlButton[i]->getRect().top, _strButton[i], _tcslen(_strButton[i]));
	}

}

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


void sceneMaptool::setup(void)
{
	_ctrlButton[CTRL_SAVE] = new button;
	_ctrlButton[CTRL_LOAD] = new button;
	_ctrlButton[CTRL_TERRAINDRAW] = new button;
	_ctrlButton[CTRL_OBJDRAW] = new button;
	_ctrlButton[CTRL_ERASER] = new button;
	
	_ctrlButton[CTRL_SAVE]->init(L"맵툴버튼",         1100, 300, { 0, 0 }, { 0, 1 }, ctrlSelectSave, this);
	_ctrlButton[CTRL_LOAD]->init(L"맵툴버튼",         1100, 400, { 0, 0 }, { 0, 1 }, ctrlSelectLoad, this);
	_ctrlButton[CTRL_TERRAINDRAW]->init(L"맵툴버튼",  1100, 500, { 0, 0 }, { 0, 1 }, ctrlSelectTerrain, this);
	_ctrlButton[CTRL_OBJDRAW]->init(L"맵툴버튼",      1100, 600, { 0, 0 }, { 0, 1 }, ctrlSelectObject, this);
	_ctrlButton[CTRL_ERASER]->init(L"맵툴버튼",       1100, 700, { 0, 0 }, { 0, 1 }, ctrlSelectEraser, this);

	
	_stprintf(_strButton[CTRL_SAVE], L"SAVE");
	_stprintf(_strButton[CTRL_LOAD], L"LOAD");
	_stprintf(_strButton[CTRL_TERRAINDRAW], L"TERRAIN");
	_stprintf(_strButton[CTRL_OBJDRAW], L"OBJECT");
	_stprintf(_strButton[CTRL_ERASER], L"ERASER");

	_ctrSelect = CTRL_TERRAINDRAW;

	//샘플타일 시작점
	POINT ptSampleStart = { WINSIZEX - TILESIZE * SAMPLETILEX, 0 };

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
		_tiles[i].terrain = terrainSelect(_tiles[i].sampleTerrainIdx);
		_tiles[i].obj = OBJECT_NONE;
	}
}

void sceneMaptool::setMap(void)
{
	if (PtInRect(&RectMake(WINSIZEX - 3 * TILESIZE, 0, 3 * TILESIZE, 10 * TILESIZE), _ptMouse))
	for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
	{
		if (PtInRect(&_sampleTiles[i].rcTile, _ptMouse))
		{
			_selectSampleIndex = i;
			break;
		}
	}

	if (PtInRect(&RectMake(0, 0, 20 * TILESIZE, 20 * TILESIZE), _ptMouse))
	for (int i = 0; i < TILEX; i++)
	{
		for (int j = 0; j < TILEY; j++)
		{
			if (PtInRect(&_tiles[i * 20 * (TILEX / 20) + j].rc, _ptMouse))
			{
				if (_ctrSelect == CTRL_TERRAINDRAW)
				{
					_tiles[(i + _countY) * 20 * (TILEX / 20) + j + _countX].sampleTerrainIdx = _selectSampleIndex;

					_tiles[(i + _countY) * 20 * (TILEX / 20) + j + _countX].terrain = terrainSelect(_tiles[(i + _countY) * 20 * (TILEX / 20) + j + _countX].sampleTerrainIdx);
				}
				else if (_ctrSelect == CTRL_OBJDRAW)
				{
					//_tiles[i].obj = objSelect(_currentTile.x, _currentTile.y);
				}
				else if (_ctrSelect == CTRL_ERASER)
				{
					_tiles[(i + _countY) * 20 * (TILEX / 20) + j + _countX].sampleTerrainIdx = NULL;

					//_tiles[i].obj = OBJ_NONE;
				}

				break;
			}
		}
	}
}
					
void sceneMaptool::save(void)
{
	HANDLE file;
	DWORD write;

	file = CreateFile(L"mapSave.map", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &write, NULL);

	CloseHandle(file);

}

void sceneMaptool::load(void)
{
	HANDLE file;
	DWORD read;

	file = CreateFile(L"mapSave.map", GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);

	CloseHandle(file);
}

TERRAIN sceneMaptool::terrainSelect(int index)
{

	return TERRAIN_NONE;
}

OBJECT sceneMaptool::objSelect(int index)
{

	return OBJECT_NONE;
}
