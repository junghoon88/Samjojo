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

	//모든 파일 스캔 test
	WIN32_FIND_DATA wfd;
	HANDLE handle = FindFirstFile(L"image/logo/*.bmp", &wfd);
	// 찾는 파일이 있다면,
	while(handle != INVALID_HANDLE_VALUE)
	{
	    
	    // FindNextFile 리턴 값으로 다음값이 있을 경우 TRUE
	    // 없을 경우 FALSE 값 리턴
		if (!FindNextFile(handle, &wfd))
		{
			break;
		}
	}
	// 파일 찾기 핸들 값 닫기   
	FindClose(handle);






	return S_OK;
}

void mainGame::initScene(void)
{
	gameNode* node = SCENEMANAGER->addScene(L"초기화씬", new sceneInit);  //게임 리소스 초기화
	node->init();
	SCENEMANAGER->addScene(L"로딩씬", new sceneLoading); //맵데이터, 유닛데이터 파일 로딩씬
	SCENEMANAGER->addScene(L"맵툴씬", new sceneMaptool);
	SCENEMANAGER->addScene(L"유닛에디터", new sceneUnitEditor);

	SCENEMANAGER->addScene(L"대화씬", new sceneStory);

	sceneSelect* _sceneSelect = new sceneSelect;
	_sceneSelect->setLinkAdressPlayer(_player);
	_sceneSelect->setLinkAdressEnemy(_enemy);
	_sceneSelect->setLinkAdressFriend(_friend);
	SCENEMANAGER->addScene(L"선택씬", _sceneSelect);

	sceneBattle* _sceneBattle = new sceneBattle;
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
		SCENEMANAGER->changeScene(L"맵툴씬");
	}
	else if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		SCENEMANAGER->changeScene(L"대화씬");
	}
	else if (KEYMANAGER->isOnceKeyDown(VK_F3))
	{
		SCENEMANAGER->changeScene(L"선택씬");
	}
	else if (KEYMANAGER->isOnceKeyDown(VK_F4))
	{
		SCENEMANAGER->changeScene(L"전투씬");
	}
	else if (KEYMANAGER->isOnceKeyDown(VK_F6))
	{
		SCENEMANAGER->changeScene(L"유닛에디터");
	}

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

