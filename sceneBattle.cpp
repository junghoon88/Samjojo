#include "stdafx.h"
#include "sceneBattle.h"


sceneBattle::sceneBattle()
{


}


sceneBattle::~sceneBattle()
{

}

HRESULT sceneBattle::init(void)
{
	_map = new gameMap;
	_map->init();

	_cursor = new infoCursor;
	_cursor->init();


	DATABASE->getSlectScenario();

	Phase = playerPhase;
	return S_OK;
}


void sceneBattle::release(void)
{
	_map->release();
	_cursor->release();
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
