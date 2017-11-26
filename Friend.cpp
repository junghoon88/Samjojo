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

	//시나리오 번호를 받고, 해당 시나리오에 필요한 유닛만 로딩하도록 해야함!
	int scenario = DATABASE->getSlectScenario();


	//모든 파일 스캔 test
	WIN32_FIND_DATA wfd;
	HANDLE handle = FindFirstFile(L"UnitData/player/*.dat", &wfd);

	// 찾는 파일이 있다면,
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

void Friend::deleteUnits(void)
{
	for (int i = 0; i < _vUnits.size(); i++)
	{
		SAFE_DELETE(_vUnits[i]);
	}
	_vUnits.clear();
}
