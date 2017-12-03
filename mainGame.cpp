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


//ÃÊ±âÈ­
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
	gameNode* node = SCENEMANAGER->addScene(L"ÃÊ±âÈ­¾À", new sceneInit);  //°ÔÀÓ ¸®¼Ò½º ÃÊ±âÈ­
	//node->init();
	
	SCENEMANAGER->addScene(L"¸ÊÅø¾À", new sceneMaptool);				//¸ÊÅø
	SCENEMANAGER->addScene(L"À¯´Ö¿¡µðÅÍ", new sceneUnitEditor);		//À¯´Ö»ý¼º

	sceneSelect* _sceneSelect = new sceneSelect;					//½Ã³ª¸®¿À ¼±ÅÃÇÏ´Â ¾À(¼±ÅÃÀÌ ¿Ï·áµÇ¸é ½ºÅä¸®, ¼¥, ¹èÆ²¿¡ ³Ñ°ÜÁØ´Ù.)
	_sceneSelect->setLinkAdressPlayer(_player);
	_sceneSelect->setLinkAdressEnemy(_enemy);
	_sceneSelect->setLinkAdressFriend(_friend);
	_sceneSelect->setLinkAdressMap(_map);
	SCENEMANAGER->addScene(L"¼±ÅÃ¾À", _sceneSelect);



	SCENEMANAGER->addScene(L"´ëÈ­¾À", new sceneStory);				//½ºÅä¸®



	
	sceneReadybase* _sceneReadybase = new sceneReadybase;          //ÁØºñ±âº»¾À
	_sceneReadybase->setLinkAdressPlayer(_player);
	SCENEMANAGER->addScene(L"ÁØºñ±âº»¾À", _sceneReadybase);


	scenePos* _scenePos = new scenePos;                            //ÃâÁø¾À
	_scenePos->setLinkAdressPlayer(_player);
	SCENEMANAGER->addScene(L"ÃâÁø¾À", _scenePos);


	sceneEquip* _sceneEquip = new sceneEquip;                      //Àåºñ¾À
	_sceneEquip->setLinkAdressPlayer(_player);
	SCENEMANAGER->addScene(L"Àåºñ¾À", _sceneEquip);

	sceneBuy* _sceneBuy = new sceneBuy;							    //±¸¸Å»óÁ¡
	_sceneBuy->setLinkAdressPlayer(_player);
	SCENEMANAGER->addScene(L"±¸¸Å»óÁ¡¾À", _sceneBuy);
	_sceneEquip->setLinkAdressSceneBuy(_sceneBuy);

	sceneSell* _sceneSell = new sceneSell;							//ÆÇ¸Å»óÁ¡
	_sceneSell->setLinkAdressPlayer(_player);
	SCENEMANAGER->addScene(L"ÆÇ¸Å»óÁ¡¾À", _sceneSell);
	

	sceneBattle* _sceneBattle = new sceneBattle;					//ÀüÅõ
	_sceneBattle->setLinkAdressPlayer(_player);
	_sceneBattle->setLinkAdressEnemy(_enemy);
	_sceneBattle->setLinkAdressFriend(_friend);
	_sceneBattle->setLinkAdressMap(_map);
	SCENEMANAGER->addScene(L"ÀüÅõ¾À", _sceneBattle);

	SCENEMANAGER->addScene(L"°á°ú¾À", new sceneResult);

	SCENEMANAGER->changeScene(L"ÃÊ±âÈ­¾À");
}



//¸Þ¸ð¸® ÇØÁ¦
void mainGame::release(void)
{
	gameNode::release();

	SCENEMANAGER->release();
}

//¿¬»ê°ü·Ã(Å¸ÀÌ¸Ó)
void mainGame::update(void)
{
	gameNode::update();

	checkWindowSize();
	controlFPS();
	//playBGM();


	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		SCENEMANAGER->changeScene(L"¼±ÅÃ¾À");
	}
	//¾À ¹Ù²Ù°í ½ÍÀ¸¸é sceneSelect.cpp -> 150 line ¿¡ ¼öÁ¤ÇÏ±â

	SCENEMANAGER->update();
}

//±×·ÁÁÖ´Â ÇÔ¼ö
void mainGame::render(void)	
{
	//Èò»ö µµÈ­Áö ÇÑ Àå ÇÊ¿ä
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==============================================================
	
	SCENEMANAGER->render();


	RENDERMANAGER->render();

	//TIMEMANAGER->render(getMemDC());
	
	//========================================================================
	//¹é¹öÆÛ¿¡ ÀÖ´Â°É HDC·Î ±×·ÁÁÖ´Â ¿ªÇÒ
	this->getBackBuffer()->render(getHDC(), 0, 0);

}

void mainGame::getChar(WPARAM wParam)
{
	if (SCENEMANAGER->isCurScene(L"À¯´Ö¿¡µðÅÍ"))
	{
		SCENEMANAGER->getChar(wParam);
	}
	else if (SCENEMANAGER->isCurScene(L"¸ÊÅø¾À"))
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
	if (SCENEMANAGER->isCurScene(L"ÃÊ±âÈ­¾À"))
	{
		setWindowResize({ WINSIZEX2, WINSIZEY2 });
	}
	else if (SCENEMANAGER->isCurScene(L"¼±ÅÃ¾À"))
	{
		setWindowResize({ WINSIZEX2, WINSIZEY2 });
	}
	else if (SCENEMANAGER->isCurScene(L"¸ÊÅø¾À"))
	{
		setWindowResize({ WINSIZEX, WINSIZEY });
	}
	else if (SCENEMANAGER->isCurScene(L"À¯´Ö¿¡µðÅÍ"))
	{
		setWindowResize({ WINSIZEX, WINSIZEY });
	}
	else if (SCENEMANAGER->isCurScene(L"´ëÈ­¾À"))
	{
		setWindowResize({ WINSIZEX2, WINSIZEY2 });
	}
	else if (SCENEMANAGER->isCurScene(L"ÀüÅõ¾À"))
	{
		setWindowResize({ WINSIZEX, WINSIZEY });
	}
	else if (SCENEMANAGER->isCurScene(L"ÁØºñ±âº»¾À"))
	{
		setWindowResize({ WINSIZEX2,WINSIZEY2 });
	}
	else if (SCENEMANAGER->isCurScene(L"ÃâÁø¾À"))
	{
		setWindowResize({ WINSIZEX3,WINSIZEY3 });
	}
	else if (SCENEMANAGER->isCurScene(L"Àåºñ¾À"))
	{
		setWindowResize({ WINSIZEX4,WINSIZEY4 });
	}
	else if (SCENEMANAGER->isCurScene(L"±¸¸Å»óÁ¡¾À"))
	{
		setWindowResize({ WINSIZEX5,WINSIZEY5 });
	}
	else if (SCENEMANAGER->isCurScene(L"ÆÇ¸Å»óÁ¡¾À"))
	{
		setWindowResize({ WINSIZEX5,WINSIZEY5 });
	}
	else if (SCENEMANAGER->isCurScene(L"°á°ú¾À"))
	{
		setWindowResize({ WINSIZEX2,WINSIZEY2 });

	}
}

void mainGame::controlFPS(void)
{
	if (SCENEMANAGER->isCurScene(L"ÃÊ±âÈ­¾À"))
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
	if (SCENEMANAGER->isCurScene(L"¼±ÅÃ¾À")
		|| SCENEMANAGER->isCurScene(L"¸ÊÅø¾À")
		|| SCENEMANAGER->isCurScene(L"À¯´Ö¿¡µðÅÍ"))
	{
		if (SOUNDMANAGER->isPlaySound(L"Se_b_00") == FALSE)		SOUNDMANAGER->play(L"Se_b_00");
		if (SOUNDMANAGER->isPlaySound(L"Se_b_02") == TRUE)		SOUNDMANAGER->stop(L"Se_b_02");
		if (SOUNDMANAGER->isPlaySound(L"Se_b_04") == TRUE)		SOUNDMANAGER->stop(L"Se_b_04");
		if (SOUNDMANAGER->isPlaySound(L"Se_b_05") == TRUE)		SOUNDMANAGER->stop(L"Se_b_05");
	}
	else if (SCENEMANAGER->isCurScene(L"´ëÈ­¾À"))
	{
		if (SOUNDMANAGER->isPlaySound(L"Se_b_00") == TRUE)		SOUNDMANAGER->stop(L"Se_b_00");
		if (SOUNDMANAGER->isPlaySound(L"Se_b_02") == TRUE)		SOUNDMANAGER->stop(L"Se_b_02");
		if (SOUNDMANAGER->isPlaySound(L"Se_b_04") == TRUE)		SOUNDMANAGER->stop(L"Se_b_04");
		if (SOUNDMANAGER->isPlaySound(L"Se_b_05") == FALSE)		SOUNDMANAGER->play(L"Se_b_05");
	}
	else if (SCENEMANAGER->isCurScene(L"ÁØºñ±âº»¾À")
			|| SCENEMANAGER->isCurScene(L"ÃâÁø¾À")
			|| SCENEMANAGER->isCurScene(L"Àåºñ¾À")
			|| SCENEMANAGER->isCurScene(L"±¸¸Å»óÁ¡¾À")
			|| SCENEMANAGER->isCurScene(L"ÆÇ¸Å»óÁ¡¾À"))
	{
		if (SOUNDMANAGER->isPlaySound(L"Se_b_00") == TRUE)		SOUNDMANAGER->stop(L"Se_b_00");
		if (SOUNDMANAGER->isPlaySound(L"Se_b_02") == FALSE)		SOUNDMANAGER->play(L"Se_b_02");
		if (SOUNDMANAGER->isPlaySound(L"Se_b_04") == TRUE)		SOUNDMANAGER->stop(L"Se_b_04");
		if (SOUNDMANAGER->isPlaySound(L"Se_b_05") == TRUE)		SOUNDMANAGER->stop(L"Se_b_05");
	}
	else if (SCENEMANAGER->isCurScene(L"ÀüÅõ¾À"))
	{
		if (SOUNDMANAGER->isPlaySound(L"Se_b_00") == TRUE)		SOUNDMANAGER->stop(L"Se_b_00");
		if (SOUNDMANAGER->isPlaySound(L"Se_b_02") == TRUE)		SOUNDMANAGER->stop(L"Se_b_02");
		if (SOUNDMANAGER->isPlaySound(L"Se_b_04") == FALSE)		SOUNDMANAGER->play(L"Se_b_04");
		if (SOUNDMANAGER->isPlaySound(L"Se_b_05") == TRUE)		SOUNDMANAGER->stop(L"Se_b_05");
	}
}
