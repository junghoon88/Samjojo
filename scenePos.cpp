#include "stdafx.h"
#include "scenePos.h"


scenePos::scenePos()
{
}


scenePos::~scenePos()
{
}
HRESULT scenePos::init(void) {

	_posImg = IMAGEMANAGER->findImage(L"����UI");

	_rcOK = RectMake(655, 915, 127, 33);

	_rcCancel = RectMake(655+127+10, 915, 127, 33);

	//_btnOk = CreateWindow(L"button", L"����", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 655, 915, 115, 30,
	//	_hWnd, HMENU(0), _hInstance, NULL);
	//
	//_btnCancel = CreateWindow(L"button", L"���", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 800, 915, 115, 30,
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
		if (PtInRect(&_rcOK, _pt)&&_availableOK) {     //����
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
		if (PtInRect(&_rcCancel, _pt)) {       //�ݱ�âŬ��
			SCENEMANAGER->changeScene(L"�غ�⺻��");
		}
	}
}
void scenePos::render(void){

	_posImg->render(getMemDC(), 0, 0);

	//������
	IMAGEMANAGER->findImage(L"��������")->render(getMemDC(), 5, 679);     
	IMAGEMANAGER->findImage(L"���ĵ�����")->render(getMemDC(), 81, 679);







	if (_availableOK) {          //Ȱ����Ȱ��
		IMAGEMANAGER->findImage(L"����Ȱ����ư")->render(getMemDC(), 655, 915);

		if (_okClicking) {         //�����񴭸�
			IMAGEMANAGER->findImage(L"����������ư")->render(getMemDC(), 655, 915);
		}
		else {
			IMAGEMANAGER->findImage(L"����Ȱ����ư")->render(getMemDC(), 655, 915);
		}
	}
	else {
		IMAGEMANAGER->findImage(L"������Ȱ����ư")->render(getMemDC(), 655, 915);
	}




	if (_cancelClicking) {
		IMAGEMANAGER->findImage(L"��Ҵ�����ư")->render(getMemDC(), 655 + 127 + 10, 915);
	}
	else {
		IMAGEMANAGER->findImage(L"��ҹ�ư")->render(getMemDC(), 655 + 127 + 10, 915);
	}

	TCHAR tmp[30];
	_stprintf(tmp, L"x: %d, y: %d", _pt.x, _pt.y);
	TextOut(getMemDC(), 100, 100, tmp, _tcslen(tmp));

	//Rectangle(getMemDC(), _rcCancel.left, _rcCancel.top, _rcCancel.right, _rcCancel.bottom);
}