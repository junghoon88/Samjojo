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

	IMAGEMANAGER->addFrameImage(L"SELECT-선택버튼", L"image/button.bmp", 100, 60, 1, 2);
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
			_stprintf(strName, L"image/tiles/terrain/tile (%02d).bmp", index + 1);
			IMAGEMANAGER->addImage(strImgKey, strName, TILESIZE, TILESIZE);
		}
	}

	//오브젝트 타일 셋팅
	//아군 셋팅
	for (int i = 0; i < SAMPLETILEY; i++)
	{
		for (int j = 0; j < SAMPLETILEX; j++)
		{
			int index = i * SAMPLETILEX + j;
			TCHAR strImgKey[100], strName[100];
			_stprintf(strImgKey, L"아군 (%02d)", index + 1);
			_stprintf(strName, L"image/tiles/aily/아군 (%02d).bmp", index + 1);
			IMAGEMANAGER->addImage(strImgKey, strName, TILESIZE, TILESIZE, false, RGB(255, 0, 255), true);
		}
	}

	//적군 셋팅
	for (int i = 0; i < SAMPLETILEY; i++)
	{
		for (int j = 0; j < SAMPLETILEX; j++)
		{
			int index = i * SAMPLETILEX + j;
			TCHAR strImgKey[100], strName[100];
			_stprintf(strImgKey, L"적군 (%02d)", index + 1);
			_stprintf(strName, L"image/tiles/enemy/적군 (%02d).bmp", index + 1);
			IMAGEMANAGER->addImage(strImgKey, strName, TILESIZE, TILESIZE, false, RGB(255, 0, 255), true);
		}
	}

	//플레이어 셋팅
	for (int i = 0; i < SAMPLETILEY; i++)
	{
		for (int j = 0; j < SAMPLETILEX; j++)
		{
			int index = i * SAMPLETILEX + j;
			TCHAR strImgKey[100], strName[100];
			_stprintf(strImgKey, L"플레이어 (%02d)", index + 1);
			_stprintf(strName, L"image/tiles/player/플레이어 (%02d).bmp", index + 1);
			IMAGEMANAGER->addImage(strImgKey, strName, TILESIZE, TILESIZE, false, RGB(255, 0, 255), true);
		}
	}

	IMAGEMANAGER->addFrameImage(L"맵툴버튼", L"image/button.bmp", 100, 60, 1, 2);
	IMAGEMANAGER->addFrameImage(L"맵툴버튼2", L"image/button2.bmp", 50, 60, 1, 2);

	//이것은 뭐시다냐
	IMAGEMANAGER->addFrameImage(L"평조테스트", L"image/combat_unit_test1.bmp", 48, 49, 1, 1);
	IMAGEMANAGER->addFrameImage(L"전조테스트", L"image/normal_unit_test1.bmp", 48, 49, 1, 1);
	IMAGEMANAGER->addFrameImage(L"평조테스트", L"image/combat_unit_test2.bmp", 48, 49, 1, 1);
	IMAGEMANAGER->addFrameImage(L"전조테스트", L"image/normal_unit_test2.bmp", 48, 49, 1, 1);

	//아무것도 로드 안했을 때의 이미지
	IMAGEMANAGER->addImage(L"빈공간", L"image/Map/빈공간.bmp", 1920, 1920, true, RGB(255, 0, 255), true);

	//원본맵 이미지 추가하기
	IMAGEMANAGER->addImage(L"M000", L"image/Map/M000.bmp", 960, 960, false, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage(L"M001", L"image/Map/M001.bmp", 960, 960, false, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage(L"M002", L"image/Map/M002.bmp", 960, 960, false, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage(L"M003", L"image/Map/M003.bmp", 1344, 960, false, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage(L"M004", L"image/Map/M004.bmp", 960, 960, false, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage(L"M005", L"image/Map/M005.bmp", 1152, 1152, false, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage(L"M006", L"image/Map/M006.bmp", 1344, 1152, false, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage(L"M007", L"image/Map/M007.bmp", 1536, 1344, false, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage(L"M008", L"image/Map/M008.bmp", 1152, 1152, false, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage(L"M009", L"image/Map/M009.bmp", 960, 960, false, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage(L"M010", L"image/Map/M010.bmp", 1152, 960, false, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage(L"M011", L"image/Map/M011.bmp", 1152, 1152, false, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage(L"M012", L"image/Map/M012.bmp", 1344, 960, false, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage(L"M013", L"image/Map/M013.bmp", 960, 1344, false, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage(L"M014", L"image/Map/M014.bmp", 1344, 1344, false, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage(L"M015", L"image/Map/M015.bmp", 1536, 960, false, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage(L"M016", L"image/Map/M016.bmp", 960, 960, false, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage(L"M017", L"image/Map/M017.bmp", 1152, 1152, false, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage(L"M018", L"image/Map/M018.bmp", 1536, 1536, false, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage(L"M019", L"image/Map/M019.bmp", 960, 1920, false, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage(L"M020", L"image/Map/M020.bmp", 1152, 1344, false, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage(L"M021", L"image/Map/M021.bmp", 960, 1920, false, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage(L"M022", L"image/Map/M022.bmp", 1536, 960, false, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage(L"M023", L"image/Map/M023.bmp", 960, 960, false, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage(L"M024", L"image/Map/M024.bmp", 1152, 1152, false, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage(L"M025", L"image/Map/M025.bmp", 960, 1536, false, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage(L"M026", L"image/Map/M026.bmp", 1536, 1152, false, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage(L"M027", L"image/Map/M027.bmp", 1536, 1920, false, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage(L"M028", L"image/Map/M028.bmp", 1536, 1920, false, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage(L"M029", L"image/Map/M029.bmp", 1728, 960, false, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage(L"M030", L"image/Map/M030.bmp", 960, 960, false, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage(L"M031", L"image/Map/M031.bmp", 960, 1536, false, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage(L"M032", L"image/Map/M032.bmp", 1344, 960, false, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage(L"M033", L"image/Map/M033.bmp", 960, 1536, false, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage(L"M034", L"image/Map/M034.bmp", 1152, 1920, false, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage(L"M035", L"image/Map/M035.bmp", 1344, 1728, false, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage(L"M036", L"image/Map/M036.bmp", 1344, 1344, false, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage(L"M037", L"image/Map/M037.bmp", 960, 1152, false, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage(L"M038", L"image/Map/M038.bmp", 1152, 1536, false, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage(L"M039", L"image/Map/M039.bmp", 1152, 1536, false, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage(L"M040", L"image/Map/M040.bmp", 1728, 1536, false, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage(L"M041", L"image/Map/M041.bmp", 1920, 1344, false, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage(L"M042", L"image/Map/M042.bmp", 1152, 1152, false, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage(L"M043", L"image/Map/M043.bmp", 1536, 1920, false, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage(L"M044", L"image/Map/M044.bmp", 1152, 1920, false, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage(L"M045", L"image/Map/M045.bmp", 1920, 1152, false, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage(L"M046", L"image/Map/M046.bmp", 1344, 1728, false, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage(L"M047", L"image/Map/M047.bmp", 1152, 1152, false, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage(L"M048", L"image/Map/M048.bmp", 960, 1152, false, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage(L"M049", L"image/Map/M049.bmp", 1536, 1920, false, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage(L"M050", L"image/Map/M050.bmp", 1152, 1920, false, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage(L"M051", L"image/Map/M051.bmp", 1920, 1152, false, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage(L"M052", L"image/Map/M052.bmp", 960, 1152, false, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage(L"M053", L"image/Map/M053.bmp", 1152, 1152, false, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage(L"M054", L"image/Map/M054.bmp", 1920, 1536, false, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage(L"M055", L"image/Map/M055.bmp", 1152, 1728, false, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage(L"M056", L"image/Map/M056.bmp", 1920, 1920, false, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage(L"M057", L"image/Map/M057.bmp", 1920, 1920, false, RGB(255, 0, 255), true);
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
		_stprintf(strKey, L"평조 %05d", i);
		_stprintf(strName, L"image/normal_unit_test %05d.bmp", i);

		IMAGEMANAGER->addFrameImage(strKey, strName, 48, 49, 1, 1);
	}

	memset(strKey, NULL, _tcslen(strKey));
	memset(strName, NULL, _tcslen(strName));

	//combat
	for (int i = 0; i <= COMBAT_IMAGE_MAX; i++)
	{
		_stprintf(strKey, L"전조 %05d", i);
		_stprintf(strName, L"image/combat_unit_test %05d.bmp", i);

		IMAGEMANAGER->addFrameImage(strKey, strName, 48, 49, 1, 1);
	}
}



void sceneInit::initSound(void)
{

}

