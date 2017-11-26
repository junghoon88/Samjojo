#include "stdafx.h"
#include "sceneStory.h"


sceneStory::sceneStory()
	: _dialog(NULL)
{
}


sceneStory::~sceneStory()
{
}

HRESULT sceneStory::init(void)
{
	DATABASE->getSlectScenario();
	

	_dialog = new scanDialog;
	_dialog->init("scripts/script 00.txt");
	
	_sSmap = new scaneStorymap;
	_sSmap->init();

	return S_OK;
}

void sceneStory::release(void)
{
}

void sceneStory::update(void)
{
	
	

	_dialog->update();
	
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE)||KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		_dialog->loadDialog();
	}
	_sSmap->update();
}


void sceneStory::render(void)
{

	_sSmap->render();
	SetBkMode(getMemDC(), TRANSPARENT);
	_dialog->render();
}
