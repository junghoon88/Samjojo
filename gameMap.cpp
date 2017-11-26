#include "stdafx.h"
#include "gameMap.h"
#include "Player.h"
#include "Friend.h"
#include "Enemy.h"

gameMap::gameMap()
{
}


gameMap::~gameMap()
{
}

HRESULT gameMap::init(void)
{
	load();

	for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
	{
		_stprintf(_strSampleImgKey[i], L"tile (%02d)", i + 1);
	}

	_stprintf(_objImage[OBJECTSELECT_AILY], L"아군");
	_stprintf(_objImage[OBJECTSELECT_ENEMY], L"적군");
	_stprintf(_objImage[OBJECTSELECT_PLAYER], L"플레이어");

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
	SetBkMode(getMemDC(), TRANSPARENT);
	//지형
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		IMAGEMANAGER->render(_strSampleImgKey[_tiles[i].sampleTerrainIdx], getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top);
		if (_tiles[i].sampleObjectSelectIdx != OBJECTSELECT_NONE)
		IMAGEMANAGER->alphaRender(_objImage[_tiles[i].sampleObjectSelectIdx], getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, 128);
		TextOut(getMemDC(), _tiles[i].rc.left, _tiles[i].rc.bottom - 20, _tiles[i].obj, _tcslen(_tiles[i].obj));
	}

}

void gameMap::load(void)
{
	HANDLE file;
	DWORD read;

	file = CreateFile(L"MapData/M000.map", GENERIC_READ, 0, NULL,
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
