#include "stdafx.h"
#include "sceneEquip.h"


sceneEquip::sceneEquip()
{
}


sceneEquip::~sceneEquip()
{
}
HRESULT sceneEquip::init(void) {
	_fontNum = FONTVERSION_SAMJOJO_HEE;

	_baseUI = IMAGEMANAGER->findImage(L"���UI");

	_button[BTN_NEXT] = new button;
	_button[BTN_NEXT]->init(L"SELECT-�������ù�ư", L"����", 585, 348, { 0,0 }, { 0,1 }, selectNext, this);
	_button[BTN_PREV] = new button;
	_button[BTN_PREV]->init(L"SELECT-�������ù�ư", L"�ڷ�", 535, 348, { 0,0 }, { 0,1 }, selectPrev, this);
	_button[BTN_EXIT] = new button;
	_button[BTN_EXIT]->init(L"SELECT-���ù�ư", L"����", 295, 348, { 0,0 }, { 0,1 }, selectExit, this);

	_vUnitsInFile = _player->getUnitsInFile();

	_index = 0;  //����

	_tcscpy(_name2[0], L"����");
	_tcscpy(_name2[1], L"���ĵ�");
	_tcscpy(_name2[2], L"����");
	_tcscpy(_name2[3], L"���Ŀ�");
	_tcscpy(_name2[4], L"����");
	_tcscpy(_name2[5], L"����");
	_tcscpy(_name2[6], L"��ȫ");


	for (int i = 0; i < _vUnitsInFile.size(); i++) {
		_vUnitsInFile[i]->update(TEAM_PLAYER);
		if (!_tcscmp(_vUnitsInFile[i]->getStatus().name, _name2[_index])) {
			_chosang = _vUnitsInFile[i]->getStatus().imgFace;
			_tcscpy(_name, _vUnitsInFile[i]->getStatus().name);
			_tcscpy(_aos, _vUnitsInFile[i]->getStatus().aos);
			_level = _vUnitsInFile[i]->getStatus().level;
			_hpMax = _vUnitsInFile[i]->getStatus().HPMax;
			_mpMax = _vUnitsInFile[i]->getStatus().MPMax;
			_atk = _vUnitsInFile[i]->getStatus().Atk;
			_dep = _vUnitsInFile[i]->getStatus().Dep;
			_res = _vUnitsInFile[i]->getStatus().Res;
			_agl = _vUnitsInFile[i]->getStatus().Agl;
			_fig = _vUnitsInFile[i]->getStatus().Fig;
			_move = _vUnitsInFile[i]->getStatus().movePoint;
		}
	}

	//test

	_weapon = new ItemWeapon;
	_weapon->init(WEAPON,SWORD, L"�ܰ�", L"�ܰ�32", L"�ܰ�16", 8, 0, 0, 0, 0);
	_vItems.push_back(_weapon);
	_weapon = new ItemWeapon;
	_weapon->init(WEAPON,SWORD, L"������", L"������32", L"������16", 12, 0, 0, 0, 0);
	_vItems.push_back(_weapon);



	return S_OK;
}
void sceneEquip::release(void) {

}
void sceneEquip::update(void) {


	for (int i = 0; i < _vUnitsInFile.size(); i++) {
		_vUnitsInFile[i]->update(TEAM_PLAYER);
		if (!_tcscmp(_vUnitsInFile[i]->getStatus().name, _name2[_index])) {
			_chosang = _vUnitsInFile[i]->getStatus().imgFace;
			_tcscpy(_name, _vUnitsInFile[i]->getStatus().name);
			_tcscpy(_aos, _vUnitsInFile[i]->getStatus().aos);
			_level = _vUnitsInFile[i]->getStatus().level;
			_hpMax = _vUnitsInFile[i]->getStatus().HPMax;
			_mpMax = _vUnitsInFile[i]->getStatus().MPMax;
			_atk = _vUnitsInFile[i]->getStatus().Atk;
			_dep = _vUnitsInFile[i]->getStatus().Dep;
			_res = _vUnitsInFile[i]->getStatus().Res;
			_agl = _vUnitsInFile[i]->getStatus().Agl;
			_fig = _vUnitsInFile[i]->getStatus().Fig;
			_move = _vUnitsInFile[i]->getStatus().movePoint;
		}
	}

	for (int i = 0; i < BTN_MAXX; i++) {
		_button[i]->update();
	}
}
void sceneEquip::render(void) {
	_baseUI->render(getMemDC(),0,0);


	_chosang->render(getMemDC(), 358, 64);
	HFONT oldFont = (HFONT)SelectObject(getMemDC(), _gFont[_fontNum]);
	SetTextColor(getMemDC(), RGB(0, 0, 0));
	TextOut(getMemDC(), 360, 40, _name, _tcslen(_name));
	TextOut(getMemDC(), 400, 40, _aos, _tcslen(_aos));


	TCHAR tmp[10];
	_stprintf(tmp, L"Lv %2d", _level);
	TextOut(getMemDC(), 450, 40, tmp, _tcslen(tmp));
	_stprintf(tmp, L"%3d", _hpMax);
	TextOut(getMemDC(), 410, 210, tmp, _tcslen(tmp));
	_stprintf(tmp, L"%3d", _mpMax);
	TextOut(getMemDC(), 410, 228, tmp, _tcslen(tmp));
	_stprintf(tmp, L"%3d", _atk);
	TextOut(getMemDC(), 410, 248, tmp, _tcslen(tmp));
	_stprintf(tmp, L"%3d", _dep);
	TextOut(getMemDC(), 410, 267, tmp, _tcslen(tmp));
	_stprintf(tmp, L"%3d", _res);
	TextOut(getMemDC(), 410, 287, tmp, _tcslen(tmp));
	_stprintf(tmp, L"%3d", _agl);
	TextOut(getMemDC(), 410, 306, tmp, _tcslen(tmp));
	_stprintf(tmp, L"%3d", _fig);
	TextOut(getMemDC(), 410, 326, tmp, _tcslen(tmp));
	_stprintf(tmp, L"%3d", _move);
	TextOut(getMemDC(), 410, 345, tmp, _tcslen(tmp));
	

	//item render
	if (!_vItems.empty()) {
		_vItems[0]->getImg16()->render(getMemDC(), 12, 64);//12,64
		_vItems[1]->getImg16()->render(getMemDC(), 12, 84);

		HFONT oldFont = (HFONT)SelectObject(getMemDC(), _gFont[_fontNum]);
		SetTextColor(getMemDC(), RGB(0, 0, 0));
		TextOut(getMemDC(), 32, 64, _vItems[0]->getName(), _tcslen(_vItems[0]->getName()));
		switch (_vItems[0]->getWclass()) {
			case HSWORD:
				_tcscpy(_itemClass, L"���");
				break;
			case SWORD:
				_tcscpy(_itemClass, L"��");
				break;
			case BOW:
				_tcscpy(_itemClass, L"Ȱ");
				break;
			case SPEAR:
				_tcscpy(_itemClass, L"â");
				break;
			default: break;
		}
		TextOut(getMemDC(), 150, 64, _itemClass, _tcslen(_itemClass));
		TextOut(getMemDC(), 190, 64, L"--", _tcslen(L"--"));
		TextOut(getMemDC(), 220, 64, L"--", _tcslen(L"--"));

		TCHAR tmp[6];
		_stprintf(tmp, L"+%2d", _vItems[0]->getAtk());
		TextOut(getMemDC(), 270, 64, tmp, _tcslen(tmp));


		//��񰡴�����//////////////////
		if (_vItems[0]->getIclass() == WEAPON) {
			switch (_vItems[0]->getWclass()) {
			case HSWORD:
				if (!_tcscmp(_aos, L"����")) {
					_availableEquip = true;
				}
				else {
					_availableEquip = false;
				}
				break;

			case SWORD:
				if (!_tcscmp(_aos, L"����") || !_tcscmp(_aos, L"�溸��") || !_tcscmp(_aos, L"����")) {
					_availableEquip = true;
				}
				else {
					_availableEquip = false;
				}
				break;
			case BOW:
				if (!_tcscmp(_aos, L"�ñ⺴")) {
					_availableEquip = true;
				}
				else {
					_availableEquip = false;
				}
				break;
			case SPEAR:
				if (!_tcscmp(_aos, L"����") || !_tcscmp(_aos, L"��⺴")
					|| !_tcscmp(_aos, L"����") || !_tcscmp(_aos, L"�⺴")) {
					_availableEquip = true;
				}
				else {
					_availableEquip = false;
				}
				break;
			default: break;
			}
		}
		else if (_vItems[0]->getIclass() == DEFENCE) {
			switch (_vItems[0]->getAclass()) {
			case ARMOR:
				_availableEquip = true;
				break;
			case SHILED:
				if (!_tcscmp(_aos, L"����") || !_tcscmp(_aos, L"�溸��"))
					_availableEquip = true;
				else
					_availableEquip = false;
				break;
			default: break;
			}
		}
		else {
			_availableEquip = true;
		}
		///////////////////
		
		if (_availableEquip) {
			TextOut(getMemDC(), 310, 64, L"O", _tcslen(L"O"));
		}
		else {
			TextOut(getMemDC(), 310, 64, L"X", _tcslen(L"X"));
		}


	}



	for (int i = 0; i < BTN_MAXX; i++) {
		_button[i]->render();
	}

}

//-----------------------------------------------------------------------------------------
//callback functions
void sceneEquip::selectNext(void* obj)
{
	sceneEquip* sEquip = (sceneEquip*)obj;

		sEquip->next();
}
void sceneEquip::selectPrev(void* obj)
{
	sceneEquip* sEquip = (sceneEquip*)obj;

		sEquip->prev();
}
void sceneEquip::selectExit(void* obj)
{
	sceneEquip* sEquip = (sceneEquip*)obj;

		sEquip->exit();

}
//--------------------------------

void sceneEquip::next(void) {

	_index++;
	if (_index > 6) _index = 0;

}
void sceneEquip::prev(void) {

	_index--;
	if (_index < 0) _index = 6;
}
void sceneEquip::exit(void) {
	SCENEMANAGER->changeScene(L"�غ�⺻��");
}