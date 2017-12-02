#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"
#include "Friend.h"
#include "gameMap.h"
#include "battleSceneInterface.h"

Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}

HRESULT Enemy::init(void)
{
	return S_OK;
}

void Enemy::release(void)
{
	deleteUnits();
}

void Enemy::update(void)
{
	for (int i = 0; i < _vUnits.size(); i++)
	{
		_vUnits[i]->update(TEAM_ENEMY);
	}
}

void Enemy::render(void)
{
	for (int i = 0; i < _vUnits.size(); i++)
	{
		_vUnits[i]->render();
	}
}

void Enemy::loadUnits(void)
{
	deleteUnits();


	//모든 파일 스캔 test
	WIN32_FIND_DATA wfd;
	HANDLE handle = FindFirstFile(L"UnitData/enemy/*.dat", &wfd);

	// 찾는 파일이 있다면,
	while (handle != INVALID_HANDLE_VALUE)
	{
		HANDLE file;
		DWORD read;

		TCHAR strFileName[100] = L"UnitData/enemy/";
		_tcscat(strFileName, wfd.cFileName);
		file = CreateFile(strFileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		tagUnitSaveInfo unitInfo;
		ZeroMemory(&unitInfo, sizeof(tagUnitSaveInfo));
		ReadFile(file, &unitInfo, sizeof(tagUnitSaveInfo), &read, NULL);

		Unit* _unit = new Unit;
		_unit->init(_map);
		_unit->loadUnitData(unitInfo);

		_vUnitsInFile.push_back(_unit);

		CloseHandle(file);

		// FindNextFile 리턴 값으로 다음값이 있을 경우 TRUE
		// 없을 경우 FALSE 값 리턴
		if (!FindNextFile(handle, &wfd))
		{
			break;
		}
	}
	// 파일 찾기 핸들 값 닫기   
	FindClose(handle);
}

void Enemy::locateUnits(void)
{
	//맵에 있는 오브젝트에 유닛을 넣자
	int tileSizeX = _map->getTileSizeX();
	int tileSizeY = _map->getTileSizeY();

	for (int i = 0; i < tileSizeY; i++)
	{
		for (int j = 0; j < tileSizeX; j++)
		{
			if (_map->getTile()[j + i * TILEY].sampleObjectSelectIdx != OBJECTSELECT_ENEMY)
				continue;

			//오브젝트의 이름을 받아서
			TCHAR* obj = _map->getTile()[j + i * TILEY].obj;
			int len = _tcslen(obj);
			if (len > 0)
			{
				for (int v = 0; v < _vUnitsInFile.size(); v++)
				{
					//파일중에 이름이 같은 유닛을 찾고
					TCHAR* name = _vUnitsInFile[v]->getStatus().name;
					if (0 == _tcscmp(obj, name))
					{
						//찾았으면 출전목록에 넣는다.
						Unit* unit = new Unit;
						unit->init(_map);
						unit->copyUnitData(_vUnitsInFile[v]);

						tagBattleState bState = unit->getBattleState();
						bState.tilePt = { j, i };
						bState.tilePtNext = bState.tilePt;
						bState.rc = RectMake(j * TILESIZE, i * TILESIZE, TILESIZE, TILESIZE);
						bState.pt = { (LONG)((bState.rc.left + bState.rc.right) * 0.5f), (LONG)((bState.rc.top + bState.rc.bottom) * 0.5f) };
						unit->setBattleState(bState);
						_vUnits.push_back(unit);
						break;
					}
				}
			}
		}
	}
}

void Enemy::deleteUnits(void)
{
	for (int i = 0; i < _vUnits.size(); i++)
	{
		SAFE_DELETE(_vUnits[i]);
	}
	_vUnits.clear();

	for (int i = 0; i < _vUnitsInFile.size(); i++)
	{
		SAFE_DELETE(_vUnitsInFile[i]);
	}
	_vUnitsInFile.clear();

}
