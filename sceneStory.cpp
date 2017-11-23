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
	_dialog->loadDialog();

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
	_dialog->render();
}
