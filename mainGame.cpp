#include "stdafx.h"
#include "mainGame.h"

#include "sceneInit.h"
#include "sceneSelect.h"
#include "sceneStory.h"
#include "sceneBattle.h"
#include "sceneBuy.h"
#include "sceneSell.h"
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
	
	SCENEMANAGER->addScene(L"������", new sceneMaptool);				//����
	SCENEMANAGER->addScene(L"���ֿ�����", new sceneUnitEditor);		//���ֻ���

	sceneSelect* _sceneSelect = new sceneSelect;					//�ó����� �����ϴ� ��(������ �Ϸ�Ǹ� ���丮, ��, ��Ʋ�� �Ѱ��ش�.)
	_sceneSelect->setLinkAdressPlayer(_player);
	_sceneSelect->setLinkAdressEnemy(_enemy);
	_sceneSelect->setLinkAdressFriend(_friend);
	SCENEMANAGER->addScene(L"���þ�", _sceneSelect);



	SCENEMANAGER->addScene(L"��ȭ��", new sceneStory);				//���丮


	sceneBuy* _sceneBuy = new sceneBuy;							    //���Ż���
	_sceneBuy->setLinkAdressPlayer(_player);
	_sceneBuy->setLinkAdressEnemy(_enemy);
	_sceneBuy->setLinkAdressFriend(_friend);
	SCENEMANAGER->addScene(L"���Ż�����", _sceneBuy);

	sceneSell* _sceneSell = new sceneSell;							//�ǸŻ���
	_sceneSell->setLinkAdressPlayer(_player);
	_sceneSell->setLinkAdressEnemy(_enemy);
	_sceneSell->setLinkAdressFriend(_friend);
	SCENEMANAGER->addScene(L"�ǸŻ�����", _sceneSell);


	sceneBattle* _sceneBattle = new sceneBattle;					//����
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
		SCENEMANAGER->changeScene(L"���þ�");
	}
	//�� �ٲٰ� ������ sceneSelect.cpp -> 150 line �� �����ϱ�

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

	//TIMEMANAGER->render(getMemDC());
	
	//========================================================================
	//����ۿ� �ִ°� HDC�� �׷��ִ� ����
	this->getBackBuffer()->render(getHDC(), 0, 0);

}

void mainGame::getChar(WPARAM wParam)
{
	if (SCENEMANAGER->isCurScene(L"���ֿ�����"))
	{
		SCENEMANAGER->getChar(wParam);
	}
	else if (SCENEMANAGER->isCurScene(L"������"))
	{
		SCENEMANAGER->getChar(wParam);
	}
}

