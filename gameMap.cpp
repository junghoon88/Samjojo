#include "stdafx.h"
#include "gameMap.h"


gameMap::gameMap()
{
}


gameMap::~gameMap()
{
}

HRESULT gameMap::init(void)
{
	load();

	return S_OK;
}

void gameMap::release(void)
{
}

void gameMap::update(void)
{
}

void gameMap::render(void)
{
	//ÁöÇü
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		IMAGEMANAGER->render(L"mapTiles", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top,
										_tiles[i].terrainFrameX * (TILESIZE + 1) + 1, _tiles[i].terrainFrameY * (TILESIZE + 1) + 1, TILESIZE, TILESIZE);
	}

}

void gameMap::load(void)
{
	HANDLE file;
	DWORD read;

	file = CreateFile(L"mapSave.map", GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);

	ZeroMemory(&_attribute, sizeof(DWORD) * TILEX * TILEY);

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		//if (_tiles[i].terrain == TR_WALL || _tiles[i].terrain == TR_BORDER)
		//{
		//	_attribute[i] |= ATTR_UNMOVE;
		//}
	}

	CloseHandle(file);
}
