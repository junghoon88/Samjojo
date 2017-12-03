#include "stdafx.h"
#include "sceneResult.h"


sceneResult::sceneResult()
{
}


sceneResult::~sceneResult()
{

}

HRESULT sceneResult::init(void)
{
	if (DATABASE->getBattleVictory() == TRUE)
	{
		_background = IMAGEMANAGER->findImage(L"logo 12");
	}
	else
	{
		_background = IMAGEMANAGER->findImage(L"logo 05");
	}


		
	return S_OK;
}

void sceneResult::release(void)
{

}

void sceneResult::update(void) 
{

}

void sceneResult::render(void) 
{
	if(_background) _background->render(getMemDC(), 0, 0);
}

