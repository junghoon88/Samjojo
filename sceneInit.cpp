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
	initImageReady();
	initImageUnits();

	initImageUI();
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
	_loading->loadImage(L"logo 37", L"image/logo/Logo 00037.bmp", 1104, 960);
	_loading->loadImage(L"logo 38", L"image/logo/Logo 00038.bmp", 1104, 960);

	_loading->loadFrameImage(L"SELECT-선택버튼", L"image/button2.bmp", 100, 60, 1, 2);
	_loading->loadFrameImage(L"SELECT-작은선택버튼", L"image/button3.bmp", 50, 60, 1, 2);
	_loading->loadFrameImage(L"LABEL-큰이름표", L"image/label.bmp", 100, 30, 1, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage(L"LABEL-작은이름표", L"image/label2.bmp", 72, 30, 1, 1, true, RGB(255, 0, 255));
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
	_loading->loadImage(L"objAliy", L"image/tiles/object/아군.bmp", TILESIZE, TILESIZE, false, RGB(255, 0, 255), true);
	_loading->loadImage(L"objEnemy", L"image/tiles/object/적군.bmp", TILESIZE, TILESIZE, false, RGB(255, 0, 255), true);
	_loading->loadImage(L"objPlayer", L"image/tiles/object/플레이어.bmp", TILESIZE, TILESIZE, false, RGB(255, 0, 255), true);

	//선택타일 체크 창
	_loading->loadImage(L"타일선택", L"image/tileSelect.bmp", TILESIZE, TILESIZE, true, RGB(255, 0, 255), false);

	//버튼 이미지
	_loading->loadFrameImage(L"맵툴버튼", L"image/button.bmp", 100, 60, 1, 2);
	_loading->loadFrameImage(L"맵툴버튼2", L"image/button.bmp", 50, 60, 1, 2);

	//하얀 배경 지우기
	IMAGEMANAGER->addImage(L"maptoolBackground", L"image/maptoolBackground.bmp", 340, 520);


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
}

void sceneInit::initImageUnits(void)
{
	_loading->loadImage(L"curAtkArea", L"image/battleScene/atk_range.bmp", TILESIZE, TILESIZE, true, RGB(255, 0, 255), true);
	_loading->loadImage(L"playerMoveAreaTile", L"image/battleScene/player_range_tile.bmp", TILESIZE, TILESIZE, false, RGB(255, 0, 255), true);
	_loading->loadImage(L"nonPlayerMoveAreaTile", L"image/battleScene/non-player_range_tile.bmp", TILESIZE, TILESIZE, false, RGB(255, 0, 255), true);


	TCHAR strKey[100], strName[100];
	int unitNum = 0;
	//조조
	{
		TCHAR strTemp[100] = L"조조.bmp";

		_stprintf(strKey, L"unit%d-atk", unitNum);
		_stprintf(strName, L"image/unitImage/atk/");
		_tcscat(strName, strTemp);
		_loading->loadFrameImage(strKey, strName, UNITSIZE_ATKX, UNITSIZE_ATKY, UNITFRAME_ATKX, UNITFRAME_ATKY, true, RGB(255, 0, 255));

		_stprintf(strKey, L"unit%d-idle", unitNum);
		_stprintf(strName, L"image/unitImage/idle/");
		_tcscat(strName, strTemp);
		_loading->loadFrameImage(strKey, strName, UNITSIZE_IDLEX, UNITSIZE_IDLEY, UNITFRAME_IDLEX, UNITFRAME_IDLEY, true, RGB(255, 0, 255));

		_stprintf(strKey, L"unit%d-spc", unitNum);
		_stprintf(strName, L"image/unitImage/spc/");
		_tcscat(strName, strTemp);
		_loading->loadFrameImage(strKey, strName, UNITSIZE_SPCX, UNITSIZE_SPCY, UNITFRAME_SPCX, UNITFRAME_SPCY, true, RGB(255, 0, 255));

		unitNum++;
	}

	//하후돈
	{
		TCHAR strTemp[100] = L"하후돈.bmp";

		_stprintf(strKey, L"unit%d-atk", unitNum);
		_stprintf(strName, L"image/unitImage/atk/");
		_tcscat(strName, strTemp);
		_loading->loadFrameImage(strKey, strName, UNITSIZE_ATKX, UNITSIZE_ATKY, UNITFRAME_ATKX, UNITFRAME_ATKY, true, RGB(255, 0, 255));

		_stprintf(strKey, L"unit%d-idle", unitNum);
		_stprintf(strName, L"image/unitImage/idle/");
		_tcscat(strName, strTemp);
		_loading->loadFrameImage(strKey, strName, UNITSIZE_IDLEX, UNITSIZE_IDLEY, UNITFRAME_IDLEX, UNITFRAME_IDLEY, true, RGB(255, 0, 255));

		_stprintf(strKey, L"unit%d-spc", unitNum);
		_stprintf(strName, L"image/unitImage/spc/");
		_tcscat(strName, strTemp);
		_loading->loadFrameImage(strKey, strName, UNITSIZE_SPCX, UNITSIZE_SPCY, UNITFRAME_SPCX, UNITFRAME_SPCY, true, RGB(255, 0, 255));

		unitNum++;
	}

	//여포
	{
		TCHAR strTemp[100] = L"여포.bmp";

		_stprintf(strKey, L"unit%d-atk", unitNum);
		_stprintf(strName, L"image/unitImage/atk/");
		_tcscat(strName, strTemp);
		_loading->loadFrameImage(strKey, strName, UNITSIZE_ATKX, UNITSIZE_ATKY, UNITFRAME_ATKX, UNITFRAME_ATKY, true, RGB(255, 0, 255));

		_stprintf(strKey, L"unit%d-idle", unitNum);
		_stprintf(strName, L"image/unitImage/idle/");
		_tcscat(strName, strTemp);
		_loading->loadFrameImage(strKey, strName, UNITSIZE_IDLEX, UNITSIZE_IDLEY, UNITFRAME_IDLEX, UNITFRAME_IDLEY, true, RGB(255, 0, 255));

		_stprintf(strKey, L"unit%d-spc", unitNum);
		_stprintf(strName, L"image/unitImage/spc/");
		_tcscat(strName, strTemp);
		_loading->loadFrameImage(strKey, strName, UNITSIZE_SPCX, UNITSIZE_SPCY, UNITFRAME_SPCX, UNITFRAME_SPCY, true, RGB(255, 0, 255));

		unitNum++;
	}

	//보병 3, 4, 5
	for(int i = 0; i < TEAM_MAX; i++)
	{
		TCHAR strTemp[100] = L"";
		_stprintf(strTemp, L"보병_%d.bmp", i);

		_stprintf(strKey, L"unit%d-%d-atk", unitNum, i);
		_stprintf(strName, L"image/unitImage/atk/");
		_tcscat(strName, strTemp);
		_loading->loadFrameImage(strKey, strName, UNITSIZE_ATKX, UNITSIZE_ATKY, UNITFRAME_ATKX, UNITFRAME_ATKY, true, RGB(255, 0, 255));

		_stprintf(strKey, L"unit%d-%d-idle", unitNum, i);
		_stprintf(strName, L"image/unitImage/idle/");
		_tcscat(strName, strTemp);
		_loading->loadFrameImage(strKey, strName, UNITSIZE_IDLEX, UNITSIZE_IDLEY, UNITFRAME_IDLEX, UNITFRAME_IDLEY, true, RGB(255, 0, 255));

		_stprintf(strKey, L"unit%d-%d-spc", unitNum, i);
		_stprintf(strName, L"image/unitImage/spc/");
		_tcscat(strName, strTemp);
		_loading->loadFrameImage(strKey, strName, UNITSIZE_SPCX, UNITSIZE_SPCY, UNITFRAME_SPCX, UNITFRAME_SPCY, true, RGB(255, 0, 255));

		unitNum++;
	}

	//기병 6, 7, 8
	for (int i = 0; i < TEAM_MAX; i++)
	{
		TCHAR strTemp[100] = L"";
		_stprintf(strTemp, L"기병_%d.bmp", i);

		_stprintf(strKey, L"unit%d-%d-atk", unitNum, i);
		_stprintf(strName, L"image/unitImage/atk/");
		_tcscat(strName, strTemp);
		_loading->loadFrameImage(strKey, strName, UNITSIZE_ATKX, UNITSIZE_ATKY, UNITFRAME_ATKX, UNITFRAME_ATKY, true, RGB(255, 0, 255));

		_stprintf(strKey, L"unit%d-%d-idle", unitNum, i);
		_stprintf(strName, L"image/unitImage/idle/");
		_tcscat(strName, strTemp);
		_loading->loadFrameImage(strKey, strName, UNITSIZE_IDLEX, UNITSIZE_IDLEY, UNITFRAME_IDLEX, UNITFRAME_IDLEY, true, RGB(255, 0, 255));

		_stprintf(strKey, L"unit%d-%d-spc", unitNum, i);
		_stprintf(strName, L"image/unitImage/spc/");
		_tcscat(strName, strTemp);
		_loading->loadFrameImage(strKey, strName, UNITSIZE_SPCX, UNITSIZE_SPCY, UNITFRAME_SPCX, UNITFRAME_SPCY, true, RGB(255, 0, 255));

		unitNum++;
	}

	//궁병 9, 10, 11
	for (int i = 0; i < TEAM_MAX; i++)
	{
		TCHAR strTemp[100] = L"";
		_stprintf(strTemp, L"궁병_%d.bmp", i);

		_stprintf(strKey, L"unit%d-%d-atk", unitNum, i);
		_stprintf(strName, L"image/unitImage/atk/");
		_tcscat(strName, strTemp);
		_loading->loadFrameImage(strKey, strName, UNITSIZE_ATKX, UNITSIZE_ATKY, UNITFRAME_ATKX, UNITFRAME_ATKY, true, RGB(255, 0, 255));

		_stprintf(strKey, L"unit%d-%d-idle", unitNum, i);
		_stprintf(strName, L"image/unitImage/idle/");
		_tcscat(strName, strTemp);
		_loading->loadFrameImage(strKey, strName, UNITSIZE_IDLEX, UNITSIZE_IDLEY, UNITFRAME_IDLEX, UNITFRAME_IDLEY, true, RGB(255, 0, 255));

		_stprintf(strKey, L"unit%d-%d-spc", unitNum, i);
		_stprintf(strName, L"image/unitImage/spc/");
		_tcscat(strName, strTemp);
		_loading->loadFrameImage(strKey, strName, UNITSIZE_SPCX, UNITSIZE_SPCY, UNITFRAME_SPCX, UNITFRAME_SPCY, true, RGB(255, 0, 255));

		unitNum++;
	}

	//궁기병 12, 13, 14
	for (int i = 0; i < TEAM_MAX; i++)
	{
		TCHAR strTemp[100] = L"";
		_stprintf(strTemp, L"궁기병_%d.bmp", i);

		_stprintf(strKey, L"unit%d-%d-atk", unitNum, i);
		_stprintf(strName, L"image/unitImage/atk/");
		_tcscat(strName, strTemp);
		_loading->loadFrameImage(strKey, strName, UNITSIZE_ATKX, UNITSIZE_ATKY, UNITFRAME_ATKX, UNITFRAME_ATKY, true, RGB(255, 0, 255));

		_stprintf(strKey, L"unit%d-%d-idle", unitNum, i);
		_stprintf(strName, L"image/unitImage/idle/");
		_tcscat(strName, strTemp);
		_loading->loadFrameImage(strKey, strName, UNITSIZE_IDLEX, UNITSIZE_IDLEY, UNITFRAME_IDLEX, UNITFRAME_IDLEY, true, RGB(255, 0, 255));

		_stprintf(strKey, L"unit%d-%d-spc", unitNum, i);
		_stprintf(strName, L"image/unitImage/spc/");
		_tcscat(strName, strTemp);
		_loading->loadFrameImage(strKey, strName, UNITSIZE_SPCX, UNITSIZE_SPCY, UNITFRAME_SPCX, UNITFRAME_SPCY, true, RGB(255, 0, 255));

		unitNum++;
	}

	//도사 15, 16, 17
	for (int i = 0; i < TEAM_MAX; i++)
	{
		TCHAR strTemp[100] = L"";
		_stprintf(strTemp, L"도사_%d.bmp", i);

		_stprintf(strKey, L"unit%d-%d-atk", unitNum, i);
		_stprintf(strName, L"image/unitImage/atk/");
		_tcscat(strName, strTemp);
		_loading->loadFrameImage(strKey, strName, UNITSIZE_ATKX, UNITSIZE_ATKY, UNITFRAME_ATKX, UNITFRAME_ATKY, true, RGB(255, 0, 255));

		_stprintf(strKey, L"unit%d-%d-idle", unitNum, i);
		_stprintf(strName, L"image/unitImage/idle/");
		_tcscat(strName, strTemp);
		_loading->loadFrameImage(strKey, strName, UNITSIZE_IDLEX, UNITSIZE_IDLEY, UNITFRAME_IDLEX, UNITFRAME_IDLEY, true, RGB(255, 0, 255));

		_stprintf(strKey, L"unit%d-%d-spc", unitNum, i);
		_stprintf(strName, L"image/unitImage/spc/");
		_tcscat(strName, strTemp);
		_loading->loadFrameImage(strKey, strName, UNITSIZE_SPCX, UNITSIZE_SPCY, UNITFRAME_SPCX, UNITFRAME_SPCY, true, RGB(255, 0, 255));

		unitNum++;
	}

	//법사 18, 19, 20
	for (int i = 0; i < TEAM_MAX; i++)
	{
		TCHAR strTemp[100] = L"";
		_stprintf(strTemp, L"법사_%d.bmp", i);

		_stprintf(strKey, L"unit%d-%d-atk", unitNum, i);
		_stprintf(strName, L"image/unitImage/atk/");
		_tcscat(strName, strTemp);
		_loading->loadFrameImage(strKey, strName, UNITSIZE_ATKX, UNITSIZE_ATKY, UNITFRAME_ATKX, UNITFRAME_ATKY, true, RGB(255, 0, 255));

		_stprintf(strKey, L"unit%d-%d-idle", unitNum, i);
		_stprintf(strName, L"image/unitImage/idle/");
		_tcscat(strName, strTemp);
		_loading->loadFrameImage(strKey, strName, UNITSIZE_IDLEX, UNITSIZE_IDLEY, UNITFRAME_IDLEX, UNITFRAME_IDLEY, true, RGB(255, 0, 255));

		_stprintf(strKey, L"unit%d-%d-spc", unitNum, i);
		_stprintf(strName, L"image/unitImage/spc/");
		_tcscat(strName, strTemp);
		_loading->loadFrameImage(strKey, strName, UNITSIZE_SPCX, UNITSIZE_SPCY, UNITFRAME_SPCX, UNITFRAME_SPCY, true, RGB(255, 0, 255));

		unitNum++;
	}

	//무도가 21, 22, 23
	for (int i = 0; i < TEAM_MAX; i++)
	{
		TCHAR strTemp[100] = L"";
		_stprintf(strTemp, L"무도가_%d.bmp", i);

		_stprintf(strKey, L"unit%d-%d-atk", unitNum, i);
		_stprintf(strName, L"image/unitImage/atk/");
		_tcscat(strName, strTemp);
		_loading->loadFrameImage(strKey, strName, UNITSIZE_ATKX, UNITSIZE_ATKY, UNITFRAME_ATKX, UNITFRAME_ATKY, true, RGB(255, 0, 255));

		_stprintf(strKey, L"unit%d-%d-idle", unitNum, i);
		_stprintf(strName, L"image/unitImage/idle/");
		_tcscat(strName, strTemp);
		_loading->loadFrameImage(strKey, strName, UNITSIZE_IDLEX, UNITSIZE_IDLEY, UNITFRAME_IDLEX, UNITFRAME_IDLEY, true, RGB(255, 0, 255));

		_stprintf(strKey, L"unit%d-%d-spc", unitNum, i);
		_stprintf(strName, L"image/unitImage/spc/");
		_tcscat(strName, strTemp);
		_loading->loadFrameImage(strKey, strName, UNITSIZE_SPCX, UNITSIZE_SPCY, UNITFRAME_SPCX, UNITFRAME_SPCY, true, RGB(255, 0, 255));

		unitNum++;
	}

	//석기 24, 25, 26
	for (int i = 0; i < TEAM_MAX; i++)
	{
		TCHAR strTemp[100] = L"";
		_stprintf(strTemp, L"석기_%d.bmp", i);

		_stprintf(strKey, L"unit%d-%d-atk", unitNum, i);
		_stprintf(strName, L"image/unitImage/atk/");
		_tcscat(strName, strTemp);
		_loading->loadFrameImage(strKey, strName, UNITSIZE_ATKX, UNITSIZE_ATKY, UNITFRAME_ATKX, UNITFRAME_ATKY, true, RGB(255, 0, 255));

		_stprintf(strKey, L"unit%d-%d-idle", unitNum, i);
		_stprintf(strName, L"image/unitImage/idle/");
		_tcscat(strName, strTemp);
		_loading->loadFrameImage(strKey, strName, UNITSIZE_IDLEX, UNITSIZE_IDLEY, UNITFRAME_IDLEX, UNITFRAME_IDLEY, true, RGB(255, 0, 255));

		_stprintf(strKey, L"unit%d-%d-spc", unitNum, i);
		_stprintf(strName, L"image/unitImage/spc/");
		_tcscat(strName, strTemp);
		_loading->loadFrameImage(strKey, strName, UNITSIZE_SPCX, UNITSIZE_SPCY, UNITFRAME_SPCX, UNITFRAME_SPCY, true, RGB(255, 0, 255));

		unitNum++;
	}
}
void sceneInit::initImageStory(void)
{
	TCHAR strKey[100], strName[100];
	//대화 face
	

	
	//대화창
	_loading->loadImage(L"좌대화창", L"image/story/좌측대화창.bmp", 464, 120,true,RGB(255,0,255),true);
	_loading->loadImage(L"우대화창", L"image/story/우측대화창.bmp", 464, 120,true,RGB(255,0,255),true);
	_loading->loadFrameImage(L"마우스", L"image/story/storyMouse.bmp", 54, 28,2,1, true, RGB(255, 0, 255));
	_loading->loadImage(L"마우스2", L"image/story/storyMouse2.bmp", 26, 26, true, RGB(255, 0, 255));
	//대화전 안내창
	for (int i = 0; i < 3; i++)
	{
		_stprintf(strKey, L"nebi %02d", i);
		_stprintf(strName, L"image/story/nebi %02d.bmp", i);
		_loading->loadImage(strKey, strName, 148, 52, true, RGB(255, 0, 255));
	}
		_loading->loadImage(L"nebi 03", L"image/story/nebi 03.bmp", 196, 52, true, RGB(255, 0, 255));
		_loading->loadImage(L"nebi 04", L"image/story/nebi 04.bmp", 196, 52, true, RGB(255, 0, 255));
		_loading->loadFrameImage(L"story jojo", L"image/story/story_jojo 00.bmp", 48, 128, 1, 2, true, RGB(255, 0, 255));
	for (int i = 0; i <= 3; i++)
	{
		_stprintf(strKey, L"smap %04d", i);
		_stprintf(strName, L"image/story/map %04d.bmp", i);
		_loading->loadImage(strKey, strName, 640, 400);
	}
	for (int i = 0; i <= 11; i++)
	{
		_stprintf(strKey, L"story_%02d", i);
		_stprintf(strName, L"image/story/story_%02d.bmp", i);
		_loading->loadImage(strKey, strName, 48, 64,true,RGB(255,0,255));
	}
	
	memset(strKey, NULL, _tcslen(strKey));
	memset(strName, NULL, _tcslen(strName)); 

}


void sceneInit::initImageReady(void) {

	_loading->loadImage(L"레디UI", L"image/ready/readyUI.bmp", 640, 400, false, RGB(255, 0, 255));
	_loading->loadImage(L"출진UI", L"image/ready/posUI.bmp", 617, 522, false, RGB(255, 0, 255));
	_loading->loadImage(L"출진눌림", L"image/ready/출진눌림버튼.bmp", 50, 50, false, RGB(255, 0, 255));
	_loading->loadImage(L"장비눌림", L"image/ready/장비눌림버튼.bmp", 50, 50, false, RGB(255, 0, 255));
	_loading->loadImage(L"구입눌림", L"image/ready/구입눌림버튼.bmp", 50, 50, false, RGB(255, 0, 255));
	_loading->loadImage(L"매각눌림", L"image/ready/매각눌림버튼.bmp", 50, 50, false, RGB(255, 0, 255));
	_loading->loadImage(L"결정비활성버튼", L"image/ready/결정비활성버튼.bmp", 86, 21, false, RGB(255, 0, 255));
	_loading->loadImage(L"결정활성버튼", L"image/ready/결정활성버튼.bmp",  86, 21, false, RGB(255, 0, 255));
	_loading->loadImage(L"결정눌림버튼", L"image/ready/결정눌림버튼.bmp",  86, 21, false, RGB(255, 0, 255));
	_loading->loadImage(L"취소버튼", L"image/ready/취소버튼.bmp", 86, 21, false, RGB(255, 0, 255));
	_loading->loadImage(L"취소눌림버튼", L"image/ready/취소눌림버튼.bmp", 86, 21, false, RGB(255, 0, 255));


	_loading->loadImage(L"체력바", L"image/ready/체력바.bmp", 129, 9, false, RGB(255, 0, 255));
	_loading->loadImage(L"마나바", L"image/ready/마나바.bmp", 129, 9, false, RGB(255, 0, 255));
	_loading->loadImage(L"경험치바", L"image/ready/경험치바.bmp", 129, 9, false, RGB(255, 0, 255));
	_loading->loadImage(L"능력치바", L"image/ready/능력치바.bmp", 129, 9, false, RGB(255, 0, 255));

	//출진유닛
	_loading->loadImage(L"조조출진", L"image/ready/조조.bmp", 84, 84, true, RGB(255, 0, 255));
	_loading->loadImage(L"하후돈출진", L"image/ready/하후돈.bmp", 84, 84, true, RGB(255, 0, 255));
	_loading->loadImage(L"하후연출진", L"image/ready/하후연.bmp", 84, 84, true, RGB(255, 0, 255));
	_loading->loadImage(L"이악조출진", L"image/ready/이악조.bmp", 84, 84, true, RGB(255, 0, 255));
	_loading->loadImage(L"조인출진", L"image/ready/조인.bmp", 84, 84, true, RGB(255, 0, 255));



	_loading->loadImage(L"레디UI", L"image/ready/readyUI.bmp", 960, 960, false, RGB(255, 0, 255));
	_loading->loadImage(L"출진UI", L"image/ready/posUI.bmp", 960, 960, false, RGB(255, 0, 255));
	_loading->loadImage(L"출진눌림", L"image/ready/출진눌림버튼.bmp", 75, 117, false, RGB(255, 0, 255));
	_loading->loadImage(L"결정비활성버튼", L"image/ready/결정비활성버튼.bmp", 86, 21, false, RGB(255, 0, 255));
	_loading->loadImage(L"결정활성버튼", L"image/ready/결정활성버튼.bmp", 86, 21, false, RGB(255, 0, 255));
	_loading->loadImage(L"결정눌림버튼", L"image/ready/결정눌림버튼.bmp", 86, 21, false, RGB(255, 0, 255));
	_loading->loadImage(L"취소버튼", L"image/ready/취소버튼.bmp", 86, 21, false, RGB(255, 0, 255));
	_loading->loadImage(L"취소눌림버튼", L"image/ready/취소눌림버튼.bmp", 86, 21, false, RGB(255, 0, 255));

}
void sceneInit::initImageUI(void)
{
	_loading->loadImage(L"화속성", L"image/icon/fire.bmp", 24, 24, true, RGB(255, 0, 255));
	_loading->loadImage(L"화속성비활성", L"image/icon/un_fire.bmp", 24, 24, true, RGB(255, 0, 255));
	_loading->loadImage(L"땅속성", L"image/icon/earth.bmp", 24, 24, true, RGB(255, 0, 255));
	_loading->loadImage(L"땅속성비활성", L"image/icon/un_earth.bmp", 24, 24, true, RGB(255, 0, 255));
	_loading->loadImage(L"풍속성", L"image/icon/wind.bmp", 24, 24, true, RGB(255, 0, 255));
	_loading->loadImage(L"풍속성비활성", L"image/icon/un_wind.bmp", 24, 24, true, RGB(255, 0, 255));
	_loading->loadImage(L"수속성", L"image/icon/water.bmp", 24, 24, true, RGB(255, 0, 255));
	_loading->loadImage(L"수속성비활성", L"image/icon/un_water.bmp", 24, 24, true, RGB(255, 0, 255));
}

void sceneInit::initSound(void)
{
	TCHAR strKey[256], strName[256];

	for (int i = 0; i <= 8; i++)
	{
		_stprintf(strKey, L"Se_b_%02d", i);
		_stprintf(strName, L"Wav/Se_b_%02d.mp3", i);
		_loading->loadSound(strKey, strName, true, true);
	}

	for (int i = 0; i <= 8; i++)
	{
		_stprintf(strKey, L"Se_e_%02d", i);
		_stprintf(strName, L"Wav/Se_e_%02d.wav", i);
		_loading->loadSound(strKey, strName, false, false);
	}

	for (int i = 0; i <= 40; i++)
	{
		_stprintf(strKey, L"Se_m_%02d", i);
		_stprintf(strName, L"Wav/Se_m_%02d.wav", i);
		_loading->loadSound(strKey, strName, false, false);
	}

	for (int i = 1; i <= 58; i++)
	{
		_stprintf(strKey, L"Se%02d", i);
		_stprintf(strName, L"Wav/Se%02d.wav", i);
		_loading->loadSound(strKey, strName, false, false);
	}

	//노래 설명
	/*
	Se_e_00 새소리
	Se_e_01 매미소리
	Se_e_02 귀뚜라미소리
	Se_e_03 으스스한바람소리
	Se_e_04 천둥번개
	Se_e_05 새소리
	Se_e_06 아이들환호성
	Se_e_07 싸우는소리
	Se_e_08 노젓는소리

	Se_m 들은 스킬관련이므로 상관 x

	Se02 마우스선택
	Se03 마우스선택해제
	Se04 사용볼가 선택 시 효과음
	Se07 출진버튼 누루면 나는 효과음
	Se08 인게임에서 컷신 시에 캐릭이 방향 전환 시 나오는 효과음
	Se15 미션승리효과음
	Se17 기습하는애들 출현시 효과음 / 출진창에서 캐릭 선택 시 효과음
	Se25 평지이동음
	Se26 기마병이동음
	Se27 투석기이동음
	Se29 숲이동음
	Se31 물가이동음
	Se32 근접공격방어성공음
	Se33 화살방어성공음
	Se35 강공격시첫효과음
	Se36 공격시첫효과음
	Se37 공격성공효과음
	Se38 강공격성공시효과음
	Se39 궁병공격시첫효과음

	Se_b_00 메인화면 배경음
	Se_b_01 전투배경음 1
	Se_b_02 전투배경음 2
	Se_b_03 전투배경음 3
	Se_b_04 전투배경음 4
	Se_b_05 전투목표배경음 1
	Se_b_06 전투목표배경음 2
	Se_b_07 캐릭선택창 배경음
	*/
}

