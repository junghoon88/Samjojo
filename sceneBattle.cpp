#include "stdafx.h"
#include "sceneBattle.h"


sceneBattle::sceneBattle()
	: _map(NULL)
{


}


sceneBattle::~sceneBattle()
{

}

HRESULT sceneBattle::init(void)
{
	DATABASE->getSlectScenario();

	_cursor = new infoCursor;
	_cursor->init();

	linkClass();

	Phase = playerPhase;
	return S_OK;
}


void sceneBattle::release(void)
{
	_cursor->release();
	SAFE_DELETE(_cursor);
}

void sceneBattle::update(void)
{
	

	_map->update(); 
	if(Phase == playerPhase)_cursor->update();
}

void sceneBattle::render(void)
{
	_map->render();

	_player->render();
	_friend->render();
	_enemy->render();

	_cursor->render();
}

void sceneBattle::initImage(void)
{

}

void sceneBattle::initSound(void)
{

}


void sceneBattle::phaseControl(void)
{

}


void sceneBattle::linkClass(void)
{
	_cursor->setLinkEnemy(_enemy);
	_cursor->setLinkFriend(_friend);
	_cursor->setLinkPlyer(_player);
	_cursor->setLinkAdressMap(_map);

	_player->setLinkCursor(_cursor);
	_enemy->setLinkCursor(_cursor);
	_friend->setLinkCursor(_cursor);
	_map->setLinkAdressCursor(_cursor);
}