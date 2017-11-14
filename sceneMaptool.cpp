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
	IMAGEMANAGER->addFrameImage(L"버튼", L"image/button.bmp", 100, 30, 1, 1);
	IMAGEMANAGER->addFrameImage(L"mapTiles", L"image/mapTiles.bmp", 0, 0, 640, 288, SAMPLETILEX, SAMPLETILEY, true, RGB(255, 0, 255));

	setup();

	return S_OK;
}
void sceneMaptool::release(void)
{

}

void sceneMaptool::update(void)	
{
	RECT rcMap = { 0, 0, TILESIZEX, TILESIZEY };

	for (int i = 0; i < CTRL_END; i++)
	{
		ctrlButton[i]->update();
	}

	if (KEYMANAGER->isOnceKeyDown(MK_LBUTTON) || KEYMANAGER->isStayKeyDown(MK_LBUTTON))
		setMap();

}

void sceneMaptool::render(void)	
{
	IMAGEMANAGER->render(L"mapTiles", getMemDC(), WINSIZEX - IMAGEMANAGER->findImage(L"mapTiles")->getWidth(), 0);


	//지형
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		IMAGEMANAGER->frameRender(L"mapTiles", getMemDC(),
												_tiles[i].rc.left, _tiles[i].rc.top,
												_tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
	}

	//오브젝트
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_tiles[i].obj == OBJ_NONE) continue;
		IMAGEMANAGER->frameRender(L"mapTiles", getMemDC(),
												_tiles[i].rc.left, _tiles[i].rc.top,
												_tiles[i].objFrameX, _tiles[i].objFrameY);
	}

	for (int i = 0; i < CTRL_END; i++)
	{
		ctrlButton[i]->render();
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
	ctrlButton[CTRL_SAVE] = new button;
	ctrlButton[CTRL_SAVE]->init(L"버튼", 700, 500, { 0, 0 }, { 0, 0 }, ctrlSelectSave, this);
	ctrlButton[CTRL_LOAD] = new button;
	ctrlButton[CTRL_LOAD]->init(L"버튼", 850, 500, { 0, 0 }, { 0, 0 }, ctrlSelectLoad, this);
	ctrlButton[CTRL_TERRAINDRAW] = new button;
	ctrlButton[CTRL_TERRAINDRAW]->init(L"버튼", 1000, 500, { 0, 0 }, { 0, 0 }, ctrlSelectTerrain, this);
	ctrlButton[CTRL_OBJDRAW] = new button;
	ctrlButton[CTRL_OBJDRAW]->init(L"버튼", 700, 600, { 0, 0 }, { 0, 0 }, ctrlSelectObject, this);
	ctrlButton[CTRL_ERASER] = new button;
	ctrlButton[CTRL_ERASER]->init(L"버튼", 850, 600, { 0, 0 }, { 0, 0 }, ctrlSelectEraser, this);

	_ctrSelect = CTRL_TERRAINDRAW;

	//타일셋 셋팅
	for (int i = 0; i < SAMPLETILEY; i++)
	{
		for (int j = 0; j < SAMPLETILEX; j++)
		{
			_sampleTiles[i * SAMPLETILEX + j].terrainFrameX = j;
			_sampleTiles[i * SAMPLETILEX + j].terrainFrameY = i;

			SetRect(&_sampleTiles[i * SAMPLETILEX + j].rcTile,
				(WINSIZEX - IMAGEMANAGER->findImage(L"mapTiles")->getWidth()) + j * TILESIZE, i * TILESIZE, 
				(WINSIZEX - IMAGEMANAGER->findImage(L"mapTiles")->getWidth()) + j * TILESIZE + TILESIZE, i * TILESIZE + TILESIZE);
		}
	}

	//타일 영역 셋팅
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			SetRect(&_tiles[i * TILEX + j].rc,
				j * TILESIZE,
				i * TILESIZE,
				j * TILESIZE + TILESIZE,
				i * TILESIZE + TILESIZE);
		}
	}

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		_tiles[i].terrainFrameX = 3;
		_tiles[i].terrainFrameY = 0;
		_tiles[i].objFrameX = 0;
		_tiles[i].objFrameY = 0;
		_tiles[i].terrain = terrainSelect(_tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
		_tiles[i].obj = OBJ_NONE;
	}
}

void sceneMaptool::setMap(void)
{
	for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
	{
		if (PtInRect(&_sampleTiles[i].rcTile, _ptMouse))
		{
			_currentTile.x = _sampleTiles[i].terrainFrameX;
			_currentTile.y = _sampleTiles[i].terrainFrameY;
			break;
		}
	}

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (PtInRect(&_tiles[i].rc, _ptMouse))
		{
			if (_ctrSelect == CTRL_TERRAINDRAW)
			{
				_tiles[i].terrainFrameX = _currentTile.x;
				_tiles[i].terrainFrameY = _currentTile.y;

				_tiles[i].terrain = terrainSelect(_currentTile.x, _currentTile.y);
			}
			else if (_ctrSelect == CTRL_OBJDRAW)
			{
				_tiles[i].objFrameX = _currentTile.x;
				_tiles[i].objFrameY = _currentTile.y;

				_tiles[i].obj = objSelect(_currentTile.x, _currentTile.y);
			}
			else if (_ctrSelect == CTRL_ERASER)
			{
				_tiles[i].objFrameX = NULL;
				_tiles[i].objFrameY = NULL;

				_tiles[i].obj = OBJ_NONE;
			}

			break;
		}
	}
}
					
void sceneMaptool::save(void)
{
	HANDLE file;
	DWORD write;

	file = CreateFile(L"mapSave.map", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &write, NULL);
	WriteFile(file, _pos, sizeof(int) * 2, &write, NULL);

	CloseHandle(file);

}

void sceneMaptool::load(void)
{
	HANDLE file;
	DWORD read;

	file = CreateFile(L"mapSave.map", GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);
	ReadFile(file, _pos, sizeof(int) * 2, &read, NULL);

	CloseHandle(file);
}

TERRAIN sceneMaptool::terrainSelect(int frameX, int frameY)
{
	if (frameX == 1 && frameY == 0)
	{
		return TR_CEMENT;
	}
	else if (frameX == 2 && frameY == 0)
	{
		return TR_DESERT;
	}
	else if (frameX == 3 && frameY == 0)
	{
		return TR_GRASS;
	}
	else if (frameX == 4 && frameY == 0)
	{
		return TR_WATER;
	}

	return TR_GRASS;
}

OBJECT sceneMaptool::objSelect(int frameX, int frameY)
{
	if (frameX == 0 && frameY == 0)
	{
		return OBJ_TANK1;
	}
	else if (frameX == 0 && frameY == 8)
	{
		return OBJ_TANK2;
	}
	else if (frameX == 0 && frameY == 1)
	{
		return OBJ_BLOCK1;
	}
	else if (frameX == 0 && frameY == 2)
	{
		return OBJ_BLOCK3;
	}
	else if (frameX == 15 && frameY == 3)
	{
		return OBJ_BLOCKS;
	}

	return OBJ_BLOCK1;
}
