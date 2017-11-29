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

	_rcOK = RectMake(415, 491, 86, 21);

	_rcCancel = RectMake(415+86+5, 491, 86, 21);
	
	_vUnits = _player->getUnits();
	_vUnitsInFile = _player->getUnitsInFile();


	_availableOK = false;
	_okClicking = false;
	_cancelClicking = false;


	//�̸�����
	_tcscpy(_posUnits[0].name, L"����");
	_tcscpy(_posUnits[1].name, L"����");
	_tcscpy(_posUnits[2].name, L"���ĵ�");
	_tcscpy(_posUnits[3].name, L"���Ŀ�");
	_tcscpy(_posUnits[4].name, L"����");
	_tcscpy(_posUnits[5].name, L"����");
	_tcscpy(_posUnits[6].name, L"��ȫ");

	//RECT define
	for (int i = 0; i < 7; i++) {
		_posUnits[i].posRC = RectMake(4 + (57 * i), 52, 48, 48);
	}


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
		for (int i = 0; i < 7; i++) {
			if (PtInRect(&_posUnits[i].posRC, _pt)) { //�� �������Ʈ�� �ϳ�Ŭ��
				for (int j = 0; j < _vUnitsInFile.size(); j++) {
					if (!_tcscmp(_posUnits[i].name, _vUnitsInFile[j]->getStatus().name)) {
						_player->registUnit(_vUnitsInFile[j]);    //vUnits ���Ϳ����� (��������Ʈ)
					}
				}
			}
		}
	}
}
void scenePos::render(void){

	_posImg->render(getMemDC(), 0, 0);

	//��
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < _vUnitsInFile.size(); j++) {
			if (!_tcscmp(_posUnits[i].name,_vUnitsInFile[j]->getStatus().name )) {
				_vUnitsInFile[j]->getBattleState().imgBattleIdle->frameRender(getMemDC(), _posUnits[i].posRC.left, _posUnits[i].posRC.top, 0, 0);
			}
		}
		
	}



	//�Ʒ� ����,���ĵ� ������
	for (int i = 0; i < _vUnits.size(); i++) {
		//if (!_tcscmp(_vUnitsInFile[i]->getStatus().name, L"����")) {
		//	_vUnitsInFile[i]->getBattleState().imgBattleIdle->frameRender(getMemDC(), 6, 367, 0, 0);
		//}
		//if (!_tcscmp(_vUnitsInFile[i]->getStatus().name, L"���ĵ�")) {
		//	_vUnitsInFile[i]->getBattleState().imgBattleIdle->frameRender(getMemDC(), 6+48, 367, 0, 0);
		//}

		_vUnits[i]->getBattleState().imgBattleIdle->frameRender(getMemDC(), 6 + (48 * i)+i, 367, 0, 0);
	}
	
	
	




	if (_availableOK) {          //Ȱ����Ȱ��
		IMAGEMANAGER->findImage(L"����Ȱ����ư")->render(getMemDC(),415, 491);

		if (_okClicking) {         //�����񴭸�
			IMAGEMANAGER->findImage(L"����������ư")->render(getMemDC(), 415, 491);
		}
		else {
			IMAGEMANAGER->findImage(L"����Ȱ����ư")->render(getMemDC(), 415, 491);
		}
	}
	else {
		IMAGEMANAGER->findImage(L"������Ȱ����ư")->render(getMemDC(), 415, 491);
	}




	if (_cancelClicking) {
		IMAGEMANAGER->findImage(L"��Ҵ�����ư")->render(getMemDC(), 415 +86 + 5, 491);
	}
	else {
		IMAGEMANAGER->findImage(L"��ҹ�ư")->render(getMemDC(), 415 +86 + 5, 491);
	}

	TCHAR tmp[30];
	_stprintf(tmp, L"x: %d, y: %d", _pt.x, _pt.y);
	TextOut(getMemDC(), 100, 100, tmp, _tcslen(tmp));

	//TextOut(getMemDC(), 300, 300, _vUnitsInFile[0]->getStatus().name, _tcslen(_vUnitsInFile[0]->getStatus().name));
	//Rectangle(getMemDC(), _rcCancel.left, _rcCancel.top, _rcCancel.right, _rcCancel.bottom);

	//for(int i = 0; i < 7; i++) {
	//	Rectangle(getMemDC(), _posUnits[i].posRC.left, _posUnits[i].posRC.top, _posUnits[i].posRC.right, _posUnits[i].posRC.bottom);
	//}
}