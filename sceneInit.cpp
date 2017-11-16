#include "stdafx.h"
#include "sceneInit.h"


sceneInit::sceneInit()
{
}


sceneInit::~sceneInit()
{
}

HRESULT sceneInit::init(void)
{
	initImage();
	initSound();

	return S_OK;
}


void sceneInit::release(void)
{
}

void sceneInit::update(void)
{

}

void sceneInit::render(void)
{

}

void sceneInit::initImage(void)
{
	initImageMapTool();
}

void sceneInit::initImageMapTool(void)
{
	//샘플 타일셋 셋팅
	for (int i = 0; i < SAMPLETILEY; i++)
	{
		for (int j = 0; j < SAMPLETILEX; j++)
		{
			int index = i * SAMPLETILEX + j;
			TCHAR strImgKey[100], strName[100];
			_stprintf(strImgKey, L"tile (%02d)", index + 1);
			_stprintf(strName, L"image/tiles/tile (%02d).bmp", index + 1);
			IMAGEMANAGER->addImage(strImgKey, strName, TILESIZE, TILESIZE);
		}
	}

	IMAGEMANAGER->addFrameImage(L"맵툴버튼", L"image/MapTool/button.bmp", 100, 60, 1, 2);


}



void sceneInit::initSound(void)
{

}

