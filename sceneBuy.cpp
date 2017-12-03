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
	_baseUI2 = IMAGEMANAGER->findImage(L"판매무기상");

	_base1 = true;

	//_OK = new button;
	//_OK->init(L"SELECT-작은선택버튼", L"예", 585, 348, { 0,0 }, { 0,1 }, selectOK, this);
	_EXIT = new button;
	_EXIT->init(L"SELECT-선택버튼", L"나가기", 55, 350, { 0,0 }, { 0,1 }, selectExit, this);




	return S_OK;
}
void sceneBuy::release(void)
{

}
void sceneBuy::update(void)	 
{
	_EXIT->update();
}
void sceneBuy::render(void)	 
{
	if(_base1)	_baseUI->render(getMemDC(), 0, 0);
	else		_baseUI2->render(getMemDC(), 0, 0);







	_EXIT->render();
}

//call back//////////////
void sceneBuy::selectExit(void* obj) {
	sceneBuy* sBuy = (sceneBuy*)obj;

	sBuy->exit();
}
void sceneBuy::selectOK(void* obj) {
	sceneBuy* sBuy = (sceneBuy*)obj;

	sBuy->buyItem();
}
void sceneBuy::selectCancel(void* obj) {
	sceneBuy* sBuy = (sceneBuy*)obj;

	sBuy->cancel();
}
//////////////////////////


void sceneBuy::buyItem(void) {  //ok

	

}
void sceneBuy::cancel(void) {


}
void sceneBuy::exit(void) {

	SCENEMANAGER->changeScene(L"준비기본씬");
}
