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
	
	initButton();
	initValues();
	initEditbox();

	return S_OK;
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
}

void sceneUnitEditor::render(void)
{
	rectSketch();		// 컨트롤 박스들 위치 도안
	editBoxRender();
	unitImageRender();

	for (int i = 0; i < UNITEDITOR_BUTTON_MAX; i++)
	{
		_ctrlButton[i]->render();
		TextOut(getMemDC(), _ctrlButton[i]->getRect().left, _ctrlButton[i]->getRect().top, _strButton[i], _tcslen(_strButton[i]));
	}
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
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_NAME]->init(L"맵툴버튼2", 350 + 25, 100 + 15, { 0, 0 }, { 0, 1 }, NULL);

	_ctrlButton[UNITEDITOR_BUTTON_LABEL_FAMILY]->init(L"맵툴버튼2", 350 + 25, 150 + 15, { 0, 0 }, { 0, 1 }, NULL);
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_AOS]->init(L"맵툴버튼2", 350 + 25, 185 + 15, { 0, 0 }, { 0, 1 }, NULL);
																											   
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_HP]->init(L"맵툴버튼2", 350 + 25, 235 + 15, { 0, 0 }, { 0, 1 }, NULL);
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_MP]->init(L"맵툴버튼2", 350 + 25, 270 + 15, { 0, 0 }, { 0, 1 }, NULL);

	_ctrlButton[UNITEDITOR_BUTTON_LABEL_ATK]->init(L"맵툴버튼2", 350 + 25, 320 + 15, { 0, 0 }, { 0, 1 }, NULL);
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_DEP]->init(L"맵툴버튼2", 350 + 25, 355 + 15, { 0, 0 }, { 0, 1 }, NULL);
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_RES]->init(L"맵툴버튼2", 350 + 25, 390 + 15, { 0, 0 }, { 0, 1 }, NULL);
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_AGL]->init(L"맵툴버튼2", 350 + 25, 425 + 15, { 0, 0 }, { 0, 1 }, NULL);
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_FIG]->init(L"맵툴버튼2", 350 + 25, 460 + 15, { 0, 0 }, { 0, 1 }, NULL);

	_ctrlButton[UNITEDITOR_BUTTON_LABEL_PWR]->init(L"맵툴버튼2", 350 + 25, 510 + 15, { 0, 0 }, { 0, 1 }, NULL);
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_LDS]->init(L"맵툴버튼2", 350 + 25, 545 + 15, { 0, 0 }, { 0, 1 }, NULL);
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_INT]->init(L"맵툴버튼2", 350 + 25, 580 + 15, { 0, 0 }, { 0, 1 }, NULL);
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_DEX]->init(L"맵툴버튼2", 350 + 25, 615 + 15, { 0, 0 }, { 0, 1 }, NULL);
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_LUK]->init(L"맵툴버튼2", 350 + 25, 650 + 15, { 0, 0 }, { 0, 1 }, NULL);


	_ctrlButton[UNITEDITOR_BUTTON_LABEL_ENTERSCENARIO]->init(L"맵툴버튼2", 600 + 25, 100 + 15, { 0, 0 }, { 0, 1 }, NULL);

	_ctrlButton[UNITEDITOR_BUTTON_LABEL_LV]->init(L"맵툴버튼2", 600 + 25, 150 + 15, { 0, 0 }, { 0, 1 }, NULL);
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_MOVE]->init(L"맵툴버튼2", 600 + 25, 185 + 15, { 0, 0 }, { 0, 1 }, NULL);
																											   
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_LVPERHP]->init(L"맵툴버튼2", 600 + 25, 235 + 15, { 0, 0 }, { 0, 1 }, NULL);
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_LVPERMP]->init(L"맵툴버튼2", 600 + 25, 270 + 15, { 0, 0 }, { 0, 1 }, NULL);
																 
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_LVPERATK]->init(L"맵툴버튼2", 600 + 25, 320 + 15, { 0, 0 }, { 0, 1 }, NULL);
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_LVPERDEP]->init(L"맵툴버튼2", 600 + 25, 355 + 15, { 0, 0 }, { 0, 1 }, NULL);
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_LVPERRES]->init(L"맵툴버튼2", 600 + 25, 390 + 15, { 0, 0 }, { 0, 1 }, NULL);
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_LVPERAGL]->init(L"맵툴버튼2", 600 + 25, 425 + 15, { 0, 0 }, { 0, 1 }, NULL);
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_LVPERFIG]->init(L"맵툴버튼2", 600 + 25, 460 + 15, { 0, 0 }, { 0, 1 }, NULL);
																 
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_LVPERPWR]->init(L"맵툴버튼2", 600 + 25, 510 + 15, { 0, 0 }, { 0, 1 }, NULL);
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_LVPERLDS]->init(L"맵툴버튼2", 600 + 25, 545 + 15, { 0, 0 }, { 0, 1 }, NULL);
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_LVPERINT]->init(L"맵툴버튼2", 600 + 25, 580 + 15, { 0, 0 }, { 0, 1 }, NULL);
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_LVPERDEX]->init(L"맵툴버튼2", 600 + 25, 615 + 15, { 0, 0 }, { 0, 1 }, NULL);
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_LVPERLUK]->init(L"맵툴버튼2", 600 + 25, 650 + 15, { 0, 0 }, { 0, 1 }, NULL);


	//prev, next
	_ctrlButton[UNITEDITOR_BUTTON_FACE_PREV]->init(L"맵툴버튼", 100 + 50, 240 + 15, { 0, 0 }, { 0, 1 }, ctrlSelectFacePrev, this);
	_ctrlButton[UNITEDITOR_BUTTON_FACE_NEXT]->init(L"맵툴버튼", 200 + 50, 240 + 15, { 0, 0 }, { 0, 1 }, ctrlSelectFaceNext, this);

	_ctrlButton[UNITEDITOR_BUTTON_NORMAL_PREV]->init(L"맵툴버튼", 100 + 50, 440 + 15, { 0, 0 }, { 0, 1 }, ctrlSelectNormalPrev, this);
	_ctrlButton[UNITEDITOR_BUTTON_NORMAL_NEXT]->init(L"맵툴버튼", 200 + 50, 440 + 15, { 0, 0 }, { 0, 1 }, ctrlSelectNormalNext, this);
	
	_ctrlButton[UNITEDITOR_BUTTON_COMBAT_PREV]->init(L"맵툴버튼", 100 + 50, 640 + 15, { 0, 0 }, { 0, 1 }, ctrlSelectCombatPrev, this);
	_ctrlButton[UNITEDITOR_BUTTON_COMBAT_NEXT]->init(L"맵툴버튼", 200 + 50, 640 + 15, { 0, 0 }, { 0, 1 }, ctrlSelectCombatNext, this);

	_ctrlButton[UNITEDITOR_BUTTON_WEAPON_PREV]->init(L"맵툴버튼2", 800 + 25, 230 + 15, { 0, 0 }, { 0, 1 }, ctrlSelectWeaponPrev, this);
	_ctrlButton[UNITEDITOR_BUTTON_WEAPON_NEXT]->init(L"맵툴버튼2", 850 + 25, 230 + 15, { 0, 0 }, { 0, 1 }, ctrlSelectWeaponNext, this);

	_ctrlButton[UNITEDITOR_BUTTON_ARMOR_PREV]->init(L"맵툴버튼2", 800 + 25, 310 + 15, { 0, 0 }, { 0, 1 }, ctrlSelectArmorPrev, this);
	_ctrlButton[UNITEDITOR_BUTTON_ARMOR_NEXT]->init(L"맵툴버튼2", 850 + 25, 310 + 15, { 0, 0 }, { 0, 1 }, ctrlSelectArmorNext, this);

	_ctrlButton[UNITEDITOR_BUTTON_SUBITEM_PREV]->init(L"맵툴버튼2", 800 + 25, 390 + 15, { 0, 0 }, { 0, 1 }, ctrlSelectSubitemPrev, this);
	_ctrlButton[UNITEDITOR_BUTTON_SUBITEM_NEXT]->init(L"맵툴버튼2", 850 + 25, 390 + 15, { 0, 0 }, { 0, 1 }, ctrlSelectSubitemNext, this);

	//new, save, load, exit
	_ctrlButton[UNITEDITOR_BUTTON_DATA_NEW]->init(L"맵툴버튼", 1300 + 50, 430 + 15, { 0, 0 }, { 0, 1 }, ctrlSelectDataNew, this);
	_ctrlButton[UNITEDITOR_BUTTON_DATA_LOAD]->init(L"맵툴버튼", 1300 + 50, 490 + 15, { 0, 0 }, { 0, 1 }, ctrlSelectDataLoad, this);
	_ctrlButton[UNITEDITOR_BUTTON_DATA_SAVE]->init(L"맵툴버튼", 1300 + 50, 550 + 15, { 0, 0 }, { 0, 1 }, ctrlSelectDataSave, this);


	//--------------------------------------------------------------------------------------------
	//버튼 이름 표시

	_stprintf(_strButton[UNITEDITOR_BUTTON_LABEL_NAME], L"이름");

	_stprintf(_strButton[UNITEDITOR_BUTTON_LABEL_FAMILY], L"부대");
	_stprintf(_strButton[UNITEDITOR_BUTTON_LABEL_AOS], L"속성");

	_stprintf(_strButton[UNITEDITOR_BUTTON_LABEL_HP], L"체력");
	_stprintf(_strButton[UNITEDITOR_BUTTON_LABEL_MP], L"마력");

	_stprintf(_strButton[UNITEDITOR_BUTTON_LABEL_ATK], L"공격력");
	_stprintf(_strButton[UNITEDITOR_BUTTON_LABEL_DEP], L"방어력");
	_stprintf(_strButton[UNITEDITOR_BUTTON_LABEL_RES], L"정신력");
	_stprintf(_strButton[UNITEDITOR_BUTTON_LABEL_AGL], L"순발력");
	_stprintf(_strButton[UNITEDITOR_BUTTON_LABEL_FIG], L"사기");

	_stprintf(_strButton[UNITEDITOR_BUTTON_LABEL_PWR], L"무력");
	_stprintf(_strButton[UNITEDITOR_BUTTON_LABEL_LDS], L"통솔");
	_stprintf(_strButton[UNITEDITOR_BUTTON_LABEL_INT], L"지력");
	_stprintf(_strButton[UNITEDITOR_BUTTON_LABEL_DEX], L"민첩");
	_stprintf(_strButton[UNITEDITOR_BUTTON_LABEL_LUK], L"행운");


	_stprintf(_strButton[UNITEDITOR_BUTTON_LABEL_ENTERSCENARIO], L"출전가능시나리오");

	_stprintf(_strButton[UNITEDITOR_BUTTON_LABEL_LV], L"레벨");
	_stprintf(_strButton[UNITEDITOR_BUTTON_LABEL_MOVE], L"이동력");

	_stprintf(_strButton[UNITEDITOR_BUTTON_LABEL_LVPERHP], L"레벨당체력");
	_stprintf(_strButton[UNITEDITOR_BUTTON_LABEL_LVPERMP], L"레벨당마력");

	_stprintf(_strButton[UNITEDITOR_BUTTON_LABEL_LVPERATK], L"레벨당공격력");
	_stprintf(_strButton[UNITEDITOR_BUTTON_LABEL_LVPERDEP], L"레벨당방어력");
	_stprintf(_strButton[UNITEDITOR_BUTTON_LABEL_LVPERRES], L"레벨당정신력");
	_stprintf(_strButton[UNITEDITOR_BUTTON_LABEL_LVPERAGL], L"레벨당순발력");
	_stprintf(_strButton[UNITEDITOR_BUTTON_LABEL_LVPERFIG], L"레벨당사기");

	_stprintf(_strButton[UNITEDITOR_BUTTON_LABEL_LVPERPWR], L"레벨당무력");
	_stprintf(_strButton[UNITEDITOR_BUTTON_LABEL_LVPERLDS], L"레벨당통솔");
	_stprintf(_strButton[UNITEDITOR_BUTTON_LABEL_LVPERINT], L"레벨당지력");
	_stprintf(_strButton[UNITEDITOR_BUTTON_LABEL_LVPERDEX], L"레벨당민첩");
	_stprintf(_strButton[UNITEDITOR_BUTTON_LABEL_LVPERLUK], L"레벨당행운");


	_stprintf(_strButton[UNITEDITOR_BUTTON_DATA_NEW], L"NEW");
	_stprintf(_strButton[UNITEDITOR_BUTTON_DATA_LOAD], L"LOAD");
	_stprintf(_strButton[UNITEDITOR_BUTTON_DATA_SAVE], L"SAVE");
	_stprintf(_strButton[UNITEDITOR_BUTTON_FACE_PREV], L"PREV");
	_stprintf(_strButton[UNITEDITOR_BUTTON_FACE_NEXT], L"NEXT");
	_stprintf(_strButton[UNITEDITOR_BUTTON_NORMAL_PREV], L"PREV");
	_stprintf(_strButton[UNITEDITOR_BUTTON_NORMAL_NEXT], L"NEXT");
	_stprintf(_strButton[UNITEDITOR_BUTTON_COMBAT_PREV], L"PREV");
	_stprintf(_strButton[UNITEDITOR_BUTTON_COMBAT_NEXT], L"NEXT");
	_stprintf(_strButton[UNITEDITOR_BUTTON_WEAPON_PREV], L"　◀");
	_stprintf(_strButton[UNITEDITOR_BUTTON_WEAPON_NEXT], L"　▶");
	_stprintf(_strButton[UNITEDITOR_BUTTON_ARMOR_PREV], L"　◀");
	_stprintf(_strButton[UNITEDITOR_BUTTON_ARMOR_NEXT], L"　▶");
	_stprintf(_strButton[UNITEDITOR_BUTTON_SUBITEM_PREV], L"　◀");
	_stprintf(_strButton[UNITEDITOR_BUTTON_SUBITEM_NEXT], L"　▶");

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
	_strEditBox[UNITEDITOR_STREDITBOX_DATA_NAME]->setRect(RectMake(450, 100, 100, 30));
	_strEditBox[UNITEDITOR_STREDITBOX_DATA_FAMILY]->setRect(RectMake(450, 150, 100, 30));
	_strEditBox[UNITEDITOR_STREDITBOX_DATA_AOS]->setRect(RectMake(450, 185, 100, 30));

	for (int i = 0; i < UNITEDITOR_NUMEDITBOX_MAX; i++)
	{
		_numEditBox[i] = new editbox;
		_numEditBox[i]->init();
		_numEditBox[i]->setOnlyNum(TRUE);
	}
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_HP]->setRect(RectMake(450, 235, 100, 30));
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_MP]->setRect(RectMake(450, 270, 100, 30));

	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_ATK]->setRect(RectMake(450, 320, 100, 30));
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_DEP]->setRect(RectMake(450, 355, 100, 30));
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_RES]->setRect(RectMake(450, 390, 100, 30));
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_AGL]->setRect(RectMake(450, 425, 100, 30));
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_FIG]->setRect(RectMake(450, 460, 100, 30));

	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_PWR]->setRect(RectMake(450, 510, 100, 30));
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LDS]->setRect(RectMake(450, 545, 100, 30));
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_INT]->setRect(RectMake(450, 580, 100, 30));
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_DEX]->setRect(RectMake(450, 615, 100, 30));
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LUK]->setRect(RectMake(450, 650, 100, 30));


	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_ENTERSCENARIO]->setRect(RectMake(700, 100, 100, 30));

	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LV]->setRect(RectMake(700, 150, 100, 30));
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_MOVE]->setRect(RectMake(700, 185, 100, 30));

	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERHP]->setRect(RectMake(700, 235, 100, 30));
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERMP]->setRect(RectMake(700, 270, 100, 30));

	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERATK]->setRect(RectMake(700, 320, 100, 30));
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERDEP]->setRect(RectMake(700, 355, 100, 30));
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERRES]->setRect(RectMake(700, 390, 100, 30));
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERAGL]->setRect(RectMake(700, 425, 100, 30));
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERFIG]->setRect(RectMake(700, 460, 100, 30));

	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERPWR]->setRect(RectMake(700, 510, 100, 30));
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERLDS]->setRect(RectMake(700, 545, 100, 30));
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERINT]->setRect(RectMake(700, 580, 100, 30));
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERDEX]->setRect(RectMake(700, 615, 100, 30));
	_numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LVPERLUK]->setRect(RectMake(700, 650, 100, 30));
}

//~init functions
//-----------------------------------------------------------------------------------------
//other functions
void sceneUnitEditor::btnSetup(void)
{
	//_btnSave = CreateWindow("button", "저장", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 700, 500, 100, 30,
	//	_hWnd, HMENU(0), _hInstance, NULL);
}

void sceneUnitEditor::rectSketch(void)
{
	Rectangle(getMemDC(), 100, 100, 300, 228);	//얼굴이미지
	Rectangle(getMemDC(), 100, 300, 300, 428);	//평조이미지
	Rectangle(getMemDC(), 100, 500, 300, 628);	//전조이미지

	Rectangle(getMemDC(), 100, 240, 300, 270);	//이전다음버튼
	Rectangle(getMemDC(), 100, 440, 300, 470);	//이전다음버튼
	Rectangle(getMemDC(), 100, 640, 300, 670);	//이전다음버튼


	Rectangle(getMemDC(), 350, 100, 414, 130);	//이름

	Rectangle(getMemDC(), 350, 150, 414, 180);	//부대
	Rectangle(getMemDC(), 350, 185, 414, 215);	//속성

	Rectangle(getMemDC(), 350, 235, 414, 265);	//HP
	Rectangle(getMemDC(), 350, 270, 414, 300);	//MP

	Rectangle(getMemDC(), 350, 320, 414, 350);	//공격력
	Rectangle(getMemDC(), 350, 355, 414, 385);	//정신력
	Rectangle(getMemDC(), 350, 390, 414, 420);	//방어력
	Rectangle(getMemDC(), 350, 425, 414, 455);	//순발력
	Rectangle(getMemDC(), 350, 460, 414, 490);	//사기

	Rectangle(getMemDC(), 350, 510, 414, 540);	//무력
	Rectangle(getMemDC(), 350, 545, 414, 575);	//지력
	Rectangle(getMemDC(), 350, 580, 414, 610);	//통솔
	Rectangle(getMemDC(), 350, 615, 414, 645);	//민첩
	Rectangle(getMemDC(), 350, 650, 414, 680);	//운


	Rectangle(getMemDC(), 450, 100, 550, 130);	//데이터입력

	Rectangle(getMemDC(), 450, 150, 550, 180);	//데이터입력
	Rectangle(getMemDC(), 450, 185, 550, 215);	//데이터입력

	Rectangle(getMemDC(), 450, 235, 550, 265);	//데이터입력
	Rectangle(getMemDC(), 450, 270, 550, 300);	//데이터입력

	Rectangle(getMemDC(), 450, 320, 550, 350);	//데이터입력
	Rectangle(getMemDC(), 450, 355, 550, 385);	//데이터입력
	Rectangle(getMemDC(), 450, 390, 550, 420);	//데이터입력
	Rectangle(getMemDC(), 450, 425, 550, 455);	//데이터입력
	Rectangle(getMemDC(), 450, 460, 550, 490);	//데이터입력

	Rectangle(getMemDC(), 450, 510, 550, 540);	//데이터입력
	Rectangle(getMemDC(), 450, 545, 550, 575);	//데이터입력
	Rectangle(getMemDC(), 450, 580, 550, 610);	//데이터입력
	Rectangle(getMemDC(), 450, 615, 550, 645);	//데이터입력
	Rectangle(getMemDC(), 450, 650, 550, 680);	//데이터입력


	Rectangle(getMemDC(), 700, 200, 764, 230);	//무기
	Rectangle(getMemDC(), 700, 280, 764, 310);	//방어구
	Rectangle(getMemDC(), 700, 360, 764, 390);	//보조

	Rectangle(getMemDC(), 800, 200, 900, 260);	//이름
	Rectangle(getMemDC(), 800, 280, 900, 340);	//이름
	Rectangle(getMemDC(), 800, 360, 900, 420);	//이름

	Rectangle(getMemDC(), 920, 200, 980, 260);	//이미지
	Rectangle(getMemDC(), 920, 280, 980, 340);	//이미지
	Rectangle(getMemDC(), 920, 360, 980, 420);	//이미지

	Rectangle(getMemDC(), 700, 470, 1000, 670);	//유닛설명

	Rectangle(getMemDC(), 1040, 100, 1400, 400);	//아이템상세설명등

	Rectangle(getMemDC(), 1040, 430, 1240, 670);	//스킬셋

	Rectangle(getMemDC(), 1300, 430, 1400, 460);	//새로만들기
	Rectangle(getMemDC(), 1300, 490, 1400, 520);	//세이브
	Rectangle(getMemDC(), 1300, 550, 1400, 580);	//로드
	Rectangle(getMemDC(), 1300, 640, 1400, 670);	//종료


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
void sceneUnitEditor::unitImageRender(void)			// 해야될 것: 프레임 이미지로 입력받아 프레임렌더로 출력
{
	TCHAR strFaceKey[100];
	_stprintf(strFaceKey, L"face %05d", _faceNum);
	//image* img = IMAGEMANAGER->findImage(strFaceKey);	
	IMAGEMANAGER->findImage(strFaceKey)->render(getMemDC(), 100, 100);

	TCHAR strNormalKey[100];
	_stprintf(strNormalKey, L"평조 %05d", _normalNum);
	IMAGEMANAGER->findImage(strNormalKey)->render(getMemDC(), 100, 300);
	//IMAGEMANAGER->findImage(strNormalKey)->frameRender(getMemDC(), 100, 300, 0, 0);

	TCHAR strCombatKey[100];
	_stprintf(strCombatKey, L"전조 %05d", _combatNum);
	IMAGEMANAGER->findImage(strCombatKey)->render(getMemDC(), 100, 500);
	//IMAGEMANAGER->findImage(strCombatKey)->frameRender(getMemDC(), 100, 300, 0, 0);

	_unit->setImages(strFaceKey, strNormalKey, strCombatKey);		// 이미지 셋
}

void sceneUnitEditor::newUnit(void)
{
	this->init();

	for (int i = 0; i < UNITEDITOR_NUMEDITBOX_MAX; i++)
	{
		// 문자열형 에딧박스 클리어
		_numEditBox[i]->clearStr();
	}

	for (int i = 0; i < UNITEDITOR_STREDITBOX_MAX; i++)
	{
		// 숫자형 에딧박스 클리어
		_strEditBox[i]->clearStr();
	}
}

void sceneUnitEditor::getChar(WPARAM wParam)
{
	//문자열 받는 함수
	for (int i = 0; i < UNITEDITOR_NUMEDITBOX_MAX; i++)
	{
		_numEditBox[i]->getChar(wParam);
	}

	for (int i = 0; i < UNITEDITOR_STREDITBOX_MAX; i++)
	{
		_strEditBox[i]->getChar(wParam);
	}
}

void sceneUnitEditor::loadUnit(void)		// 로드유닛 일단 보류
{
	//set
}
void sceneUnitEditor::saveUnit(void)
{
	_tcscpy_s(_tempStatus.name, _strEditBox[UNITEDITOR_STREDITBOX_DATA_NAME]->getStr());
	_tcscpy_s(_tempStatus.family, _strEditBox[UNITEDITOR_STREDITBOX_DATA_FAMILY]->getStr());
	_tcscpy_s(_tempStatus.aos, _strEditBox[UNITEDITOR_STREDITBOX_DATA_AOS]->getStr());

	_tempStatus.isLive = TRUE;
	_tempStatus.exp = 0;
	_tempStatus.expMax = 100;
	_tempStatus.HP		= _numEditBox[UNITEDITOR_NUMEDITBOX_DATA_HP]->getStrNum();
	_tempStatus.HPMax	= _numEditBox[UNITEDITOR_NUMEDITBOX_DATA_HP]->getStrNum();
	_tempStatus.MP		= _numEditBox[UNITEDITOR_NUMEDITBOX_DATA_MP]->getStrNum();
	_tempStatus.MPMax	= _numEditBox[UNITEDITOR_NUMEDITBOX_DATA_MP]->getStrNum();
	_tempStatus.Atk		= _numEditBox[UNITEDITOR_NUMEDITBOX_DATA_ATK]->getStrNum();
	_tempStatus.Dep		= _numEditBox[UNITEDITOR_NUMEDITBOX_DATA_DEP]->getStrNum();
	_tempStatus.Res		= _numEditBox[UNITEDITOR_NUMEDITBOX_DATA_RES]->getStrNum();
	_tempStatus.Agl		= _numEditBox[UNITEDITOR_NUMEDITBOX_DATA_AGL]->getStrNum();
	_tempStatus.Fig		= _numEditBox[UNITEDITOR_NUMEDITBOX_DATA_FIG]->getStrNum();
	_tempStatus.Pwr		= _numEditBox[UNITEDITOR_NUMEDITBOX_DATA_PWR]->getStrNum();
	_tempStatus.Lds		= _numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LDS]->getStrNum();
	_tempStatus.Int		= _numEditBox[UNITEDITOR_NUMEDITBOX_DATA_INT]->getStrNum();
	_tempStatus.Dex		= _numEditBox[UNITEDITOR_NUMEDITBOX_DATA_DEX]->getStrNum();
	_tempStatus.Luk		= _numEditBox[UNITEDITOR_NUMEDITBOX_DATA_LUK]->getStrNum();

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

	_unit->setStatus(_tempStatus);

	HANDLE file;
	DWORD write;
	TCHAR tempStr[1024];

	_stprintf(tempStr, L"UnitData/%s", _filename);

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
