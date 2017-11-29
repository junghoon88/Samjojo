#include "stdafx.h"
#include "gameMap.h"
#include "Player.h"
#include "Friend.h"
#include "Enemy.h"
#include "infoCursor.h"


gameMap::gameMap()
	: _imgMap(NULL)
{
}


gameMap::~gameMap()
{
}

HRESULT gameMap::init(void)
{
	ZeroMemory(&_tiles, sizeof(tagTile) * TILEX * TILEY);

	for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
	{
		_stprintf(_strSampleImgKey[i], L"tile (%02d)", i + 1);
	}

	_stprintf(_objImage[OBJECTSELECT_AILY], L"objAliy");
	_stprintf(_objImage[OBJECTSELECT_ENEMY], L"objEnemy");
	_stprintf(_objImage[OBJECTSELECT_PLAYER], L"objPlayer");

	_tilesizeX = 0;
	_tilesizeY = 0;


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
#if 0
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		image* img = IMAGEMANAGER->findImage(_strSampleImgKey[_tiles[i].sampleTerrainIdx]);
		if (img)
		{
			img->render(getMemDC(), _tiles[i].rc.left - MAINCAMERA->getCameraX(), _tiles[i].rc.top - MAINCAMERA->getCameraY());
		}

		if (_tiles[i].sampleObjectSelectIdx != OBJECTSELECT_NONE)
		{
			IMAGEMANAGER->alphaRender(_objImage[_tiles[i].sampleObjectSelectIdx], getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, 128);
			TextOut(getMemDC(), _tiles[i].rc.left, _tiles[i].rc.bottom - 20, _tiles[i].obj, _tcslen(_tiles[i].obj));
		}
	}

	if (_imgMap)
	{
		if (KEYMANAGER->isStayKeyDown(VK_TAB))
		{
			_imgMap->alphaRender(getMemDC(), 0, 0, 180);
		}
	}
#else
	_imgMap->render(getMemDC(),0 - MAINCAMERA->getCameraX(),0 - MAINCAMERA->getCameraY());

#endif

}

void gameMap::loadData(int num)
{
	HANDLE file;
	DWORD read;

	//맵 이미지, 맵타일 개수를 불러온다.
	TCHAR strMapKey[100];
	_stprintf(strMapKey, L"M%03d", num);
	_imgMap = IMAGEMANAGER->findImage(strMapKey);

	if (_imgMap == NULL) return;

	_tilesizeX = _imgMap->getWidth() / TILESIZE;
	_tilesizeY = _imgMap->getHeight() / TILESIZE;

	//실제 맵 데이터를 불러온다.
	TCHAR strMapName[100];
	_stprintf(strMapName, L"MapData/M%03d.map", num);

	file = CreateFile(strMapName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);

	ZeroMemory(&_attribute, sizeof(DWORD) * TILEX * TILEY);

	CloseHandle(file);
}
