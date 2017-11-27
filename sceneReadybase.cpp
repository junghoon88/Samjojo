#include "stdafx.h"
#include "sceneReadybase.h"


sceneReadybase::sceneReadybase()
{
}


sceneReadybase::~sceneReadybase()
{
}

HRESULT sceneReadybase::init(void) {

	DATABASE->getSlectScenario();

	_baseImg = IMAGEMANAGER->findImage(L"����UI");

	_rcPosUI = RectMake(660, 840, 74, 115);
	_rcEquipUI = RectMake(735, 840, 74, 115);
	_rcBuyUI = RectMake(810, 840, 74, 115);
	_rcSellUI = RectMake(884, 840, 74, 115);

	_posClicking = false;
	return S_OK;
}
void sceneReadybase::release(void) {

}
void sceneReadybase::update(void) {


	_pt.x = _ptMouse.x;
	_pt.y = _ptMouse.y;
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)) {
		if (PtInRect(&_rcPosUI, _pt)) {  //����â ����
			_posClicking = true;
		}
		else{
			_posClicking = false;
		}
	}
	if(KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) {
		if (PtInRect(&_rcPosUI, _pt)) {   //����â ������
			_posClicking = false;
			SCENEMANAGER->changeScene(L"������");
		}
	}

}
void sceneReadybase::render(void) {

	_baseImg->render(getMemDC(), 0, 0);

	TCHAR tmp[30];
	_stprintf(tmp, L"x: %d, y: %d", _pt.x, _pt.y);
	TextOut(getMemDC(), 100, 100, tmp, _tcslen(tmp));

	if (_posClicking) {
		IMAGEMANAGER->findImage(L"��������")->render(getMemDC(), _rcPosUI.left, _rcPosUI.top-2);
	}

	//Rectangle(getMemDC(), _rcPosUI.left, _rcPosUI.top, _rcPosUI.right, _rcPosUI.bottom);
	

}