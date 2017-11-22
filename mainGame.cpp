#include "stdafx.h"
#include "mainGame.h"

#include "sceneInit.h"
#include "sceneLoading.h"
#include "sceneSelect.h"
#include "sceneStory.h"
#include "sceneBattle.h"
#include "sceneShop.h"
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

	//��� ���� ��ĵ test
	WIN32_FIND_DATA wfd;
	HANDLE handle = FindFirstFile(L"image/logo/*.bmp", &wfd);
	// ã�� ������ �ִٸ�,
	while(handle != INVALID_HANDLE_VALUE)
	{
	    
	    // FindNextFile ���� ������ �������� ���� ��� TRUE
	    // ���� ��� FALSE �� ����
		if (!FindNextFile(handle, &wfd))
		{
			break;
		}
	}
	// ���� ã�� �ڵ� �� �ݱ�   
	FindClose(handle);

	return S_OK;
}

void mainGame::initScene(void)
{
	gameNode* node = SCENEMANAGER->addScene(L"�ʱ�ȭ��", new sceneInit);  //���� ���ҽ� �ʱ�ȭ
	node->init();
	SCENEMANAGER->addScene(L"�ε���", new sceneLoading);				//�ʵ�����, ���ֵ����� ���� �ε���
	SCENEMANAGER->addScene(L"������", new sceneMaptool);				//����
	SCENEMANAGER->addScene(L"���ֿ�����", new sceneUnitEditor);		//���ֻ���

	sceneSelect* _sceneSelect = new sceneSelect;					//�ó����� �����ϴ� ��(������ �Ϸ�Ǹ� ���丮, ��, ��Ʋ�� �Ѱ��ش�.)
	_sceneSelect->setLinkAdressPlayer(_player);
	_sceneSelect->setLinkAdressEnemy(_enemy);
	_sceneSelect->setLinkAdressFriend(_friend);
	SCENEMANAGER->addScene(L"���þ�", _sceneSelect);



	SCENEMANAGER->addScene(L"��ȭ��", new sceneStory);				//���丮

	sceneShop* _sceneShop = new sceneShop;							//����
	_sceneShop->setLinkAdressPlayer(_player);
	_sceneShop->setLinkAdressEnemy(_enemy);
	_sceneShop->setLinkAdressFriend(_friend);
	SCENEMANAGER->addScene(L"������", _sceneShop);


	sceneBattle* _sceneBattle = new sceneBattle;					//����
	_sceneBattle->setLinkAdressPlayer(_player);
	_sceneBattle->setLinkAdressEnemy(_enemy);
	_sceneBattle->setLinkAdressFriend(_friend);
	SCENEMANAGER->addScene(L"������", _sceneBattle);

	SCENEMANAGER->changeScene(L"���ֿ�����");
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
		SCENEMANAGER->changeScene(L"���þ�");
	}
	else if (KEYMANAGER->isOnceKeyDown(VK_F3))
	{
		SCENEMANAGER->changeScene(L"��ȭ��");
	}
	else if (KEYMANAGER->isOnceKeyDown(VK_F4))
	{
		SCENEMANAGER->changeScene(L"������");
	}
	else if (KEYMANAGER->isOnceKeyDown(VK_F6))
	{
		SCENEMANAGER->changeScene(L"���ֿ�����");
	}
	else if (KEYMANAGER->isOnceKeyDown(VK_F7))
	{
		SCENEMANAGER->changeScene(L"������");
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
}

