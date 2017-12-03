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

	_baseUI = IMAGEMANAGER->findImage(L"장비UI");

	_button[BTN_NEXT] = new button;
	_button[BTN_NEXT]->init(L"SELECT-작은선택버튼", L"다음", 585, 348, { 0,0 }, { 0,1 }, selectNext, this);
	_button[BTN_PREV] = new button;
	_button[BTN_PREV]->init(L"SELECT-작은선택버튼", L"뒤로", 535, 348, { 0,0 }, { 0,1 }, selectPrev, this);
	_button[BTN_EXIT] = new button;
	_button[BTN_EXIT]->init(L"SELECT-선택버튼", L"종료", 295, 348, { 0,0 }, { 0,1 }, selectExit, this);

	_vUnitsInFile = _player->getUnitsInFile();

	_index = 0;  //조조

	_tcscpy(_name2[0], L"조조");
	_tcscpy(_name2[1], L"하후돈");
	_tcscpy(_name2[2], L"조인");
	_tcscpy(_name2[3], L"하후연");
	_tcscpy(_name2[4], L"악진");
	_tcscpy(_name2[5], L"이전");
	_tcscpy(_name2[6], L"조홍");


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
	_weapon->init(WEAPON,SWORD, L"단검",8, 0, 0, 0, 0);
	_vItems.push_back(_weapon);
	_weapon = new ItemWeapon;
	_weapon->init(WEAPON,SWORD, L"고정도", 12, 0, 0, 0, 0);
	_vItems.push_back(_weapon);
	_weapon = new ItemWeapon;
	_weapon->init(WEAPON, HSWORD, L"의천검", 16, 0, 0, 0, 0);
	_vItems.push_back(_weapon);
	_armor = new ItemArmor;
	_armor->init(DEFENCE, SHILED, L"가죽방패", 0, 10, 0, 0, 0);
	_vItems.push_back(_armor);
	_special = new ItemSpecial;
	_special->init(SPECIAL, L"태평청령서", 0, 0, 0, 50, 0);
	_vItems.push_back(_special);
	//
	for (int i = 0; i < _vUnitsInFile.size(); i++)
		_vUnitsInFile[i]->updateStatus();

	for (int i = 0; i < 13; i++) {
		_rcItm[i] = RectMake(12, 64 + (i * 20), 327, 16);
	}

	_rcItm2[0] = RectMake(484, 65, 144, 90);
	_rcItm2[1] = RectMake(484, 162, 144, 90);
	_rcItm2[2] = RectMake(484, 260, 144, 72);

	return S_OK;
}
void sceneEquip::release(void) {

}
void sceneEquip::update(void) {
	_pt = _ptMouse;

	for (int i = 0; i < _vUnitsInFile.size(); i++) {
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

	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) {       //실질적 장착
		for (int i = 0; i < _vItems.size(); i++) {
			if (PtInRect(&_rcItm[i], _pt) && _available[i] == true) {
				switch (_vItems[i]->getIclass()) {
				case WEAPON:
					//_weaponU = new ItemWeapon;
					//_weaponU->copyItem(_vItems[i]);
					//_vUnitsInFile[_index]->setItemW(_weaponU);
					_vUnitsInFile[_index]->setItemW(_vItems[i]);
					break;
				case DEFENCE:
					//_armorU = new ItemArmor;
					//_armorU->copyItem(_vItems[i]);
					//_vUnitsInFile[_index]->setItemA(_armorU);
					_vUnitsInFile[_index]->setItemA(_vItems[i]);
					break;
				case SPECIAL:
					//_specialU = new ItemSpecial;
					//_specialU->copyItem(_vItems[i]);
					//_vUnitsInFile[_index]->setItemS(_specialU);
					_vUnitsInFile[_index]->setItemS(_vItems[i]);
					break;
				default:
					break;
				}
				SAFE_DELETE(_vItems[i]);                 //메모리해제
				_vItems.erase(_vItems.begin() + i);      //목록에서 제거	
				_vUnitsInFile[_index]->updateStatus();             //스탯 업데이트
			}
		}
	}

	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) {
		for (int i = 0; i < 3; i++) {
			if (PtInRect(&_rcItm2[i], _pt)) {
				switch (i) {
				case 0:
					//if (_vUnitsInFile[i]->getItemW() != NULL) {
						_weapon = new ItemWeapon;
						_weapon->copyItem(_vUnitsInFile[i]->getItemW());
						_vItems.push_back(_weapon);
						_vUnitsInFile[i]->setItemW(NULL);
				//	}
					break;
				case 1:
					if (_vUnitsInFile[i]->getItemA() != NULL) {
						_armor = new ItemArmor;
						_armor->copyItem(_vUnitsInFile[i]->getItemA());
						_vItems.push_back(_armor);
						_vUnitsInFile[i]->setItemA(NULL);
					}
					break;
				case 2:
					if (_vUnitsInFile[i]->getItemS() != NULL) {
						_special = new ItemSpecial;
						_special->copyItem(_vUnitsInFile[i]->getItemS());
						_vItems.push_back(_special);
						//SAFE_DELETE(_vUnitsInFile[i]->getItemS());
						_vUnitsInFile[i]->setItemS(NULL);
					}
					break;
				default: break;
				}
			}
		}






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
	for (int i = 0; i < _vItems.size(); i++) {
		_vItems[i]->getImg16()->render(getMemDC(), 12, 64 + (i * 20));//12,64

		HFONT oldFont = (HFONT)SelectObject(getMemDC(), _gFont[_fontNum]);
		SetTextColor(getMemDC(), RGB(0, 0, 0));
		TextOut(getMemDC(), 32, 64 + (i * 20), _vItems[i]->getName(), _tcslen(_vItems[i]->getName()));

		if (_vItems[i]->getIclass() == WEAPON) {
			switch (_vItems[i]->getWclass()) {
			case HSWORD:
				_tcscpy(_itemClass, L"명검");
				break;
			case SWORD:
				_tcscpy(_itemClass, L"검");
				break;
			case BOW:
				_tcscpy(_itemClass, L"활");
				break;
			case SPEAR:
				_tcscpy(_itemClass, L"창");
				break;
			default: break;
			}
		}
		else if(_vItems[i]->getIclass()==DEFENCE) {
			switch (_vItems[i]->getAclass()) {
			case ARMOR:
				_tcscpy(_itemClass, L"갑옷");
				break;
			case SHILED:
				_tcscpy(_itemClass, L"방패");
				break;
			default: break;
			}
		}
		else { //special
			_tcscpy(_itemClass, L"보조");
		}
		TextOut(getMemDC(), 150, 64+ (i * 20), _itemClass, _tcslen(_itemClass));
		TextOut(getMemDC(), 190, 64+ (i * 20), L"--", _tcslen(L"--"));
		TextOut(getMemDC(), 220, 64+ (i * 20), L"--", _tcslen(L"--"));

		TCHAR tmp[6];
		if (_vItems[i]->getIclass() == WEAPON)
			_stprintf(tmp, L"+%2d", _vItems[i]->getAtk());
		else if (_vItems[i]->getIclass() == DEFENCE)
			_stprintf(tmp, L"+%2d", _vItems[i]->getDep());
		else //special
			_stprintf(tmp, L"--");
		TextOut(getMemDC(), 270, 64 + (i * 20), tmp, _tcslen(tmp));


		//장비가능유무//////////////////
		if (_vItems[i]->getIclass() == WEAPON) {
			switch (_vItems[i]->getWclass()) {
			case HSWORD:
				if (!_tcscmp(_aos, L"군웅")) {
					_availableEquip = true;
				}
				else {
					_availableEquip = false;
				}
				break;

			case SWORD:
				if (!_tcscmp(_aos, L"군웅") || !_tcscmp(_aos, L"경보병") || !_tcscmp(_aos, L"보병")) {
					_availableEquip = true;
				}
				else {
					_availableEquip = false;
				}
				break;
			case BOW:
				if (!_tcscmp(_aos, L"궁기병")) {
					_availableEquip = true;
				}
				else {
					_availableEquip = false;
				}
				break;
			case SPEAR:
				if (!_tcscmp(_aos, L"용장") || !_tcscmp(_aos, L"경기병")
					|| !_tcscmp(_aos, L"도위") || !_tcscmp(_aos, L"기병")) {
					_availableEquip = true;
				}
				else {
					_availableEquip = false;
				}
				break;
			default: break;
			}
		}
		else if (_vItems[i]->getIclass() == DEFENCE) {
			switch (_vItems[i]->getAclass()) {
			case ARMOR:
				_availableEquip = true;
				break;
			case SHILED:
				if (!_tcscmp(_aos, L"보병") || !_tcscmp(_aos, L"경보병"))
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
		_available[i] = _availableEquip;
		///////////////////

		if (_availableEquip) {
			TextOut(getMemDC(), 310, 64 + (i * 20), L"O", _tcslen(L"O"));
		}
		else {
			TextOut(getMemDC(), 310, 64 + (i * 20), L"X", _tcslen(L"X"));
		}
	}
	for (int i = 0; i < 13; i++) {
		if (PtInRect(&_rcItm[i], _pt)) {
			IMAGEMANAGER->findImage(L"선택바")->alphaRender(getMemDC(), 12, 64 + (i * 20), 100);
		}
	}
	for (int i = 0; i < 3; i++) {
		if (PtInRect(&_rcItm2[i], _pt)) {
			IMAGEMANAGER->findImage(L"선택바2")->alphaRender(getMemDC(), _rcItm2[i].left, _rcItm2[i].top, 100);
		}
	}

	if (_vUnitsInFile[_index]->getItemW() != NULL) {
		_vUnitsInFile[_index]->getItemW()->getImg32()->render(getMemDC(), 488, 86);
		HFONT oldFont = (HFONT)SelectObject(getMemDC(), _gFont[_fontNum]);
		SetTextColor(getMemDC(), RGB(0, 0, 0));
		TextOut(getMemDC(), 520, 67, _vUnitsInFile[_index]->getItemW()->getName(), _tcslen(_vUnitsInFile[_index]->getItemW()->getName()));
		TCHAR tmp[32];
		_stprintf(tmp, L"공격력 +%2d", _vUnitsInFile[_index]->getItemW()->getAtk());
		TextOut(getMemDC(), 486, 120, tmp, _tcslen(tmp));
	}
	if (_vUnitsInFile[_index]->getItemA() != NULL) {
		_vUnitsInFile[_index]->getItemA()->getImg32()->render(getMemDC(), 488, 182);
		HFONT oldFont = (HFONT)SelectObject(getMemDC(), _gFont[_fontNum]);
		SetTextColor(getMemDC(), RGB(0, 0, 0));
		TextOut(getMemDC(), 520, 164, _vUnitsInFile[_index]->getItemA()->getName(), _tcslen(_vUnitsInFile[_index]->getItemA()->getName()));
		TCHAR tmp[32];
		_stprintf(tmp, L"방어력 +%2d", _vUnitsInFile[_index]->getItemA()->getDep());
		TextOut(getMemDC(), 486, 216, tmp, _tcslen(tmp));
	}
	if (_vUnitsInFile[_index]->getItemS() != NULL) {
		_vUnitsInFile[_index]->getItemS()->getImg32()->render(getMemDC(), 488, 279);
		HFONT oldFont = (HFONT)SelectObject(getMemDC(), _gFont[_fontNum]);
		SetTextColor(getMemDC(), RGB(0, 0, 0));
		TextOut(getMemDC(), 520, 262, _vUnitsInFile[_index]->getItemS()->getName(), _tcslen(_vUnitsInFile[_index]->getItemS()->getName()));
		TCHAR tmp[32];
		_stprintf(tmp, L"HP +%2d", _vUnitsInFile[_index]->getItemS()->getHP());
		TextOut(getMemDC(), 486, 313, tmp, _tcslen(tmp));
	}

	//for(int i=0; i<13; i++)
	//	Rectangle(getMemDC(), _rcItm[i].left, _rcItm[i].top, _rcItm[i].right, _rcItm[i].bottom);
	//for (int i = 0; i < 3; i++)
	//	Rectangle(getMemDC(), _rcItm2[i].left, _rcItm2[i].top, _rcItm2[i].right, _rcItm2[i].bottom);
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
	SCENEMANAGER->changeScene(L"준비기본씬");
}