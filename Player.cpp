#include "stdafx.h"
#include "Player.h"
#include "Friend.h"
#include "Enemy.h"
#include "gameMap.h"
#include "battleSceneInterface.h"

Player::Player()
{
}


Player::~Player()
{
}

HRESULT Player::init(void)
{
	_gold = 3000;
	return S_OK;
}

void Player::release(void)
{
}

void Player::update(void)
{
	for (int i = 0; i < _vUnits.size(); i++)
	{
		_vUnits[i]->update(TEAM_PLAYER);
	}

	UnitLiveCheck();
}

void Player::render(void)
{
	for (int i = 0; i < _vUnits.size(); i++)
	{
		_vUnits[i]->render();
	}
}

void Player::loadUnits(void)
{
	deleteUnits();
	//��� ���� ��ĵ test
	WIN32_FIND_DATA wfd;
	HANDLE handle = FindFirstFile(L"UnitData/player/*.dat", &wfd);

	// ã�� ������ �ִٸ�,
	while (handle != INVALID_HANDLE_VALUE)
	{
		HANDLE file;
		DWORD read;

		TCHAR strFileName[100] = L"UnitData/player/";
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

void Player::registUnitAll(void)
{
	//0. ����
	for (viUnits iter = _vUnitsInFile.begin(); iter != _vUnitsInFile.end(); ++iter)
	{
		if (0 == _tcscmp((*iter)->getStatus().name, L"����"))
		{
			registUnit((*iter));
			break;
		}
	}
	//1. ���ĵ�
	for (viUnits iter = _vUnitsInFile.begin(); iter != _vUnitsInFile.end(); ++iter)
	{
		if (0 == _tcscmp((*iter)->getStatus().name, L"���ĵ�"))
		{
			registUnit((*iter));
			break;
		}
	}


	//����� ���� �����ؾߵ�.
	//�׽�Ʈ�� �׳� ��������
	for (viUnits iter = _vUnitsInFile.begin(); iter != _vUnitsInFile.end(); ++iter)
	{
		if (0 == _tcscmp((*iter)->getStatus().name, L"����"))	continue;
		if (0 == _tcscmp((*iter)->getStatus().name, L"���ĵ�"))	continue;

		registUnit(*iter);

		if (_vUnits.size() >= ENTRANT_MAX)
			break;
	}

	


}
void Player::registUnitBasic(void) {
	//0. ����
	for (viUnits iter = _vUnitsInFile.begin(); iter != _vUnitsInFile.end(); ++iter)
	{
		if (0 == _tcscmp((*iter)->getStatus().name, L"����"))
		{
			registUnit((*iter));
			break;
		}
	}
	//1. ���ĵ�
	for (viUnits iter = _vUnitsInFile.begin(); iter != _vUnitsInFile.end(); ++iter)
	{
		if (0 == _tcscmp((*iter)->getStatus().name, L"���ĵ�"))
		{
			registUnit((*iter));
			break;
		}
	}

}


void Player::registUnit(Unit* unit)
{
	//�ִ� ���������� 7��
	if (_vUnits.size() >= ENTRANT_MAX)
		return;

	_vUnits.push_back(unit);
}

void Player::cancleUnit(int num)
{
	//����, ���ĵ��� ������
	if (num < 2)
		return;
	//7�̻��� ��ȿó��
	if (num >= ENTRANT_MAX)
		return;

	_vUnits.erase(_vUnits.begin() + num);
}



void Player::locateUnits(void)
{
	//�ʿ� �ִ� ������Ʈ�� ������ ����
	int tileSizeX = _map->getTileSizeX();
	int tileSizeY = _map->getTileSizeY();

	for (int i = 0; i < tileSizeY; i++)
	{
		for (int j = 0; j < tileSizeX; j++)
		{
			if (_map->getTile()[j + i * TILEY].sampleObjectSelectIdx != OBJECTSELECT_PLAYER)
				continue;

			//������Ʈ�� �̸��� �޾Ƽ�
			TCHAR* obj = _map->getTile()[j + i * TILEY].obj;
			int len = _tcslen(obj);
			if (len > 0)
			{
				int v = -1;
				if (0 == _tcscmp(obj, L"S1"))
				{
					v = 2;
				}
				else if (0 == _tcscmp(obj, L"S2"))
				{
					v = 3;
				}
				else if (0 == _tcscmp(obj, L"S3"))
				{
					v = 4;
				}
				else if (0 == _tcscmp(obj, L"S4"))
				{
					v = 5;
				}
				else if (0 == _tcscmp(obj, L"S5"))
				{
					v = 6;
				}
				else
				{
					for (int s = 0; s < 2; s++)
					{
						//�����߿� �̸��� ���� ������ ã�� (����, ���ĵ�)
						TCHAR* name = _vUnits[s]->getStatus().name;
						if (0 == _tcscmp(obj, name))
						{
							v = s;
							break;
						}
					}
				}

				if (v >= 0 && v < _vUnits.size())
				{
					//ã������ ��ġ������ �Է����ش�.
					tagBattleState bState = _vUnits[v]->getBattleState();
					bState.tilePt = { j, i };
					bState.tilePtNext = bState.tilePt;
					bState.rc = RectMake(j * TILESIZE, i * TILESIZE, TILESIZE, TILESIZE);
					bState.pt = { (LONG)((bState.rc.left + bState.rc.right) * 0.5f), (LONG)((bState.rc.top + bState.rc.bottom) * 0.5f) };
					_vUnits[v]->setBattleState(bState);
				}

			}
		}
	}
}

void Player::deleteUnits(void)
{
	_vUnits.clear();

	for (int i = 0; i < _vUnitsInFile.size(); i++)
	{
		SAFE_DELETE(_vUnitsInFile[i]);
	}
	_vUnitsInFile.clear();
}

Unit* Player::findUnit(TCHAR* name)
{

	return NULL;
}

void Player::UnitLiveCheck(void)
{
	viUnits iter = _vUnits.begin();
	while (iter != _vUnits.end())
	{
		if ((*iter)->getIsLive() == FALSE)
		{
			iter = _vUnits.erase(iter);
		}
		else ++iter;
	}
}

void Player::eatKong(Unit* player, Unit* opponent)
{
	if (_kongNum > 0)
	{
		_kongNum--;							// �� ���� ���̰�
		player->useItem(opponent, 0, 50);	// useItem
	}
}