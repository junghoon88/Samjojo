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

	_baseImg = IMAGEMANAGER->findImage(L"레디UI");
	_baseImg2 = IMAGEMANAGER->findImage(L"레디UI2");
	_rcPosUI = RectMake(440, 350, 50, 50);
	_rcEquipUI = RectMake(490, 350, 50, 50);
	_rcBuyUI = RectMake(540, 350, 50, 50);
	_rcSellUI = RectMake(590, 350, 50, 50);

	_posClicking = _equipClicking = _buyClicking = _sellClicking = false;
	
	_sD = new scanDialog;
	_sD->init("scripts/script 04.txt");
	_sD->setNext(7);
	ShowCursor(true);

	
	_battleStart = false;

	SOUNDMANAGER->play(L"Se_b_02", 1.0f);

	_isSound = false;



	return S_OK;
}
void sceneReadybase::release(void) {
	_sD->release();
	SOUNDMANAGER->stop(L"Se_b_02");
	SOUNDMANAGER->stop(L"Se07");
	SAFE_DELETE(_sD);

}
void sceneReadybase::update(void) {


	_pt.x = _ptMouse.x;
	_pt.y = _ptMouse.y;

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON) && !_battleStart)
	{
		if (PtInRect(&_rcPosUI, _pt)) {  //출진창 누름
			_posClicking = true;
		}
		else{
			_posClicking = false;
		}
		if (PtInRect(&_rcEquipUI, _pt)) {  //장비창 누름
			_equipClicking = true;
		}
		else {
			_equipClicking = false;
		}
		if (PtInRect(&_rcBuyUI, _pt)) {  //장비창 누름
			_buyClicking = true;
		}
		else {
			_buyClicking = false;
		}
		if (PtInRect(&_rcSellUI, _pt)) {  //매각창 누름
			_sellClicking = true;
		}
		else {
			_sellClicking = false;
		}
	}
	if(KEYMANAGER->isOnceKeyUp(VK_LBUTTON)&&!_battleStart) 
	{
		if (PtInRect(&_rcPosUI, _pt)) 
		{   //출진창 누르고땜
			_posClicking = false;
			SOUNDMANAGER->play(L"Se02", 1.0f);
			SOUNDMANAGER->stop(L"Se_b_02");
			SCENEMANAGER->changeScene(L"출진씬");
		}
		else if (PtInRect(&_rcEquipUI, _pt))
		{
	
			_equipClicking = false;
			SOUNDMANAGER->play(L"Se02", 1.0f);
			SCENEMANAGER->changeScene(L"장비씬");
		}
		else if (PtInRect(&_rcBuyUI, _pt))
		{   
			_buyClicking = false;

			SOUNDMANAGER->play(L"Se02", 1.0f);
			SCENEMANAGER->changeScene(L"구매상점씬");

		}
		else if (PtInRect(&_rcSellUI, _pt))
		{   
			_sellClicking = false;

			SOUNDMANAGER->play(L"Se02", 1.0f);
			SCENEMANAGER->changeScene(L"판매상점씬");

		}
	}
	if (_isSound)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			SOUNDMANAGER->play(L"Se07", 1.0f);
			_isSound = false;
		}
	}
	_vUnits = _player->getUnits();
	if (_vUnits.size() > 3)
	{
		SOUNDMANAGER->stop(L"Se_b_02");

		_baseImg = IMAGEMANAGER->findImage(L"smap 0003");
		_battleStart = true;
		_sD->update();

		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_sD->loadDialog();
			_sD->update();
			_isSound = true;
	
			if (_sD->getNext() == 8)
			{
				SCENEMANAGER->changeScene(L"전투씬");
			}
		}
		
		
	}
	
}
void sceneReadybase::render(void) {

	if (!_battleStart)
		_baseImg->render(getMemDC(), 0, 0);
	else
		_baseImg2->render(getMemDC(), 0, 0);

	//TCHAR tmp[30];
	//_stprintf(tmp, L"x: %d, y: %d", _pt.x, _pt.y);
	//TextOut(getMemDC(), 100, 100, tmp, _tcslen(tmp));
	
	if (_posClicking) {
		IMAGEMANAGER->findImage(L"출진눌림")->render(getMemDC(), _rcPosUI.left, _rcPosUI.top);
	}
	if (_equipClicking) {
		IMAGEMANAGER->findImage(L"장비눌림")->render(getMemDC(), _rcEquipUI.left, _rcEquipUI.top );
	}
	if (_buyClicking) {
		IMAGEMANAGER->findImage(L"구입눌림")->render(getMemDC(), _rcBuyUI.left, _rcBuyUI.top);
	}
	if (_sellClicking) {
		IMAGEMANAGER->findImage(L"매각눌림")->render(getMemDC(), _rcSellUI.left, _rcSellUI.top);
	}

	//Rectangle(getMemDC(), _rcPosUI.left, _rcPosUI.top, _rcPosUI.right, _rcPosUI.bottom);
	
	_sD->render();
}