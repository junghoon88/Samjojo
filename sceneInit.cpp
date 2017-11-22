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
	initImageSlect();
	initImageMapTool();
	initImageUnitEditor();
}

void sceneInit::initImageSlect(void)
{
	TCHAR strKey[100], strName[100];
	for (int i = 1; i <= 36; i++)
	{
		_stprintf(strKey, L"logo %02d", i);
		_stprintf(strName, L"image/logo/Logo %05d.bmp", i);
		IMAGEMANAGER->addImage(strKey, strName, 640, 400);
	}

	IMAGEMANAGER->addFrameImage(L"SELECT-���ù�ư", L"image/button.bmp", 100, 60, 1, 2);
}

void sceneInit::initImageMapTool(void)
{
	//���� Ÿ�ϼ� ����
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

	IMAGEMANAGER->addFrameImage(L"������ư", L"image/button.bmp", 100, 60, 1, 2);
	IMAGEMANAGER->addFrameImage(L"������ư2", L"image/button2.bmp", 50, 60, 1, 2);
	IMAGEMANAGER->addFrameImage(L"�����׽�Ʈ", L"image/combat_unit_test1.bmp", 48, 49, 1, 1);
	IMAGEMANAGER->addFrameImage(L"�����׽�Ʈ", L"image/normal_unit_test1.bmp", 48, 49, 1, 1);
	IMAGEMANAGER->addFrameImage(L"�����׽�Ʈ", L"image/combat_unit_test2.bmp", 48, 49, 1, 1);
	IMAGEMANAGER->addFrameImage(L"�����׽�Ʈ", L"image/normal_unit_test2.bmp", 48, 49, 1, 1);


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
	
	memset(strKey, NULL, _tcslen(strKey));
	memset(strName, NULL, _tcslen(strName));
	
	//normal
	for (int i = 0; i <= NORMAL_IMAGE_MAX; i++)
	{
		_stprintf(strKey, L"���� %05d", i);
		_stprintf(strName, L"image/normal_unit_test %05d.bmp", i);

		IMAGEMANAGER->addFrameImage(strKey, strName, 48, 49, 1, 1);
	}

	memset(strKey, NULL, _tcslen(strKey));
	memset(strName, NULL, _tcslen(strName));

	//combat
	for (int i = 0; i <= COMBAT_IMAGE_MAX; i++)
	{
		_stprintf(strKey, L"���� %05d", i);
		_stprintf(strName, L"image/combat_unit_test %05d.bmp", i);

		IMAGEMANAGER->addFrameImage(strKey, strName, 48, 49, 1, 1);
	}
}



void sceneInit::initSound(void)
{

}

