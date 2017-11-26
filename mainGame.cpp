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
	gameNode* node = SCENEMANAGER->addScene(L"초기화씬", new sceneInit);  //게임 리소스 초기화
	node->init();
	
	SCENEMANAGER->addScene(L"맵툴씬", new sceneMaptool);				//맵툴
	SCENEMANAGER->addScene(L"유닛에디터", new sceneUnitEditor);		//유닛생성

	sceneSelect* _sceneSelect = new sceneSelect;					//시나리오 선택하는 씬(선택이 완료되면 스토리, 샵, 배틀에 넘겨준다.)
	_sceneSelect->setLinkAdressPlayer(_player);
	_sceneSelect->setLinkAdressEnemy(_enemy);
	_sceneSelect->setLinkAdressFriend(_friend);
	SCENEMANAGER->addScene(L"선택씬", _sceneSelect);



	SCENEMANAGER->addScene(L"대화씬", new sceneStory);				//스토리


	sceneBuy* _sceneBuy = new sceneBuy;							    //구매상점
	_sceneBuy->setLinkAdressPlayer(_player);
	_sceneBuy->setLinkAdressEnemy(_enemy);
	_sceneBuy->setLinkAdressFriend(_friend);
	SCENEMANAGER->addScene(L"구매상점씬", _sceneBuy);

	sceneSell* _sceneSell = new sceneSell;							//판매상점
	_sceneSell->setLinkAdressPlayer(_player);
	_sceneSell->setLinkAdressEnemy(_enemy);
	_sceneSell->setLinkAdressFriend(_friend);
	SCENEMANAGER->addScene(L"판매상점씬", _sceneSell);


	sceneBattle* _sceneBattle = new sceneBattle;					//전투
	_sceneBattle->setLinkAdressPlayer(_player);
	_sceneBattle->setLinkAdressEnemy(_enemy);
	_sceneBattle->setLinkAdressFriend(_friend);
	SCENEMANAGER->addScene(L"전투씬", _sceneBattle);

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

