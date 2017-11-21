#pragma once
#include "gameNode.h"
#include "Unit.h"
#include "button.h"
#include "editbox.h"

enum UNITEDITOR_BUTTON
{
	UNITEDITOR_BUTTON_DATA_NEW,			//새 영웅 만들기
	UNITEDITOR_BUTTON_DATA_LOAD,		//영웅 데이터 불러오기
	UNITEDITOR_BUTTON_DATA_SAVE,		//영웅 데이터 저장하기

	UNITEDITOR_BUTTON_FACE_PREV,		//얼굴 이전 이미지
	UNITEDITOR_BUTTON_FACE_NEXT,		//얼굴 다음 이미지

	UNITEDITOR_BUTTON_MAX
};



class sceneUnitEditor : public gameNode
{
private:
	Unit* _unit;

	button* _ctrlButton[UNITEDITOR_BUTTON_MAX];
	TCHAR _strButton[UNITEDITOR_BUTTON_MAX][100];

	editbox* _ebtest;


	int _faceNum;

private:
	static void ctrlSelectDataNew(void* obj);
	static void ctrlSelectDataLoad(void* obj);
	static void ctrlSelectDataSave(void* obj);
	static void ctrlSelectFacePrev(void* obj);
	static void ctrlSelectFaceNext(void* obj);


public:
	sceneUnitEditor();
	~sceneUnitEditor();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void getChar(WPARAM wParam);

public:
	inline void setFacePrev(void) { _faceNum = _faceNum == 0 ? FACE_MAX : _faceNum - 1; }
	inline void setFaceNext(void) { _faceNum = _faceNum == FACE_MAX ? 0 : _faceNum + 1; }
};

