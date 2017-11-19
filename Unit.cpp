#include "stdafx.h"
#include "Unit.h"


Unit::Unit()
{
	ZeroMemory(&_status, sizeof(tagStatus));
	_status.isLive = true;
	_status.level = 1;

	_itemW = NULL;
	_itemA = NULL;
	_itemS = NULL;

	_team = TEAM_NONE;

	//¿ÃπÃ¡ˆ
	_img = NULL;
	
	ZeroMemory(&_atkRange, sizeof(_atkRange));

}


Unit::~Unit()
{
}
