#include "stdafx.h"
#include "sceneStory.h"


sceneStory::sceneStory()
{
}


sceneStory::~sceneStory()
{
}

HRESULT sceneStory::init(void)
{
	DATABASE->getSlectScenario();


	return S_OK;
}

void sceneStory::release(void)
{
}

void sceneStory::update(void)
{
}

void sceneStory::render(void)
{
}
