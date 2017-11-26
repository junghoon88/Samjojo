#include "stdafx.h"
#include "Friend.h"
#include "Player.h"
#include "Enemy.h"
#include "gameMap.h"


Friend::Friend()
{
}


Friend::~Friend()
{
}

HRESULT Friend::init(void)
{
	return S_OK;
}

void Friend::release(void)
{
}

void Friend::update(void)
{
}

void Friend::render(void)
{
}

void Friend::loadUnits(void)
{
	deleteUnits();

	//�ó����� ��ȣ�� �ް�, �ش� �ó������� �ʿ��� ���ָ� �ε��ϵ��� �ؾ���!
	int scenario = DATABASE->getSlectScenario();


	//��� ���� ��ĵ test
	WIN32_FIND_DATA wfd;
	HANDLE handle = FindFirstFile(L"UnitData/player/*.dat", &wfd);

	// ã�� ������ �ִٸ�,
	while (handle != INVALID_HANDLE_VALUE)
	{
		HANDLE file;
		DWORD read;

		file = CreateFile(wfd.cFileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		Unit* _unit = new Unit;
		_unit->init();
		ReadFile(file, _unit, sizeof(Unit), &read, NULL);

		_vUnits.push_back(_unit);

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

void Friend::deleteUnits(void)
{
	for (int i = 0; i < _vUnits.size(); i++)
	{
		SAFE_DELETE(_vUnits[i]);
	}
	_vUnits.clear();
}
