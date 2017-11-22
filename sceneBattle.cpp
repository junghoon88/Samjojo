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

	DATABASE->getSlectScenario();


	return S_OK;
}


void sceneBattle::release(void)
{
	_map->release();
}

void sceneBattle::update(void)
{
	_map->update();
}

void sceneBattle::render(void)
{
	_map->render();
}

void sceneBattle::initImage(void)
{

}

void sceneBattle::initSound(void)
{

}

