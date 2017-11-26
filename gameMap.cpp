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
	for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
	{
		_stprintf(_strSampleImgKey[i], L"tile (%02d)", i);
	}

	_stprintf(_objImage[OBJECTSELECT_AILY], L"objAliy");
	_stprintf(_objImage[OBJECTSELECT_ENEMY], L"objEnemy");
	_stprintf(_objImage[OBJECTSELECT_PLAYER], L"objPlayer");

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
	//ÁöÇü
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		image* img = IMAGEMANAGER->findImage(_strSampleImgKey[_tiles[i].sampleTerrainIdx]);
		if (img)
		{
			img->render(getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top);
		}
		if (_tiles[i].sampleObjectSelectIdx != OBJECTSELECT_NONE)
		{
			IMAGEMANAGER->alphaRender(_objImage[_tiles[i].sampleObjectSelectIdx], getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, 128);
		}
		TextOut(getMemDC(), _tiles[i].rc.left, _tiles[i].rc.bottom - 20, _tiles[i].obj, _tcslen(_tiles[i].obj));
	}

}

void gameMap::loadData(int num)
{
	HANDLE file;
	DWORD read;

	TCHAR strMapName[100];
	_stprintf(strMapName, L"MapData/M%03d.map", num);

	file = CreateFile(strMapName, GENERIC_READ, 0, NULL,
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
