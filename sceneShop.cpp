#include "stdafx.h"
#include "sceneShop.h"


sceneShop::sceneShop()
{
}


sceneShop::~sceneShop()
{
}

HRESULT sceneShop::init(void)
{
	DATABASE->getSlectScenario();


	return S_OK;
}

void sceneShop::release(void)
{
}

void sceneShop::update(void)
{
}

void sceneShop::render(void)
{
}
