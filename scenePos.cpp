#include "stdafx.h"
#include "scenePos.h"


scenePos::scenePos()
{
}


scenePos::~scenePos()
{
}
HRESULT scenePos::init(void) {

	_posImg = IMAGEMANAGER->findImage(L"출진UI");

	_rcOK = RectMake(655, 915, 127, 33);

	_rcCancel = RectMake(655+127+10, 915, 127, 33);

	//_btnOk = CreateWindow(L"button", L"결정", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 655, 915, 115, 30,
	//	_hWnd, HMENU(0), _hInstance, NULL);
	//
	//_btnCancel = CreateWindow(L"button", L"취소", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 800, 915, 115, 30,
	//	_hWnd, HMENU(1), _hInstance, NULL);


	_availableOK = false;
	_okClicking = false;
	_cancelClicking = false;



	return S_OK;
}
void scenePos::release(void) {

}
void scenePos::update(void){
	_pt.x = _ptMouse.x;
	_pt.y = _ptMouse.y;

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)) {
		if (PtInRect(&_rcOK, _pt)&&_availableOK) {     //눌림
			_okClicking = true;
		}
		else {
			_okClicking = false;
		}
	
		if (PtInRect(&_rcCancel, _pt)) {
			_cancelClicking = true;
		}
		else {
			_cancelClicking = false;
		}
	}


	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) {
		if (PtInRect(&_rcCancel, _pt)) {       //닫기창클릭
			SCENEMANAGER->changeScene(L"준비기본씬");
		}
	}
}
void scenePos::render(void){

	_posImg->render(getMemDC(), 0, 0);

	//고정픽
	IMAGEMANAGER->findImage(L"조조출진")->render(getMemDC(), 5, 679);     
	IMAGEMANAGER->findImage(L"하후돈출진")->render(getMemDC(), 81, 679);







	if (_availableOK) {          //활성비활성
		IMAGEMANAGER->findImage(L"결정활성버튼")->render(getMemDC(), 655, 915);

		if (_okClicking) {         //눌림비눌림
			IMAGEMANAGER->findImage(L"결정눌림버튼")->render(getMemDC(), 655, 915);
		}
		else {
			IMAGEMANAGER->findImage(L"결정활성버튼")->render(getMemDC(), 655, 915);
		}
	}
	else {
		IMAGEMANAGER->findImage(L"결정비활성버튼")->render(getMemDC(), 655, 915);
	}




	if (_cancelClicking) {
		IMAGEMANAGER->findImage(L"취소눌림버튼")->render(getMemDC(), 655 + 127 + 10, 915);
	}
	else {
		IMAGEMANAGER->findImage(L"취소버튼")->render(getMemDC(), 655 + 127 + 10, 915);
	}

	TCHAR tmp[30];
	_stprintf(tmp, L"x: %d, y: %d", _pt.x, _pt.y);
	TextOut(getMemDC(), 100, 100, tmp, _tcslen(tmp));

	//Rectangle(getMemDC(), _rcCancel.left, _rcCancel.top, _rcCancel.right, _rcCancel.bottom);
}