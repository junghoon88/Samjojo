#include "stdafx.h"
#include "mainGame.h"

#include "sceneInit.h"
#include "sceneSelect.h"
#include "sceneStory.h"
#include "sceneBattle.h"
#include "sceneReadybase.h"
#include "scenePos.h"
#include "sceneEquip.h"
#include "sceneBuy.h"
#include "sceneSell.h"
#include "sceneMaptool.h"
#include "sceneUnitEditor.h"
#include "sceneResult.h"


mainGame::mainGame()
	: _player(NULL), _friend(NULL), _enemy(NULL), _map(NULL)
{
	_stop = false;
	_winsize = { WINSIZEX, WINSIZEY };

	_FPS = 60.0f;
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
	_map = new gameMap;
	_map->init();

	_player->setLinkAdressFriend(_friend);
	_player->setLinkAdressEnemy(_enemy);
	_player->setLinkAdressMap(_map);

	_friend->setLinkAdressPlayer(_player);
	_friend->setLinkAdressEnemy(_enemy);
	_friend->setLinkAdressMap(_map);

	_enemy->setLinkAdressPlayer(_player);
	_enemy->setLinkAdressFriend(_friend);
	_enemy->setLinkAdressMap(_map);

	_map->setLinkAdressPlayer(_player);
	_map->setLinkAdressFriend(_friend);
	_map->setLinkAdressEnemy(_enemy);

	initScene();

	return S_OK;
}

void mainGame::initScene(void)
{
	gameNode* node = SCENEMANAGER->addScene(L"�ʱ�ȭ��", new sceneInit);  //���� ���ҽ� �ʱ�ȭ
	//node->init();
	
	SCENEMANAGER->addScene(L"������", new sceneMaptool);				//����
	SCENEMANAGER->addScene(L"���ֿ�����", new sceneUnitEditor);		//���ֻ���

	sceneSelect* _sceneSelect = new sceneSelect;					//�ó����� �����ϴ� ��(������ �Ϸ�Ǹ� ���丮, ��, ��Ʋ�� �Ѱ��ش�.)
	_sceneSelect->setLinkAdressPlayer(_player);
	_sceneSelect->setLinkAdressEnemy(_enemy);
	_sceneSelect->setLinkAdressFriend(_friend);
	_sceneSelect->setLinkAdressMap(_map);
	SCENEMANAGER->addScene(L"���þ�", _sceneSelect);



	SCENEMANAGER->addScene(L"��ȭ��", new sceneStory);				//���丮



	
	sceneReadybase* _sceneReadybase = new sceneReadybase;          //�غ�⺻��
	_sceneReadybase->setLinkAdressPlayer(_player);
	SCENEMANAGER->addScene(L"�غ�⺻��", _sceneReadybase);


	scenePos* _scenePos = new scenePos;                            //������
	_scenePos->setLinkAdressPlayer(_player);
	SCENEMANAGER->addScene(L"������", _scenePos);


	sceneEquip* _sceneEquip = new sceneEquip;                      //����
	_sceneEquip->setLinkAdressPlayer(_player);
	SCENEMANAGER->addScene(L"����", _sceneEquip);

	sceneBuy* _sceneBuy = new sceneBuy;							    //���Ż���
	_sceneBuy->setLinkAdressPlayer(_player);
	SCENEMANAGER->addScene(L"���Ż�����", _sceneBuy);
	_sceneEquip->setLinkAdressSceneBuy(_sceneBuy);

	sceneSell* _sceneSell = new sceneSell;							//�ǸŻ���
	_sceneSell->setLinkAdressPlayer(_player);
	_sceneSell->setLinkAdressSceneBuy(_sceneBuy);
	SCENEMANAGER->addScene(L"�ǸŻ�����", _sceneSell);
	

	sceneBattle* _sceneBattle = new sceneBattle;					//����
	_sceneBattle->setLinkAdressPlayer(_player);
	_sceneBattle->setLinkAdressEnemy(_enemy);
	_sceneBattle->setLinkAdressFriend(_friend);
	_sceneBattle->setLinkAdressMap(_map);
	SCENEMANAGER->addScene(L"������", _sceneBattle);

	SCENEMANAGER->addScene(L"�����", new sceneResult);

	SCENEMANAGER->changeScene(L"�ʱ�ȭ��");
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

	checkWindowSize();
	controlFPS();
	//playBGM();


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

void mainGame::setWindowResize(POINT size)
{
	if (_winsize.x == size.x && _winsize.y == size.y)
		return;

	_stop = true; 
	_winsize = size;
}

void mainGame::checkWindowSize(void)
{
	if (SCENEMANAGER->isCurScene(L"�ʱ�ȭ��"))
	{
		setWindowResize({ WINSIZEX2, WINSIZEY2 });
	}
	else if (SCENEMANAGER->isCurScene(L"���þ�"))
	{
		setWindowResize({ WINSIZEX2, WINSIZEY2 });
	}
	else if (SCENEMANAGER->isCurScene(L"������"))
	{
		setWindowResize({ WINSIZEX, WINSIZEY });
	}
	else if (SCENEMANAGER->isCurScene(L"���ֿ�����"))
	{
		setWindowResize({ WINSIZEX, WINSIZEY });
	}
	else if (SCENEMANAGER->isCurScene(L"��ȭ��"))
	{
		setWindowResize({ WINSIZEX2, WINSIZEY2 });
	}
	else if (SCENEMANAGER->isCurScene(L"������"))
	{
		setWindowResize({ WINSIZEX, WINSIZEY });
	}
	else if (SCENEMANAGER->isCurScene(L"�غ�⺻��"))
	{
		setWindowResize({ WINSIZEX2,WINSIZEY2 });
	}
	else if (SCENEMANAGER->isCurScene(L"������"))
	{
		setWindowResize({ WINSIZEX3,WINSIZEY3 });
	}
	else if (SCENEMANAGER->isCurScene(L"����"))
	{
		setWindowResize({ WINSIZEX4,WINSIZEY4 });
	}
	else if (SCENEMANAGER->isCurScene(L"���Ż�����"))
	{
		setWindowResize({ WINSIZEX5,WINSIZEY5 });
	}
	else if (SCENEMANAGER->isCurScene(L"�ǸŻ�����"))
	{
		setWindowResize({ WINSIZEX5,WINSIZEY5 });
	}
	else if (SCENEMANAGER->isCurScene(L"�����"))
	{
		setWindowResize({ WINSIZEX2,WINSIZEY2 });

	}
}

void mainGame::controlFPS(void)
{
	if (SCENEMANAGER->isCurScene(L"�ʱ�ȭ��"))
	{
		_FPS = 300.0f;
	}
	else
	{
		_FPS = 60.0f;
	}
}

void mainGame::playBGM(void)
{
	if (SCENEMANAGER->isCurScene(L"���þ�")
		|| SCENEMANAGER->isCurScene(L"������")
		|| SCENEMANAGER->isCurScene(L"���ֿ�����"))
	{
		if (SOUNDMANAGER->isPlaySound(L"Se_b_00") == FALSE)		SOUNDMANAGER->play(L"Se_b_00");
		if (SOUNDMANAGER->isPlaySound(L"Se_b_02") == TRUE)		SOUNDMANAGER->stop(L"Se_b_02");
		if (SOUNDMANAGER->isPlaySound(L"Se_b_04") == TRUE)		SOUNDMANAGER->stop(L"Se_b_04");
		if (SOUNDMANAGER->isPlaySound(L"Se_b_05") == TRUE)		SOUNDMANAGER->stop(L"Se_b_05");
	}
	else if (SCENEMANAGER->isCurScene(L"��ȭ��"))
	{
		if (SOUNDMANAGER->isPlaySound(L"Se_b_00") == TRUE)		SOUNDMANAGER->stop(L"Se_b_00");
		if (SOUNDMANAGER->isPlaySound(L"Se_b_02") == TRUE)		SOUNDMANAGER->stop(L"Se_b_02");
		if (SOUNDMANAGER->isPlaySound(L"Se_b_04") == TRUE)		SOUNDMANAGER->stop(L"Se_b_04");
		if (SOUNDMANAGER->isPlaySound(L"Se_b_05") == FALSE)		SOUNDMANAGER->play(L"Se_b_05");
	}
	else if (SCENEMANAGER->isCurScene(L"�غ�⺻��")
			|| SCENEMANAGER->isCurScene(L"������")
			|| SCENEMANAGER->isCurScene(L"����")
			|| SCENEMANAGER->isCurScene(L"���Ż�����")
			|| SCENEMANAGER->isCurScene(L"�ǸŻ�����"))
	{
		if (SOUNDMANAGER->isPlaySound(L"Se_b_00") == TRUE)		SOUNDMANAGER->stop(L"Se_b_00");
		if (SOUNDMANAGER->isPlaySound(L"Se_b_02") == FALSE)		SOUNDMANAGER->play(L"Se_b_02");
		if (SOUNDMANAGER->isPlaySound(L"Se_b_04") == TRUE)		SOUNDMANAGER->stop(L"Se_b_04");
		if (SOUNDMANAGER->isPlaySound(L"Se_b_05") == TRUE)		SOUNDMANAGER->stop(L"Se_b_05");
	}
	else if (SCENEMANAGER->isCurScene(L"������"))
	{
		if (SOUNDMANAGER->isPlaySound(L"Se_b_00") == TRUE)		SOUNDMANAGER->stop(L"Se_b_00");
		if (SOUNDMANAGER->isPlaySound(L"Se_b_02") == TRUE)		SOUNDMANAGER->stop(L"Se_b_02");
		if (SOUNDMANAGER->isPlaySound(L"Se_b_04") == FALSE)		SOUNDMANAGER->play(L"Se_b_04");
		if (SOUNDMANAGER->isPlaySound(L"Se_b_05") == TRUE)		SOUNDMANAGER->stop(L"Se_b_05");
	}
}
