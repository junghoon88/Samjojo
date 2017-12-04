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

	_fontNum = FONTVERSION_SAMJOJO_HEE;
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

	//RECT & bool define
	for (int i = 0; i < 7; i++) {
		_posUnits[i].posRC = RectMake(4 + (57 * i), 52, 48, 48);
		_posUnits[i].isPos = false;
	}
	//���� ���ĵ�������
	_posUnits[0].isPos = true;
	_posUnits[2].isPos = true;
	
	for (int i = 0; i < _vUnitsInFile.size(); i++) {
		_vUnitsInFile[i]->updateStatus();
		if (!_tcscmp(_vUnitsInFile[i]->getStatus().name, L"����")) {
			_chosang = _vUnitsInFile[i]->getStatus().imgFace;
			_tcscpy(_name, _vUnitsInFile[i]->getStatus().name);
			_tcscpy(_aos, _vUnitsInFile[i]->getStatus().aos);
			
			_level = _vUnitsInFile[i]->getStatus().level;
			_pwr = _vUnitsInFile[i]->getStatus().Pwr;
			_lds = _vUnitsInFile[i]->getStatus().Lds;
			_int = _vUnitsInFile[i]->getStatus().Int;
			_dex = _vUnitsInFile[i]->getStatus().Dex;
			_luk = _vUnitsInFile[i]->getStatus().Luk;
			_hpMax = _vUnitsInFile[i]->getStatus().HPMax;
			_mpMax = _vUnitsInFile[i]->getStatus().MPMax;
			_exp = _vUnitsInFile[i]->getStatus().exp;
			_atk = _vUnitsInFile[i]->getStatus().Atk;
			_dep = _vUnitsInFile[i]->getStatus().Dep;
			_res = _vUnitsInFile[i]->getStatus().Res;
			_agl = _vUnitsInFile[i]->getStatus().Agl;
			_fig = _vUnitsInFile[i]->getStatus().Fig;
			_move = _vUnitsInFile[i]->getStatus().movePoint;

		}

	}
	_hpbar = IMAGEMANAGER->findImage(L"ü�¹�");
	_mpbar = IMAGEMANAGER->findImage(L"������");
	_expbar = IMAGEMANAGER->findImage(L"����ġ��");

	_atkbar	= IMAGEMANAGER->findImage(L"�ɷ�ġ��");
	_depbar	= IMAGEMANAGER->findImage(L"�ɷ�ġ��");
	_resbar	= IMAGEMANAGER->findImage(L"�ɷ�ġ��");
	_aglbar	= IMAGEMANAGER->findImage(L"�ɷ�ġ��");
	_figbar = IMAGEMANAGER->findImage(L"�ɷ�ġ��");

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
					_chosang = _vUnitsInFile[j]->getStatus().imgFace;
					_tcscpy(_name, _vUnitsInFile[j]->getStatus().name);
					_tcscpy(_aos, _vUnitsInFile[j]->getStatus().aos);
					_level = _vUnitsInFile[j]->getStatus().level;
					_pwr = _vUnitsInFile[j]->getStatus().Pwr;
					_lds = _vUnitsInFile[j]->getStatus().Lds;
					_int = _vUnitsInFile[j]->getStatus().Int;
					_dex = _vUnitsInFile[j]->getStatus().Dex;
					_luk = _vUnitsInFile[j]->getStatus().Luk;
					_hpMax = _vUnitsInFile[j]->getStatus().HPMax;
					_mpMax = _vUnitsInFile[j]->getStatus().MPMax;
					_exp = _vUnitsInFile[j]->getStatus().exp;
					_atk = _vUnitsInFile[j]->getStatus().Atk;
					_dep = _vUnitsInFile[j]->getStatus().Dep;
					_res = _vUnitsInFile[j]->getStatus().Res;
					_agl = _vUnitsInFile[j]->getStatus().Agl;
					_fig = _vUnitsInFile[j]->getStatus().Fig;
					_move = _vUnitsInFile[j]->getStatus().movePoint;
				}
			}
		}
	}
	for (int i = 0; i < _vUnits.size(); i++) {
		if (PtInRect(&posRC2[i], _pt)) {
			_chosang = _vUnits[i]->getStatus().imgFace;
			_tcscpy(_name, _vUnits[i]->getStatus().name);
			_tcscpy(_aos, _vUnits[i]->getStatus().aos);
			_level = _vUnits[i]->getStatus().level;
			_pwr = _vUnits[i]->getStatus().Pwr;
			_lds = _vUnits[i]->getStatus().Lds;
			_int = _vUnits[i]->getStatus().Int;
			_dex = _vUnits[i]->getStatus().Dex;
			_luk = _vUnits[i]->getStatus().Luk;
			_hpMax = _vUnits[i]->getStatus().HPMax;
			_mpMax = _vUnits[i]->getStatus().MPMax;
			_exp = _vUnits[i]->getStatus().exp;
			_atk = _vUnits[i]->getStatus().Atk;
			_dep = _vUnits[i]->getStatus().Dep;
			_res = _vUnits[i]->getStatus().Res;
			_agl = _vUnits[i]->getStatus().Agl;
			_fig = _vUnits[i]->getStatus().Fig;
			_move = _vUnits[i]->getStatus().movePoint;
		}
	}



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
			SOUNDMANAGER->play(L"Se03", 1.0f);

			_vUnits.clear();
			_player->setUnits(_vUnits);
			_player->registUnitBasic();
			SCENEMANAGER->changeScene(L"�غ�⺻��");
		}
		if(PtInRect(&_rcOK, _pt) && _availableOK) {  //����Ŭ��
			_player->locateUnits();
			
			SOUNDMANAGER->play(L"Se03", 1.0f);
			SCENEMANAGER->changeScene(L"�غ�⺻��");
		}
		for (int i = 0; i < 7; i++) {
			if (PtInRect(&_posUnits[i].posRC, _pt) && !_posUnits[i].isPos) { //�� �������Ʈ�� �ϳ�Ŭ��  (�߰�)
				SOUNDMANAGER->play(L"Se02", 1.0f);
				_posUnits[i].isPos = true;
				for (int j = 0; j < _vUnitsInFile.size(); j++) {
					if (!_tcscmp(_posUnits[i].name, _vUnitsInFile[j]->getStatus().name)) {
						_player->registUnit(_vUnitsInFile[j]);    //vUnits ���Ϳ����� (��������Ʈ)
						_vUnits = _player->getUnits();
					}
				}
			}
		}
		for (int i = 0; i < _vUnits.size(); i++) {
			if (PtInRect(&posRC2[i], _pt) && i != 0 && i != 1) {   //�Ʒ� �������Ʈ�� �ϳ�Ŭ�� (����)
				SOUNDMANAGER->play(L"Se03", 1.0f);
				for (int j = 0; j < 7; j++) {
					if (!_tcscmp(_vUnits[i]->getStatus().name, _posUnits[j].name)) {
						_posUnits[j].isPos = false;
						break;
					}
				}
				_player->cancleUnit(i); //����
				_vUnits = _player->getUnits();  //����
			}
		}
	}

	if (_vUnits.size() > 3) _availableOK = true;
	else _availableOK = false;

	for (int i = 0; i < _vUnits.size(); i++) {
		posRC2[i] = RectMake(6 + (50 * i), 367, 48, 48);
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

	//for (int i = 0; i < 7; i++) {
	//	Rectangle(getMemDC(), _posUnits[i].posRC.left, _posUnits[i].posRC.top, _posUnits[i].posRC.right, _posUnits[i].posRC.bottom);
	//}

	//�Ʒ� ����,���ĵ� ������
	for (int i = 0; i < _vUnits.size(); i++) {
		_vUnits[i]->getBattleState().imgBattleIdle->frameRender(getMemDC(), 6 + (50 * i), 367, 0, 0);
	}
	
	_chosang->render(getMemDC(), 416, 44);

	HFONT oldFont = (HFONT)SelectObject(getMemDC(), _gFont[_fontNum]);
	TextOut(getMemDC(),538, 45,_name,_tcslen(_name));
	TextOut(getMemDC(), 538, 60, _aos, _tcslen(_aos));
	TCHAR tmp2[4];
	_stprintf(tmp2, L"%2d", _level);
	TextOut(getMemDC(), 579, 75, tmp2, _tcslen(tmp2));
	_stprintf(tmp2, L"%d", _pwr);
	TextOut(getMemDC(), 579, 91, tmp2, _tcslen(tmp2));
	_stprintf(tmp2, L"%d", _lds);
	TextOut(getMemDC(), 579, 106, tmp2, _tcslen(tmp2));
	_stprintf(tmp2, L"%d", _int);
	TextOut(getMemDC(), 579, 121, tmp2, _tcslen(tmp2));
	_stprintf(tmp2, L"%d", _dex);
	TextOut(getMemDC(), 579, 136, tmp2, _tcslen(tmp2));
	_stprintf(tmp2, L"%d", _luk);
	TextOut(getMemDC(), 579, 151, tmp2, _tcslen(tmp2));
	_stprintf(tmp2, L"%3d", _hpMax);
	TextOut(getMemDC(), 569, 179, tmp2, _tcslen(tmp2));
	_stprintf(tmp2, L"%3d", _mpMax);
	TextOut(getMemDC(), 569, 215, tmp2, _tcslen(tmp2));
	_stprintf(tmp2, L"%3d", _exp);
	TextOut(getMemDC(), 569, 248, tmp2, _tcslen(tmp2));
	_stprintf(tmp2, L"%3d", _atk);
	TextOut(getMemDC(), 569, 286, tmp2, _tcslen(tmp2));
	_stprintf(tmp2, L"%3d", _dep);
	TextOut(getMemDC(), 569, 319, tmp2, _tcslen(tmp2));
	_stprintf(tmp2, L"%3d", _res);
	TextOut(getMemDC(), 569, 355, tmp2, _tcslen(tmp2));
	_stprintf(tmp2, L"%3d", _agl);
	TextOut(getMemDC(), 569, 388, tmp2, _tcslen(tmp2));
	_stprintf(tmp2, L"%3d", _fig);
	TextOut(getMemDC(), 569, 424, tmp2, _tcslen(tmp2));
	_stprintf(tmp2, L"%3d", _move);
	TextOut(getMemDC(), 569, 457, tmp2, _tcslen(tmp2));
	_stprintf(tmp2, L"%d", _vUnits.size());
	TextOut(getMemDC(), 81, 348, tmp2, _tcslen(tmp2));
	SelectObject(getMemDC(), oldFont);
	DeleteObject(oldFont);
	
	_hpbar->render(getMemDC(), 424, 182 ,0, 0, 129*(_hpMax/1000.0f), 9);
	_mpbar->render(getMemDC(), 424, 218, 0, 0, 129 * (_mpMax / 250.0f), 9);
	_expbar->render(getMemDC(), 424, 251, 0, 0, 129 * (_exp / 100.0f), 9);
	
	_atkbar->render(getMemDC(), 424, 287, 0, 0, 129 * (_atk / 1000.0f), 9);
	_depbar->render(getMemDC(), 424, 320, 0, 0, 129 * (_dep / 1000.0f), 9);
	_resbar->render(getMemDC(), 424, 356, 0, 0, 129 * (_res / 1000.f), 9);
	_aglbar->render(getMemDC(), 424, 389, 0, 0, 129 * (_agl / 1000.0f), 9);
	_figbar->render(getMemDC(), 424, 425, 0, 0, 129 * (_fig / 1000.0f), 9);

	TCHAR tmp3[32];
	SetTextColor(getMemDC(), RGB(255, 255, 255));
	_stprintf(tmp3, L"����");
	TextOut(getMemDC(), 12, 105, tmp3, _tcslen(tmp3));
	_stprintf(tmp3, L"����");
	TextOut(getMemDC(), 70, 105, tmp3, _tcslen(tmp3));
	_stprintf(tmp3, L"���ĵ�");
	TextOut(getMemDC(), 118, 105, tmp3, _tcslen(tmp3));
	_stprintf(tmp3, L"���Ŀ�");
	TextOut(getMemDC(), 178, 105, tmp3, _tcslen(tmp3));
	_stprintf(tmp3, L"����");
	TextOut(getMemDC(), 244, 105, tmp3, _tcslen(tmp3));
	_stprintf(tmp3, L"����");
	TextOut(getMemDC(), 300, 105, tmp3, _tcslen(tmp3));
	_stprintf(tmp3, L"��ȫ");
	TextOut(getMemDC(), 356, 105, tmp3, _tcslen(tmp3));
	SetTextColor(getMemDC(), RGB(0, 0, 0));

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

	//TCHAR tmp[30];
	//_stprintf(tmp, L"x: %d, y: %d", _pt.x, _pt.y);
	//TextOut(getMemDC(), 100, 100, tmp, _tcslen(tmp));

	//TextOut(getMemDC(), 300, 300, _vUnitsInFile[0]->getStatus().name, _tcslen(_vUnitsInFile[0]->getStatus().name));
	//Rectangle(getMemDC(), _rcCancel.left, _rcCancel.top, _rcCancel.right, _rcCancel.bottom);
	//for(int i=0; i<_vUnits.size(); i++)
	//	Rectangle(getMemDC(), posRC2[i].left, posRC2[i].top, posRC2[i].right, posRC2[i].bottom);
	
}