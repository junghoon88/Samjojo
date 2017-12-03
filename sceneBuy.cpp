#include "stdafx.h"
#include "sceneBuy.h"


sceneBuy::sceneBuy()
{

}


sceneBuy::~sceneBuy()
{
}

HRESULT sceneBuy::init(void)
{
	DATABASE->getSlectScenario();
	_baseUI = IMAGEMANAGER->findImage(L"구입무기상");
	_baseUI2 = IMAGEMANAGER->findImage(L"구입도구상");

	_base1 = true;

	_baseRC[0] = RectMake(13, 47, 66, 20);
	_baseRC[1] = RectMake(83, 47, 66, 20);
	
	_EXIT = new button;
	_EXIT->init(L"SELECT-선택버튼", L"나가기", 55, 350, { 0,0 }, { 0,1 }, selectExit, this);

	_gold = _player->getGold();
	_fontNum = FONTVERSION_SAMJOJO_HEE;

	if (_vItemlist.empty()) {   //최초1번
		//검
		_weaponList = new ItemWeapon;
		_weaponList->init(WEAPON, SWORD, L"단검", 8, 0, 0, 0, 0, 500);
		_vItemlist.push_back(_weaponList);
		_weaponList = new ItemWeapon;
		_weaponList->init(WEAPON, SWORD, L"고정도", 12, 0, 0, 0, 0, 1000);
		_vItemlist.push_back(_weaponList);
		_weaponList = new ItemWeapon;
		_weaponList->init(WEAPON, HSWORD, L"의천검", 16, 0, 0, 0, 0, 1500);
		_vItemlist.push_back(_weaponList);
		_weaponList = new ItemWeapon;
		_weaponList->init(WEAPON, HSWORD, L"제후검", 14, 0, 0, 0, 0, 1300);
		_vItemlist.push_back(_weaponList);
		//창
		_weaponList = new ItemWeapon;
		_weaponList->init(WEAPON, SPEAR, L"단창", 8, 0, 0, 0, 0, 500);
		_vItemlist.push_back(_weaponList);
		//활
		_weaponList = new ItemWeapon;
		_weaponList->init(WEAPON, BOW, L"반궁", 10, 0, 0, 0, 0, 700);
		_vItemlist.push_back(_weaponList);
		//갑옷
		_armorList = new ItemArmor;
		_armorList->init(DEFENCE, ARMOR, L"가죽갑옷", 0, 10, 0, 0, 0, 500);
		_vItemlist.push_back(_armorList);
		//방패
		_armorList = new ItemArmor;
		_armorList->init(DEFENCE, SHILED, L"가죽방패", 0, 10, 0, 0, 0, 500);
		_vItemlist.push_back(_armorList);
		_armorList = new ItemArmor;
		_armorList->init(DEFENCE, SHILED, L"황금방패", 0, 15, 0, 0, 0, 1000);
		_vItemlist.push_back(_armorList);

		//보조
		_specialList = new ItemSpecial;
		_specialList->init(SPECIAL, L"태평청령서", 0, 0, 0, 50, 0, 700);
		_vItemlist.push_back(_specialList);
		_specialList = new ItemSpecial;
		_specialList->init(SPECIAL, L"신수장갑", 0, 0, 0, 30, 0, 600);
		_vItemlist.push_back(_specialList);
	}

	for (int i = 0; i < 12; i++) {
		_listRC[i] = RectMake(15, 88+(i*20), 440, 16);
	}

	return S_OK;
}
void sceneBuy::release(void)
{

}
void sceneBuy::update(void)	 
{
	_pt = _ptMouse;

	if (PtInRect(&_baseRC[0], _pt)&&!_base1) {
		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) {
			_base1 = true;
		}
	}
	if (PtInRect(&_baseRC[1], _pt) && _base1) {
		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) {
			_base1 = false;
		}
	}
	
	_EXIT->update();
}
void sceneBuy::render(void)	 
{
	if(_base1)	_baseUI->render(getMemDC(), 0, 0);
	else		_baseUI2->render(getMemDC(), 0, 0);

	if (_base1) {
		for (int i = 0; i < _vItemlist.size(); i++) {
			_vItemlist[i]->getImg16()->render(getMemDC(), 15, 88 + (i * 20));  //이미지
			TextOut(getMemDC(), 40, 90 + (i * 20), _vItemlist[i]->getName(), _tcslen(_vItemlist[i]->getName())); //이름
			switch (_vItemlist[i]->getIclass()) { //속성
			case WEAPON:
				TCHAR tmp[20];
				_stprintf(tmp, L"공격력+%2d", _vItemlist[i]->getAtk());
				TextOut(getMemDC(), 335, 90 + (i * 20), tmp, _tcslen(tmp));
				if (_vItemlist[i]->getWclass() == HSWORD) TextOut(getMemDC(), 205, 90 + (i * 20), L"명검", _tcslen(L"명검"));
				else if(_vItemlist[i]->getWclass()==SWORD) TextOut(getMemDC(), 205, 90 + (i * 20), L"검", _tcslen(L"검"));
				else if(_vItemlist[i]->getWclass()==BOW) TextOut(getMemDC(), 205, 90 + (i * 20), L"활", _tcslen(L"활"));
				else TextOut(getMemDC(), 205, 90 + (i * 20), L"창", _tcslen(L"창"));
				break;
			case DEFENCE:
				TCHAR tmp2[20];
				_stprintf(tmp2, L"방어력+%2d", _vItemlist[i]->getDep());
				TextOut(getMemDC(), 335, 90 + (i * 20), tmp2, _tcslen(tmp2));
				if (_vItemlist[i]->getAclass() == ARMOR) TextOut(getMemDC(), 205, 90 + (i * 20), L"갑옷", _tcslen(L"갑옷"));
				else TextOut(getMemDC(), 205, 90 + (i * 20), L"방패", _tcslen(L"방패"));
				break;
			case SPECIAL:
				TCHAR tmp3[20];
				_stprintf(tmp3, L"HP+%2d", _vItemlist[i]->getHP());
				TextOut(getMemDC(), 335, 90 + (i * 20), tmp3, _tcslen(tmp3));
				TextOut(getMemDC(), 205, 90 + (i * 20), L"보조", _tcslen(L"보조"));
				break;
			default: break;
			}
			TextOut(getMemDC(), 262, 90 + (i * 20), L"--", _tcslen(L"--"));
			TextOut(getMemDC(), 305, 90 + (i * 20), L"--", _tcslen(L"--"));
			TCHAR tmp4[20];
			_stprintf(tmp4, L"%4d", _vItemlist[i]->getPrice());        
			TextOut(getMemDC(), 420, 90 + (i * 20), tmp4, _tcslen(tmp4));     //가격
		}
	}
	else {    //콩
		IMAGEMANAGER->findImage(L"회복의콩")->render(getMemDC(), 15, 88);
		TextOut(getMemDC(), 40, 90, L"회복의 콩", _tcslen(L"회복의 콩"));
		TextOut(getMemDC(), 205, 90, L"HP회복", _tcslen(L"HP회복"));
		TextOut(getMemDC(), 335, 90, L"+50", _tcslen(L"+50"));
		TCHAR tmp5[4];
		//_stprintf(tmp5,L"%2d",)


	}






	for (int i = 0; i < 12; i++) {
		if (PtInRect(&_listRC[i], _pt)) {
			IMAGEMANAGER->findImage(L"선택바3")->alphaRender(getMemDC(),_listRC[i].left,_listRC[i].top, 100);
		}
	}


	HFONT oldFont = (HFONT)SelectObject(getMemDC(), _gFont[_fontNum]);
	SetTextColor(getMemDC(), RGB(0, 0, 0));
	TCHAR tmp[32];
	_stprintf(tmp, L"%5d", _gold);
	TextOut(getMemDC(), 330, 345, tmp, _tcslen(tmp));



	_EXIT->render();
}

//call back//////////////
void sceneBuy::selectExit(void* obj) {
	sceneBuy* sBuy = (sceneBuy*)obj;

	sBuy->exit();
}
//////////////////////////


void sceneBuy::buyItem(void) {  //ok

	

}

void sceneBuy::exit(void) {

	SCENEMANAGER->changeScene(L"준비기본씬");
}
