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
	_cursor->render();

	_player->render();
	_friend->render();
	_enemy->render();
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
