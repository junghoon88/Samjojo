#include "stdafx.h"
#include "Player.h"
#include "Friend.h"
#include "Enemy.h"
#include "gameMap.h"
#include "infoCursor.h"

Player::Player()
{
}


Player::~Player()
{
}

HRESULT Player::init(void)
{
	return S_OK;
}

void Player::release(void)
{
}

void Player::update(void)
{
}

void Player::render(void)
{
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

void Player::deleteUnits(void)
{
	_vUnits.clear();

	for (int i = 0; i < _vUnitsInFile.size(); i++)
	{
		SAFE_DELETE(_vUnitsInFile[i]);
	}
	_vUnitsInFile.clear();
}
