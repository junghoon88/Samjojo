#include "stdafx.h"
#include "sceneInit.h"


sceneInit::sceneInit()
	: _loading(NULL)
{
}


sceneInit::~sceneInit()
{
}

HRESULT sceneInit::init(void)
{
	_loading = new loading;
	_loading->init();


	initImage();
	initSound();

	return S_OK;
}


void sceneInit::release(void)
{
	_loading->release();
	SAFE_DELETE(_loading);
}

void sceneInit::update(void)
{
	if (_loading->loadingImageDone())
	{
		_loading->update();
		SCENEMANAGER->changeScene(L"선택씬");
	}
	else
	{
		_loading->update();
	}
}

void sceneInit::render(void)
{
	_loading->render();
}

void sceneInit::initImage(void)
{
	initImageSlect();
	initImageMapTool();
	initImageUnitEditor();

	initImageStory();

	initImageUnits();

}

void sceneInit::initImageSlect(void)
{
	TCHAR strKey[100], strName[100];
	for (int i = 1; i <= 36; i++)
	{
		_stprintf(strKey, L"logo %02d", i);
		_stprintf(strName, L"image/logo/Logo %05d.bmp", i);
		_loading->loadImage(strKey, strName, 640, 400);
	}

	_loading->loadFrameImage(L"SELECT-선택버튼", L"image/button.bmp", 100, 60, 1, 2);
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
			_loading->loadImage(strImgKey, strName, TILESIZE, TILESIZE);
		}
	}

	//오브젝트 타일 셋팅
	_loading->loadImage(L"아군", L"image/tiles/object/아군.bmp", TILESIZE, TILESIZE, false, RGB(255, 0, 255), true);
	_loading->loadImage(L"적군", L"image/tiles/object/적군.bmp", TILESIZE, TILESIZE, false, RGB(255, 0, 255), true);
	_loading->loadImage(L"플레이어", L"image/tiles/object/플레이어.bmp", TILESIZE, TILESIZE, false, RGB(255, 0, 255), true);

	//선택타일 체크 창
	_loading->loadImage(L"타일선택", L"image/tileSelect.bmp", TILESIZE, TILESIZE, true, RGB(255, 0, 255), false);


	IMAGEMANAGER->addFrameImage(L"맵툴버튼", L"image/button.bmp", 100, 60, 1, 2);
	IMAGEMANAGER->addFrameImage(L"맵툴버튼2", L"image/button.bmp", 50, 60, 1, 2);

	//아군 셋팅
	//for (int i = 0; i < SAMPLETILEY; i++)
	//{
	//	for (int j = 0; j < SAMPLETILEX; j++)
	//	{
	//		int index = i * SAMPLETILEX + j;
	//		TCHAR strImgKey[100], strName[100];
	//		_stprintf(strImgKey, L"아군 (%02d)", index + 1);
	//		_stprintf(strName, L"image/tiles/aily/아군 (%02d).bmp", index + 1);
	//		_loading->loadImage(strImgKey, strName, TILESIZE, TILESIZE, false, RGB(255, 0, 255), true);
	//	}
	//}
	//
	////적군 셋팅
	//for (int i = 0; i < SAMPLETILEY; i++)
	//{
	//	for (int j = 0; j < SAMPLETILEX; j++)
	//	{
	//		int index = i * SAMPLETILEX + j;
	//		TCHAR strImgKey[100], strName[100];
	//		_stprintf(strImgKey, L"적군 (%02d)", index + 1);
	//		_stprintf(strName, L"image/tiles/enemy/적군 (%02d).bmp", index + 1);
	//		_loading->loadImage(strImgKey, strName, TILESIZE, TILESIZE, false, RGB(255, 0, 255), true);
	//	}
	//}
	//
	////플레이어 셋팅
	//for (int i = 0; i < SAMPLETILEY; i++)
	//{
	//	for (int j = 0; j < SAMPLETILEX; j++)
	//	{
	//		int index = i * SAMPLETILEX + j;
	//		TCHAR strImgKey[100], strName[100];
	//		_stprintf(strImgKey, L"플레이어 (%02d)", index + 1);
	//		_stprintf(strName, L"image/tiles/player/플레이어 (%02d).bmp", index + 1);
	//		_loading->loadImage(strImgKey, strName, TILESIZE, TILESIZE, false, RGB(255, 0, 255), true);
	//	}
	//}

	//버튼 이미지
	_loading->loadFrameImage(L"맵툴버튼", L"image/button.bmp", 100, 60, 1, 2);
	_loading->loadFrameImage(L"맵툴버튼2", L"image/button.bmp", 50, 60, 1, 2);

	//이것은 뭐시다냐
	_loading->loadFrameImage(L"평조테스트", L"image/combat_unit_test1.bmp", 48, 49, 1, 1);
	_loading->loadFrameImage(L"전조테스트", L"image/normal_unit_test1.bmp", 48, 49, 1, 1);
	_loading->loadFrameImage(L"평조테스트", L"image/combat_unit_test2.bmp", 48, 49, 1, 1);
	_loading->loadFrameImage(L"전조테스트", L"image/normal_unit_test2.bmp", 48, 49, 1, 1);

	//아무것도 로드 안했을 때의 이미지
	_loading->loadImage(L"빈공간", L"image/Map/빈공간.bmp", 1920, 1920, true, RGB(255, 0, 255), true);

	//원본맵 이미지 추가하기
	_loading->loadImage(L"M000", L"image/Map/M000.bmp", 960, 960, false, RGB(255, 0, 255), true);
	_loading->loadImage(L"M001", L"image/Map/M001.bmp", 960, 960, false, RGB(255, 0, 255), true);
	_loading->loadImage(L"M002", L"image/Map/M002.bmp", 960, 960, false, RGB(255, 0, 255), true);
	_loading->loadImage(L"M003", L"image/Map/M003.bmp", 1344, 960, false, RGB(255, 0, 255), true);
	_loading->loadImage(L"M004", L"image/Map/M004.bmp", 960, 960, false, RGB(255, 0, 255), true);
	_loading->loadImage(L"M005", L"image/Map/M005.bmp", 1152, 1152, false, RGB(255, 0, 255), true);
	_loading->loadImage(L"M006", L"image/Map/M006.bmp", 1344, 1152, false, RGB(255, 0, 255), true);
	_loading->loadImage(L"M007", L"image/Map/M007.bmp", 1536, 1344, false, RGB(255, 0, 255), true);
	_loading->loadImage(L"M008", L"image/Map/M008.bmp", 1152, 1152, false, RGB(255, 0, 255), true);
	_loading->loadImage(L"M009", L"image/Map/M009.bmp", 960, 960, false, RGB(255, 0, 255), true);
	_loading->loadImage(L"M010", L"image/Map/M010.bmp", 1152, 960, false, RGB(255, 0, 255), true);
	_loading->loadImage(L"M011", L"image/Map/M011.bmp", 1152, 1152, false, RGB(255, 0, 255), true);
	_loading->loadImage(L"M012", L"image/Map/M012.bmp", 1344, 960, false, RGB(255, 0, 255), true);
	_loading->loadImage(L"M013", L"image/Map/M013.bmp", 960, 1344, false, RGB(255, 0, 255), true);
	_loading->loadImage(L"M014", L"image/Map/M014.bmp", 1344, 1344, false, RGB(255, 0, 255), true);
	_loading->loadImage(L"M015", L"image/Map/M015.bmp", 1536, 960, false, RGB(255, 0, 255), true);
	_loading->loadImage(L"M016", L"image/Map/M016.bmp", 960, 960, false, RGB(255, 0, 255), true);
	_loading->loadImage(L"M017", L"image/Map/M017.bmp", 1152, 1152, false, RGB(255, 0, 255), true);
	_loading->loadImage(L"M018", L"image/Map/M018.bmp", 1536, 1536, false, RGB(255, 0, 255), true);
	_loading->loadImage(L"M019", L"image/Map/M019.bmp", 960, 1920, false, RGB(255, 0, 255), true);
	_loading->loadImage(L"M020", L"image/Map/M020.bmp", 1152, 1344, false, RGB(255, 0, 255), true);
	_loading->loadImage(L"M021", L"image/Map/M021.bmp", 960, 1920, false, RGB(255, 0, 255), true);
	_loading->loadImage(L"M022", L"image/Map/M022.bmp", 1536, 960, false, RGB(255, 0, 255), true);
	_loading->loadImage(L"M023", L"image/Map/M023.bmp", 960, 960, false, RGB(255, 0, 255), true);
	_loading->loadImage(L"M024", L"image/Map/M024.bmp", 1152, 1152, false, RGB(255, 0, 255), true);
	_loading->loadImage(L"M025", L"image/Map/M025.bmp", 960, 1536, false, RGB(255, 0, 255), true);
	_loading->loadImage(L"M026", L"image/Map/M026.bmp", 1536, 1152, false, RGB(255, 0, 255), true);
	_loading->loadImage(L"M027", L"image/Map/M027.bmp", 1536, 1920, false, RGB(255, 0, 255), true);
	_loading->loadImage(L"M028", L"image/Map/M028.bmp", 1536, 1920, false, RGB(255, 0, 255), true);
	_loading->loadImage(L"M029", L"image/Map/M029.bmp", 1728, 960, false, RGB(255, 0, 255), true);
	_loading->loadImage(L"M030", L"image/Map/M030.bmp", 960, 960, false, RGB(255, 0, 255), true);
	_loading->loadImage(L"M031", L"image/Map/M031.bmp", 960, 1536, false, RGB(255, 0, 255), true);
	_loading->loadImage(L"M032", L"image/Map/M032.bmp", 1344, 960, false, RGB(255, 0, 255), true);
	_loading->loadImage(L"M033", L"image/Map/M033.bmp", 960, 1536, false, RGB(255, 0, 255), true);
	_loading->loadImage(L"M034", L"image/Map/M034.bmp", 1152, 1920, false, RGB(255, 0, 255), true);
	_loading->loadImage(L"M035", L"image/Map/M035.bmp", 1344, 1728, false, RGB(255, 0, 255), true);
	_loading->loadImage(L"M036", L"image/Map/M036.bmp", 1344, 1344, false, RGB(255, 0, 255), true);
	_loading->loadImage(L"M037", L"image/Map/M037.bmp", 960, 1152, false, RGB(255, 0, 255), true);
	_loading->loadImage(L"M038", L"image/Map/M038.bmp", 1152, 1536, false, RGB(255, 0, 255), true);
	_loading->loadImage(L"M039", L"image/Map/M039.bmp", 1152, 1536, false, RGB(255, 0, 255), true);
	_loading->loadImage(L"M040", L"image/Map/M040.bmp", 1728, 1536, false, RGB(255, 0, 255), true);
	_loading->loadImage(L"M041", L"image/Map/M041.bmp", 1920, 1344, false, RGB(255, 0, 255), true);
	_loading->loadImage(L"M042", L"image/Map/M042.bmp", 1152, 1152, false, RGB(255, 0, 255), true);
	_loading->loadImage(L"M043", L"image/Map/M043.bmp", 1536, 1920, false, RGB(255, 0, 255), true);
	_loading->loadImage(L"M044", L"image/Map/M044.bmp", 1152, 1920, false, RGB(255, 0, 255), true);
	_loading->loadImage(L"M045", L"image/Map/M045.bmp", 1920, 1152, false, RGB(255, 0, 255), true);
	_loading->loadImage(L"M046", L"image/Map/M046.bmp", 1344, 1728, false, RGB(255, 0, 255), true);
	_loading->loadImage(L"M047", L"image/Map/M047.bmp", 1152, 1152, false, RGB(255, 0, 255), true);
	_loading->loadImage(L"M048", L"image/Map/M048.bmp", 960, 1152, false, RGB(255, 0, 255), true);
	_loading->loadImage(L"M049", L"image/Map/M049.bmp", 1536, 1920, false, RGB(255, 0, 255), true);
	_loading->loadImage(L"M050", L"image/Map/M050.bmp", 1152, 1920, false, RGB(255, 0, 255), true);
	_loading->loadImage(L"M051", L"image/Map/M051.bmp", 1920, 1152, false, RGB(255, 0, 255), true);
	_loading->loadImage(L"M052", L"image/Map/M052.bmp", 960, 1152, false, RGB(255, 0, 255), true);
	_loading->loadImage(L"M053", L"image/Map/M053.bmp", 1152, 1152, false, RGB(255, 0, 255), true);
	_loading->loadImage(L"M054", L"image/Map/M054.bmp", 1920, 1536, false, RGB(255, 0, 255), true);
	_loading->loadImage(L"M055", L"image/Map/M055.bmp", 1152, 1728, false, RGB(255, 0, 255), true);
	_loading->loadImage(L"M056", L"image/Map/M056.bmp", 1920, 1920, false, RGB(255, 0, 255), true);
	_loading->loadImage(L"M057", L"image/Map/M057.bmp", 1920, 1920, false, RGB(255, 0, 255), true);
}

void sceneInit::initImageUnitEditor(void)
{
	TCHAR strKey[100], strName[100];
	//face
	for (int i = 0; i <= FACE_MAX; i++)
	{
		_stprintf(strKey,  L"face %05d", i);
		_stprintf(strName, L"image/face/face %05d.bmp", i);
		_loading->loadImage(strKey, strName, 120, 120);
	}
	
	memset(strKey, NULL, _tcslen(strKey));
	memset(strName, NULL, _tcslen(strName));
	
	//normal
	for (int i = 0; i <= NORMAL_IMAGE_MAX; i++)
	{
		_stprintf(strKey, L"평조 %05d", i);
		_stprintf(strName, L"image/normal_unit_test %05d.bmp", i);

		_loading->loadFrameImage(strKey, strName, 48, 49, 1, 1);
	}

	memset(strKey, NULL, _tcslen(strKey));
	memset(strName, NULL, _tcslen(strName));

	//combat
	for (int i = 0; i <= COMBAT_IMAGE_MAX; i++)
	{
		_stprintf(strKey, L"전조 %05d", i);
		_stprintf(strName, L"image/combat_unit_test %05d.bmp", i);

		_loading->loadFrameImage(strKey, strName, 48, 49, 1, 1);
	}
}

void sceneInit::initImageUnits(void)
{
	TCHAR strKey[100], strName[100];
	int unitNum = 0;
	//조조
	{
		TCHAR strTemp[100] = L"조조.bmp";

		_stprintf(strKey, L"unit%d-atk", unitNum);
		_stprintf(strName, L"image/unitImage/atk/");
		_tcscat(strName, strTemp);
		_loading->loadFrameImage(strKey, strName, UNITSIZE_ATKX, UNITSIZE_ATKY, UNITFRAME_ATKX, UNITFRAME_ATKY);

		_stprintf(strKey, L"unit%d-idle", unitNum);
		_stprintf(strName, L"image/unitImage/idle/");
		_tcscat(strName, strTemp);
		_loading->loadFrameImage(strKey, strName, UNITSIZE_IDLEX, UNITSIZE_IDLEY, UNITFRAME_IDLEX, UNITFRAME_IDLEY);

		_stprintf(strKey, L"unit%d-spc", unitNum);
		_stprintf(strName, L"image/unitImage/spc/");
		_tcscat(strName, strTemp);
		_loading->loadFrameImage(strKey, strName, UNITSIZE_SPCX, UNITSIZE_SPCY, UNITFRAME_SPCX, UNITFRAME_SPCY);

		unitNum++;
	}

	//하후돈
	{
		TCHAR strTemp[100] = L"하후돈.bmp";

		_stprintf(strKey, L"unit%d-atk", unitNum);
		_stprintf(strName, L"image/unitImage/atk/");
		_tcscat(strName, strTemp);
		_loading->loadFrameImage(strKey, strName, UNITSIZE_ATKX, UNITSIZE_ATKY, UNITFRAME_ATKX, UNITFRAME_ATKY);

		_stprintf(strKey, L"unit%d-idle", unitNum);
		_stprintf(strName, L"image/unitImage/idle/");
		_tcscat(strName, strTemp);
		_loading->loadFrameImage(strKey, strName, UNITSIZE_IDLEX, UNITSIZE_IDLEY, UNITFRAME_IDLEX, UNITFRAME_IDLEY);

		_stprintf(strKey, L"unit%d-spc", unitNum);
		_stprintf(strName, L"image/unitImage/spc/");
		_tcscat(strName, strTemp);
		_loading->loadFrameImage(strKey, strName, UNITSIZE_SPCX, UNITSIZE_SPCY, UNITFRAME_SPCX, UNITFRAME_SPCY);

		unitNum++;
	}

	//여포
	{
		TCHAR strTemp[100] = L"여포.bmp";

		_stprintf(strKey, L"unit%d-atk", unitNum);
		_stprintf(strName, L"image/unitImage/atk/");
		_tcscat(strName, strTemp);
		_loading->loadFrameImage(strKey, strName, UNITSIZE_ATKX, UNITSIZE_ATKY, UNITFRAME_ATKX, UNITFRAME_ATKY);

		_stprintf(strKey, L"unit%d-idle", unitNum);
		_stprintf(strName, L"image/unitImage/idle/");
		_tcscat(strName, strTemp);
		_loading->loadFrameImage(strKey, strName, UNITSIZE_IDLEX, UNITSIZE_IDLEY, UNITFRAME_IDLEX, UNITFRAME_IDLEY);

		_stprintf(strKey, L"unit%d-spc", unitNum);
		_stprintf(strName, L"image/unitImage/spc/");
		_tcscat(strName, strTemp);
		_loading->loadFrameImage(strKey, strName, UNITSIZE_SPCX, UNITSIZE_SPCY, UNITFRAME_SPCX, UNITFRAME_SPCY);

		unitNum++;
	}

	//보병
	for(int i = 0; i < TEAM_MAX; i++)
	{
		TCHAR strTemp[100] = L"";
		_stprintf(strTemp, L"보병_%d.bmp", i);

		_stprintf(strKey, L"unit%d-%d-atk", unitNum, i);
		_stprintf(strName, L"image/unitImage/atk/");
		_tcscat(strName, strTemp);
		_loading->loadFrameImage(strKey, strName, UNITSIZE_ATKX, UNITSIZE_ATKY, UNITFRAME_ATKX, UNITFRAME_ATKY);

		_stprintf(strKey, L"unit%d-%d-idle", unitNum, i);
		_stprintf(strName, L"image/unitImage/idle/");
		_tcscat(strName, strTemp);
		_loading->loadFrameImage(strKey, strName, UNITSIZE_IDLEX, UNITSIZE_IDLEY, UNITFRAME_IDLEX, UNITFRAME_IDLEY);

		_stprintf(strKey, L"unit%d-%d-spc", unitNum, i);
		_stprintf(strName, L"image/unitImage/spc/");
		_tcscat(strName, strTemp);
		_loading->loadFrameImage(strKey, strName, UNITSIZE_SPCX, UNITSIZE_SPCY, UNITFRAME_SPCX, UNITFRAME_SPCY);

		unitNum++;
	}

	//기병
	for (int i = 0; i < TEAM_MAX; i++)
	{
		TCHAR strTemp[100] = L"";
		_stprintf(strTemp, L"기병_%d.bmp", i);

		_stprintf(strKey, L"unit%d-%d-atk", unitNum, i);
		_stprintf(strName, L"image/unitImage/atk/");
		_tcscat(strName, strTemp);
		_loading->loadFrameImage(strKey, strName, UNITSIZE_ATKX, UNITSIZE_ATKY, UNITFRAME_ATKX, UNITFRAME_ATKY);

		_stprintf(strKey, L"unit%d-%d-idle", unitNum, i);
		_stprintf(strName, L"image/unitImage/idle/");
		_tcscat(strName, strTemp);
		_loading->loadFrameImage(strKey, strName, UNITSIZE_IDLEX, UNITSIZE_IDLEY, UNITFRAME_IDLEX, UNITFRAME_IDLEY);

		_stprintf(strKey, L"unit%d-%d-spc", unitNum, i);
		_stprintf(strName, L"image/unitImage/spc/");
		_tcscat(strName, strTemp);
		_loading->loadFrameImage(strKey, strName, UNITSIZE_SPCX, UNITSIZE_SPCY, UNITFRAME_SPCX, UNITFRAME_SPCY);

		unitNum++;
	}

	//궁병
	for (int i = 0; i < TEAM_MAX; i++)
	{
		TCHAR strTemp[100] = L"";
		_stprintf(strTemp, L"궁병_%d.bmp", i);

		_stprintf(strKey, L"unit%d-%d-atk", unitNum, i);
		_stprintf(strName, L"image/unitImage/atk/");
		_tcscat(strName, strTemp);
		_loading->loadFrameImage(strKey, strName, UNITSIZE_ATKX, UNITSIZE_ATKY, UNITFRAME_ATKX, UNITFRAME_ATKY);

		_stprintf(strKey, L"unit%d-%d-idle", unitNum, i);
		_stprintf(strName, L"image/unitImage/idle/");
		_tcscat(strName, strTemp);
		_loading->loadFrameImage(strKey, strName, UNITSIZE_IDLEX, UNITSIZE_IDLEY, UNITFRAME_IDLEX, UNITFRAME_IDLEY);

		_stprintf(strKey, L"unit%d-%d-spc", unitNum, i);
		_stprintf(strName, L"image/unitImage/spc/");
		_tcscat(strName, strTemp);
		_loading->loadFrameImage(strKey, strName, UNITSIZE_SPCX, UNITSIZE_SPCY, UNITFRAME_SPCX, UNITFRAME_SPCY);

		unitNum++;
	}

	//궁기병
	for (int i = 0; i < TEAM_MAX; i++)
	{
		TCHAR strTemp[100] = L"";
		_stprintf(strTemp, L"궁기병_%d.bmp", i);

		_stprintf(strKey, L"unit%d-%d-atk", unitNum, i);
		_stprintf(strName, L"image/unitImage/atk/");
		_tcscat(strName, strTemp);
		_loading->loadFrameImage(strKey, strName, UNITSIZE_ATKX, UNITSIZE_ATKY, UNITFRAME_ATKX, UNITFRAME_ATKY);

		_stprintf(strKey, L"unit%d-%d-idle", unitNum, i);
		_stprintf(strName, L"image/unitImage/idle/");
		_tcscat(strName, strTemp);
		_loading->loadFrameImage(strKey, strName, UNITSIZE_IDLEX, UNITSIZE_IDLEY, UNITFRAME_IDLEX, UNITFRAME_IDLEY);

		_stprintf(strKey, L"unit%d-%d-spc", unitNum, i);
		_stprintf(strName, L"image/unitImage/spc/");
		_tcscat(strName, strTemp);
		_loading->loadFrameImage(strKey, strName, UNITSIZE_SPCX, UNITSIZE_SPCY, UNITFRAME_SPCX, UNITFRAME_SPCY);

		unitNum++;
	}

	//도사
	for (int i = 0; i < TEAM_MAX; i++)
	{
		TCHAR strTemp[100] = L"";
		_stprintf(strTemp, L"도사_%d.bmp", i);

		_stprintf(strKey, L"unit%d-%d-atk", unitNum, i);
		_stprintf(strName, L"image/unitImage/atk/");
		_tcscat(strName, strTemp);
		_loading->loadFrameImage(strKey, strName, UNITSIZE_ATKX, UNITSIZE_ATKY, UNITFRAME_ATKX, UNITFRAME_ATKY);

		_stprintf(strKey, L"unit%d-%d-idle", unitNum, i);
		_stprintf(strName, L"image/unitImage/idle/");
		_tcscat(strName, strTemp);
		_loading->loadFrameImage(strKey, strName, UNITSIZE_IDLEX, UNITSIZE_IDLEY, UNITFRAME_IDLEX, UNITFRAME_IDLEY);

		_stprintf(strKey, L"unit%d-%d-spc", unitNum, i);
		_stprintf(strName, L"image/unitImage/spc/");
		_tcscat(strName, strTemp);
		_loading->loadFrameImage(strKey, strName, UNITSIZE_SPCX, UNITSIZE_SPCY, UNITFRAME_SPCX, UNITFRAME_SPCY);

		unitNum++;
	}

	//법사
	for (int i = 0; i < TEAM_MAX; i++)
	{
		TCHAR strTemp[100] = L"";
		_stprintf(strTemp, L"법사_%d.bmp", i);

		_stprintf(strKey, L"unit%d-%d-atk", unitNum, i);
		_stprintf(strName, L"image/unitImage/atk/");
		_tcscat(strName, strTemp);
		_loading->loadFrameImage(strKey, strName, UNITSIZE_ATKX, UNITSIZE_ATKY, UNITFRAME_ATKX, UNITFRAME_ATKY);

		_stprintf(strKey, L"unit%d-%d-idle", unitNum, i);
		_stprintf(strName, L"image/unitImage/idle/");
		_tcscat(strName, strTemp);
		_loading->loadFrameImage(strKey, strName, UNITSIZE_IDLEX, UNITSIZE_IDLEY, UNITFRAME_IDLEX, UNITFRAME_IDLEY);

		_stprintf(strKey, L"unit%d-%d-spc", unitNum, i);
		_stprintf(strName, L"image/unitImage/spc/");
		_tcscat(strName, strTemp);
		_loading->loadFrameImage(strKey, strName, UNITSIZE_SPCX, UNITSIZE_SPCY, UNITFRAME_SPCX, UNITFRAME_SPCY);

		unitNum++;
	}

	//무도가
	for (int i = 0; i < TEAM_MAX; i++)
	{
		TCHAR strTemp[100] = L"";
		_stprintf(strTemp, L"무도가_%d.bmp", i);

		_stprintf(strKey, L"unit%d-%d-atk", unitNum, i);
		_stprintf(strName, L"image/unitImage/atk/");
		_tcscat(strName, strTemp);
		_loading->loadFrameImage(strKey, strName, UNITSIZE_ATKX, UNITSIZE_ATKY, UNITFRAME_ATKX, UNITFRAME_ATKY);

		_stprintf(strKey, L"unit%d-%d-idle", unitNum, i);
		_stprintf(strName, L"image/unitImage/idle/");
		_tcscat(strName, strTemp);
		_loading->loadFrameImage(strKey, strName, UNITSIZE_IDLEX, UNITSIZE_IDLEY, UNITFRAME_IDLEX, UNITFRAME_IDLEY);

		_stprintf(strKey, L"unit%d-%d-spc", unitNum, i);
		_stprintf(strName, L"image/unitImage/spc/");
		_tcscat(strName, strTemp);
		_loading->loadFrameImage(strKey, strName, UNITSIZE_SPCX, UNITSIZE_SPCY, UNITFRAME_SPCX, UNITFRAME_SPCY);

		unitNum++;
	}

	//석기
	for (int i = 0; i < TEAM_MAX; i++)
	{
		TCHAR strTemp[100] = L"";
		_stprintf(strTemp, L"석기_%d.bmp", i);

		_stprintf(strKey, L"unit%d-%d-atk", unitNum, i);
		_stprintf(strName, L"image/unitImage/atk/");
		_tcscat(strName, strTemp);
		_loading->loadFrameImage(strKey, strName, UNITSIZE_ATKX, UNITSIZE_ATKY, UNITFRAME_ATKX, UNITFRAME_ATKY);

		_stprintf(strKey, L"unit%d-%d-idle", unitNum, i);
		_stprintf(strName, L"image/unitImage/idle/");
		_tcscat(strName, strTemp);
		_loading->loadFrameImage(strKey, strName, UNITSIZE_IDLEX, UNITSIZE_IDLEY, UNITFRAME_IDLEX, UNITFRAME_IDLEY);

		_stprintf(strKey, L"unit%d-%d-spc", unitNum, i);
		_stprintf(strName, L"image/unitImage/spc/");
		_tcscat(strName, strTemp);
		_loading->loadFrameImage(strKey, strName, UNITSIZE_SPCX, UNITSIZE_SPCY, UNITFRAME_SPCX, UNITFRAME_SPCY);

		unitNum++;
	}
}
void sceneInit::initImageStory(void)
{
	TCHAR strKey[100], strName[100];
	//대화 face
	

	
	//대화창
	IMAGEMANAGER->addImage(L"좌대화창", L"image/좌측대화창.bmp", 464, 120,true,RGB(255,0,255));
	IMAGEMANAGER->addImage(L"우대화창", L"image/우측대화창.bmp", 464, 120,true,RGB(255,0,255));
	for (int i = 0; i <= 3; i++)
	{
		_stprintf(strKey, L"smap %04d", i);
		_stprintf(strName, L"image/map %04d.bmp", i);
		IMAGEMANAGER->addImage(strKey, strName, 640, 400);
	}
	memset(strKey, NULL, _tcslen(strKey));
	memset(strName, NULL, _tcslen(strName)); 

}




void sceneInit::initSound(void)
{

}

