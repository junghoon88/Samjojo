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
	_sSmap->setAddressLinkDialog(_dialog);


	return S_OK;
}

void sceneStory::release(void)
{
	_dialog->release();
	SAFE_DELETE(_dialog);

	_sSmap->release();
	SAFE_DELETE(_sSmap);
}

void sceneStory::update(void)
{
	if (!(_dialog->getDirection() ==4))
	{
		if (_dialog->getNext() == 0)
		{
			if (_dialog->getTime() > 4.0f &&KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				_dialog->loadDialog();
				SOUNDMANAGER->play(L"Se02", 1.0f);
			}
			
			
		}
		else if (_dialog->getNext() == 2 || _dialog->getNext() == 3)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				_dialog->loadDialog();
				SOUNDMANAGER->play(L"Se02", 1.0f);
			}
		}
		else
		{
			if (_dialog->getTime() > 2.0f &&KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				_dialog->loadDialog();
				SOUNDMANAGER->play(L"Se02", 1.0f);
			}
		}
	}
	_sSmap->update();
	_dialog->update();
}


void sceneStory::render(void)
{

	_sSmap->render();
	SetBkMode(getMemDC(), TRANSPARENT);
	_dialog->render();
	if (_dialog->getNext() == 6)
	{
		
		SCENEMANAGER->changeScene(L"준비기본씬");
	}

}
