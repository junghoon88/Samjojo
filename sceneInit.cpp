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
		SCENEMANAGER->changeScene(L"���þ�");
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

	_loading->loadFrameImage(L"SELECT-���ù�ư", L"image/button2.bmp", 100, 60, 1, 2);
	_loading->loadFrameImage(L"SELECT-�������ù�ư", L"image/button3.bmp", 50, 60, 1, 2);
	_loading->loadFrameImage(L"LABEL-ū�̸�ǥ", L"image/label.bmp", 100, 30, 1, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage(L"LABEL-�����̸�ǥ", L"image/label2.bmp", 72, 30, 1, 1, true, RGB(255, 0, 255));
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
			_stprintf(strName, L"image/tiles/terrain/tile (%02d).bmp", index + 1);
			_loading->loadImage(strImgKey, strName, TILESIZE, TILESIZE);
		}
	}

	//������Ʈ Ÿ�� ����
	_loading->loadImage(L"objAliy", L"image/tiles/object/�Ʊ�.bmp", TILESIZE, TILESIZE, false, RGB(255, 0, 255), true);
	_loading->loadImage(L"objEnemy", L"image/tiles/object/����.bmp", TILESIZE, TILESIZE, false, RGB(255, 0, 255), true);
	_loading->loadImage(L"objPlayer", L"image/tiles/object/�÷��̾�.bmp", TILESIZE, TILESIZE, false, RGB(255, 0, 255), true);

	//����Ÿ�� üũ â
	_loading->loadImage(L"Ÿ�ϼ���", L"image/tileSelect.bmp", TILESIZE, TILESIZE, true, RGB(255, 0, 255), false);

	//��ư �̹���
	_loading->loadFrameImage(L"������ư", L"image/button.bmp", 100, 60, 1, 2);
	_loading->loadFrameImage(L"������ư2", L"image/button.bmp", 50, 60, 1, 2);

	//�Ͼ� ��� �����
	IMAGEMANAGER->addImage(L"maptoolBackground", L"image/maptoolBackground.bmp", 340, 520);


	//������ �̹��� �߰��ϱ�
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
	//����
	{
		TCHAR strTemp[100] = L"����.bmp";

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

	//���ĵ�
	{
		TCHAR strTemp[100] = L"���ĵ�.bmp";

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

	//����
	{
		TCHAR strTemp[100] = L"����.bmp";

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

	//���� 3, 4, 5
	for(int i = 0; i < TEAM_MAX; i++)
	{
		TCHAR strTemp[100] = L"";
		_stprintf(strTemp, L"����_%d.bmp", i);

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

	//�⺴ 6, 7, 8
	for (int i = 0; i < TEAM_MAX; i++)
	{
		TCHAR strTemp[100] = L"";
		_stprintf(strTemp, L"�⺴_%d.bmp", i);

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

	//�ú� 9, 10, 11
	for (int i = 0; i < TEAM_MAX; i++)
	{
		TCHAR strTemp[100] = L"";
		_stprintf(strTemp, L"�ú�_%d.bmp", i);

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

	//�ñ⺴ 12, 13, 14
	for (int i = 0; i < TEAM_MAX; i++)
	{
		TCHAR strTemp[100] = L"";
		_stprintf(strTemp, L"�ñ⺴_%d.bmp", i);

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

	//���� 15, 16, 17
	for (int i = 0; i < TEAM_MAX; i++)
	{
		TCHAR strTemp[100] = L"";
		_stprintf(strTemp, L"����_%d.bmp", i);

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

	//���� 18, 19, 20
	for (int i = 0; i < TEAM_MAX; i++)
	{
		TCHAR strTemp[100] = L"";
		_stprintf(strTemp, L"����_%d.bmp", i);

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

	//������ 21, 22, 23
	for (int i = 0; i < TEAM_MAX; i++)
	{
		TCHAR strTemp[100] = L"";
		_stprintf(strTemp, L"������_%d.bmp", i);

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

	//���� 24, 25, 26
	for (int i = 0; i < TEAM_MAX; i++)
	{
		TCHAR strTemp[100] = L"";
		_stprintf(strTemp, L"����_%d.bmp", i);

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
	//��ȭ face
	

	
	//��ȭâ
	_loading->loadImage(L"�´�ȭâ", L"image/story/������ȭâ.bmp", 464, 120,true,RGB(255,0,255),true);
	_loading->loadImage(L"���ȭâ", L"image/story/������ȭâ.bmp", 464, 120,true,RGB(255,0,255),true);
	_loading->loadFrameImage(L"���콺", L"image/story/storyMouse.bmp", 54, 28,2,1, true, RGB(255, 0, 255));
	_loading->loadImage(L"���콺2", L"image/story/storyMouse2.bmp", 26, 26, true, RGB(255, 0, 255));
	//��ȭ�� �ȳ�â
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

	_loading->loadImage(L"����UI", L"image/ready/readyUI.bmp", 640, 400, false, RGB(255, 0, 255));
	_loading->loadImage(L"����UI", L"image/ready/posUI.bmp", 617, 522, false, RGB(255, 0, 255));
	_loading->loadImage(L"��������", L"image/ready/����������ư.bmp", 50, 50, false, RGB(255, 0, 255));
	_loading->loadImage(L"��񴭸�", L"image/ready/��񴭸���ư.bmp", 50, 50, false, RGB(255, 0, 255));
	_loading->loadImage(L"���Դ���", L"image/ready/���Դ�����ư.bmp", 50, 50, false, RGB(255, 0, 255));
	_loading->loadImage(L"�Ű�����", L"image/ready/�Ű�������ư.bmp", 50, 50, false, RGB(255, 0, 255));
	_loading->loadImage(L"������Ȱ����ư", L"image/ready/������Ȱ����ư.bmp", 86, 21, false, RGB(255, 0, 255));
	_loading->loadImage(L"����Ȱ����ư", L"image/ready/����Ȱ����ư.bmp",  86, 21, false, RGB(255, 0, 255));
	_loading->loadImage(L"����������ư", L"image/ready/����������ư.bmp",  86, 21, false, RGB(255, 0, 255));
	_loading->loadImage(L"��ҹ�ư", L"image/ready/��ҹ�ư.bmp", 86, 21, false, RGB(255, 0, 255));
	_loading->loadImage(L"��Ҵ�����ư", L"image/ready/��Ҵ�����ư.bmp", 86, 21, false, RGB(255, 0, 255));


	_loading->loadImage(L"ü�¹�", L"image/ready/ü�¹�.bmp", 129, 9, false, RGB(255, 0, 255));
	_loading->loadImage(L"������", L"image/ready/������.bmp", 129, 9, false, RGB(255, 0, 255));
	_loading->loadImage(L"����ġ��", L"image/ready/����ġ��.bmp", 129, 9, false, RGB(255, 0, 255));
	_loading->loadImage(L"�ɷ�ġ��", L"image/ready/�ɷ�ġ��.bmp", 129, 9, false, RGB(255, 0, 255));

	//��������
	_loading->loadImage(L"��������", L"image/ready/����.bmp", 84, 84, true, RGB(255, 0, 255));
	_loading->loadImage(L"���ĵ�����", L"image/ready/���ĵ�.bmp", 84, 84, true, RGB(255, 0, 255));
	_loading->loadImage(L"���Ŀ�����", L"image/ready/���Ŀ�.bmp", 84, 84, true, RGB(255, 0, 255));
	_loading->loadImage(L"�̾�������", L"image/ready/�̾���.bmp", 84, 84, true, RGB(255, 0, 255));
	_loading->loadImage(L"��������", L"image/ready/����.bmp", 84, 84, true, RGB(255, 0, 255));



	_loading->loadImage(L"����UI", L"image/ready/readyUI.bmp", 960, 960, false, RGB(255, 0, 255));
	_loading->loadImage(L"����UI", L"image/ready/posUI.bmp", 960, 960, false, RGB(255, 0, 255));
	_loading->loadImage(L"��������", L"image/ready/����������ư.bmp", 75, 117, false, RGB(255, 0, 255));
	_loading->loadImage(L"������Ȱ����ư", L"image/ready/������Ȱ����ư.bmp", 86, 21, false, RGB(255, 0, 255));
	_loading->loadImage(L"����Ȱ����ư", L"image/ready/����Ȱ����ư.bmp", 86, 21, false, RGB(255, 0, 255));
	_loading->loadImage(L"����������ư", L"image/ready/����������ư.bmp", 86, 21, false, RGB(255, 0, 255));
	_loading->loadImage(L"��ҹ�ư", L"image/ready/��ҹ�ư.bmp", 86, 21, false, RGB(255, 0, 255));
	_loading->loadImage(L"��Ҵ�����ư", L"image/ready/��Ҵ�����ư.bmp", 86, 21, false, RGB(255, 0, 255));

}
void sceneInit::initImageUI(void)
{
	_loading->loadImage(L"ȭ�Ӽ�", L"image/icon/fire.bmp", 24, 24, true, RGB(255, 0, 255));
	_loading->loadImage(L"ȭ�Ӽ���Ȱ��", L"image/icon/un_fire.bmp", 24, 24, true, RGB(255, 0, 255));
	_loading->loadImage(L"���Ӽ�", L"image/icon/earth.bmp", 24, 24, true, RGB(255, 0, 255));
	_loading->loadImage(L"���Ӽ���Ȱ��", L"image/icon/un_earth.bmp", 24, 24, true, RGB(255, 0, 255));
	_loading->loadImage(L"ǳ�Ӽ�", L"image/icon/wind.bmp", 24, 24, true, RGB(255, 0, 255));
	_loading->loadImage(L"ǳ�Ӽ���Ȱ��", L"image/icon/un_wind.bmp", 24, 24, true, RGB(255, 0, 255));
	_loading->loadImage(L"���Ӽ�", L"image/icon/water.bmp", 24, 24, true, RGB(255, 0, 255));
	_loading->loadImage(L"���Ӽ���Ȱ��", L"image/icon/un_water.bmp", 24, 24, true, RGB(255, 0, 255));
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

	//�뷡 ����
	/*
	Se_e_00 ���Ҹ�
	Se_e_01 �Ź̼Ҹ�
	Se_e_02 �ͶѶ�̼Ҹ�
	Se_e_03 �������ѹٶ��Ҹ�
	Se_e_04 õ�չ���
	Se_e_05 ���Ҹ�
	Se_e_06 ���̵�ȯȣ��
	Se_e_07 �ο�¼Ҹ�
	Se_e_08 �����¼Ҹ�

	Se_m ���� ��ų�����̹Ƿ� ��� x

	Se02 ���콺����
	Se03 ���콺��������
	Se04 ��뺼�� ���� �� ȿ����
	Se07 ������ư ����� ���� ȿ����
	Se08 �ΰ��ӿ��� �ƽ� �ÿ� ĳ���� ���� ��ȯ �� ������ ȿ����
	Se15 �̼ǽ¸�ȿ����
	Se17 ����ϴ¾ֵ� ������ ȿ���� / ����â���� ĳ�� ���� �� ȿ����
	Se25 �����̵���
	Se26 �⸶���̵���
	Se27 �������̵���
	Se29 ���̵���
	Se31 �����̵���
	Se32 �������ݹ�����
	Se33 ȭ�������
	Se35 �����ݽ�ùȿ����
	Se36 ���ݽ�ùȿ����
	Se37 ���ݼ���ȿ����
	Se38 �����ݼ�����ȿ����
	Se39 �ú����ݽ�ùȿ����

	Se_b_00 ����ȭ�� �����
	Se_b_01 ��������� 1
	Se_b_02 ��������� 2
	Se_b_03 ��������� 3
	Se_b_04 ��������� 4
	Se_b_05 ������ǥ����� 1
	Se_b_06 ������ǥ����� 2
	Se_b_07 ĳ������â �����
	*/
}

