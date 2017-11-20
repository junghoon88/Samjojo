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


	_stprintf(_strButton[UNITEDITOR_BUTTON_DATA_NEW],  L"NEW");
	_stprintf(_strButton[UNITEDITOR_BUTTON_DATA_LOAD], L"LOAD");
	_stprintf(_strButton[UNITEDITOR_BUTTON_DATA_SAVE], L"SAVE");
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
	_stprintf(_strButton[UNITEDITOR_BUTTON_LABEL_NAME], L"�̸�");


	_faceNum = 0;
	_normalNum = 0;
	_combatNum = 0;
	_weaponNum = 0;
	_armorNum = 0;
	_subitemNum = 0;


	//_editTest = EDITBOXMANAGER->addEditbox(L"�׽�Ʈ", RectMake(200, 100, 100, 30));
	_editTest = new editbox;
	_editTest->init();
	_editTest->setRect(RectMake(500, 100, 100, 30));

	return S_OK;
}

void sceneUnitEditor::release(void)
{
	SAFE_DELETE(_unit);
	_editTest->release();
	SAFE_DELETE(_editTest);
}

void sceneUnitEditor::update(void)
{
	for (int i = 0; i < UNITEDITOR_BUTTON_MAX; i++)
	{
		_ctrlButton[i]->update();
	}

	_editTest->update();
}

void sceneUnitEditor::render(void)
{
	rectSketch();

	TCHAR strFaceKey[100];
	_stprintf(strFaceKey, L"face %05d - size(128, 128)", _faceNum);
	//image* img = IMAGEMANAGER->findImage(strFaceKey);	
	IMAGEMANAGER->findImage(strFaceKey)->render(getMemDC(), 100, 100);

	TCHAR strNormalKey[100];
	_stprintf(strNormalKey, L"���� %05d", _normalNum);
	IMAGEMANAGER->findImage(strNormalKey)->render(getMemDC(), 100, 300);
	//IMAGEMANAGER->findImage(strNormalKey)->frameRender(getMemDC(), 100, 300, 1, 1);

	TCHAR strCombatKey[100];
	_stprintf(strCombatKey, L"���� %05d", _combatNum);
	IMAGEMANAGER->findImage(strCombatKey)->render(getMemDC(), 100, 500);
	//IMAGEMANAGER->findImage(strCombatKey)->frameRender(getMemDC(), 100, 300);

	//_unit->setImage(strFaceKey, strNormalKey, strCombatKey);		<< ��, ����, ���� ������ Ű�������� �̹��� ��

	for (int i = 0; i < UNITEDITOR_BUTTON_MAX; i++)
	{
		_ctrlButton[i]->render();
		TextOut(getMemDC(), _ctrlButton[i]->getRect().left, _ctrlButton[i]->getRect().top, _strButton[i], _tcslen(_strButton[i]));
	}

}


void sceneUnitEditor::initButton(void)
{
	//label
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_NAME] = new button;
	_ctrlButton[UNITEDITOR_BUTTON_LABEL_NAME]->init(L"������ư2", 400 + 25, 100 + 15, { 0, 0 }, { 0, 1 }, ctrlSelectFacePrev, this);

	//prev, next
	_ctrlButton[UNITEDITOR_BUTTON_FACE_PREV] = new button;
	_ctrlButton[UNITEDITOR_BUTTON_FACE_PREV]->init(L"������ư", 100 + 50, 240 + 15, { 0, 0 }, { 0, 1 }, ctrlSelectFacePrev, this);
	_ctrlButton[UNITEDITOR_BUTTON_FACE_NEXT] = new button;
	_ctrlButton[UNITEDITOR_BUTTON_FACE_NEXT]->init(L"������ư", 200 + 50, 240 + 15, { 0, 0 }, { 0, 1 }, ctrlSelectFaceNext, this);

	_ctrlButton[UNITEDITOR_BUTTON_NORMAL_PREV] = new button;
	_ctrlButton[UNITEDITOR_BUTTON_NORMAL_PREV]->init(L"������ư", 100 + 50, 440 + 15, { 0, 0 }, { 0, 1 }, ctrlSelectNormalPrev, this);
	_ctrlButton[UNITEDITOR_BUTTON_NORMAL_NEXT] = new button;
	_ctrlButton[UNITEDITOR_BUTTON_NORMAL_NEXT]->init(L"������ư", 200 + 50, 440 + 15, { 0, 0 }, { 0, 1 }, ctrlSelectNormalNext, this);
	
	_ctrlButton[UNITEDITOR_BUTTON_COMBAT_PREV] = new button;
	_ctrlButton[UNITEDITOR_BUTTON_COMBAT_PREV]->init(L"������ư", 100 + 50, 640 + 15, { 0, 0 }, { 0, 1 }, ctrlSelectCombatPrev, this);
	_ctrlButton[UNITEDITOR_BUTTON_COMBAT_NEXT] = new button;
	_ctrlButton[UNITEDITOR_BUTTON_COMBAT_NEXT]->init(L"������ư", 200 + 50, 640 + 15, { 0, 0 }, { 0, 1 }, ctrlSelectCombatNext, this);

	_ctrlButton[UNITEDITOR_BUTTON_WEAPON_PREV] = new button;
	_ctrlButton[UNITEDITOR_BUTTON_WEAPON_PREV]->init(L"������ư2", 800 + 25, 230 + 15, { 0, 0 }, { 0, 1 }, ctrlSelectWeaponPrev, this);
	_ctrlButton[UNITEDITOR_BUTTON_WEAPON_NEXT] = new button;
	_ctrlButton[UNITEDITOR_BUTTON_WEAPON_NEXT]->init(L"������ư2", 850 + 25, 230 + 15, { 0, 0 }, { 0, 1 }, ctrlSelectWeaponNext, this);

	_ctrlButton[UNITEDITOR_BUTTON_ARMOR_PREV] = new button;
	_ctrlButton[UNITEDITOR_BUTTON_ARMOR_PREV]->init(L"������ư2", 800 + 25, 310 + 15, { 0, 0 }, { 0, 1 }, ctrlSelectArmorPrev, this);
	_ctrlButton[UNITEDITOR_BUTTON_ARMOR_NEXT] = new button;
	_ctrlButton[UNITEDITOR_BUTTON_ARMOR_NEXT]->init(L"������ư2", 850 + 25, 310 + 15, { 0, 0 }, { 0, 1 }, ctrlSelectArmorNext, this);

	_ctrlButton[UNITEDITOR_BUTTON_SUBITEM_PREV] = new button;
	_ctrlButton[UNITEDITOR_BUTTON_SUBITEM_PREV]->init(L"������ư2", 800 + 25, 390 + 15, { 0, 0 }, { 0, 1 }, ctrlSelectSubitemPrev, this);
	_ctrlButton[UNITEDITOR_BUTTON_SUBITEM_NEXT] = new button;
	_ctrlButton[UNITEDITOR_BUTTON_SUBITEM_NEXT]->init(L"������ư2", 850 + 25, 390 + 15, { 0, 0 }, { 0, 1 }, ctrlSelectSubitemNext, this);

	//new, save, load, exit
	_ctrlButton[UNITEDITOR_BUTTON_DATA_NEW] = new button;
	_ctrlButton[UNITEDITOR_BUTTON_DATA_NEW]->init(L"������ư", 1300 + 50, 430 + 15, { 0, 0 }, { 0, 1 }, ctrlSelectDataNew, this);
	_ctrlButton[UNITEDITOR_BUTTON_DATA_LOAD] = new button;
	_ctrlButton[UNITEDITOR_BUTTON_DATA_LOAD]->init(L"������ư", 1300 + 50, 490 + 15, { 0, 0 }, { 0, 1 }, ctrlSelectDataLoad, this);
	_ctrlButton[UNITEDITOR_BUTTON_DATA_SAVE] = new button;
	_ctrlButton[UNITEDITOR_BUTTON_DATA_SAVE]->init(L"������ư", 1300 + 50, 550 + 15, { 0, 0 }, { 0, 1 }, ctrlSelectDataSave, this);
}

void sceneUnitEditor::btnSetup(void)
{
	//_btnSave = CreateWindow("button", "����", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 700, 500, 100, 30,
	//	_hWnd, HMENU(0), _hInstance, NULL);
}

void sceneUnitEditor::rectSketch(void)
{
	Rectangle(getMemDC(), 100, 100, 300, 228);	//���̹���
	Rectangle(getMemDC(), 100, 300, 300, 428);	//�����̹���
	Rectangle(getMemDC(), 100, 500, 300, 628);	//�����̹���
	Rectangle(getMemDC(), 100, 240, 300, 270);	//����������ư
	Rectangle(getMemDC(), 100, 440, 300, 470);	//����������ư
	Rectangle(getMemDC(), 100, 640, 300, 670);	//����������ư

	Rectangle(getMemDC(), 400, 100, 464, 130);	//�̸�
	Rectangle(getMemDC(), 400, 160, 464, 190);	//HP
	Rectangle(getMemDC(), 400, 200, 464, 230);	//MP
	Rectangle(getMemDC(), 400, 260, 464, 290);	//���ݷ�
	Rectangle(getMemDC(), 400, 300, 464, 330);	//���ŷ�
	Rectangle(getMemDC(), 400, 340, 464, 370);	//����
	Rectangle(getMemDC(), 400, 380, 464, 410);	//���߷�
	Rectangle(getMemDC(), 400, 420, 464, 450);	//���
	Rectangle(getMemDC(), 400, 480, 464, 510);	//����
	Rectangle(getMemDC(), 400, 520, 464, 550);	//����
	Rectangle(getMemDC(), 400, 560, 464, 590);	//���
	Rectangle(getMemDC(), 400, 600, 464, 630);	//��ø
	Rectangle(getMemDC(), 400, 640, 464, 670);	//��

	Rectangle(getMemDC(), 500, 100, 600, 130);	//�������Է�
	Rectangle(getMemDC(), 500, 160, 600, 190);	//�������Է�
	Rectangle(getMemDC(), 500, 200, 600, 230);	//�������Է�
	Rectangle(getMemDC(), 500, 260, 600, 290);	//�������Է�
	Rectangle(getMemDC(), 500, 300, 600, 330);	//�������Է�
	Rectangle(getMemDC(), 500, 340, 600, 370);	//�������Է�
	Rectangle(getMemDC(), 500, 380, 600, 410);	//�������Է�
	Rectangle(getMemDC(), 500, 420, 600, 450);	//�������Է�
	Rectangle(getMemDC(), 500, 480, 600, 510);	//�������Է�
	Rectangle(getMemDC(), 500, 520, 600, 550);	//�������Է�
	Rectangle(getMemDC(), 500, 560, 600, 590);	//�������Է�
	Rectangle(getMemDC(), 500, 600, 600, 630);	//�������Է�
	Rectangle(getMemDC(), 500, 640, 600, 670);	//�������Է�

	Rectangle(getMemDC(), 700, 100, 764, 130);	//�δ�
	Rectangle(getMemDC(), 700, 140, 764, 170);	//�Ӽ�
	Rectangle(getMemDC(), 800, 100, 900, 130);	//�������Է�
	Rectangle(getMemDC(), 800, 140, 900, 170);	//�������Է�

	Rectangle(getMemDC(), 700, 200, 764, 230);	//����
	Rectangle(getMemDC(), 700, 280, 764, 310);	//��
	Rectangle(getMemDC(), 700, 360, 764, 390);	//����
	Rectangle(getMemDC(), 800, 200, 900, 260);	//�̸�
	Rectangle(getMemDC(), 800, 280, 900, 340);	//�̸�
	Rectangle(getMemDC(), 800, 360, 900, 420);	//�̸�
	Rectangle(getMemDC(), 920, 200, 980, 260);	//�̹���
	Rectangle(getMemDC(), 920, 280, 980, 340);	//�̹���
	Rectangle(getMemDC(), 920, 360, 980, 420);	//�̹���

	Rectangle(getMemDC(), 700, 470, 1000, 670);	//���ּ���

	Rectangle(getMemDC(), 1040, 100, 1400, 400);	//�����ۻ󼼼����

	Rectangle(getMemDC(), 1040, 430, 1240, 670);	//��ų��

	Rectangle(getMemDC(), 1300, 430, 1400, 460);	//���θ����
	Rectangle(getMemDC(), 1300, 490, 1400, 520);	//���̺�
	Rectangle(getMemDC(), 1300, 550, 1400, 580);	//�ε�
	Rectangle(getMemDC(), 1300, 640, 1400, 670);	//����

	_editTest->render();

}

//-----------------------------------------------------------------------------------------
//callback functions
void sceneUnitEditor::ctrlSelectDataNew(void* obj) 
{
	sceneUnitEditor* unitEditor = (sceneUnitEditor*)obj;

}

void sceneUnitEditor::ctrlSelectDataLoad(void* obj)
{
	sceneUnitEditor* unitEditor = (sceneUnitEditor*)obj;

}

void sceneUnitEditor::ctrlSelectDataSave(void* obj)
{
	sceneUnitEditor* unitEditor = (sceneUnitEditor*)obj;

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
