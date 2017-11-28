#include "stdafx.h"
#include "mainGame.h"

#include "sceneInit.h"
#include "sceneSelect.h"
#include "sceneStory.h"
#include "sceneBattle.h"
#include "sceneReadybase.h"
#include "scenePos.h"
#include "sceneBuy.h"
#include "sceneSell.h"
#include "sceneMaptool.h"
#include "sceneUnitEditor.h"


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
	gameNode* node = SCENEMANAGER->addScene(L"초기화씬", new sceneInit);  //게임 리소스 초기화
	//node->init();
	
	SCENEMANAGER->addScene(L"맵툴씬", new sceneMaptool);				//맵툴
	SCENEMANAGER->addScene(L"유닛에디터", new sceneUnitEditor);		//유닛생성

	sceneSelect* _sceneSelect = new sceneSelect;					//시나리오 선택하는 씬(선택이 완료되면 스토리, 샵, 배틀에 넘겨준다.)
	_sceneSelect->setLinkAdressPlayer(_player);
	_sceneSelect->setLinkAdressEnemy(_enemy);
	_sceneSelect->setLinkAdressFriend(_friend);
	_sceneSelect->setLinkAdressMap(_map);
	SCENEMANAGER->addScene(L"선택씬", _sceneSelect);



	SCENEMANAGER->addScene(L"대화씬", new sceneStory);				//스토리



	
	sceneReadybase* _sceneReadybase = new sceneReadybase;          //준비기본씬
	_sceneReadybase->setLinkAdressPlayer(_player);
	SCENEMANAGER->addScene(L"준비기본씬", _sceneReadybase);


	scenePos* _scenePos = new scenePos;                            //출진씬
	SCENEMANAGER->addScene(L"출진씬", _scenePos);

	sceneBuy* _sceneBuy = new sceneBuy;							    //구매상점
	SCENEMANAGER->addScene(L"구매상점씬", _sceneBuy);

	sceneSell* _sceneSell = new sceneSell;							//판매상점
	SCENEMANAGER->addScene(L"판매상점씬", _sceneSell);


	sceneBattle* _sceneBattle = new sceneBattle;					//전투
	_sceneBattle->setLinkAdressPlayer(_player);
	_sceneBattle->setLinkAdressEnemy(_enemy);
	_sceneBattle->setLinkAdressFriend(_friend);
	_sceneBattle->setLinkAdressMap(_map);
	SCENEMANAGER->addScene(L"전투씬", _sceneBattle);

	SCENEMANAGER->changeScene(L"초기화씬");
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

	checkWindowSize();
	controlFPS();


	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		SCENEMANAGER->changeScene(L"선택씬");
	}
	//씬 바꾸고 싶으면 sceneSelect.cpp -> 150 line 에 수정하기

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

	//TIMEMANAGER->render(getMemDC());
	
	//========================================================================
	//백버퍼에 있는걸 HDC로 그려주는 역할
	this->getBackBuffer()->render(getHDC(), 0, 0);

}

void mainGame::getChar(WPARAM wParam)
{
	if (SCENEMANAGER->isCurScene(L"유닛에디터"))
	{
		SCENEMANAGER->getChar(wParam);
	}
	else if (SCENEMANAGER->isCurScene(L"맵툴씬"))
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
	if (SCENEMANAGER->isCurScene(L"초기화씬"))
	{
		setWindowResize({ WINSIZEX2, WINSIZEY2 });
	}
	else if (SCENEMANAGER->isCurScene(L"선택씬"))
	{
		setWindowResize({ WINSIZEX2, WINSIZEY2 });
	}
	else if (SCENEMANAGER->isCurScene(L"맵툴씬"))
	{
		setWindowResize({ WINSIZEX, WINSIZEY });
	}
	else if (SCENEMANAGER->isCurScene(L"유닛에디터"))
	{
		setWindowResize({ WINSIZEX, WINSIZEY });
	}
	else if (SCENEMANAGER->isCurScene(L"대화씬"))
	{
		setWindowResize({ WINSIZEX2, WINSIZEY2 });
	}
	else if (SCENEMANAGER->isCurScene(L"전투씬"))
	{
		setWindowResize({ WINSIZEX, WINSIZEY });
	}
	else if (SCENEMANAGER->isCurScene(L"준비기본씬"))
	{
		setWindowResize({ WINSIZEX,WINSIZEY });
	}
	else if (SCENEMANAGER->isCurScene(L"출진씬"))
	{
		setWindowResize({ WINSIZEX3,WINSIZEY3 });
	}
}

void mainGame::controlFPS(void)
{
	if (SCENEMANAGER->isCurScene(L"초기화씬"))
	{
		_FPS = 300.0f;
	}
	else
	{
		_FPS = 60.0f;
	}
}