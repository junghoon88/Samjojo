#include "stdafx.h"
#include "sceneSell.h"
#include "sceneBuy.h"

sceneSell::sceneSell()
{
}


sceneSell::~sceneSell()
{
}


HRESULT sceneSell::init(void) 
{
	DATABASE->getSlectScenario();
	_baseUI = IMAGEMANAGER->findImage(L"�Ű������");
	_baseUI2 = IMAGEMANAGER->findImage(L"�Ű�������");
	_baseRC[0] = RectMake(13, 47, 66, 20);
	_baseRC[1] = RectMake(83, 47, 66, 20);

	_EXIT = new button;
	_EXIT->init(L"SELECT-���ù�ư", L"������", 55, 350, { 0,0 }, { 0,1 }, selectExit, this);

	_gold = _player->getGold();
	_fontNum = FONTVERSION_SAMJOJO_HEE;
	_sold = false;
	_messageTime = 0;
	_vItems = _sBuy->getVItems();

	for (int i = 0; i < 12; i++) {
		_listRC[i] = RectMake(15, 88 + (i * 20), 440, 16);
	}
	_base1 = true;
	return S_OK;
}
void sceneSell::release(void) 
{

}
void sceneSell::update(void)
{
	_pt = _ptMouse;
	if (PtInRect(&_baseRC[0], _pt) && !_base1) {
		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) {
			SOUNDMANAGER->play(L"Se02", 1.0f);
			_base1 = true;
		}
	}
	if (PtInRect(&_baseRC[1], _pt) && _base1) {
		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) {
			SOUNDMANAGER->play(L"Se02", 1.0f);
			_base1 = false;
		}
	}

	if (_base1) {
		for (int i = 0; i < _vItems.size(); i++) {
			if (PtInRect(&_listRC[i], _pt)) {
				if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) {
					SOUNDMANAGER->play(L"Se03", 1.0f);
					_sold = true;
					_gold += _vItems[i]->getPrice()*0.75f;
					SAFE_DELETE(_vItems[i]);
					_vItems.erase(_vItems.begin() + i);
				}
			}
		}
	}
	else {
		if (PtInRect(&_listRC[0], _pt)) {
			if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON)&&_player->getKong()>0) {
				SOUNDMANAGER->play(L"Se03", 1.0f);
				_sold = true;
				_gold += 75;
				_player->setKong(_player->getKong() - 1);
			}
		}
	}


	_EXIT->update();
}
void sceneSell::render(void)
{
	if (_base1)	_baseUI->render(getMemDC(), 0, 0);
	else		_baseUI2->render(getMemDC(), 0, 0);

	for (int i = 0; i < 12; i++) {
		if (PtInRect(&_listRC[i], _pt)) {
			IMAGEMANAGER->findImage(L"���ù�3")->alphaRender(getMemDC(), _listRC[i].left, _listRC[i].top, 100);
		}
	}

	if (_base1) {
		for (int i = 0; i < _vItems.size(); i++) {
			_vItems[i]->getImg16()->render(getMemDC(), 15, 88 + (i * 20));  //�̹���
			TextOut(getMemDC(), 40, 90 + (i * 20), _vItems[i]->getName(), _tcslen(_vItems[i]->getName())); //�̸�
			switch (_vItems[i]->getIclass()) { //�Ӽ�
			case WEAPON:
				TCHAR tmp[20];
				_stprintf(tmp, L"Atk+%2d", _vItems[i]->getAtk());
				TextOut(getMemDC(), 335, 90 + (i * 20), tmp, _tcslen(tmp));
				if (_vItems[i]->getWclass() == HSWORD) TextOut(getMemDC(), 205, 90 + (i * 20), L"���", _tcslen(L"���"));
				else if (_vItems[i]->getWclass() == SWORD) TextOut(getMemDC(), 205, 90 + (i * 20), L"��", _tcslen(L"��"));
				else if (_vItems[i]->getWclass() == BOW) TextOut(getMemDC(), 205, 90 + (i * 20), L"Ȱ", _tcslen(L"Ȱ"));
				else TextOut(getMemDC(), 205, 90 + (i * 20), L"â", _tcslen(L"â"));
				break;
			case DEFENCE:
				TCHAR tmp2[20];
				_stprintf(tmp2, L"Def+%2d", _vItems[i]->getDep());
				TextOut(getMemDC(), 335, 90 + (i * 20), tmp2, _tcslen(tmp2));
				if (_vItems[i]->getAclass() == ARMOR) TextOut(getMemDC(), 205, 90 + (i * 20), L"����", _tcslen(L"����"));
				else TextOut(getMemDC(), 205, 90 + (i * 20), L"����", _tcslen(L"����"));
				break;
			case SPECIAL:
				TCHAR tmp3[20];
				_stprintf(tmp3, L"HP+%2d", _vItems[i]->getHP());
				TextOut(getMemDC(), 335, 90 + (i * 20), tmp3, _tcslen(tmp3));
				TextOut(getMemDC(), 205, 90 + (i * 20), L"����", _tcslen(L"����"));
				break;
			default: break;
			}
			TextOut(getMemDC(), 262, 90 + (i * 20), L"--", _tcslen(L"--"));
			TextOut(getMemDC(), 305, 90 + (i * 20), L"--", _tcslen(L"--"));
			TCHAR tmp4[20];
			_stprintf(tmp4, L"%4.0f", _vItems[i]->getPrice()*0.75f);
			TextOut(getMemDC(), 420, 90 + (i * 20), tmp4, _tcslen(tmp4));     //����
		}
	}
	else {
		if (_player->getKong() > 0) {
			IMAGEMANAGER->findImage(L"ȸ������")->render(getMemDC(), 15, 88);
			TextOut(getMemDC(), 40, 90, L"ȸ���� ��", _tcslen(L"ȸ���� ��"));
			TextOut(getMemDC(), 205, 90, L"HPȸ��", _tcslen(L"HPȸ��"));
			TextOut(getMemDC(), 330, 90, L"+50", _tcslen(L"+50"));
			TCHAR tmp5[5];
			_stprintf(tmp5, L"%2d", _player->getKong());
			TextOut(getMemDC(), 380, 90, tmp5, _tcslen(tmp5));
			TextOut(getMemDC(), 425, 90, L"75", _tcslen(L"75"));
		}
	}
	HFONT oldFont = (HFONT)SelectObject(getMemDC(), _gFont[_fontNum]);
	SetTextColor(getMemDC(), RGB(0, 0, 0));
	TCHAR tmp[32];
	_stprintf(tmp, L"%5d", _gold);
	TextOut(getMemDC(), 330, 345, tmp, _tcslen(tmp));

	if (_sold) {  //�ǸſϷ� �޼���
		_messageTime += TIMEMANAGER->getElapsedTime();
		TextOut(getMemDC(), 180, 345, L"�ǸſϷ�", _tcslen(L"�ǸſϷ�"));
		if (_messageTime > 2.0f) {
			_sold = false;
			_messageTime = 0;
		}
	}
	SelectObject(getMemDC(), oldFont);
	DeleteObject(oldFont);

	_EXIT->render();
}

//call back//////////////
void sceneSell::selectExit(void* obj) {
	sceneSell* sSell = (sceneSell*)obj;

	sSell->exit();
}
//////////////////////////
void sceneSell::exit(void) {
	_player->setGold(_gold);
	_sBuy->setVItems(_vItems);
	SCENEMANAGER->changeScene(L"�غ�⺻��");
}