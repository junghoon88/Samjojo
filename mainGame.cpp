#include "stdafx.h"
#include "mainGame.h"

#include "sceneInit.h"
#include "sceneLoading.h"
#include "sceneStory.h"
#include "sceneSelect.h"
#include "sceneBattle.h"
#include "sceneMaptool.h"
#include "sceneUnitEditor.h"


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
	gameNode* node = SCENEMANAGER->addScene(L"�ʱ�ȭ��", new sceneInit);  //���� ���ҽ� �ʱ�ȭ
	node->init();
	SCENEMANAGER->addScene(L"�ε���", new sceneLoading); //���� ���̺� ���� �ε���
	SCENEMANAGER->addScene(L"������", new sceneMaptool);
	SCENEMANAGER->addScene(L"���ֿ�����", new sceneUnitEditor);

	SCENEMANAGER->addScene(L"��ȭ��", new sceneStory);

	sceneSelect* _sceneSelect = new sceneSelect;
	_sceneSelect->setLinkAdressPlayer(_player);
	_sceneSelect->setLinkAdressEnemy(_enemy);
	_sceneSelect->setLinkAdressFriend(_friend);
	SCENEMANAGER->addScene(L"���þ�", _sceneSelect);

	sceneBattle* _sceneBattle = new sceneBattle;
	_sceneBattle->setLinkAdressPlayer(_player);
	_sceneBattle->setLinkAdressEnemy(_enemy);
	_sceneBattle->setLinkAdressFriend(_friend);
	SCENEMANAGER->addScene(L"������", _sceneBattle);

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

	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		SCENEMANAGER->changeScene(L"������");
	}
	else if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		SCENEMANAGER->changeScene(L"��ȭ��");
	}
	else if (KEYMANAGER->isOnceKeyDown(VK_F3))
	{
		SCENEMANAGER->changeScene(L"���þ�");
	}
	else if (KEYMANAGER->isOnceKeyDown(VK_F4))
	{
		SCENEMANAGER->changeScene(L"������");
	}
	else if (KEYMANAGER->isOnceKeyDown(VK_F6))
	{
		SCENEMANAGER->changeScene(L"���ֿ�����");
	}

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

