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


	return S_OK;
}


void sceneBattle::release(void)
{
}

void sceneBattle::update(void)
{
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

