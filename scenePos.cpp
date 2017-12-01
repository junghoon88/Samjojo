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

	_rcOK = RectMake(415, 491, 86, 21);

	_rcCancel = RectMake(415+86+5, 491, 86, 21);
	
	_vUnits = _player->getUnits();
	_vUnitsInFile = _player->getUnitsInFile();


	_availableOK = false;
	_okClicking = false;
	_cancelClicking = false;


	//이름배정
	_tcscpy(_posUnits[0].name, L"조조");
	_tcscpy(_posUnits[1].name, L"조인");
	_tcscpy(_posUnits[2].name, L"하후돈");
	_tcscpy(_posUnits[3].name, L"하후연");
	_tcscpy(_posUnits[4].name, L"이전");
	_tcscpy(_posUnits[5].name, L"악진");
	_tcscpy(_posUnits[6].name, L"조홍");

	//RECT & bool define
	for (int i = 0; i < 7; i++) {
		_posUnits[i].posRC = RectMake(4 + (57 * i), 52, 48, 48);
		_posUnits[i].isPos = false;
	}
	//조조 하후돈고정픽
	_posUnits[0].isPos = true;
	_posUnits[2].isPos = true;

	for (int i = 0; i < _vUnitsInFile.size(); i++) {
		if (!_tcscmp(_vUnitsInFile[i]->getStatus().name, L"조조")) {
			_chosang = _vUnitsInFile[i]->getStatus().imgFace;
			_tcscpy(_name, _vUnitsInFile[i]->getStatus().name);
			_tcscpy(_aos, _vUnitsInFile[i]->getStatus().aos);
			_level = _vUnitsInFile[i]->getStatus().level;
			_pwr = _vUnitsInFile[i]->getStatus().InitPwr;

		}
	}
	



	return S_OK;
}
void scenePos::release(void) {

}
void scenePos::update(void){
	_pt.x = _ptMouse.x;
	_pt.y = _ptMouse.y;


	for (int i = 0; i < 7; i++) {
		if (PtInRect(&_posUnits[i].posRC, _pt)) {
			for (int j = 0; j < _vUnitsInFile.size(); j++) {
				if (!_tcscmp(_posUnits[i].name, _vUnitsInFile[j]->getStatus().name)) {

				}
			}
		}
	}
	



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
		for (int i = 0; i < 7; i++) {
			if (PtInRect(&_posUnits[i].posRC, _pt) && !_posUnits[i].isPos) { //위 장수리스트중 하나클릭  (추가)
				_posUnits[i].isPos = true;
				for (int j = 0; j < _vUnitsInFile.size(); j++) {
					if (!_tcscmp(_posUnits[i].name, _vUnitsInFile[j]->getStatus().name)) {
						_player->registUnit(_vUnitsInFile[j]);    //vUnits 벡터에넣음 (출진리스트)
						_vUnits = _player->getUnits();
					}
				}
			}

			if (PtInRect(&posRC2[i], _pt) && i != 0 && i != 1) {   //아래 장수리스트중 하나클릭 (제거)
				for (int j = 0; j < 7; j++) {
					if (!_tcscmp(_vUnits[i]->getStatus().name, _posUnits[j].name)) {
						_posUnits[j].isPos = false;
						break;
					}
				}
				_player->cancleUnit(i); //제거
				_vUnits = _player->getUnits();  //갱신
			}
		}
	
	}


	for (int i = 0; i < _vUnits.size(); i++) {
		posRC2[i] = RectMake(6 + (50 * i), 367, 48, 48);
	}
}
void scenePos::render(void){

	_posImg->render(getMemDC(), 0, 0);

	//위
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < _vUnitsInFile.size(); j++) {
			if (!_tcscmp(_posUnits[i].name,_vUnitsInFile[j]->getStatus().name )) {
				_vUnitsInFile[j]->getBattleState().imgBattleIdle->frameRender(getMemDC(), _posUnits[i].posRC.left, _posUnits[i].posRC.top, 0, 0);
			}
		}
		
	}

	//for (int i = 0; i < 7; i++) {
	//	Rectangle(getMemDC(), _posUnits[i].posRC.left, _posUnits[i].posRC.top, _posUnits[i].posRC.right, _posUnits[i].posRC.bottom);
	//}

	//아래 조조,하후돈 고정픽
	for (int i = 0; i < _vUnits.size(); i++) {
		_vUnits[i]->getBattleState().imgBattleIdle->frameRender(getMemDC(), 6 + (50 * i), 367, 0, 0);
	}
	
	_chosang->render(getMemDC(), 416, 44);
	




	if (_availableOK) {          //활성비활성
		IMAGEMANAGER->findImage(L"결정활성버튼")->render(getMemDC(),415, 491);

		if (_okClicking) {         //눌림비눌림
			IMAGEMANAGER->findImage(L"결정눌림버튼")->render(getMemDC(), 415, 491);
		}
		else {
			IMAGEMANAGER->findImage(L"결정활성버튼")->render(getMemDC(), 415, 491);
		}
	}
	else {
		IMAGEMANAGER->findImage(L"결정비활성버튼")->render(getMemDC(), 415, 491);
	}




	if (_cancelClicking) {
		IMAGEMANAGER->findImage(L"취소눌림버튼")->render(getMemDC(), 415 +86 + 5, 491);
	}
	else {
		IMAGEMANAGER->findImage(L"취소버튼")->render(getMemDC(), 415 +86 + 5, 491);
	}

	TCHAR tmp[30];
	_stprintf(tmp, L"x: %d, y: %d", _pt.x, _pt.y);
	TextOut(getMemDC(), 100, 100, tmp, _tcslen(tmp));

	//TextOut(getMemDC(), 300, 300, _vUnitsInFile[0]->getStatus().name, _tcslen(_vUnitsInFile[0]->getStatus().name));
	//Rectangle(getMemDC(), _rcCancel.left, _rcCancel.top, _rcCancel.right, _rcCancel.bottom);
	//for(int i=0; i<_vUnits.size(); i++)
	//	Rectangle(getMemDC(), posRC2[i].left, posRC2[i].top, posRC2[i].right, posRC2[i].bottom);
	
}