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

	_ctrlButton[UNITEDITOR_BUTTON_DATA_NEW] = new button;
	_ctrlButton[UNITEDITOR_BUTTON_DATA_NEW]->init(L"¸ÊÅø¹öÆ°",  1100, 300, { 0, 0 }, { 0, 1 }, ctrlSelectDataNew,  this);
	_ctrlButton[UNITEDITOR_BUTTON_DATA_LOAD] = new button;
	_ctrlButton[UNITEDITOR_BUTTON_DATA_LOAD]->init(L"¸ÊÅø¹öÆ°", 1100, 400, { 0, 0 }, { 0, 1 }, ctrlSelectDataLoad, this);
	_ctrlButton[UNITEDITOR_BUTTON_DATA_SAVE] = new button;
	_ctrlButton[UNITEDITOR_BUTTON_DATA_SAVE]->init(L"¸ÊÅø¹öÆ°", 1100, 500, { 0, 0 }, { 0, 1 }, ctrlSelectDataSave, this);
	_ctrlButton[UNITEDITOR_BUTTON_FACE_PREV] = new button;
	_ctrlButton[UNITEDITOR_BUTTON_FACE_PREV]->init(L"¸ÊÅø¹öÆ°", 1100, 600, { 0, 0 }, { 0, 1 }, ctrlSelectFacePrev, this);
	_ctrlButton[UNITEDITOR_BUTTON_FACE_NEXT] = new button;
	_ctrlButton[UNITEDITOR_BUTTON_FACE_NEXT]->init(L"¸ÊÅø¹öÆ°", 1100, 700, { 0, 0 }, { 0, 1 }, ctrlSelectFaceNext, this);

	_stprintf(_strButton[UNITEDITOR_BUTTON_DATA_NEW],  L"NEW");
	_stprintf(_strButton[UNITEDITOR_BUTTON_DATA_LOAD], L"LOAD");
	_stprintf(_strButton[UNITEDITOR_BUTTON_DATA_SAVE], L"SAVE");
	_stprintf(_strButton[UNITEDITOR_BUTTON_FACE_PREV], L"PREV");
	_stprintf(_strButton[UNITEDITOR_BUTTON_FACE_NEXT], L"NEXT");


	_faceNum = 0;

	return S_OK;
}

void sceneUnitEditor::release(void)
{
	SAFE_DELETE(_unit);
}

void sceneUnitEditor::update(void)
{
	for (int i = 0; i < UNITEDITOR_BUTTON_MAX; i++)
	{
		_ctrlButton[i]->update();
	}
}

void sceneUnitEditor::render(void)
{
	TCHAR strKey[100];
	_stprintf(strKey, L"face %05d - size(128, 128)", _faceNum);
	image* img = IMAGEMANAGER->findImage(strKey);
	IMAGEMANAGER->findImage(strKey)->render(getMemDC(), 100, 100);

	for (int i = 0; i < UNITEDITOR_BUTTON_MAX; i++)
	{
		_ctrlButton[i]->render();
		TextOut(getMemDC(), _ctrlButton[i]->getRect().left, _ctrlButton[i]->getRect().top, _strButton[i], _tcslen(_strButton[i]));
	}
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
//~callback functions
//-----------------------------------------------------------------------------------------
