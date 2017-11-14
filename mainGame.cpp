#include "stdafx.h"
#include "mainGame.h"

mainGame::mainGame()
{

}


mainGame::~mainGame()
{

}

//초기화
HRESULT mainGame::init(void)
{
	gameNode::init(true);

	_player = new Player;
	_player->init();
	_friend = new Friend;
	_friend->init();
	_enemy = new Enemy;
	_enemy->init();


	initScene();




	return S_OK;
}

void mainGame::initScene(void)
{
	SCENEMANAGER->addScene(L"초기화씬", new sceneInit);
	SCENEMANAGER->addScene(L"로딩씬", new sceneLoading);
	SCENEMANAGER->addScene(L"맵툴씬", new sceneMaptool);

	sceneSelect* _sceneSelect = new sceneSelect;
	_sceneSelect->setLinkAdressPlayer(_player);
	_sceneSelect->setLinkAdressEnemy(_enemy);
	_sceneSelect->setLinkAdressFriend(_friend);
	SCENEMANAGER->addScene(L"셀렉씬", _sceneSelect);

	sceneBattle* _sceneBattle = new sceneBattle;
	_sceneBattle->setLinkAdressPlayer(_player);
	_sceneBattle->setLinkAdressEnemy(_enemy);
	_sceneBattle->setLinkAdressFriend(_friend);
	SCENEMANAGER->addScene(L"배틀씬", _sceneBattle);

	SCENEMANAGER->changeScene(L"맵툴씬");
}



//메모리 해제
void mainGame::release(void)
{
	gameNode::release();

	SCENEMANAGER->release();
}

//연산관련(타이머)
void mainGame::update(void)	
{
	gameNode::update();

	SCENEMANAGER->update();
}

//그려주는 함수
void mainGame::render(void)	
{
	//흰색 도화지 한 장 필요
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==============================================================
	
	SCENEMANAGER->render();


	RENDERMANAGER->render();

	TIMEMANAGER->render(getMemDC());
	
	//========================================================================
	//백버퍼에 있는걸 HDC로 그려주는 역할
	this->getBackBuffer()->render(getHDC(), 0, 0);

}

