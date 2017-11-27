#include "stdafx.h"
#include "sceneUnitEditor.h"


sceneUnitEditor::sceneUnitEditor()
	: _imgFace(NULL), _imgBattleAtk(NULL), _imgBattleIdle(NULL), _imgBattleSpc(NULL)
{
	for (int i = 0; i < UNITEDITOR_BUTTON_MAX; i++)
	{
		_ctrlButton[i] = NULL;
	}
	for (int i = 0; i < UNITEDITOR_NUMEDITBOX_MAX; i++)
	{
		_numEditBox[i] = NULL;
	}
	for (int i = 0; i < UNITEDITOR_STREDITBOX_MAX; i++)
	{
		_strEditBox[i] = NULL;
	}
}


sceneUnitEditor::~sceneUnitEditor()
{
}


HRESULT sceneUnitEditor::init(void)
{
	ZeroMemory(&_unitInfo, sizeof(tagUnitSaveInfo));

	initButton();
	initValues();
	initImage();
	initEditbox();
	initRangeRect();
	initTeamButton();


	loadUnitFiles();

	hBrushWhite = CreateSolidBrush(RGB(255, 255, 255));
	hBrushBlue = CreateSolidBrush(RGB(0, 0, 180));
	
	hBrushRange = CreateSolidBrush(RGB(64, 64, 64));
	hBrushPlayer = CreateSolidBrush(RGB(32, 32, 240));
	hBrushAttack = CreateSolidBrush(RGB(240, 32, 32));

	_exit = false;

	return S_OK;
}

void sceneUnitEditor::loadUnitFiles(void)
{
	_vUnits.clear();

	int filenum = 0;
	//��� ���� ��ĵ test
	WIN32_FIND_DATA wfd;
	HANDLE handle = NULL;

	switch (_team)
	{
		case TEAM_PLAYER:
			handle = FindFirstFile(L"UnitData/player/*.dat", &wfd);
		break;
		case TEAM_FRIEND:
			handle = FindFirstFile(L"UnitData/friend/*.dat", &wfd);
		break;
		case TEAM_ENEMY:
			handle = FindFirstFile(L"UnitData/enemy/*.dat", &wfd);
		break;
	}

	// ã�� ������ �ִٸ�,
	while (handle != INVALID_HANDLE_VALUE)
	{
		tagUnitFileInfo temp;
		ZeroMemory(&temp, sizeof(tagUnitFileInfo));
		_tcscpy(temp.str, wfd.cFileName);
		temp.rc = RectMake(FILENAME_STARTX, FILENAME_STARTY + FILENAME_HEIGHT * filenum, FILENAME_WIDTH, FILENAME_HEIGHT);
		temp.img = NULL;
		temp.clicked = false;
		_vUnits.push_back(temp);
		filenum++;

		// FindNextFile ���� ������ �������� ���� ��� TRUE
		// ���� ��� FALSE �� ����
		if (!FindNextFile(handle, &wfd))
		{
			break;
		}
	}
	// ���� ã�� �ڵ� �� �ݱ�   
	FindClose(handle);
}

void sceneUnitEditor::release(void)
{
	for (int i = 0; i < UNITEDITOR_NUMEDITBOX_MAX; i++)
	{
		_numEditBox[i]->release();
		SAFE_DELETE(_numEditBox[i]);
	}

	for (int i = 0; i < UNITEDITOR_STREDITBOX_MAX; i++)
	{
		_strEditBox[i]->release();
		SAFE_DELETE(_strEditBox[i]);
	}

	DeleteObject(hBrushWhite);
	DeleteObject(hBrushBlue);
	DeleteObject(hBrushRange);
	DeleteObject(hBrushPlayer);
	DeleteObject(hBrushAttack);
}

void sceneUnitEditor::update(void)
{
	for (int i = 0; i < UNITEDITOR_BUTTON_MAX; i++)
	{
		_ctrlButton[i]->update();
	}

	for (int i = 0; i < UNITEDITOR_NUMEDITBOX_MAX; i++)
	{
		_numEditBox[i]->update();
	}

	for (int i = 0; i < UNITEDITOR_STREDITBOX_MAX; i++)
	{
		_strEditBox[i]->update();
	}

	filesUpdate();
	teamButtonUpdate();



	for (int i = 0; i < RANGESIZEX; i++)
	{
		for (int j = 0; j < RANGESIZEY; j++)
		{
			if (PtInRect(&_atkRange[i][j].rc, _ptMouse))
			{
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					if (!_atkRange[i][j].clicked)
						_atkRange[i][j].clicked = TRUE;
					else
						_atkRange[i][j].clicked = FALSE;
				}
			}
		}
	}

	if (_exit)
	{
		SCENEMANAGER->changeScene(L"���þ�");
	}
}

void sceneUnitEditor::render(void)
{
	rectSketch();		// ��Ʈ�� �ڽ��� ��ġ ����
	editBoxRender();
	unitImageRender();

	for (int i = 0; i < UNITEDITOR_BUTTON_MAX; i++)
	{
		_ctrlButton[i]->render();
		TextOut(getMemDC(), _ctrlButton[i]->getRect().left, _ctrlButton[i]->getRect().top, _strButton[i], _tcslen(_strButton[i]));
	}

	filesRender();

	atkRangeRender();

	//������ ��ư
	teamButtonRender();
}

void sceneUnitEditor::initImage(void)
{
	selectImgFace();
	selectImgBattleAtk();
	selectImgBattleIdle();
	selectImgBattleSpc();
}

//--------------------------------------------------------------------------------------------------
//init functions
void sceneUnitEditor::initButton(void)
{
	for (int i = 0; i < UNITEDITOR_BUTTON_MAX; i++)
	{
		_ctrlButton[i] = new button;
	}
	
	//label

	_ctrlButton[UNITEDITOR_BUTTON_LABEL_FILELIST]->init(L"������ư", 50 + UPDATEPOSX, 100 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, NULL);

	_ctrlButton[UNITEDITOR_BUTTON_LABEL_NAME]->init(L"������ư2", 450 + 25 + UPDATEPOSX, 100 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, NULL);

	_ctrlButton[UNITEDITOR_BUTTON_LABEL_FAMILY]->init(L"������ư2", 450 + 25 + UPDATEPOSX, 150 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, NULL);
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_AOS]->init(L"������ư2", 450 + 25 + UPDATEPOSX, 185 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, NULL);
																											   
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_HP]->init(L"������ư2", 450 + 25 + UPDATEPOSX, 235 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, NULL);
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_MP]->init(L"������ư2", 450 + 25 + UPDATEPOSX, 270 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, NULL);

	_ctrlButton[UNITEDITOR_BUTTON_LABEL_ATK]->init(L"������ư2", 450 + 25 + UPDATEPOSX, 320 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, NULL);
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_DEP]->init(L"������ư2", 450 + 25 + UPDATEPOSX, 355 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, NULL);
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_RES]->init(L"������ư2", 450 + 25 + UPDATEPOSX, 390 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, NULL);
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_AGL]->init(L"������ư2", 450 + 25 + UPDATEPOSX, 425 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, NULL);
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_FIG]->init(L"������ư2", 450 + 25 + UPDATEPOSX, 460 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, NULL);

	_ctrlButton[UNITEDITOR_BUTTON_LABEL_PWR]->init(L"������ư2", 450 + 25 + UPDATEPOSX, 510 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, NULL);
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_LDS]->init(L"������ư2", 450 + 25 + UPDATEPOSX, 545 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, NULL);
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_INT]->init(L"������ư2", 450 + 25 + UPDATEPOSX, 580 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, NULL);
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_DEX]->init(L"������ư2", 450 + 25 + UPDATEPOSX, 615 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, NULL);
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_LUK]->init(L"������ư2", 450 + 25 + UPDATEPOSX, 650 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, NULL);


	_ctrlButton[UNITEDITOR_BUTTON_LABEL_ENTERSCENARIO]->init(L"������ư2", 675 + 25 + UPDATEPOSX, 100 + 15, { 0, 0 }, { 0, 1 }, NULL);

	_ctrlButton[UNITEDITOR_BUTTON_LABEL_LV]->init(L"������ư2", 675 + 25 + UPDATEPOSX, 150 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, NULL);
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_MOVE]->init(L"������ư2", 675 + 25 + UPDATEPOSX, 185 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, NULL);
																											   
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_LVPERHP]->init(L"������ư2", 675 + 25 + UPDATEPOSX, 235 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, NULL);
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_LVPERMP]->init(L"������ư2", 675 + 25 + UPDATEPOSX, 270 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, NULL);
																 
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_LVPERATK]->init(L"������ư2", 675 + 25 + UPDATEPOSX, 320 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, NULL);
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_LVPERDEP]->init(L"������ư2", 675 + 25 + UPDATEPOSX, 355 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, NULL);
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_LVPERRES]->init(L"������ư2", 675 + 25 + UPDATEPOSX, 390 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, NULL);
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_LVPERAGL]->init(L"������ư2", 675 + 25 + UPDATEPOSX, 425 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, NULL);
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_LVPERFIG]->init(L"������ư2", 675 + 25 + UPDATEPOSX, 460 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, NULL);
																 
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_LVPERPWR]->init(L"������ư2", 675 + 25 + UPDATEPOSX, 510 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, NULL);
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_LVPERLDS]->init(L"������ư2", 675 + 25 + UPDATEPOSX, 545 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, NULL);
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_LVPERINT]->init(L"������ư2", 675 + 25 + UPDATEPOSX, 580 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, NULL);
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_LVPERDEX]->init(L"������ư2", 675 + 25 + UPDATEPOSX, 615 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, NULL);
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_LVPERLUK]->init(L"������ư2", 675 + 25 + UPDATEPOSX, 650 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, NULL);


	_ctrlButton[UNITEDITOR_BUTTON_LABEL_RANGE]->init(L"������ư", 900 + 50 + UPDATEPOSX, 100 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, NULL);

	_ctrlButton[UNITEDITOR_BUTTON_LABEL_WEAPON]->init(L"������ư", 900 + 50 + UPDATEPOSX, 345 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, NULL);
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_ARMOR]->init(L"������ư", 900 + 50 + UPDATEPOSX, 460 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, NULL);
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_SUBITEM]->init(L"������ư", 900 + 50 + UPDATEPOSX, 575 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, NULL);


	_ctrlButton[UNITEDITOR_BUTTON_LABEL_FILENAME]->init(L"������ư", 550 + 50 + UPDATEPOSX, 710 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, NULL);


	//prev, next
	_ctrlButton[UNITEDITOR_BUTTON_FACE_PREV]->init(L"������ư", 150 + 50 + UPDATEPOSX, 240 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, ctrlSelectFacePrev, this);
	_ctrlButton[UNITEDITOR_BUTTON_FACE_NEXT]->init(L"������ư", 250 + 50 + UPDATEPOSX, 240 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, ctrlSelectFaceNext, this);

	_ctrlButton[UNITEDITOR_BUTTON_NORMAL_PREV]->init(L"������ư", 150 + 50 + UPDATEPOSX, 710 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, ctrlSelectNormalPrev, this);
	_ctrlButton[UNITEDITOR_BUTTON_NORMAL_NEXT]->init(L"������ư", 250 + 50 + UPDATEPOSX, 710 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, ctrlSelectNormalNext, this);
	
	//_ctrlButton[UNITEDITOR_BUTTON_COMBAT_PREV]->init(L"������ư", 100 + 50 + UPDATEPOSX, 640 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, ctrlSelectCombatPrev, this);
	//_ctrlButton[UNITEDITOR_BUTTON_COMBAT_NEXT]->init(L"������ư", 200 + 50 + UPDATEPOSX, 640 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, ctrlSelectCombatNext, this);


	_ctrlButton[UNITEDITOR_BUTTON_WEAPON_PREV]->init(L"������ư2", 900 + 25 + UPDATEPOSX, 410 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, ctrlSelectWeaponPrev, this);
	_ctrlButton[UNITEDITOR_BUTTON_WEAPON_NEXT]->init(L"������ư2", 950 + 25 + UPDATEPOSX, 410 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, ctrlSelectWeaponNext, this);

	_ctrlButton[UNITEDITOR_BUTTON_ARMOR_PREV]->init(L"������ư2", 900 + 25 + UPDATEPOSX, 525 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, ctrlSelectArmorPrev, this);
	_ctrlButton[UNITEDITOR_BUTTON_ARMOR_NEXT]->init(L"������ư2", 950 + 25 + UPDATEPOSX, 525 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, ctrlSelectArmorNext, this);

	_ctrlButton[UNITEDITOR_BUTTON_SUBITEM_PREV]->init(L"������ư2", 900 + 25 + UPDATEPOSX, 640 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, ctrlSelectSubitemPrev, this);
	_ctrlButton[UNITEDITOR_BUTTON_SUBITEM_NEXT]->init(L"������ư2", 950 + 25 + UPDATEPOSX, 640 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, ctrlSelectSubitemNext, this);

	//new, save, load, exit
	_ctrlButton[UNITEDITOR_BUTTON_DATA_NEW]->init(L"������ư", 950 + 50 + UPDATEPOSX, 710 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, ctrlSelectDataNew, this);
	_ctrlButton[UNITEDITOR_BUTTON_DATA_LOAD]->init(L"������ư", 950 + 50 + UPDATEPOSX, 750 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, ctrlSelectDataLoad, this);
	_ctrlButton[UNITEDITOR_BUTTON_DATA_SAVE]->init(L"������ư", 950 + 50 + UPDATEPOSX, 790 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, ctrlSelectDataSave, this);
	_ctrlButton[UNITEDITOR_BUTTON_DATA_EXIT]->init(L"������ư", 950 + 50 + UPDATEPOSX, 850 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, ctrlSelectExit, this);


	//--------------------------------------------------------------------------------------------
	//��ư �̸� ǥ��
	_stprintf(_strButton[UNITEDITOR_BUTTON_LABEL_FILELIST], L"���ָ��");

	_stprintf(_strButton[UNITEDITOR_BUTTON_LABEL_NAME], L"�̸�");

	_stprintf(_strButton[UNITEDITOR_BUTTON_LABEL_FAMILY], L"�Ҽ�");
	_stprintf(_strButton[UNITEDITOR_BUTTON_LABEL_AOS], L"����");

	_stprintf(_strButton[UNITEDITOR_BUTTON_LABEL_HP], L"ü��");
	_stprintf(_strButton[UNITEDITOR_BUTTON_LABEL_MP], L"����");

	_stprintf(_strButton[UNITEDITOR_BUTTON_LABEL_ATK], L"���ݷ�");
	_stprintf(_strButton[UNITEDITOR_BUTTON_LABEL_DEP], L"����");
	_stprintf(_strButton[UNITEDITOR_BUTTON_LABEL_RES], L"���ŷ�");
	_stprintf(_strButton[UNITEDITOR_BUTTON_LABEL_AGL], L"���߷�");
	_stprintf(_strButton[UNITEDITOR_BUTTON_LABEL_FIG], L"���");

	_stprintf(_strButton[UNITEDITOR_BUTTON_LABEL_PWR], L"����");
	_stprintf(_strButton[UNITEDITOR_BUTTON_LABEL_LDS], L"���");
	_stprintf(_strButton[UNITEDITOR_BUTTON_LABEL_INT], L"����");
	_stprintf(_strButton[UNITEDITOR_BUTTON_LABEL_DEX], L"��ø");
	_stprintf(_strButton[UNITEDITOR_BUTTON_LABEL_LUK], L"���");


	_stprintf(_strButton[UNITEDITOR_BUTTON_LABEL_ENTERSCENARIO], L"�ó�����");

	_stprintf(_strButton[UNITEDITOR_BUTTON_LABEL_LV], L"����");
	_stprintf(_strButton[UNITEDITOR_BUTTON_LABEL_MOVE], L"�̵���");

	_stprintf(_strButton[UNITEDITOR_BUTTON_LABEL_LVPERHP], L"������ü��");
	_stprintf(_strButton[UNITEDITOR_BUTTON_LABEL_LVPERMP], L"�����縶��");

	_stprintf(_strButton[UNITEDITOR_BUTTON_LABEL_LVPERATK], L"��������ݷ�");
	_stprintf(_strButton[UNITEDITOR_BUTTON_LABEL_LVPERDEP], L"���������");
	_stprintf(_strButton[UNITEDITOR_BUTTON_LABEL_LVPERRES], L"���������ŷ�");
	_stprintf(_strButton[UNITEDITOR_BUTTON_LABEL_LVPERAGL], L"��������߷�");
	_stprintf(_strButton[UNITEDITOR_BUTTON_LABEL_LVPERFIG], L"��������");

	_stprintf(_strButton[UNITEDITOR_BUTTON_LABEL_LVPERPWR], L"�����繫��");
	_stprintf(_strButton[UNITEDITOR_BUTTON_LABEL_LVPERLDS], L"���������");
	_stprintf(_strButton[UNITEDITOR_BUTTON_LABEL_LVPERINT], L"����������");
	_stprintf(_strButton[UNITEDITOR_BUTTON_LABEL_LVPERDEX], L"�������ø");
	_stprintf(_strButton[UNITEDITOR_BUTTON_LABEL_LVPERLUK], L"���������");


	_stprintf(_strButton[UNITEDITOR_BUTTON_LABEL_RANGE], L"���ݹ���");

	_stprintf(_strButton[UNITEDITOR_BUTTON_LABEL_WEAPON], L"����");
	_stprintf(_strButton[UNITEDITOR_BUTTON_LABEL_ARMOR], L"��");
	_stprintf(_strButton[UNITEDITOR_BUTTON_LABEL_SUBITEM], L"����");


	_stprintf(_strButton[UNITEDITOR_BUTTON_DATA_NEW], L"NEW");
	_stprintf(_strButton[UNITEDITOR_BUTTON_DATA_LOAD], L"LOAD");
	_stprintf(_strButton[UNITEDITOR_BUTTON_DATA_SAVE], L"SAVE");
	_stprintf(_strButton[UNITEDITOR_BUTTON_DATA_EXIT], L"EXIT");

	_stprintf(_strButton[UNITEDITOR_BUTTON_LABEL_FILENAME], L"�����̸�");

	_stprintf(_strButton[UNITEDITOR_BUTTON_FACE_PREV], L"PREV");
	_stprintf(_strButton[UNITEDITOR_BUTTON_FACE_NEXT], L"NEXT");
	_stprintf(_strButton[UNITEDITOR_BUTTON_NORMAL_PREV], L"PREV");
	_stprintf(_strButton[UNITEDITOR_BUTTON_NORMAL_NEXT], L"NEXT");
	//_stprintf(_strButton[UNITEDITOR_BUTTON_COMBAT_PREV], L"PREV");
	//_stprintf(_strButton[UNITEDITOR_BUTTON_COMBAT_NEXT], L"NEXT");
	_stprintf(_strButton[UNITEDITOR_BUTTON_WEAPON_PREV], L"����");
	_stprintf(_strButton[UNITEDITOR_BUTTON_WEAPON_NEXT], L"����");
	_stprintf(_strButton[UNITEDITOR_BUTTON_ARMOR_PREV], L"����");
	_stprintf(_strButton[UNITEDITOR_BUTTON_ARMOR_NEXT], L"����");
	_stprintf(_strButton[UNITEDITOR_BUTTON_SUBITEM_PREV], L"����");
	_stprintf(_strButton[UNITEDITOR_BUTTON_SUBITEM_NEXT], L"����");

	//-------------------------------------------------------------------------------------------
}
void sceneUnitEditor::initValues(void)
{
	_faceNum = 0;
	_normalNum = 0;
	_combatNum = 0;
	_weaponNum = 0;
	_armorNum = 0;
	_subitemNum = 0;
}
void sceneUnitEditor::initEditbox(void)
{
	for (int i = 0; i < UNITEDITOR_STREDITBOX_MAX; i++)
	{
		_strEditBox[i] = new editbox;
		_strEditBox[i]->init();
	}
	_strEditBox[UNITEDITOR_STREDITBOX_DATA_NAME]->setRect(RectMake(550 + UPDATEPOSX, 100 + UPDATEPOSY, 100, 30));
	_strEditBox[UNITEDITOR_STREDITBOX_DATA_FAMILY]->setRect(RectMake(550 + UPDATEPOSX, 150 + UPDATEPOSY, 100, 30));
	_strEditBox[UNITEDITOR_STREDITBOX_DATA_AOS]->setRect(RectMake(550 + UPDATEPOSX, 185 + UPDATEPOSY, 100, 30));


	_strEditBox[UNITEDITOR_STREDITBOX_DATA_FILENAME]->setRect(RectMake(725 + UPDATEPOSX, 710 + UPDATEPOSY, 150, 30));


	for (int i = 0; i < UNITEDITOR_NUMEDITBOX_MAX; i++)
	{
		_numEditBox[i] = new editbox;
		_numEditBox[i]->init();
		_numEditBox[i]->setOnlyNum(TRUE);
		_numEditBox[i]->setMinMax(0, 200);
	}
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_HP]->setRect(RectMake(550 + UPDATEPOSX, 235 + UPDATEPOSY, 100, 30));
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_MP]->setRect(RectMake(550 + UPDATEPOSX, 270 + UPDATEPOSY, 100, 30));

	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_ATK]->setRect(RectMake(550 + UPDATEPOSX, 320 + UPDATEPOSY, 100, 30));
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_DEP]->setRect(RectMake(550 + UPDATEPOSX, 355 + UPDATEPOSY, 100, 30));
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_RES]->setRect(RectMake(550 + UPDATEPOSX, 390 + UPDATEPOSY, 100, 30));
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_AGL]->setRect(RectMake(550 + UPDATEPOSX, 425 + UPDATEPOSY, 100, 30));
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_FIG]->setRect(RectMake(550 + UPDATEPOSX, 460 + UPDATEPOSY, 100, 30));

	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_PWR]->setRect(RectMake(550 + UPDATEPOSX, 510 + UPDATEPOSY, 100, 30));
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LDS]->setRect(RectMake(550 + UPDATEPOSX, 545 + UPDATEPOSY, 100, 30));
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_INT]->setRect(RectMake(550 + UPDATEPOSX, 580 + UPDATEPOSY, 100, 30));
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_DEX]->setRect(RectMake(550 + UPDATEPOSX, 615 + UPDATEPOSY, 100, 30));
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LUK]->setRect(RectMake(550 + UPDATEPOSX, 650 + UPDATEPOSY, 100, 30));


	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_ENTERSCENARIO]->setRect(RectMake(775 + UPDATEPOSX, 100 + UPDATEPOSY, 100, 30));

	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LV]->setRect(RectMake(775 + UPDATEPOSX, 150 + UPDATEPOSY, 100, 30));
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_MOVE]->setRect(RectMake(775 + UPDATEPOSX, 185 + UPDATEPOSY, 100, 30));

	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERHP]->setRect(RectMake(775 + UPDATEPOSX, 235 + UPDATEPOSY, 100, 30));
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERMP]->setRect(RectMake(775 + UPDATEPOSX, 270 + UPDATEPOSY, 100, 30));

	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERATK]->setRect(RectMake(775 + UPDATEPOSX, 320 + UPDATEPOSY, 100, 30));
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERDEP]->setRect(RectMake(775 + UPDATEPOSX, 355 + UPDATEPOSY, 100, 30));
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERRES]->setRect(RectMake(775 + UPDATEPOSX, 390 + UPDATEPOSY, 100, 30));
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERAGL]->setRect(RectMake(775 + UPDATEPOSX, 425 + UPDATEPOSY, 100, 30));
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERFIG]->setRect(RectMake(775 + UPDATEPOSX, 460 + UPDATEPOSY, 100, 30));

	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERPWR]->setRect(RectMake(775 + UPDATEPOSX, 510 + UPDATEPOSY, 100, 30));
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERLDS]->setRect(RectMake(775 + UPDATEPOSX, 545 + UPDATEPOSY, 100, 30));
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERINT]->setRect(RectMake(775 + UPDATEPOSX, 580 + UPDATEPOSY, 100, 30));
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERDEX]->setRect(RectMake(775 + UPDATEPOSX, 615 + UPDATEPOSY, 100, 30));
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERLUK]->setRect(RectMake(775 + UPDATEPOSX, 650 + UPDATEPOSY, 100, 30));
}
void sceneUnitEditor::initRangeRect(void)
{
	for (int i = 0; i < RANGESIZEX; i++)
	{
		for (int j = 0; j < RANGESIZEY; j++)
		{
			_atkRange[i][j].rc = RectMake(
				900 + i * TILEWIDTH / 2 + UPDATEPOSX,
				135 + j * TILEHEIGHT / 2 + UPDATEPOSY,
				TILEWIDTH / 2,
				TILEHEIGHT / 2);

			_atkRange[i][j].clicked = FALSE;
		}
	}
}

void sceneUnitEditor::initTeamButton(void)
{
	for (int i = 0; i < TEAM_MAX; i++)
	{
		_teamButton[i].rc = RectMake(UPDATEPOSX, 150 + UPDATEPOSY + 35 * i, 100, 30);
		_teamButton[i].img = NULL;
		_teamButton[i].clicked = false;

		switch (i)
		{
		case TEAM_PLAYER:
			_stprintf(_teamButton[i].str, L"�÷��̾�");
		break;
		case TEAM_FRIEND:
			_stprintf(_teamButton[i].str, L"�Ʊ�");
		break;
		case TEAM_ENEMY:
			_stprintf(_teamButton[i].str, L"����");
		break;
		}
	}

	_teamButton[TEAM_PLAYER].clicked = true;
	_team = TEAM_PLAYER;
}

void sceneUnitEditor::filesUpdate(void)
{
	RECT temp = RectMake(FILENAME_STARTX, FILENAME_STARTY, FILENAME_WIDTH, FILENAME_HEIGHT * _vUnits.size());
	if (PtInRect(&temp, _ptMouse))
	{
		for (int i = 0; i < _vUnits.size(); i++)
		{
			if (PtInRect(&_vUnits[i].rc, _ptMouse))
			{
				if (!_vUnits[i].clicked && KEYMANAGER->isStayKeyDown(VK_LBUTTON))
					_vUnits[i].clicked = true;
			}
			else
			{
				if (_vUnits[i].clicked && KEYMANAGER->isStayKeyDown(VK_LBUTTON))
					_vUnits[i].clicked = false;
			}
		}
	}
}

void sceneUnitEditor::teamButtonUpdate(void)
{
	for (int i = 0; i < TEAM_MAX; i++)
	{
		if (PtInRect(&_teamButton[i].rc, _ptMouse))
		{
			if (!_teamButton[i].clicked && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				if (i == TEAM_PLAYER)
				{
					_teamButton[TEAM_PLAYER].clicked = true;
					_teamButton[TEAM_FRIEND].clicked = false;
					_teamButton[TEAM_ENEMY].clicked = false;
					_team = TEAM_PLAYER;
					loadUnitFiles();
				}
				else if (i == TEAM_FRIEND)
				{
					_teamButton[TEAM_PLAYER].clicked = false;
					_teamButton[TEAM_FRIEND].clicked = true;
					_teamButton[TEAM_ENEMY].clicked = false;
					_team = TEAM_FRIEND;
					loadUnitFiles();
				}
				else if (i == TEAM_ENEMY)
				{
					_teamButton[TEAM_PLAYER].clicked = false;
					_teamButton[TEAM_FRIEND].clicked = false;
					_teamButton[TEAM_ENEMY].clicked = true;
					_team = TEAM_ENEMY;
					loadUnitFiles();
				}
			}
		}
	}
}

//~init functions
//-----------------------------------------------------------------------------------------
//other functions

void sceneUnitEditor::rectSketch(void)
{
	Rectangle(getMemDC(), 150 + UPDATEPOSX, 100 + UPDATEPOSY, 438 + UPDATEPOSX, 228 + UPDATEPOSY);		//���̹���
	Rectangle(getMemDC(), 150 + UPDATEPOSX, 290 + UPDATEPOSY, 438 + UPDATEPOSX, 546 + UPDATEPOSY);		//�����̹���
	Rectangle(getMemDC(), 150 + UPDATEPOSX, 551 + UPDATEPOSY, 438 + UPDATEPOSX, 647 + UPDATEPOSY);		//�����̹���
	Rectangle(getMemDC(), 150 + UPDATEPOSX, 652 + UPDATEPOSY, 438 + UPDATEPOSX, 700 + UPDATEPOSY);		//�����̹���

	Rectangle(getMemDC(), 150 + UPDATEPOSX, 240 + UPDATEPOSY, 438 + UPDATEPOSX, 270 + UPDATEPOSY);		//����������ư
	Rectangle(getMemDC(), 150 + UPDATEPOSX, 710 + UPDATEPOSY, 438 + UPDATEPOSX, 740 + UPDATEPOSY);		//����������ư
	//Rectangle(getMemDC(), 100 + UPDATEPOSX, 640 + UPDATEPOSY, 300 + UPDATEPOSX, 670 + UPDATEPOSY);	//����������ư


	Rectangle(getMemDC(), 450 + UPDATEPOSX, 100 + UPDATEPOSY, 464 + UPDATEPOSX, 130 + UPDATEPOSY);	//�̸�

	Rectangle(getMemDC(), 450 + UPDATEPOSX, 150 + UPDATEPOSY, 464 + UPDATEPOSX, 180 + UPDATEPOSY);	//�δ�
	Rectangle(getMemDC(), 450 + UPDATEPOSX, 185 + UPDATEPOSY, 464 + UPDATEPOSX, 215 + UPDATEPOSY);	//�Ӽ�

	Rectangle(getMemDC(), 450 + UPDATEPOSX, 235 + UPDATEPOSY, 464 + UPDATEPOSX, 265 + UPDATEPOSY);	//HP
	Rectangle(getMemDC(), 450 + UPDATEPOSX, 270 + UPDATEPOSY, 464 + UPDATEPOSX, 300 + UPDATEPOSY);	//MP

	Rectangle(getMemDC(), 450 + UPDATEPOSX, 320 + UPDATEPOSY, 464 + UPDATEPOSX, 400 + UPDATEPOSY);	//���ݷ�
	Rectangle(getMemDC(), 450 + UPDATEPOSX, 355 + UPDATEPOSY, 464 + UPDATEPOSX, 385 + UPDATEPOSY);	//���ŷ�
	Rectangle(getMemDC(), 450 + UPDATEPOSX, 390 + UPDATEPOSY, 464 + UPDATEPOSX, 420 + UPDATEPOSY);	//����
	Rectangle(getMemDC(), 450 + UPDATEPOSX, 425 + UPDATEPOSY, 464 + UPDATEPOSX, 455 + UPDATEPOSY);	//���߷�
	Rectangle(getMemDC(), 450 + UPDATEPOSX, 460 + UPDATEPOSY, 464 + UPDATEPOSX, 490 + UPDATEPOSY);	//���

	Rectangle(getMemDC(), 450 + UPDATEPOSX, 510 + UPDATEPOSY, 464 + UPDATEPOSX, 540 + UPDATEPOSY);	//����
	Rectangle(getMemDC(), 450 + UPDATEPOSX, 545 + UPDATEPOSY, 464 + UPDATEPOSX, 575 + UPDATEPOSY);	//����
	Rectangle(getMemDC(), 450 + UPDATEPOSX, 580 + UPDATEPOSY, 464 + UPDATEPOSX, 610 + UPDATEPOSY);	//���
	Rectangle(getMemDC(), 450 + UPDATEPOSX, 615 + UPDATEPOSY, 464 + UPDATEPOSX, 645 + UPDATEPOSY);	//��ø
	Rectangle(getMemDC(), 450 + UPDATEPOSX, 650 + UPDATEPOSY, 464 + UPDATEPOSX, 680 + UPDATEPOSY);	//��


	Rectangle(getMemDC(), 550 + UPDATEPOSX, 100 + UPDATEPOSY, 600 + UPDATEPOSX, 130 + UPDATEPOSY);	//�������Է�

	Rectangle(getMemDC(), 550 + UPDATEPOSX, 150 + UPDATEPOSY, 600 + UPDATEPOSX, 180 + UPDATEPOSY);	//�������Է�
	Rectangle(getMemDC(), 550 + UPDATEPOSX, 185 + UPDATEPOSY, 600 + UPDATEPOSX, 215 + UPDATEPOSY);	//�������Է�

	Rectangle(getMemDC(), 550 + UPDATEPOSX, 235 + UPDATEPOSY, 600 + UPDATEPOSX, 265 + UPDATEPOSY);	//�������Է�
	Rectangle(getMemDC(), 550 + UPDATEPOSX, 270 + UPDATEPOSY, 600 + UPDATEPOSX, 300 + UPDATEPOSY);	//�������Է�

	Rectangle(getMemDC(), 550 + UPDATEPOSX, 320 + UPDATEPOSY, 600 + UPDATEPOSX, 400 + UPDATEPOSY);	//�������Է�
	Rectangle(getMemDC(), 550 + UPDATEPOSX, 355 + UPDATEPOSY, 600 + UPDATEPOSX, 385 + UPDATEPOSY);	//�������Է�
	Rectangle(getMemDC(), 550 + UPDATEPOSX, 390 + UPDATEPOSY, 600 + UPDATEPOSX, 420 + UPDATEPOSY);	//�������Է�
	Rectangle(getMemDC(), 550 + UPDATEPOSX, 425 + UPDATEPOSY, 600 + UPDATEPOSX, 455 + UPDATEPOSY);	//�������Է�
	Rectangle(getMemDC(), 550 + UPDATEPOSX, 460 + UPDATEPOSY, 600 + UPDATEPOSX, 490 + UPDATEPOSY);	//�������Է�

	Rectangle(getMemDC(), 550 + UPDATEPOSX, 510 + UPDATEPOSY, 600 + UPDATEPOSX, 540 + UPDATEPOSY);	//�������Է�
	Rectangle(getMemDC(), 550 + UPDATEPOSX, 545 + UPDATEPOSY, 600 + UPDATEPOSX, 575 + UPDATEPOSY);	//�������Է�
	Rectangle(getMemDC(), 550 + UPDATEPOSX, 580 + UPDATEPOSY, 600 + UPDATEPOSX, 610 + UPDATEPOSY);	//�������Է�
	Rectangle(getMemDC(), 550 + UPDATEPOSX, 615 + UPDATEPOSY, 600 + UPDATEPOSX, 645 + UPDATEPOSY);	//�������Է�
	Rectangle(getMemDC(), 550 + UPDATEPOSX, 650 + UPDATEPOSY, 600 + UPDATEPOSX, 680 + UPDATEPOSY);	//�������Է�


	Rectangle(getMemDC(), 900 + UPDATEPOSX, 345 + UPDATEPOSY, 964 + UPDATEPOSX, 375 + UPDATEPOSY);		//����
	Rectangle(getMemDC(), 900 + UPDATEPOSX, 505 + UPDATEPOSY, 964 + UPDATEPOSX, 535 + UPDATEPOSY);		//��
	Rectangle(getMemDC(), 900 + UPDATEPOSX, 575 + UPDATEPOSY, 964 + UPDATEPOSX, 605 + UPDATEPOSY);		//����

	Rectangle(getMemDC(), 900 + UPDATEPOSX, 380 + UPDATEPOSY, 1000 + UPDATEPOSX, 440 + UPDATEPOSY);		//�̸�
	Rectangle(getMemDC(), 900 + UPDATEPOSX, 495 + UPDATEPOSY, 1000 + UPDATEPOSX, 555 + UPDATEPOSY);		//�̸�
	Rectangle(getMemDC(), 900 + UPDATEPOSX, 610 + UPDATEPOSY, 1000 + UPDATEPOSX, 670 + UPDATEPOSY);		//�̸�

	Rectangle(getMemDC(), 1005 + UPDATEPOSX, 380 + UPDATEPOSY, 1065 + UPDATEPOSX, 440 + UPDATEPOSY);		//�̹���
	Rectangle(getMemDC(), 1005 + UPDATEPOSX, 495 + UPDATEPOSY, 1065 + UPDATEPOSX, 555 + UPDATEPOSY);		//�̹���
	Rectangle(getMemDC(), 1005 + UPDATEPOSX, 610 + UPDATEPOSY, 1065 + UPDATEPOSX, 670 + UPDATEPOSY);		//�̹���

	//Rectangle(getMemDC(), 700 + UPDATEPOSX, 470 + UPDATEPOSY, 1000 + UPDATEPOSX, 670 + UPDATEPOSY);		//���ּ���
	//
	//Rectangle(getMemDC(), 1040 + UPDATEPOSX, 100 + UPDATEPOSY, 1400 + UPDATEPOSX, 400 + UPDATEPOSY);	//�����ۻ󼼼����
	//
	//Rectangle(getMemDC(), 1040 + UPDATEPOSX, 430 + UPDATEPOSY, 1240 + UPDATEPOSX, 670 + UPDATEPOSY);	//��ų��

	Rectangle(getMemDC(), 950 + UPDATEPOSX, 710 + UPDATEPOSY, 1050 + UPDATEPOSX, 740 + UPDATEPOSY);	//���θ����
	Rectangle(getMemDC(), 950 + UPDATEPOSX, 750 + UPDATEPOSY, 1050 + UPDATEPOSX, 780 + UPDATEPOSY);	//���̺�
	Rectangle(getMemDC(), 950 + UPDATEPOSX, 790 + UPDATEPOSY, 1050 + UPDATEPOSX, 820 + UPDATEPOSY);	//�ε�
	Rectangle(getMemDC(), 950 + UPDATEPOSX, 850 + UPDATEPOSY, 1050 + UPDATEPOSX, 880 + UPDATEPOSY);	//����


}
void sceneUnitEditor::editBoxRender(void)
{
	for (int i = 0; i < UNITEDITOR_NUMEDITBOX_MAX; i++)
	{
		_numEditBox[i]->render();
	}

	for (int i = 0; i < UNITEDITOR_STREDITBOX_MAX; i++)
	{
		_strEditBox[i]->render();
	}
}
void sceneUnitEditor::unitImageRender(void)			// �ؾߵ� ��: ������ �̹����� �Է¹޾� �����ӷ����� ���
{
	if (_imgFace)		_imgFace->render(getMemDC(), 150 + UPDATEPOSX, 100 + UPDATEPOSY);
	if (_imgBattleAtk)  _imgBattleAtk->render(getMemDC(), 150 + UPDATEPOSX + 144 - _imgBattleAtk->getWidth() / 2, 290 + UPDATEPOSY);
	if (_imgBattleIdle) _imgBattleIdle->render(getMemDC(), 150 + UPDATEPOSX + 144 - _imgBattleIdle->getWidth() / 2, 290 + 256 + 5 + UPDATEPOSY);
	if (_imgBattleSpc)  _imgBattleSpc->render(getMemDC(), 150 + UPDATEPOSX + 144 - _imgBattleSpc->getWidth() / 2, 290 + 256 + 5 + 96 + 5 + UPDATEPOSY);
}
void sceneUnitEditor::atkRangeRender(void)
{
	HBRUSH oldBrushRange;

	for (int i = 0; i < RANGESIZEX; i++)
	{
		for (int j = 0; j < RANGESIZEY; j++)
		{
			if (i == RANGESIZEX / 2 && j == RANGESIZEY / 2) continue;

			if (_atkRange[i][j].clicked)
			{
				oldBrushRange = (HBRUSH)SelectObject(getMemDC(), hBrushAttack);
			}
			else
			{
				oldBrushRange = (HBRUSH)SelectObject(getMemDC(), hBrushRange);
			}

			Rectangle(getMemDC(), _atkRange[i][j].rc.left, _atkRange[i][j].rc.top, _atkRange[i][j].rc.right, _atkRange[i][j].rc.bottom);

			SelectObject(getMemDC(), oldBrushRange);
		}
	}
	DeleteObject(oldBrushRange);

	HBRUSH oldBrushPlayer;
	oldBrushPlayer = (HBRUSH)SelectObject(getMemDC(), hBrushPlayer);
	Rectangle(getMemDC(), _atkRange[3][3].rc.left, _atkRange[3][3].rc.top, _atkRange[3][3].rc.right, _atkRange[3][3].rc.bottom);
	SelectObject(getMemDC(), oldBrushPlayer);
	DeleteObject(oldBrushPlayer);
}

void sceneUnitEditor::filesRender(void)
{
	if (_vUnits.size() == 0)
		return;

	HBRUSH oldBrush;
	for (int i = 0; i < _vUnits.size(); i++)
	{
		if (_vUnits[i].clicked)
		{
			oldBrush = (HBRUSH)SelectObject(getMemDC(), hBrushBlue);
		}
		else
		{
			oldBrush = (HBRUSH)SelectObject(getMemDC(), hBrushWhite);
		}
		Rectangle(getMemDC(), _vUnits[i].rc.left, _vUnits[i].rc.top, _vUnits[i].rc.right, _vUnits[i].rc.bottom);
		TextOut(getMemDC(), _vUnits[i].rc.left, _vUnits[i].rc.top, _vUnits[i].str, _tcslen(_vUnits[i].str));
		SelectObject(getMemDC(), oldBrush);
	}
	DeleteObject(oldBrush);
}

void sceneUnitEditor::teamButtonRender(void)
{
	HBRUSH oldBrush;
	for (int i = 0; i < TEAM_MAX; i++)
	{
		if (_teamButton[i].clicked)
		{
			oldBrush = (HBRUSH)SelectObject(getMemDC(), hBrushBlue);
		}
		else
		{
			oldBrush = (HBRUSH)SelectObject(getMemDC(), hBrushWhite);
		}

		Rectangle(getMemDC(), _teamButton[i].rc.left, _teamButton[i].rc.top, _teamButton[i].rc.right, _teamButton[i].rc.bottom);
		TextOut(getMemDC(), _teamButton[i].rc.left, _teamButton[i].rc.top, _teamButton[i].str, _tcslen(_teamButton[i].str));
		SelectObject(getMemDC(), oldBrush);
	}
	DeleteObject(oldBrush);

}

void sceneUnitEditor::newUnit(void)
{
	ZeroMemory(&_unitInfo, sizeof(tagUnitSaveInfo));

	for (int i = 0; i < UNITEDITOR_NUMEDITBOX_MAX; i++)
	{
		// ���ڿ��� �����ڽ� Ŭ����
		_numEditBox[i]->clearStr();
	}

	for (int i = 0; i < UNITEDITOR_STREDITBOX_MAX; i++)
	{
		// ������ �����ڽ� Ŭ����
		_strEditBox[i]->clearStr();
	}
}

void sceneUnitEditor::getChar(WPARAM wParam)
{
	//���ڿ� �޴� �Լ�
	for (int i = 0; i < UNITEDITOR_NUMEDITBOX_MAX; i++)
	{
		_numEditBox[i]->getChar(wParam);
	}

	for (int i = 0; i < UNITEDITOR_STREDITBOX_MAX; i++)
	{
		_strEditBox[i]->getChar(wParam);
	}
}

void sceneUnitEditor::loadUnit(void)		// �ε����� �ϴ� ����
{
	if (_vUnits.size() == 0) 
		return;

	bool find = false;
	TCHAR filename[100] = L"";
	int index = 0;

	switch (_team)
	{
		case TEAM_PLAYER:
			_stprintf(filename, L"UnitData/player/");
		break;
		case TEAM_FRIEND:
			_stprintf(filename, L"UnitData/friend/");
		break;
		case TEAM_ENEMY:
			_stprintf(filename, L"UnitData/enemy/");
		break;
	}

	for (int i = 0; i < _vUnits.size(); i++)
	{
		if (_vUnits[i].clicked)
		{
			_tcscat(filename, _vUnits[i].str);
			index = i;
			find = true;
			break;
		}
	}

	if (find == false)
		return;

	HANDLE file;
	DWORD read;

	file = CreateFile(filename, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	newUnit();

	ReadFile(file, &_unitInfo, sizeof(tagUnitSaveInfo), &read, NULL);

	CloseHandle(file);

	//�ε� ������ ȭ�� ���� �ѹ� ������� �Ʒ� �̸� �����ֵ��� ���� �Լ� ���� ȣ���ϵ���
	//test

	_faceNum = _unitInfo.status.numImagFace;

	TCHAR strFaceKey[100];
	_stprintf(strFaceKey, L"face %05d", _faceNum);
	_imgFace = IMAGEMANAGER->findImage(strFaceKey);

	_normalNum = _unitInfo.numImgBattle;
	

	selectImgFace();
	selectImgBattleAtk();
	selectImgBattleIdle();
	selectImgBattleSpc();


	_strEditBox[UNITEDITOR_STREDITBOX_DATA_NAME]->setStr(_unitInfo.status.name);

	_strEditBox[UNITEDITOR_STREDITBOX_DATA_FAMILY]->setStr(_unitInfo.status.family);
	_strEditBox[UNITEDITOR_STREDITBOX_DATA_AOS]->setStr(_unitInfo.status.aos);

	_tcscpy(filename, _vUnits[index].str);
	_strEditBox[UNITEDITOR_STREDITBOX_DATA_FILENAME]->setStr(_tcstok(filename, L"."));

	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_HP]->setStrNum(_unitInfo.status.InitHPMax);
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_MP]->setStrNum(_unitInfo.status.InitMPMax);

	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_ATK]->setStrNum(_unitInfo.status.InitAtk);
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_DEP]->setStrNum(_unitInfo.status.InitDep);
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_RES]->setStrNum(_unitInfo.status.InitRes);
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_AGL]->setStrNum(_unitInfo.status.InitAgl);
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_FIG]->setStrNum(_unitInfo.status.InitFig);
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_PWR]->setStrNum(_unitInfo.status.InitPwr);
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LDS]->setStrNum(_unitInfo.status.InitLds);
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_INT]->setStrNum(_unitInfo.status.InitInt);
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_DEX]->setStrNum(_unitInfo.status.InitDex);
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LUK]->setStrNum(_unitInfo.status.InitLuk);


	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_ENTERSCENARIO]->setStrNum(_unitInfo.status.enterScenario);
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LV]->setStrNum(_unitInfo.status.level);
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_MOVE]->setStrNum(_unitInfo.status.movePoint);

	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERHP]->setStrNum(_unitInfo.status.LvPerHPMax);;
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERMP]->setStrNum(_unitInfo.status.LvPerMPMax);;

	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERATK]->setStrNum(_unitInfo.status.LvPerAtk);
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERDEP]->setStrNum(_unitInfo.status.LvPerDep);
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERRES]->setStrNum(_unitInfo.status.LvPerRes);
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERAGL]->setStrNum(_unitInfo.status.LvPerAgl);
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERFIG]->setStrNum(_unitInfo.status.LvPerFig);
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERPWR]->setStrNum(_unitInfo.status.LvPerPwr);
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERLDS]->setStrNum(_unitInfo.status.LvPerLds);
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERINT]->setStrNum(_unitInfo.status.LvPerInt);
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERDEX]->setStrNum(_unitInfo.status.LvPerDex);
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERLUK]->setStrNum(_unitInfo.status.LvPerLuk);

	for (int i = 0; i < RANGESIZEX; i++)
	{
		for (int j = 0; j < RANGESIZEY; j++)
		{
			_atkRange[i][j].clicked = _unitInfo.status.atkRange[i][j];
		}
	}
}
void sceneUnitEditor::saveUnit(void)
{
	if (_imgBattleAtk)  _unitInfo.numImgBattle = _normalNum;

	_tcscpy_s(_unitInfo.status.name, _strEditBox[UNITEDITOR_STREDITBOX_DATA_NAME]->getStr());
	_tcscpy_s(_unitInfo.status.family, _strEditBox[UNITEDITOR_STREDITBOX_DATA_FAMILY]->getStr());
	_tcscpy_s(_unitInfo.status.aos, _strEditBox[UNITEDITOR_STREDITBOX_DATA_AOS]->getStr());

	_unitInfo.status.numImagFace		= _faceNum;
	_unitInfo.status.team				= _team;
	_unitInfo.status.isLive				= TRUE;
	_unitInfo.status.exp				= 0;
	_unitInfo.status.expMax				= 100;
	_unitInfo.status.InitHPMax			= _numEditBox[UNITEDITOR_NUMEDITBOX_DATA_HP]->getStrNum();
	_unitInfo.status.InitMPMax			= _numEditBox[UNITEDITOR_NUMEDITBOX_DATA_MP]->getStrNum();
	_unitInfo.status.InitAtk			= _numEditBox[UNITEDITOR_NUMEDITBOX_DATA_ATK]->getStrNum();
	_unitInfo.status.InitDep			= _numEditBox[UNITEDITOR_NUMEDITBOX_DATA_DEP]->getStrNum();
	_unitInfo.status.InitRes			= _numEditBox[UNITEDITOR_NUMEDITBOX_DATA_RES]->getStrNum();
	_unitInfo.status.InitAgl			= _numEditBox[UNITEDITOR_NUMEDITBOX_DATA_AGL]->getStrNum();
	_unitInfo.status.InitFig			= _numEditBox[UNITEDITOR_NUMEDITBOX_DATA_FIG]->getStrNum();
	_unitInfo.status.InitPwr			= _numEditBox[UNITEDITOR_NUMEDITBOX_DATA_PWR]->getStrNum();
	_unitInfo.status.InitLds			= _numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LDS]->getStrNum();
	_unitInfo.status.InitInt			= _numEditBox[UNITEDITOR_NUMEDITBOX_DATA_INT]->getStrNum();
	_unitInfo.status.InitDex			= _numEditBox[UNITEDITOR_NUMEDITBOX_DATA_DEX]->getStrNum();
	_unitInfo.status.InitLuk			= _numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LUK]->getStrNum();

	_unitInfo.status.enterScenario		= _numEditBox[UNITEDITOR_NUMEDITBOX_DATA_ENTERSCENARIO]->getStrNum();
	_unitInfo.status.level				= _numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LV]->getStrNum();
	_unitInfo.status.movePoint			= _numEditBox[UNITEDITOR_NUMEDITBOX_DATA_MOVE]->getStrNum();
	_unitInfo.status.LvPerHPMax			= _numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERHP]->getStrNum();;
	_unitInfo.status.LvPerMPMax			= _numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERMP]->getStrNum();;
	_unitInfo.status.LvPerAtk			= _numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERATK]->getStrNum();
	_unitInfo.status.LvPerDep			= _numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERDEP]->getStrNum();
	_unitInfo.status.LvPerRes			= _numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERRES]->getStrNum();
	_unitInfo.status.LvPerAgl			= _numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERAGL]->getStrNum();
	_unitInfo.status.LvPerFig			= _numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERFIG]->getStrNum();
	_unitInfo.status.LvPerPwr			= _numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERPWR]->getStrNum();
	_unitInfo.status.LvPerLds			= _numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERLDS]->getStrNum();
	_unitInfo.status.LvPerInt			= _numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERINT]->getStrNum();
	_unitInfo.status.LvPerDex			= _numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERDEX]->getStrNum();
	_unitInfo.status.LvPerLuk			= _numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERLUK]->getStrNum();

	

	for (int i = 0; i < RANGESIZEX; i++)
	{
		for (int j = 0; j < RANGESIZEY; j++)
		{
			_unitInfo.status.atkRange[i][j] = _atkRange[i][j].clicked;
		}
	}


	HANDLE file;
	DWORD write;
	TCHAR tempStr[1024] = L"UnitData/";

	switch (_team)
	{
	case TEAM_PLAYER:
		_stprintf(tempStr, L"UnitData/player/");
	break;
	case TEAM_FRIEND:
		_stprintf(tempStr, L"UnitData/friend/");
	break;
	case TEAM_ENEMY:
		_stprintf(tempStr, L"UnitData/enemy/");
	break;
	}

	_tcscat(tempStr, _strEditBox[UNITEDITOR_STREDITBOX_DATA_FILENAME]->getStr());
	_tcscat(tempStr, L".dat");

	file = CreateFile(tempStr, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, &_unitInfo, sizeof(tagUnitSaveInfo), &write, NULL);

	CloseHandle(file);
}

void sceneUnitEditor::selectImgFace(void)
{
	TCHAR strFaceKey[100];
	_stprintf(strFaceKey, L"face %05d", _faceNum);
	_imgFace = IMAGEMANAGER->findImage(strFaceKey);
}

void sceneUnitEditor::selectImgBattleAtk(void)
{
	TCHAR strKey[100];
	if (_normalNum < UNIT_BATTLE_IMAGE1)
	{
		_stprintf(strKey, L"unit%d-atk", _normalNum);
	}
	else
	{
		_stprintf(strKey, L"unit%d-%d-atk", _normalNum, _team);
	}
	_imgBattleAtk = IMAGEMANAGER->findImage(strKey);
}

void sceneUnitEditor::selectImgBattleIdle(void)
{
	TCHAR strKey[100];
	if (_normalNum < UNIT_BATTLE_IMAGE1)
	{
		_stprintf(strKey, L"unit%d-idle", _normalNum);
	}
	else
	{
		_stprintf(strKey, L"unit%d-%d-idle", _normalNum, _team);
	}
	_imgBattleIdle = IMAGEMANAGER->findImage(strKey);
}

void sceneUnitEditor::selectImgBattleSpc(void)
{
	TCHAR strKey[100];
	if (_normalNum < UNIT_BATTLE_IMAGE1)
	{
		_stprintf(strKey, L"unit%d-spc", _normalNum);
	}
	else
	{
		_stprintf(strKey, L"unit%d-%d-spc", _normalNum, _team);
	}
	_imgBattleSpc = IMAGEMANAGER->findImage(strKey);
}

//~other functions
//-----------------------------------------------------------------------------------------
//callback functions
void sceneUnitEditor::ctrlSelectDataNew(void* obj) 
{
	sceneUnitEditor* unitEditor = (sceneUnitEditor*)obj;
	unitEditor->newUnit();
}
void sceneUnitEditor::ctrlSelectDataLoad(void* obj)
{
	sceneUnitEditor* unitEditor = (sceneUnitEditor*)obj;
	unitEditor->loadUnit();
}
void sceneUnitEditor::ctrlSelectDataSave(void* obj)
{
	sceneUnitEditor* unitEditor = (sceneUnitEditor*)obj;
	unitEditor->saveUnit();
	unitEditor->loadUnitFiles();
}
void sceneUnitEditor::ctrlSelectExit(void * obj)
{
	sceneUnitEditor* unitEditor = (sceneUnitEditor*)obj;
	unitEditor->setExit();
}
void sceneUnitEditor::ctrlSelectFacePrev(void* obj)
{
	sceneUnitEditor* unitEditor = (sceneUnitEditor*)obj;
	unitEditor->setFacePrev();
	unitEditor->selectImgFace();
}
void sceneUnitEditor::ctrlSelectFaceNext(void* obj)
{
	sceneUnitEditor* unitEditor = (sceneUnitEditor*)obj;
	unitEditor->setFaceNext();
	unitEditor->selectImgFace();
}
void sceneUnitEditor::ctrlSelectNormalPrev(void* obj)
{
	sceneUnitEditor* unitEditor = (sceneUnitEditor*)obj;
	unitEditor->setNormalPrev();
	unitEditor->selectImgBattleAtk();
	unitEditor->selectImgBattleIdle();
	unitEditor->selectImgBattleSpc();
}
void sceneUnitEditor::ctrlSelectNormalNext(void* obj)
{
	sceneUnitEditor* unitEditor = (sceneUnitEditor*)obj;
	unitEditor->setNormalNext();
	unitEditor->selectImgBattleAtk();
	unitEditor->selectImgBattleIdle();
	unitEditor->selectImgBattleSpc();
}
void sceneUnitEditor::ctrlSelectCombatPrev(void* obj)
{
	sceneUnitEditor* unitEditor = (sceneUnitEditor*)obj;
	unitEditor->setCombatPrev();
}
void sceneUnitEditor::ctrlSelectCombatNext(void* obj)
{
	sceneUnitEditor* unitEditor = (sceneUnitEditor*)obj;
	unitEditor->setCombatNext();
}
void sceneUnitEditor::ctrlSelectWeaponPrev(void* obj)
{
	sceneUnitEditor* unitEditor = (sceneUnitEditor*)obj;
	unitEditor->setWeaponPrev();
}
void sceneUnitEditor::ctrlSelectWeaponNext(void* obj)
{
	sceneUnitEditor* unitEditor = (sceneUnitEditor*)obj;
	unitEditor->setWeaponNext();
}
void sceneUnitEditor::ctrlSelectArmorPrev(void* obj)
{
	sceneUnitEditor* unitEditor = (sceneUnitEditor*)obj;
	unitEditor->setArmorPrev();
}
void sceneUnitEditor::ctrlSelectArmorNext(void* obj)
{
	sceneUnitEditor* unitEditor = (sceneUnitEditor*)obj;
	unitEditor->setArmorNext();
}
void sceneUnitEditor::ctrlSelectSubitemPrev(void* obj)
{
	sceneUnitEditor* unitEditor = (sceneUnitEditor*)obj;
	unitEditor->setSubitemPrev();
}
void sceneUnitEditor::ctrlSelectSubitemNext(void* obj)
{
	sceneUnitEditor* unitEditor = (sceneUnitEditor*)obj;
	unitEditor->setSubitemNext();
}

void sceneUnitEditor::cbFuncChangeTeamPlayer(void * obj)
{
	sceneUnitEditor* unitEditor = (sceneUnitEditor*)obj;
}

void sceneUnitEditor::cbFuncChangeTeamFriend(void * obj)
{
	sceneUnitEditor* unitEditor = (sceneUnitEditor*)obj;
}

void sceneUnitEditor::cbFuncChangeTeamEnemy(void * obj)
{
	sceneUnitEditor* unitEditor = (sceneUnitEditor*)obj;
}

//~callback functions
//-----------------------------------------------------------------------------------------
