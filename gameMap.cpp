#include "stdafx.h"
#include "gameMap.h"
#include "Player.h"
#include "Friend.h"
#include "Enemy.h"
#include "battleSceneInterface.h"
#include "Unit.h"


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

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		switch (_tiles[i].terrain)
		{
		case TERRAIN_NONE:
			break;
		case TERRAIN_RIVER:
		case TERRAIN_WATER:
		case TERRAIN_DITCH:
		case TERRAIN_ROCK:
		case TERRAIN_SHIP:
		case TERRAIN_BROW:
		case TERRAIN_FIRE:
		case TERRAIN_CASTLEGATE:
		case TERRAIN_RAMPART:
		case TERRAIN_POND:
		case TERAAIN_FENCE:
		case TERRAIN_ALTER:
		case TERRAIN_UNDERGROUND:
			_attribute[i] = ATTR_UNMOVE;
			break;
		case TERRAIN_BRIDGE:
			_attribute[i] = ATTR_BRIDGE;
			break;
		case TERRAIN_VILLAGE:
		case TERRAIN_BARRACK:
		case TERRAIN_CASTLE:
		case TERRAIN_STRONGHOLD:
		case TERRAIN_GATEWAY:
			_attribute[i] = ATTR_CASTLE;
			break;
		case TERRAIN_PREMISES:
		case TERRAIN_FOREST:
			_attribute[i] = ATTR_FOREST;
			break;
		case TERRAIN_WAREHOUSE:
			_attribute[i] = ATTR_WAREHOUSE;
			break;
		case TERRAIN_MOUNTAIN:
		case TERRAIN_BADLANDS:
			_attribute[i] = ATTR_MOUNTAIN;
			break;
		case TERRAIN_SNOW:
			_attribute[i] = ATTR_SNOW;
			break;
		case TERRAIN_INCASTLE:
			_attribute[i] = ATTR_INCASTLE;
			break;
		case TERRAIN_SWAMP:
		case TERRAIN_FORD:
			_attribute[i] = ATTR_WATER;
			break;
		case TERRAIN_GRASSLAND:
		case TERRAIN_FLAT:
			_attribute[i] = ATTR_FLAT;
			break;
		case TERRAIN_MAX:
			break;
		default:
			break;
		}
	}

	memset(&_teamInfo, TEAM_NONE, sizeof(TEAM)*TILEX*TILEY);

	CloseHandle(file);
}

void gameMap::scanUnitsPos(void)
{
	memset(&_teamInfo, TEAM_NONE, sizeof(TEAM)*TILEX*TILEY);

	for (int i = 0; i < _player->getUnits().size(); i++)
	{
		POINT tilept = _player->getUnits()[i]->getBattleState().tilePt;
		_teamInfo[tilept.x + tilept.y * TILEX] = TEAM_PLAYER;
	}
	for (int i = 0; i < _friend->getUnits().size(); i++)
	{
		POINT tilept = _friend->getUnits()[i]->getBattleState().tilePt;
		_teamInfo[tilept.x + tilept.y * TILEX] = TEAM_FRIEND;
	}
	for (int i = 0; i < _enemy->getUnits().size(); i++)
	{
		if (_enemy->getUnits()[i]->getBattleState().isHiding) continue;

		POINT tilept = _enemy->getUnits()[i]->getBattleState().tilePt;
		_teamInfo[tilept.x + tilept.y * TILEX] = TEAM_ENEMY;
	}
}

Unit* gameMap::findEnemyUnit(TEAM myTeam, POINT tilePt)
{
	switch (myTeam)
	{
	case TEAM_PLAYER:
	case TEAM_FRIEND:
		for (int i = 0; i < _enemy->getUnits().size(); i++)
		{
			POINT emTilePt = _enemy->getUnits()[i]->getBattleState().tilePt;

			if (tilePt.x == emTilePt.x && tilePt.y == emTilePt.y)
			{
				return _enemy->getUnits()[i];
			}
		}
		break;
	case TEAM_ENEMY:
		for (int i = 0; i < _player->getUnits().size(); i++)
		{
			POINT emTilePt = _player->getUnits()[i]->getBattleState().tilePt;

			if (tilePt.x == emTilePt.x && tilePt.y == emTilePt.y)
			{
				return _player->getUnits()[i];
			}
		}
		for (int i = 0; i < _friend->getUnits().size(); i++)
		{
			POINT emTilePt = _friend->getUnits()[i]->getBattleState().tilePt;

			if (tilePt.x == emTilePt.x && tilePt.y == emTilePt.y)
			{
				return _friend->getUnits()[i];
			}
		}
		break;
	}
	return NULL;
}
