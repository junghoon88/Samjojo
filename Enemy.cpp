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


	//��� ���� ��ĵ test
	WIN32_FIND_DATA wfd;
	HANDLE handle = FindFirstFile(L"UnitData/enemy/*.dat", &wfd);

	// ã�� ������ �ִٸ�,
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

		// FindNextFile ���� ������ �������� ���� ��� TRUE
		// ���� ��� FALSE �� ����
		if (!FindNextFile(handle, &wfd))
		{
			break;
		}
	}
	// ���� ã�� �ڵ� �� �ݱ�   
	FindClose(handle);
}

void Enemy::locateUnits(void)
{
	//�ʿ� �ִ� ������Ʈ�� ������ ����
	int tileSizeX = _map->getTileSizeX();
	int tileSizeY = _map->getTileSizeY();

	for (int i = 0; i < tileSizeY; i++)
	{
		for (int j = 0; j < tileSizeX; j++)
		{
			if (_map->getTile()[j + i * TILEY].sampleObjectSelectIdx != OBJECTSELECT_ENEMY)
				continue;

			//������Ʈ�� �̸��� �޾Ƽ�
			TCHAR* obj = _map->getTile()[j + i * TILEY].obj;
			int len = _tcslen(obj);
			if (len > 0)
			{
				for (int v = 0; v < _vUnitsInFile.size(); v++)
				{
					//�����߿� �̸��� ���� ������ ã��
					TCHAR* name = _vUnitsInFile[v]->getStatus().name;
					if (0 == _tcscmp(obj, name))
					{
						//ã������ ������Ͽ� �ִ´�.
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
