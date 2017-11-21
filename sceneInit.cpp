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
	initImageUnitEditor();
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

	IMAGEMANAGER->addFrameImage(L"맵툴버튼", L"image/button.bmp", 100, 60, 1, 2);


}

void sceneInit::initImageUnitEditor(void)
{
	TCHAR strKey[100], strName[100];
	//face
	for (int i = 0; i <= FACE_MAX; i++)
	{
		_stprintf(strKey,  L"face %05d", i);
		_stprintf(strName, L"image/face/face %05d.bmp", i);
		IMAGEMANAGER->addImage(strKey, strName, 120, 120);
	}
}



void sceneInit::initSound(void)
{

}

