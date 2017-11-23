#include "stdafx.h"
#include "sceneUnitEditor.h"


sceneUnitEditor::sceneUnitEditor()
{
}


sceneUnitEditor::~sceneUnitEditor()
{
}


HRESULT sceneUnitEditor::init(void)
{
	_unit = new Unit;
	_unit->init();
	
	initButton();
	initValues();
	initEditbox();
	initRangeRect();

	loadUnitFiles();

	hBrushWhite = CreateSolidBrush(RGB(255, 255, 255));
	hBrushBlue = CreateSolidBrush(RGB(0, 0, 180));
	
	hBrushRange = CreateSolidBrush(RGB(64, 64, 64));
	hBrushPlayer = CreateSolidBrush(RGB(32, 32, 240));
	hBrushAttack = CreateSolidBrush(RGB(240, 32, 32));

	return S_OK;
}

void sceneUnitEditor::loadUnitFiles(void)
{
	_vUnits.clear();

	int filenum = 0;
	//��� ���� ��ĵ test
	WIN32_FIND_DATA wfd;
	HANDLE handle = FindFirstFile(L"UnitData/*.dat", &wfd);
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
	SAFE_DELETE(_unit);

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
}

void sceneUnitEditor::render(void)
{
	//rectSketch();		// ��Ʈ�� �ڽ��� ��ġ ����
	editBoxRender();
	unitImageRender();

	for (int i = 0; i < UNITEDITOR_BUTTON_MAX; i++)
	{
		_ctrlButton[i]->render();
		TextOut(getMemDC(), _ctrlButton[i]->getRect().left, _ctrlButton[i]->getRect().top, _strButton[i], _tcslen(_strButton[i]));
	}

	if (_vUnits.size() > 0)
	{
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

	atkRangeRender();

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

	_ctrlButton[UNITEDITOR_BUTTON_LABEL_FILELIST]->init(L"������ư", 64 + 50 - UPDATEPOSX + UPDATEPOSX, 100 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, NULL);

	_ctrlButton[UNITEDITOR_BUTTON_LABEL_NAME]->init(L"������ư2", 350 + 25 + UPDATEPOSX, 100 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, NULL);

	_ctrlButton[UNITEDITOR_BUTTON_LABEL_FAMILY]->init(L"������ư2", 350 + 25 + UPDATEPOSX, 150 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, NULL);
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_AOS]->init(L"������ư2", 350 + 25 + UPDATEPOSX, 185 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, NULL);
																											   
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_HP]->init(L"������ư2", 350 + 25 + UPDATEPOSX, 235 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, NULL);
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_MP]->init(L"������ư2", 350 + 25 + UPDATEPOSX, 270 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, NULL);

	_ctrlButton[UNITEDITOR_BUTTON_LABEL_ATK]->init(L"������ư2", 350 + 25 + UPDATEPOSX, 320 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, NULL);
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_DEP]->init(L"������ư2", 350 + 25 + UPDATEPOSX, 355 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, NULL);
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_RES]->init(L"������ư2", 350 + 25 + UPDATEPOSX, 390 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, NULL);
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_AGL]->init(L"������ư2", 350 + 25 + UPDATEPOSX, 425 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, NULL);
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_FIG]->init(L"������ư2", 350 + 25 + UPDATEPOSX, 460 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, NULL);

	_ctrlButton[UNITEDITOR_BUTTON_LABEL_PWR]->init(L"������ư2", 350 + 25 + UPDATEPOSX, 510 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, NULL);
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_LDS]->init(L"������ư2", 350 + 25 + UPDATEPOSX, 545 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, NULL);
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_INT]->init(L"������ư2", 350 + 25 + UPDATEPOSX, 580 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, NULL);
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_DEX]->init(L"������ư2", 350 + 25 + UPDATEPOSX, 615 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, NULL);
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_LUK]->init(L"������ư2", 350 + 25 + UPDATEPOSX, 650 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, NULL);


	_ctrlButton[UNITEDITOR_BUTTON_LABEL_ENTERSCENARIO]->init(L"������ư2", 600 + 25 + UPDATEPOSX, 100 + 15, { 0, 0 }, { 0, 1 }, NULL);

	_ctrlButton[UNITEDITOR_BUTTON_LABEL_LV]->init(L"������ư2", 600 + 25 + UPDATEPOSX, 150 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, NULL);
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_MOVE]->init(L"������ư2", 600 + 25 + UPDATEPOSX, 185 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, NULL);
																											   
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_LVPERHP]->init(L"������ư2", 600 + 25 + UPDATEPOSX, 235 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, NULL);
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_LVPERMP]->init(L"������ư2", 600 + 25 + UPDATEPOSX, 270 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, NULL);
																 
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_LVPERATK]->init(L"������ư2", 600 + 25 + UPDATEPOSX, 320 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, NULL);
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_LVPERDEP]->init(L"������ư2", 600 + 25 + UPDATEPOSX, 355 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, NULL);
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_LVPERRES]->init(L"������ư2", 600 + 25 + UPDATEPOSX, 390 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, NULL);
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_LVPERAGL]->init(L"������ư2", 600 + 25 + UPDATEPOSX, 425 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, NULL);
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_LVPERFIG]->init(L"������ư2", 600 + 25 + UPDATEPOSX, 460 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, NULL);
																 
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_LVPERPWR]->init(L"������ư2", 600 + 25 + UPDATEPOSX, 510 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, NULL);
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_LVPERLDS]->init(L"������ư2", 600 + 25 + UPDATEPOSX, 545 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, NULL);
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_LVPERINT]->init(L"������ư2", 600 + 25 + UPDATEPOSX, 580 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, NULL);
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_LVPERDEX]->init(L"������ư2", 600 + 25 + UPDATEPOSX, 615 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, NULL);
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_LVPERLUK]->init(L"������ư2", 600 + 25 + UPDATEPOSX, 650 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, NULL);


	_ctrlButton[UNITEDITOR_BUTTON_LABEL_WEAPON]->init(L"������ư2", 850 + 25 + UPDATEPOSX, 470 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, NULL);
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_ARMOR]->init(L"������ư2", 850 + 25 + UPDATEPOSX, 540 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, NULL);
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_SUBITEM]->init(L"������ư2", 850 + 25 + UPDATEPOSX, 610 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, NULL);


	_ctrlButton[UNITEDITOR_BUTTON_LABEL_FILENAME]->init(L"������ư2", 1025 + 25 + UPDATEPOSX, 430 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, NULL);


	//prev, next
	_ctrlButton[UNITEDITOR_BUTTON_FACE_PREV]->init(L"������ư", 100 + 50 + UPDATEPOSX, 240 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, ctrlSelectFacePrev, this);
	_ctrlButton[UNITEDITOR_BUTTON_FACE_NEXT]->init(L"������ư", 200 + 50 + UPDATEPOSX, 240 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, ctrlSelectFaceNext, this);

	_ctrlButton[UNITEDITOR_BUTTON_NORMAL_PREV]->init(L"������ư", 100 + 50 + UPDATEPOSX, 440 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, ctrlSelectNormalPrev, this);
	_ctrlButton[UNITEDITOR_BUTTON_NORMAL_NEXT]->init(L"������ư", 200 + 50 + UPDATEPOSX, 440 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, ctrlSelectNormalNext, this);
	
	_ctrlButton[UNITEDITOR_BUTTON_COMBAT_PREV]->init(L"������ư", 100 + 50 + UPDATEPOSX, 640 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, ctrlSelectCombatPrev, this);
	_ctrlButton[UNITEDITOR_BUTTON_COMBAT_NEXT]->init(L"������ư", 200 + 50 + UPDATEPOSX, 640 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, ctrlSelectCombatNext, this);


	_ctrlButton[UNITEDITOR_BUTTON_WEAPON_PREV]->init(L"������ư2", 950 + 25 + UPDATEPOSX, 500 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, ctrlSelectWeaponPrev, this);
	_ctrlButton[UNITEDITOR_BUTTON_WEAPON_NEXT]->init(L"������ư2", 1000 + 25 + UPDATEPOSX, 500 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, ctrlSelectWeaponNext, this);

	_ctrlButton[UNITEDITOR_BUTTON_ARMOR_PREV]->init(L"������ư2", 950 + 25 + UPDATEPOSX, 570 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, ctrlSelectArmorPrev, this);
	_ctrlButton[UNITEDITOR_BUTTON_ARMOR_NEXT]->init(L"������ư2", 1000 + 25 + UPDATEPOSX, 570 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, ctrlSelectArmorNext, this);

	_ctrlButton[UNITEDITOR_BUTTON_SUBITEM_PREV]->init(L"������ư2", 950 + 25 + UPDATEPOSX, 640 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, ctrlSelectSubitemPrev, this);
	_ctrlButton[UNITEDITOR_BUTTON_SUBITEM_NEXT]->init(L"������ư2", 1000 + 25 + UPDATEPOSX, 640 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, ctrlSelectSubitemNext, this);

	//new, save, load, exit
	_ctrlButton[UNITEDITOR_BUTTON_DATA_NEW]->init(L"������ư", 1175 + 50 + UPDATEPOSX, 470 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, ctrlSelectDataNew, this);
	_ctrlButton[UNITEDITOR_BUTTON_DATA_LOAD]->init(L"������ư", 1175 + 50 + UPDATEPOSX, 510 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, ctrlSelectDataLoad, this);
	_ctrlButton[UNITEDITOR_BUTTON_DATA_SAVE]->init(L"������ư", 1175 + 50 + UPDATEPOSX, 550 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, ctrlSelectDataSave, this);
	_ctrlButton[UNITEDITOR_BUTTON_DATA_EXIT]->init(L"������ư", 1175 + 50 + UPDATEPOSX, 640 + 15 + UPDATEPOSY, { 0, 0 }, { 0, 1 }, NULL);


	//--------------------------------------------------------------------------------------------
	//��ư �̸� ǥ��
	_stprintf(_strButton[UNITEDITOR_BUTTON_LABEL_FILELIST], L"���ָ��");

	_stprintf(_strButton[UNITEDITOR_BUTTON_LABEL_NAME], L"�̸�");

	_stprintf(_strButton[UNITEDITOR_BUTTON_LABEL_FAMILY], L"�δ�");
	_stprintf(_strButton[UNITEDITOR_BUTTON_LABEL_AOS], L"�Ӽ�");

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


	_stprintf(_strButton[UNITEDITOR_BUTTON_LABEL_ENTERSCENARIO], L"�������ɽó�����");

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
	_stprintf(_strButton[UNITEDITOR_BUTTON_COMBAT_PREV], L"PREV");
	_stprintf(_strButton[UNITEDITOR_BUTTON_COMBAT_NEXT], L"NEXT");
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
	_strEditBox[UNITEDITOR_STREDITBOX_DATA_NAME]->setRect(RectMake(450 + UPDATEPOSX, 100 + UPDATEPOSY, 100, 30));
	_strEditBox[UNITEDITOR_STREDITBOX_DATA_FAMILY]->setRect(RectMake(450 + UPDATEPOSX, 150 + UPDATEPOSY, 100, 30));
	_strEditBox[UNITEDITOR_STREDITBOX_DATA_AOS]->setRect(RectMake(450 + UPDATEPOSX, 185 + UPDATEPOSY, 100, 30));


	_strEditBox[UNITEDITOR_STREDITBOX_DATA_FILENAME]->setRect(RectMake(1125 + UPDATEPOSX, 430 + UPDATEPOSY, 150, 30));


	for (int i = 0; i < UNITEDITOR_NUMEDITBOX_MAX; i++)
	{
		_numEditBox[i] = new editbox;
		_numEditBox[i]->init();
		_numEditBox[i]->setOnlyNum(TRUE);
		_numEditBox[i]->setMinMax(0, 200);
	}
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_HP]->setRect(RectMake(450 + UPDATEPOSX, 235 + UPDATEPOSY, 100, 30));
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_MP]->setRect(RectMake(450 + UPDATEPOSX, 270 + UPDATEPOSY, 100, 30));

	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_ATK]->setRect(RectMake(450 + UPDATEPOSX, 320 + UPDATEPOSY, 100, 30));
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_DEP]->setRect(RectMake(450 + UPDATEPOSX, 355 + UPDATEPOSY, 100, 30));
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_RES]->setRect(RectMake(450 + UPDATEPOSX, 390 + UPDATEPOSY, 100, 30));
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_AGL]->setRect(RectMake(450 + UPDATEPOSX, 425 + UPDATEPOSY, 100, 30));
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_FIG]->setRect(RectMake(450 + UPDATEPOSX, 460 + UPDATEPOSY, 100, 30));

	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_PWR]->setRect(RectMake(450 + UPDATEPOSX, 510 + UPDATEPOSY, 100, 30));
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LDS]->setRect(RectMake(450 + UPDATEPOSX, 545 + UPDATEPOSY, 100, 30));
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_INT]->setRect(RectMake(450 + UPDATEPOSX, 580 + UPDATEPOSY, 100, 30));
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_DEX]->setRect(RectMake(450 + UPDATEPOSX, 615 + UPDATEPOSY, 100, 30));
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LUK]->setRect(RectMake(450 + UPDATEPOSX, 650 + UPDATEPOSY, 100, 30));


	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_ENTERSCENARIO]->setRect(RectMake(700 + UPDATEPOSX, 100 + UPDATEPOSY, 100, 30));

	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LV]->setRect(RectMake(700 + UPDATEPOSX, 150 + UPDATEPOSY, 100, 30));
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_MOVE]->setRect(RectMake(700 + UPDATEPOSX, 185 + UPDATEPOSY, 100, 30));

	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERHP]->setRect(RectMake(700 + UPDATEPOSX, 235 + UPDATEPOSY, 100, 30));
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERMP]->setRect(RectMake(700 + UPDATEPOSX, 270 + UPDATEPOSY, 100, 30));

	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERATK]->setRect(RectMake(700 + UPDATEPOSX, 320 + UPDATEPOSY, 100, 30));
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERDEP]->setRect(RectMake(700 + UPDATEPOSX, 355 + UPDATEPOSY, 100, 30));
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERRES]->setRect(RectMake(700 + UPDATEPOSX, 390 + UPDATEPOSY, 100, 30));
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERAGL]->setRect(RectMake(700 + UPDATEPOSX, 425 + UPDATEPOSY, 100, 30));
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERFIG]->setRect(RectMake(700 + UPDATEPOSX, 460 + UPDATEPOSY, 100, 30));

	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERPWR]->setRect(RectMake(700 + UPDATEPOSX, 510 + UPDATEPOSY, 100, 30));
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERLDS]->setRect(RectMake(700 + UPDATEPOSX, 545 + UPDATEPOSY, 100, 30));
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERINT]->setRect(RectMake(700 + UPDATEPOSX, 580 + UPDATEPOSY, 100, 30));
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERDEX]->setRect(RectMake(700 + UPDATEPOSX, 615 + UPDATEPOSY, 100, 30));
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERLUK]->setRect(RectMake(700 + UPDATEPOSX, 650 + UPDATEPOSY, 100, 30));
}
void sceneUnitEditor::initRangeRect(void)
{
	for (int i = 0; i < RANGESIZEX; i++)
	{
		for (int j = 0; j < RANGESIZEY; j++)
		{
			_atkRange[i][j].rc = RectMake(
				850 + i * TILEWIDTH / 2 + UPDATEPOSX,
				100 + j * TILEHEIGHT / 2 + UPDATEPOSY,
				TILEWIDTH / 2,
				TILEHEIGHT / 2);

			_atkRange[i][j].clicked = FALSE;
		}
	}
}

//~init functions
//-----------------------------------------------------------------------------------------
//other functions
void sceneUnitEditor::btnSetup(void)
{
	//_btnSave = CreateWindow("button", "����", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 700, 500, 100, 30,
	//	_hWnd, HMENU(0), _hInstance, NULL);
}

void sceneUnitEditor::rectSketch(void)
{
	Rectangle(getMemDC(), 100 + UPDATEPOSX, 100 + UPDATEPOSY, 300 + UPDATEPOSX, 228 + UPDATEPOSY);	//���̹���
	Rectangle(getMemDC(), 100 + UPDATEPOSX, 300 + UPDATEPOSY, 300 + UPDATEPOSX, 428 + UPDATEPOSY);	//�����̹���
	Rectangle(getMemDC(), 100 + UPDATEPOSX, 500 + UPDATEPOSY, 300 + UPDATEPOSX, 628 + UPDATEPOSY);	//�����̹���

	Rectangle(getMemDC(), 100 + UPDATEPOSX, 240 + UPDATEPOSY, 300 + UPDATEPOSX, 270 + UPDATEPOSY);	//����������ư
	Rectangle(getMemDC(), 100 + UPDATEPOSX, 440 + UPDATEPOSY, 300 + UPDATEPOSX, 470 + UPDATEPOSY);	//����������ư
	Rectangle(getMemDC(), 100 + UPDATEPOSX, 640 + UPDATEPOSY, 300 + UPDATEPOSX, 670 + UPDATEPOSY);	//����������ư


	Rectangle(getMemDC(), 350 + UPDATEPOSX, 100 + UPDATEPOSY, 414 + UPDATEPOSX, 130 + UPDATEPOSY);	//�̸�

	Rectangle(getMemDC(), 350 + UPDATEPOSX, 150 + UPDATEPOSY, 414 + UPDATEPOSX, 180 + UPDATEPOSY);	//�δ�
	Rectangle(getMemDC(), 350 + UPDATEPOSX, 185 + UPDATEPOSY, 414 + UPDATEPOSX, 215 + UPDATEPOSY);	//�Ӽ�

	Rectangle(getMemDC(), 350 + UPDATEPOSX, 235 + UPDATEPOSY, 414 + UPDATEPOSX, 265 + UPDATEPOSY);	//HP
	Rectangle(getMemDC(), 350 + UPDATEPOSX, 270 + UPDATEPOSY, 414 + UPDATEPOSX, 300 + UPDATEPOSY);	//MP

	Rectangle(getMemDC(), 350 + UPDATEPOSX, 320 + UPDATEPOSY, 414 + UPDATEPOSX, 350 + UPDATEPOSY);	//���ݷ�
	Rectangle(getMemDC(), 350 + UPDATEPOSX, 355 + UPDATEPOSY, 414 + UPDATEPOSX, 385 + UPDATEPOSY);	//���ŷ�
	Rectangle(getMemDC(), 350 + UPDATEPOSX, 390 + UPDATEPOSY, 414 + UPDATEPOSX, 420 + UPDATEPOSY);	//����
	Rectangle(getMemDC(), 350 + UPDATEPOSX, 425 + UPDATEPOSY, 414 + UPDATEPOSX, 455 + UPDATEPOSY);	//���߷�
	Rectangle(getMemDC(), 350 + UPDATEPOSX, 460 + UPDATEPOSY, 414 + UPDATEPOSX, 490 + UPDATEPOSY);	//���

	Rectangle(getMemDC(), 350 + UPDATEPOSX, 510 + UPDATEPOSY, 414 + UPDATEPOSX, 540 + UPDATEPOSY);	//����
	Rectangle(getMemDC(), 350 + UPDATEPOSX, 545 + UPDATEPOSY, 414 + UPDATEPOSX, 575 + UPDATEPOSY);	//����
	Rectangle(getMemDC(), 350 + UPDATEPOSX, 580 + UPDATEPOSY, 414 + UPDATEPOSX, 610 + UPDATEPOSY);	//���
	Rectangle(getMemDC(), 350 + UPDATEPOSX, 615 + UPDATEPOSY, 414 + UPDATEPOSX, 645 + UPDATEPOSY);	//��ø
	Rectangle(getMemDC(), 350 + UPDATEPOSX, 650 + UPDATEPOSY, 414 + UPDATEPOSX, 680 + UPDATEPOSY);	//��


	Rectangle(getMemDC(), 450 + UPDATEPOSX, 100 + UPDATEPOSY, 550 + UPDATEPOSX, 130 + UPDATEPOSY);	//�������Է�

	Rectangle(getMemDC(), 450 + UPDATEPOSX, 150 + UPDATEPOSY, 550 + UPDATEPOSX, 180 + UPDATEPOSY);	//�������Է�
	Rectangle(getMemDC(), 450 + UPDATEPOSX, 185 + UPDATEPOSY, 550 + UPDATEPOSX, 215 + UPDATEPOSY);	//�������Է�

	Rectangle(getMemDC(), 450 + UPDATEPOSX, 235 + UPDATEPOSY, 550 + UPDATEPOSX, 265 + UPDATEPOSY);	//�������Է�
	Rectangle(getMemDC(), 450 + UPDATEPOSX, 270 + UPDATEPOSY, 550 + UPDATEPOSX, 300 + UPDATEPOSY);	//�������Է�

	Rectangle(getMemDC(), 450 + UPDATEPOSX, 320 + UPDATEPOSY, 550 + UPDATEPOSX, 350 + UPDATEPOSY);	//�������Է�
	Rectangle(getMemDC(), 450 + UPDATEPOSX, 355 + UPDATEPOSY, 550 + UPDATEPOSX, 385 + UPDATEPOSY);	//�������Է�
	Rectangle(getMemDC(), 450 + UPDATEPOSX, 390 + UPDATEPOSY, 550 + UPDATEPOSX, 420 + UPDATEPOSY);	//�������Է�
	Rectangle(getMemDC(), 450 + UPDATEPOSX, 425 + UPDATEPOSY, 550 + UPDATEPOSX, 455 + UPDATEPOSY);	//�������Է�
	Rectangle(getMemDC(), 450 + UPDATEPOSX, 460 + UPDATEPOSY, 550 + UPDATEPOSX, 490 + UPDATEPOSY);	//�������Է�

	Rectangle(getMemDC(), 450 + UPDATEPOSX, 510 + UPDATEPOSY, 550 + UPDATEPOSX, 540 + UPDATEPOSY);	//�������Է�
	Rectangle(getMemDC(), 450 + UPDATEPOSX, 545 + UPDATEPOSY, 550 + UPDATEPOSX, 575 + UPDATEPOSY);	//�������Է�
	Rectangle(getMemDC(), 450 + UPDATEPOSX, 580 + UPDATEPOSY, 550 + UPDATEPOSX, 610 + UPDATEPOSY);	//�������Է�
	Rectangle(getMemDC(), 450 + UPDATEPOSX, 615 + UPDATEPOSY, 550 + UPDATEPOSX, 645 + UPDATEPOSY);	//�������Է�
	Rectangle(getMemDC(), 450 + UPDATEPOSX, 650 + UPDATEPOSY, 550 + UPDATEPOSX, 680 + UPDATEPOSY);	//�������Է�


	Rectangle(getMemDC(), 850 + UPDATEPOSX, 470 + UPDATEPOSY, 914 + UPDATEPOSX, 500 + UPDATEPOSY);		//����
	Rectangle(getMemDC(), 850 + UPDATEPOSX, 540 + UPDATEPOSY, 914 + UPDATEPOSX, 570 + UPDATEPOSY);		//��
	Rectangle(getMemDC(), 850 + UPDATEPOSX, 610 + UPDATEPOSY, 914 + UPDATEPOSX, 640 + UPDATEPOSY);		//����

	Rectangle(getMemDC(), 950 + UPDATEPOSX, 470 + UPDATEPOSY, 1050 + UPDATEPOSX, 530 + UPDATEPOSY);		//�̸�
	Rectangle(getMemDC(), 950 + UPDATEPOSX, 540 + UPDATEPOSY, 1050 + UPDATEPOSX, 600 + UPDATEPOSY);		//�̸�
	Rectangle(getMemDC(), 950 + UPDATEPOSX, 610 + UPDATEPOSY, 1050 + UPDATEPOSX, 670 + UPDATEPOSY);		//�̸�

	Rectangle(getMemDC(), 1055 + UPDATEPOSX, 470 + UPDATEPOSY, 1115 + UPDATEPOSX, 530 + UPDATEPOSY);	//�̹���
	Rectangle(getMemDC(), 1055 + UPDATEPOSX, 540 + UPDATEPOSY, 1115 + UPDATEPOSX, 600 + UPDATEPOSY);	//�̹���
	Rectangle(getMemDC(), 1055 + UPDATEPOSX, 610 + UPDATEPOSY, 1115 + UPDATEPOSX, 670 + UPDATEPOSY);	//�̹���

	//Rectangle(getMemDC(), 700 + UPDATEPOSX, 470 + UPDATEPOSY, 1000 + UPDATEPOSX, 670 + UPDATEPOSY);		//���ּ���
	//
	//Rectangle(getMemDC(), 1040 + UPDATEPOSX, 100 + UPDATEPOSY, 1400 + UPDATEPOSX, 400 + UPDATEPOSY);	//�����ۻ󼼼����
	//
	//Rectangle(getMemDC(), 1040 + UPDATEPOSX, 430 + UPDATEPOSY, 1240 + UPDATEPOSX, 670 + UPDATEPOSY);	//��ų��

	Rectangle(getMemDC(), 1175 + UPDATEPOSX, 470 + UPDATEPOSY, 1275 + UPDATEPOSX, 500 + UPDATEPOSY);	//���θ����
	Rectangle(getMemDC(), 1175 + UPDATEPOSX, 510 + UPDATEPOSY, 1275 + UPDATEPOSX, 540 + UPDATEPOSY);	//���̺�
	Rectangle(getMemDC(), 1175 + UPDATEPOSX, 550 + UPDATEPOSY, 1275 + UPDATEPOSX, 580 + UPDATEPOSY);	//�ε�
	Rectangle(getMemDC(), 1175 + UPDATEPOSX, 640 + UPDATEPOSY, 1275 + UPDATEPOSX, 670 + UPDATEPOSY);	//����


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
	TCHAR strFaceKey[100];
	_stprintf(strFaceKey, L"face %05d", _faceNum);
	//image* img = IMAGEMANAGER->findImage(strFaceKey);	
	IMAGEMANAGER->findImage(strFaceKey)->render(getMemDC(), 100 + UPDATEPOSX, 100 + UPDATEPOSY);

	TCHAR strNormalKey[100];
	_stprintf(strNormalKey, L"���� %05d", _normalNum);
	IMAGEMANAGER->findImage(strNormalKey)->render(getMemDC(), 100 + UPDATEPOSX, 300 + UPDATEPOSY);
	//IMAGEMANAGER->findImage(strNormalKey)->frameRender(getMemDC(), 100, 300, 0, 0);

	TCHAR strCombatKey[100];
	_stprintf(strCombatKey, L"���� %05d", _combatNum);
	IMAGEMANAGER->findImage(strCombatKey)->render(getMemDC(), 100 + UPDATEPOSX, 500 + UPDATEPOSY);
	//IMAGEMANAGER->findImage(strCombatKey)->frameRender(getMemDC(), 100, 300, 0, 0);

	_unit->setImages(strFaceKey, strNormalKey, strCombatKey);		// �̹��� ��
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

void sceneUnitEditor::newUnit(void)
{
	this->init();

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
	TCHAR filename[100] = L"UnitData/";

	for (int i = 0; i < _vUnits.size(); i++)
	{
		if (_vUnits[i].clicked)
		{
			_tcscat(filename, _vUnits[i].str);
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

	ReadFile(file, _unit, sizeof(Unit), &read, NULL);

	CloseHandle(file);

	//�ε� ������ ȭ�� ���� �ѹ� ������� �Ʒ� �̸� �����ֵ��� ���� �Լ� ���� ȣ���ϵ���
	//test
	_strEditBox[UNITEDITOR_STREDITBOX_DATA_NAME]->setStr(_unit->getStatus().name);

	_strEditBox[UNITEDITOR_STREDITBOX_DATA_FAMILY]->setStr(_unit->getStatus().family);
	_strEditBox[UNITEDITOR_STREDITBOX_DATA_AOS]->setStr(_unit->getStatus().aos);

	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_HP]->setStrNum(_unit->getStatus().HPMax);
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_MP]->setStrNum(_unit->getStatus().MPMax);

	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_ATK]->setStrNum(_unit->getStatus().Atk);
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_DEP]->setStrNum(_unit->getStatus().Dep);
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_RES]->setStrNum(_unit->getStatus().Res);
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_AGL]->setStrNum(_unit->getStatus().Agl);
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_FIG]->setStrNum(_unit->getStatus().Fig);

	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_PWR]->setStrNum(_unit->getStatus().Pwr);
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LDS]->setStrNum(_unit->getStatus().Lds);
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_INT]->setStrNum(_unit->getStatus().Int);
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_DEX]->setStrNum(_unit->getStatus().Dex);
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LUK]->setStrNum(_unit->getStatus().Luk);


	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_ENTERSCENARIO]->setStrNum(_unit->getStatus().enterScenario);

	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LV]->setStrNum(_unit->getStatus().level);
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_MOVE]->setStrNum(_unit->getStatus().movePoint);

	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERHP]->setStrNum(_unit->getStatus().LvPerHPMax);;
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERMP]->setStrNum(_unit->getStatus().LvPerMPMax);;

	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERATK]->setStrNum(_unit->getStatus().Atk);
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERDEP]->setStrNum(_unit->getStatus().Dep);
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERRES]->setStrNum(_unit->getStatus().Res);
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERAGL]->setStrNum(_unit->getStatus().Agl);
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERFIG]->setStrNum(_unit->getStatus().Fig);

	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERPWR]->setStrNum(_unit->getStatus().Pwr);
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERLDS]->setStrNum(_unit->getStatus().Lds);
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERINT]->setStrNum(_unit->getStatus().Int);
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERDEX]->setStrNum(_unit->getStatus().Dex);
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERLUK]->setStrNum(_unit->getStatus().Luk);
}
void sceneUnitEditor::saveUnit(void)
{
	_tcscpy_s(_tempStatus.name, _strEditBox[UNITEDITOR_STREDITBOX_DATA_NAME]->getStr());
	_tcscpy_s(_tempStatus.family, _strEditBox[UNITEDITOR_STREDITBOX_DATA_FAMILY]->getStr());
	_tcscpy_s(_tempStatus.aos, _strEditBox[UNITEDITOR_STREDITBOX_DATA_AOS]->getStr());

	_tempStatus.isLive			= TRUE;
	_tempStatus.exp				= 0;
	_tempStatus.expMax			= 100;
	_tempStatus.HP				= _numEditBox[UNITEDITOR_NUMEDITBOX_DATA_HP]->getStrNum();
	_tempStatus.HPMax			= _numEditBox[UNITEDITOR_NUMEDITBOX_DATA_HP]->getStrNum();
	_tempStatus.MP				= _numEditBox[UNITEDITOR_NUMEDITBOX_DATA_MP]->getStrNum();
	_tempStatus.MPMax			= _numEditBox[UNITEDITOR_NUMEDITBOX_DATA_MP]->getStrNum();
	_tempStatus.Atk				= _numEditBox[UNITEDITOR_NUMEDITBOX_DATA_ATK]->getStrNum();
	_tempStatus.Dep				= _numEditBox[UNITEDITOR_NUMEDITBOX_DATA_DEP]->getStrNum();
	_tempStatus.Res				= _numEditBox[UNITEDITOR_NUMEDITBOX_DATA_RES]->getStrNum();
	_tempStatus.Agl				= _numEditBox[UNITEDITOR_NUMEDITBOX_DATA_AGL]->getStrNum();
	_tempStatus.Fig				= _numEditBox[UNITEDITOR_NUMEDITBOX_DATA_FIG]->getStrNum();
	_tempStatus.Pwr				= _numEditBox[UNITEDITOR_NUMEDITBOX_DATA_PWR]->getStrNum();
	_tempStatus.Lds				= _numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LDS]->getStrNum();
	_tempStatus.Int				= _numEditBox[UNITEDITOR_NUMEDITBOX_DATA_INT]->getStrNum();
	_tempStatus.Dex				= _numEditBox[UNITEDITOR_NUMEDITBOX_DATA_DEX]->getStrNum();
	_tempStatus.Luk				= _numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LUK]->getStrNum();

	_tempStatus.enterScenario	= _numEditBox[UNITEDITOR_NUMEDITBOX_DATA_ENTERSCENARIO]->getStrNum();
	_tempStatus.level			= _numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LV]->getStrNum();
	_tempStatus.movePoint		= _numEditBox[UNITEDITOR_NUMEDITBOX_DATA_MOVE]->getStrNum();
	_tempStatus.LvPerHPMax		= _numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERHP]->getStrNum();;
	_tempStatus.LvPerMPMax		= _numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERMP]->getStrNum();;
	_tempStatus.LvPerAtk		= _numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERATK]->getStrNum();
	_tempStatus.LvPerDep		= _numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERDEP]->getStrNum();
	_tempStatus.LvPerRes		= _numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERRES]->getStrNum();
	_tempStatus.LvPerAgl		= _numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERAGL]->getStrNum();
	_tempStatus.LvPerFig		= _numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERFIG]->getStrNum();
	_tempStatus.LvPerPwr		= _numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERPWR]->getStrNum();
	_tempStatus.LvPerLds		= _numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERLDS]->getStrNum();
	_tempStatus.LvPerInt		= _numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERINT]->getStrNum();
	_tempStatus.LvPerDex		= _numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERDEX]->getStrNum();
	_tempStatus.LvPerLuk		= _numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERLUK]->getStrNum();

	

	BOOL tempRange[RANGESIZEX][RANGESIZEY];
	for (int i = 0; i < RANGESIZEX; i++)
	{
		for (int j = 0; j < RANGESIZEY; j++)
		{
			tempRange[i][j] = _atkRange[i][j].clicked;
		}
	}

	_unit->setStatus(_tempStatus);
	_unit->setAtkRange(tempRange);

	HANDLE file;
	DWORD write;
	TCHAR tempStr[1024] = L"UnitData/";
	_tcscat(tempStr, _strEditBox[UNITEDITOR_STREDITBOX_DATA_FILENAME]->getStr());
	_tcscat(tempStr, L".dat");

	file = CreateFile(tempStr, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, _unit, sizeof(Unit), &write, NULL);

	CloseHandle(file);
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
void sceneUnitEditor::ctrlSelectFacePrev(void* obj)
{
	sceneUnitEditor* unitEditor = (sceneUnitEditor*)obj;
	unitEditor->setFacePrev();
}
void sceneUnitEditor::ctrlSelectFaceNext(void* obj)
{
	sceneUnitEditor* unitEditor = (sceneUnitEditor*)obj;
	unitEditor->setFaceNext();
}
void sceneUnitEditor::ctrlSelectNormalPrev(void* obj)
{
	sceneUnitEditor* unitEditor = (sceneUnitEditor*)obj;
	unitEditor->setNormalPrev();
}
void sceneUnitEditor::ctrlSelectNormalNext(void* obj)
{
	sceneUnitEditor* unitEditor = (sceneUnitEditor*)obj;
	unitEditor->setNormalNext();
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

//~callback functions
//-----------------------------------------------------------------------------------------
