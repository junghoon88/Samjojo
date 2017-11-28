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

	_loading->loadFrameImage(L"SELECT-���ù�ư", L"image/button2.bmp", 100, 60, 1, 2);
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

	//����
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

	//�⺴
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

	//�ú�
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

	//�ñ⺴
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

	//����
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

	//����
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

	//������
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

	//����
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
	_loading->loadImage(L"�´�ȭâ", L"image/������ȭâ.bmp", 464, 120,true,RGB(255,0,255));
	_loading->loadImage(L"���ȭâ", L"image/������ȭâ.bmp", 464, 120,true,RGB(255,0,255));
	

	for (int i = 0; i <= 3; i++)
	{
		_stprintf(strKey, L"smap %04d", i);
		_stprintf(strName, L"image/map %04d.bmp", i);
		_loading->loadImage(strKey, strName, 640, 400);
	}
	for (int i = 0; i <= 10; i++)
	{
		_stprintf(strKey, L"story_%02d", i);
		_stprintf(strName, L"image/story/story_%02d.bmp", i);
		_loading->loadImage(strKey, strName, 48, 64,true,RGB(255,0,255));
	}
	memset(strKey, NULL, _tcslen(strKey));
	memset(strName, NULL, _tcslen(strName)); 

}


void sceneInit::initImageReady(void) {

	IMAGEMANAGER->addImage(L"����UI", L"image/ready/readyUI.bmp", 960, 960, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage(L"����UI", L"image/ready/posUI.bmp", 617, 522, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage(L"��������", L"image/ready/����������ư.bmp", 75, 117, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage(L"������Ȱ����ư", L"image/ready/������Ȱ����ư.bmp", 86, 21, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage(L"����Ȱ����ư", L"image/ready/����Ȱ����ư.bmp",  86, 21, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage(L"����������ư", L"image/ready/����������ư.bmp",  86, 21, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage(L"��ҹ�ư", L"image/ready/��ҹ�ư.bmp", 86, 21, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage(L"��Ҵ�����ư", L"image/ready/��Ҵ�����ư.bmp", 86, 21, false, RGB(255, 0, 255));

	//��������
	IMAGEMANAGER->addImage(L"��������", L"image/ready/����.bmp", 84, 84, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage(L"���ĵ�����", L"image/ready/���ĵ�.bmp", 84, 84, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage(L"���Ŀ�����", L"image/ready/���Ŀ�.bmp", 84, 84, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage(L"�̾�������", L"image/ready/�̾���.bmp", 84, 84, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage(L"��������", L"image/ready/����.bmp", 84, 84, true, RGB(255, 0, 255));



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
}

