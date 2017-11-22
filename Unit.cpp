#include "stdafx.h"
#include "Unit.h"


Unit::Unit()
{
}


Unit::~Unit()
{
}

void Unit::init(void)
{
	ZeroMemory(&_status, sizeof(tagStatus));
	_status.isLive = true;
	_status.enterScenario = 1;
	_status.level = 1;

	_itemW = NULL;
	_itemA = NULL;
	_itemS = NULL;

	_team = TEAM_NONE;

	//¿ÃπÃ¡ˆ
	_imgFace = NULL;
	_imgStory = NULL;
	_imgBattle = NULL;

	ZeroMemory(&_atkRange, sizeof(_atkRange));

}
