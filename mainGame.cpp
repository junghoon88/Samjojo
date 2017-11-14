#include "stdafx.h"
#include "mainGame.h"

mainGame::mainGame()
{

}


mainGame::~mainGame()
{

}

//�ʱ�ȭ
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
	SCENEMANAGER->addScene(L"�ʱ�ȭ��", new sceneInit);
	SCENEMANAGER->addScene(L"�ε���", new sceneLoading);
	SCENEMANAGER->addScene(L"������", new sceneMaptool);

	sceneSelect* _sceneSelect = new sceneSelect;
	_sceneSelect->setLinkAdressPlayer(_player);
	_sceneSelect->setLinkAdressEnemy(_enemy);
	_sceneSelect->setLinkAdressFriend(_friend);
	SCENEMANAGER->addScene(L"������", _sceneSelect);

	sceneBattle* _sceneBattle = new sceneBattle;
	_sceneBattle->setLinkAdressPlayer(_player);
	_sceneBattle->setLinkAdressEnemy(_enemy);
	_sceneBattle->setLinkAdressFriend(_friend);
	SCENEMANAGER->addScene(L"��Ʋ��", _sceneBattle);

	SCENEMANAGER->changeScene(L"������");
}



//�޸� ����
void mainGame::release(void)
{
	gameNode::release();

	SCENEMANAGER->release();
}

//�������(Ÿ�̸�)
void mainGame::update(void)	
{
	gameNode::update();

	SCENEMANAGER->update();
}

//�׷��ִ� �Լ�
void mainGame::render(void)	
{
	//��� ��ȭ�� �� �� �ʿ�
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==============================================================
	
	SCENEMANAGER->render();


	RENDERMANAGER->render();

	TIMEMANAGER->render(getMemDC());
	
	//========================================================================
	//����ۿ� �ִ°� HDC�� �׷��ִ� ����
	this->getBackBuffer()->render(getHDC(), 0, 0);

}

