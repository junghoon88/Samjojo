#include "stdafx.h"
#include "Player.h"
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

void Player::deleteUnits(void)
{
	for (int i = 0; i < _vUnits.size(); i++)
	{
		SAFE_DELETE(_vUnits[i]);
	}
	_vUnits.clear();
}
