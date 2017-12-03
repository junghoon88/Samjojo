#include "stdafx.h"
#include "battleSceneInterface.h"
#include "Player.h"
#include "Enemy.h"
#include "Friend.h"
#include "gameMap.h"
//전투씬 내에서 플레이어 인터페이스 제공 클래스로 쓸겁니다.

battleSceneInterface::battleSceneInterface()
	:_player(NULL), _friend(NULL), _enemy(NULL), findtile(NULL)
{}
battleSceneInterface::~battleSceneInterface(){}

HRESULT battleSceneInterface::init(void) 
{
	infoSetup();

	return S_OK;
}

void battleSceneInterface::release(void)
{
}

void battleSceneInterface::update(void) 
{
	if (!isCommand && !popUpMenu)
	{
		mouse_Scanning();//지형 타일 갱신
		if (!isShow)moveCamera();
		if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
		{
			if(clickUnit == PLAYER &&  !_player->getUnits()[vNum]->getBattleState().moveable) 	mouse_ActionCancel();
			else dataClean();  //윈도우 닫기
		}
		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
		{
	
			if (isShow && clickUnit == PLAYER && _player->getUnits()[vNum]->getUnitSequnce() == UNITSEQUENCE_TURNON) mouse_ClickToAction(); // 
		//	else if (!isShow) dataClean();
			else if (!isShow) mouse_ClickToTile();//지형 클릭 시 
		}
	}
	else if (isCommand)//명령 내린 상태이면 해당 동작이 끝날때까지 조작불가
	{
		if (UNITSEQUENCE_MOVE != _player->getUnits()[vNum]->getUnitSequnce()) 
		{
			//이동취소.
			_player->getUnits()[vNum]->setMoveable(false);
			callToMenu();//메뉴화면을 호출
			isCommand = false;
		}
	}
	else if (popUpMenu)
	{
		callToMenu();
	}
}

void battleSceneInterface::render(void) 
{
	tileLineDraw(); //커서 타일 테두리 그림
	Rectangle(getMemDC(), rc.left, rc.top, rc.right, rc.bottom);
	if (isShow)
	{
		infoDraw();// 정보 표시
	}
}

void battleSceneInterface::mouse_Scanning(void)
{
	indexTile = (int)(_ptMouse.x / TILESIZE) + (int)(_ptMouse.y / TILESIZE)  * TILEX;
	if (!isShow)
	{
		drawLine = { findtile->getTile()[indexTile].rc.left,findtile->getTile()[indexTile].rc.top,findtile->getTile()[indexTile].rc.right,findtile->getTile()[indexTile].rc.bottom };
	}
	else if (isShow && clickUnit == PLAYER)
	{
		int findIndex = indexTile + (MAINCAMERA->getCameraX() / TILESIZE) + (MAINCAMERA->getCameraY() / TILESIZE) * TILEX;
		if(_player->getUnits()[vNum]->isMovableArea(findIndex))drawMoveLine = { findtile->getTile()[indexTile].rc.left,findtile->getTile()[indexTile].rc.top,findtile->getTile()[indexTile].rc.right,findtile->getTile()[indexTile].rc.bottom };
		drawLine = _player->getUnits()[vNum]->getRect();
	}
}

void battleSceneInterface::mouse_ClickToTile(void)
{
	int findIndex = indexTile + (MAINCAMERA->getCameraX() / TILESIZE) + (MAINCAMERA->getCameraY() / TILESIZE) * TILEX;

	if (findtile->getTeamInfo()[findIndex] == TEAM_PLAYER)
	{
		for (int i = 0; i < _player->getUnits().size(); i++)
		{
			if (findIndex == (int)(_player->getUnits()[i]->getBattleState().tilePt.x + _player->getUnits()[i]->getBattleState().tilePt.y * TILEX))
			{
				vNum = i;
				isUnit = true;
				clickUnit = PLAYER;
				_tcscpy(factionName, L"플레이어");
				_tcscpy(unitName, _player->getUnits()[i]->getStatus().name);
				unitImg = _player->getUnits()[i]->getStatus().imgFace;
				_player->getUnits()[i]->findMoveArea();
				break;
			}
		}
	}
	else if (findtile->getTeamInfo()[findIndex] == TEAM_FRIEND)
	{
		for (int i = 0; i < _friend->getUnits().size(); i++)
		{
			if (findIndex == (int)(_friend->getUnits()[i]->getBattleState().tilePt.x + _friend->getUnits()[i]->getBattleState().tilePt.y * TILEX))
			{
				vNum = i;
				isUnit = true;
				clickUnit = FRIEND;
				_tcscpy(factionName, L"아군");
				_tcscpy(unitName, _friend->getUnits()[i]->getStatus().name);
				unitImg = _friend->getUnits()[i]->getStatus().imgFace;
				_friend->getUnits()[i]->findMoveArea();
				break;
			}
		}
	}
	else if (findtile->getTeamInfo()[findIndex] == TEAM_ENEMY)
	{
		for (int i = 0; i < _enemy->getUnits().size(); i++)
		{
			if (findIndex == (int)(_enemy->getUnits()[i]->getBattleState().tilePt.x + _enemy->getUnits()[i]->getBattleState().tilePt.y * TILEX))
			{
				vNum = i;
				isUnit = true;
				clickUnit = ENEMY;
				_tcscpy(factionName, L"적군");
				_tcscpy(unitName, _enemy->getUnits()[i]->getStatus().name);
				unitImg = _enemy->getUnits()[i]->getStatus().imgFace;
				_enemy->getUnits()[i]->findMoveArea();
				break;
			}
		}
	}

	tileNum = findtile->getTile()[findIndex].terrain;//해당번호를 키값으로 찾으면 된다. 이미지를!
	switch (findtile->getTile()[findIndex].terrain)
	{
	case TERRAIN_RIVER:
		_tcscpy(tilename, L"강");
		_tcscpy(prop, L"이동 불가");
		fire = false;
		water = false;
		wind = false;
		earth = false;
		break;
	case TERRAIN_BRIDGE:
		_tcscpy(tilename, L"다리");
		_tcscpy(prop, L"");
		fire = true;
		water = true;
		wind = true;
		earth = false;
		break;
	case TERRAIN_WATER:
		_tcscpy(tilename, L"대하");
		_tcscpy(prop, L"이동 불가");
		fire = true;
		water = true;
		wind = true;
		earth = false;
		break;

	case TERRAIN_DITCH:
		_tcscpy(tilename, L"도랑");
		_tcscpy(prop, L"이동 불가");
		fire = false;
		water = false;
		wind = false;
		earth = false;
		break;

	case TERRAIN_VILLAGE:
		_tcscpy(tilename, L"마을");
		_tcscpy(prop, L"회복 있음");
		fire = true;
		water = false;
		wind = false;
		earth = false;
		break;

	case TERRAIN_PREMISES:
		_tcscpy(tilename, L"가옥");
		_tcscpy(prop, L"");
		fire = true;
		water = false;
		wind = false;
		earth = false;
		break;

	case TERRAIN_ROCK:
		_tcscpy(tilename, L"암벽");
		_tcscpy(prop, L"이동 불가");
		fire = false;
		water = false;
		wind = false;
		earth = false;
		break;

	case TERRAIN_SHIP:
		_tcscpy(tilename, L"배");
		_tcscpy(prop, L"이동 불가");
		fire = false;
		water = false;
		wind = false;
		earth = false;
		break;

	case TERRAIN_BROW:
		_tcscpy(tilename, L"벼랑");
		_tcscpy(prop, L"이동 불가");
		fire = false;
		water = false;
		wind = false;
		earth = false;
		break;

	case TERRAIN_BARRACK:
		_tcscpy(tilename, L"병영");
		_tcscpy(prop, L"회복 있음");
		fire = true;
		water = false;
		wind = false;
		earth = false;
		break;

	case TERRAIN_WAREHOUSE:
		_tcscpy(tilename, L"보급소");
		_tcscpy(prop, L"회복 있음");
		fire = true;
		water = false;
		wind = false;
		earth = false;
		break;

	case TERRAIN_FIRE:
		_tcscpy(tilename, L"불");
		_tcscpy(prop, L"이동 불가");
		fire = false;
		water = false;
		wind = false;
		earth = false;
		break;

	case TERRAIN_MOUNTAIN:
		_tcscpy(tilename, L"산");
		_tcscpy(prop, L"");
		fire = false;
		water = false;
		wind = true;
		earth = true;
		break;

	case TERRAIN_SNOW:
		_tcscpy(tilename, L"설원");
		_tcscpy(prop, L"");
		fire = false;
		water = false;
		wind = false;
		earth = false;
		break;

	case TERRAIN_CASTLE:
		_tcscpy(tilename, L"성");
		_tcscpy(prop, L"회복 있음");
		fire = true;
		water = false;
		wind = false;
		earth = false;
		break;

	case TERRAIN_INCASTLE:
		_tcscpy(tilename, L"성내");
		_tcscpy(prop, L"");
		fire = true;
		water = false;
		wind = false;
		earth = false;
		break;

	case TERRAIN_CASTLEGATE:
		_tcscpy(tilename, L"성문");
		_tcscpy(prop, L"이동 불가");
		fire = false;
		water = false;
		wind = false;
		earth = false;
		break;

	case TERRAIN_RAMPART:
		_tcscpy(tilename, L"성벽");
		_tcscpy(prop, L"이동 불가");
		fire = false;
		water = false;
		wind = false;
		earth = false;
		break;

	case TERRAIN_FOREST:
		_tcscpy(tilename, L"숲");
		_tcscpy(prop, L"");
		fire = true;
		water = false;
		wind = false;
		earth = false;
		break;

	case TERRAIN_SWAMP:
		_tcscpy(tilename, L"슾지");
		_tcscpy(prop, L"");
		fire = false;
		water = true;
		wind = true;
		earth = false;
		break;

	case TERRAIN_FORD:
		_tcscpy(tilename, L"여울");
		_tcscpy(prop, L"");
		fire = false;
		water = true;
		wind = true;
		earth = false;
		break;

	case TERRAIN_POND:
		_tcscpy(tilename, L"연못");
		_tcscpy(prop, L"이동 불가");
		fire = false;
		water = false;
		wind = false;
		earth = false;
		break;

	case TERRAIN_STRONGHOLD:
		_tcscpy(tilename, L"요새");
		_tcscpy(prop, L"회복 있음");
		fire = true;
		water = false;
		wind = false;
		earth = false;
		break;

	case TERAAIN_FENCE:
		_tcscpy(tilename, L"울타리");
		_tcscpy(prop, L"이동 불가");
		fire = false;
		water = false;
		wind = false;
		earth = false;
		break;

	case TERRAIN_ALTER:
		_tcscpy(tilename, L"제단");
		_tcscpy(prop, L"");
		fire = false;
		water = false;
		wind = false;
		earth = false;
		break;

	case TERRAIN_UNDERGROUND:
		_tcscpy(tilename, L"지하");
		_tcscpy(prop, L"이동 불가");
		fire = false;
		water = false;
		wind = false;
		earth = false;
		break;

	case TERRAIN_GRASSLAND:
		_tcscpy(tilename, L"초원");
		_tcscpy(prop, L"");
		fire = true;
		water = false;
		wind = true;
		earth = false;
		break;

	case TERRAIN_FLAT:
		_tcscpy(tilename, L"평지");
		_tcscpy(prop, L"");
		fire = true;
		water = false;
		wind = true;
		earth = false;
		break;

	case TERRAIN_BADLANDS:
		_tcscpy(tilename, L"황무지");
		_tcscpy(prop, L"");
		fire = false;
		water = false;
		wind = true;
		earth = true;
		break;

	case TERRAIN_GATEWAY:
		_tcscpy(tilename, L"관문");
		_tcscpy(prop, L"회복 있음");
		fire = true;
		water = false;
		wind = false;
		earth = false;
		break;

	case TERRAIN_NONE:
		_tcscpy(tilename, L"지형정보없음");
		_tcscpy(prop, L"");
		fire = false;
		water = false;
		wind = false;
		earth = false;
		break;

	}
	isShow = true;
}

void battleSceneInterface::mouse_ClickToAction(void)//행동가능한 플레이어 유닛을 누른상태일때 클릭하면 취해줄 액션들
{
	int setindex = (int)(_ptMouse.x / TILESIZE) + (int)(_ptMouse.y / TILESIZE)  * TILEX;
	int findIndex = setindex + (MAINCAMERA->getCameraX() / TILESIZE) + (MAINCAMERA->getCameraY() / TILESIZE) * TILEX;
	//_player->getUnits()[vNum]->getBattleState().rc.right;//액션 메뉴 렉트는 이걸 기준으로..
	POINT goToTile;
	goToTile.x = (findtile->getTile()[findIndex].rc.left ) / TILESIZE ;
	goToTile.y = (findtile->getTile()[findIndex].rc.top ) / TILESIZE;

	//해당유닛 한번 더 클릭하면
	if (findIndex == (int)(_player->getUnits()[vNum]->getBattleState().tilePt.x + _player->getUnits()[vNum]->getBattleState().tilePt.y * TILEX) && _player->getUnits()[vNum]->getUnitSequnce() == UNITSEQUENCE_TURNON)
	{
		popUpMenu = true;;//행동가능 버튼 출력.
	}
	//적 유닛 클릭 시
	if (findtile->getTeamInfo()[findIndex] == TEAM_ENEMY)
	{
		mouse_ClickToAttack();
	}
	else if (_player->getUnits()[vNum]->isMovableArea(findIndex) && _player->getUnits()[vNum]->getBattleState().moveable)//유닛이 아니고 땅 누르면 
	{

		backToPT.x = _player->getUnits()[vNum]->getBattleState().pt.x;
		backToPT.y = _player->getUnits()[vNum]->getBattleState().pt.y;
		backToDir = _player->getUnits()[vNum]->getBattleState().dir;
		_player->getUnits()[vNum]->moveTo(goToTile);
		_player->getUnits()[vNum]->setUnitSequnce(UNITSEQUENCE_MOVE);
		isCommand = true;
	}
	else if(_player->getUnits()[vNum]->getBattleState().moveable) dataClean();
}
void battleSceneInterface::mouse_ClickToAttack(void)
{
	int setindex = (int)(_ptMouse.x / TILESIZE) + (int)(_ptMouse.y / TILESIZE)  * TILEX;
	int findIndex = setindex + (MAINCAMERA->getCameraX() / TILESIZE) + (MAINCAMERA->getCameraY() / TILESIZE) * TILEX;

//	_player->getUnits()[vNum]->attack(_enemy->getUnits()[1]);

	if (_player->getUnits()[vNum]->isAttackTarget(findIndex) == FALSE)
		return;

	for (int i = 0; i < _enemy->getUnits().size(); i++)
	{
		if (findIndex == (int)(_enemy->getUnits()[i]->getBattleState().tilePt.x + _enemy->getUnits()[i]->getBattleState().tilePt.y * TILEX))//
		{
			POINT tilePtEnemy = { _enemy->getUnits()[i]->getBattleState().tilePt.x, _enemy->getUnits()[i]->getBattleState().tilePt.y };
			_player->getUnits()[vNum]->setOpponent(_enemy->getUnits()[i]);
			_player->getUnits()[vNum]->setOpponentTilePt(tilePtEnemy);

			int dirX = _enemy->getUnits()[i]->getBattleState().tilePt.x - _player->getUnits()[vNum]->getBattleState().tilePt.x;
			int dirY = _enemy->getUnits()[i]->getBattleState().tilePt.y - _player->getUnits()[vNum]->getBattleState().tilePt.y;

			if (abs(dirX) >= abs(dirY))
			{
				if (dirX > 0)	_player->getUnits()[vNum]->setDir(DIRECTION_RG);
				else			_player->getUnits()[vNum]->setDir(DIRECTION_LF);
			}
			else
			{
				if (dirY > 0)	_player->getUnits()[vNum]->setDir(DIRECTION_UP);
				else			_player->getUnits()[vNum]->setDir(DIRECTION_DN);
			}



			_player->getUnits()[vNum]->setUnitSequnce(UNITSEQUENCE_ATTACK);
			break;
		}
	}

}

void battleSceneInterface::mouse_ActionCancel(void)//이동명령 취소용
{
	_player->getUnits()[vNum]->moveBack(backToPT);
	_player->getUnits()[vNum]->setUnitSequnce(UNITSEQUENCE_TURNON);
	_player->getUnits()[vNum]->setMoveable(true);
	_player->getUnits()[vNum]->setDir(backToDir);
	isCommand = false;
	dataClean();
}

void battleSceneInterface::moveCamera(void)
{
	if (_ptMouse.x > WINSIZEX - TILESIZE/2 - 144 && _ptMouse.x <= WINSIZEX - 144 && MAINCAMERA->getCameraX() < findtile->getTileSizeX() * TILESIZE - TILESIZE * 20)// 마우스가 오른쪽 
		MAINCAMERA->setCameraX(MAINCAMERA->getCameraX() + TILESIZE ); 
	if (_ptMouse.x < TILESIZE/2 && _ptMouse.x >= 0 && MAINCAMERA->getCameraX() > 0)//마우스가 왼쪽
		MAINCAMERA->setCameraX(MAINCAMERA->getCameraX() - TILESIZE); 
	if (_ptMouse.y > WINSIZEY - TILESIZE/2 && _ptMouse.y < WINSIZEY && MAINCAMERA->getCameraY() < findtile->getTileSizeY() * TILESIZE - TILESIZE * 20)//마우스가 화면 아래쪽
		MAINCAMERA->setCameraY(MAINCAMERA->getCameraY() + TILESIZE); 
	if (_ptMouse.y < TILESIZE/2 && _ptMouse.y >= 0 && MAINCAMERA->getCameraY() > 0)//마우스가 화면 윗쪽
		MAINCAMERA->setCameraY(MAINCAMERA->getCameraY() - TILESIZE); 


	if(KEYMANAGER->isOnceKeyDown(VK_LEFT) && MAINCAMERA->getCameraX() > 0)//왼쪽
		MAINCAMERA->setCameraX(MAINCAMERA->getCameraX() - TILESIZE);
	if (KEYMANAGER->isOnceKeyDown(VK_UP) && MAINCAMERA->getCameraY() > 0)//위쪽
		MAINCAMERA->setCameraY(MAINCAMERA->getCameraY() - TILESIZE);
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT) && MAINCAMERA->getCameraX() < findtile->getTileSizeX() * TILESIZE - TILESIZE * 20)//오른쪽
		MAINCAMERA->setCameraX(MAINCAMERA->getCameraX() + TILESIZE);
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN) && MAINCAMERA->getCameraY() < findtile->getTileSizeY() * TILESIZE - TILESIZE * 20)//아래  
		MAINCAMERA->setCameraY(MAINCAMERA->getCameraY() + TILESIZE);
}

void battleSceneInterface::dataClean(void)//마우스 우클릭 시 현재 인터페이스의 정보를 초기화 해주는 역할을 할 것.
{
	isShow = false;
	isUnit = false;
	fire = false;
	wind = false;
	earth = false;
	water = false;

	switch (clickUnit)
	{
	case PLAYER:
		_player->getUnits()[vNum]->clearMoveArea();
		break;
	case FRIEND:
		_friend->getUnits()[vNum]->clearMoveArea();
		break;
	case ENEMY:
		_enemy->getUnits()[vNum]->clearMoveArea();
		break;
	}
	clickUnit = NONE;
	isCommand = false;
	drawMoveLine = { 0,0,0,0 };
}
void battleSceneInterface::callToMenu(void)
{
	
}

void battleSceneInterface::tileLineDraw(void)
{
	SelectObject(getMemDC(), (HPEN)linePen);
	MoveToEx(getMemDC(), drawLine.left, drawLine.top, NULL); //현재 타일 테두리그림
	LineTo(getMemDC(), drawLine.right, drawLine.top);		 //현재 타일 테두리그림
	LineTo(getMemDC(), drawLine.right, drawLine.bottom);	 //현재 타일 테두리그림
	LineTo(getMemDC(), drawLine.left, drawLine.bottom);		 //현재 타일 테두리그림
	LineTo(getMemDC(), drawLine.left, drawLine.top);		 //현재 타일 테두리그림

		MoveToEx(getMemDC(), drawMoveLine.left, drawMoveLine.top, NULL); //이동 타일
		LineTo(getMemDC(), drawMoveLine.right, drawMoveLine.top);		 //이동 타일 테두리그림
		LineTo(getMemDC(), drawMoveLine.right, drawMoveLine.bottom);	 //이동 타일 테두리그림
		LineTo(getMemDC(), drawMoveLine.left, drawMoveLine.bottom);		 //이동 타일 테두리그림
		LineTo(getMemDC(), drawMoveLine.left, drawMoveLine.top);		 //이동 타일 테두리그림
		SelectObject(getMemDC(), (HPEN)oPen);
}

void battleSceneInterface::infoDraw(void)
{
	IMAGEMANAGER->findImage(L"스크롤")->render(getMemDC(), rc.left, rc.top);
	if (isUnit) //유닛을 눌렀을때 표시할 것들
	{
		Rectangle(getMemDC(), unitImgRect.left, unitImgRect.top, unitImgRect.right, unitImgRect.bottom); // 디버그용 렉트출력
		unitImg->render(getMemDC(), unitImgRect.left, unitImgRect.top);
		TextOut(getMemDC(), unitImgRect.left, unitImgRect.bottom + 48, unitName, _tcslen(unitName));
		TextOut(getMemDC(), unitImgRect.left, unitImgRect.bottom + 24, factionName, _tcslen(factionName));
	}
	Rectangle(getMemDC(), tileImgRect.left, tileImgRect.top, tileImgRect.right, tileImgRect.bottom); // 디버그용 렉트출력
	TextOut(getMemDC(), tileImgRect.left, tileImgRect.bottom + 50, tilename, _tcslen(tilename));
	TextOut(getMemDC(), tileImgRect.left, tileImgRect.bottom + 80, prop, _tcslen(prop));

	hpBar->render();
	mpBar->render();

	//for (int i = 0; i < 4; i++) // 디버그용 렉트출력
	//{
	//	Rectangle(getMemDC(), element[i].left, element[i].top, element[i].right, element[i].bottom);
	//}

	if (fire) IMAGEMANAGER->findImage(L"화속성")->render(getMemDC(), element[0].left, element[0].top);
	else if(!fire) IMAGEMANAGER->findImage(L"화속성비활성")->render(getMemDC(), element[0].left, element[0].top);
	if (water) IMAGEMANAGER->findImage(L"수속성")->render(getMemDC(), element[1].left, element[1].top);
	else if (!water) IMAGEMANAGER->findImage(L"수속성비활성")->render(getMemDC(), element[1].left, element[1].top);
	if (wind) IMAGEMANAGER->findImage(L"풍속성")->render(getMemDC(), element[2].left, element[2].top);
	else if (!wind) IMAGEMANAGER->findImage(L"풍속성비활성")->render(getMemDC(), element[2].left, element[2].top);
	if (earth) IMAGEMANAGER->findImage(L"땅속성")->render(getMemDC(), element[3].left, element[3].top);
	else if (!earth) IMAGEMANAGER->findImage(L"땅속성비활성")->render(getMemDC(), element[3].left, element[3].top);
}



void battleSceneInterface::buttonSetup(void)
{
	for (int i = 0; i < BTN_MAX; i++)
	{
		switch (i)
		{
		case BTN_ATTACK:
			actionBtn[i] = new button;
			actionBtn[i]->init(L"SELECT-선택버튼", L"공격", cmdBox.left + 5, cmdBox.top + 5, { 0,0 }, { 0,1 }, cb_attack, this);
			break;
		case BTN_SKILL:
			actionBtn[i] = new button;
			actionBtn[i]->init(L"SELECT-선택버튼", L"도구", cmdBox.left + 5, cmdBox.top + 5 + 35, { 0,0 }, { 0,1 }, cb_item, this);
			break;
		case BTN_ITEM:
			actionBtn[i] = new button;
			actionBtn[i]->init(L"SELECT-선택버튼", L"대기", cmdBox.left + 5, cmdBox.top + 5 + 35 + 35, { 0,0 }, { 0,1 }, cb_wait, this);
			break;
		case BTN_WAIT:
			actionBtn[i] = new button;
			actionBtn[i]->init(L"SELECT-선택버튼", L"취소", cmdBox.left + 5, cmdBox.top + 5 + 35 + 35 + 35, { 0,0 }, { 0,1 }, cb_cancel, this);
			break;
		}
	}
}

void battleSceneInterface::cb_attack(void* obj)
{
	battleSceneInterface* cursor = (battleSceneInterface*)obj;
	cursor->cmd_atk();
}
void battleSceneInterface::cb_item(void* obj)
{
	battleSceneInterface* cursor = (battleSceneInterface*)obj;
	cursor->cmd_item();
}
void battleSceneInterface::cb_wait(void* obj)
{
	battleSceneInterface* cursor = (battleSceneInterface*)obj;
	cursor->cmd_wait();
}
void battleSceneInterface::cb_cancel(void* obj)
{
	battleSceneInterface* cursor = (battleSceneInterface*)obj;
	cursor->cmd_cancel();
}

void battleSceneInterface::cmd_atk(void)
{
	popUpMenu = false;
}
void battleSceneInterface::cmd_item(void)	 
{
	//아이템 목록을 불러와서 쓰자.
}
void battleSceneInterface::cmd_wait(void)	 
{
	_player->getUnits()[vNum]->setUnitSequnce(UNITSEQUENCE_TURNOFF);
	dataClean();
}
void battleSceneInterface::cmd_cancel(void)
{

}

void battleSceneInterface::infoSetup(void)
{
	isShow = false;
	isUnit = false;
	targetAttack = false;
	isCommand = false;
	indexTile = 0;
	popUpMenu = false;
	for (int i = 0; i < BTN_MAX; i++)
	{
		actionBtn[i] = NULL;
	}

	rc = { WINSIZEX - SIDEWINSIZE,0,WINSIZEX,WINSIZEY };//인터페이스 간이 렉트
	tileImgRect = RectMakeCenter(rc.left + SIDEWINSIZE / 2, 80, FROFILEIMAGE, FROFILEIMAGE);
	unitImgRect = RectMakeCenter(rc.left + SIDEWINSIZE / 2, WINSIZEY / 2, FROFILEIMAGE, FROFILEIMAGE);
	for (int i = 0; i < 4; i++)
	{
		element[i] = RectMakeCenter(rc.left + TILESIZE / 2 + ((TILESIZE / 2 + (TILESIZE / 2 * 0.25)) * i), tileImgRect.bottom + TILESIZE / 2, TILESIZE / 2, TILESIZE / 2);
	}
	clickUnit = NONE;
	vNum = 0;
	_tcscpy(factionName, L"진영정보");
	_stprintf(unitName, L"유닛이름정보");
	_tcscpy(tilename, L"타일이름정보");
	_tcscpy(prop, L"지형속성정보");
	_tcscpy(txtExp, L"Exp");
	_tcscpy(txtAtk, L"공격력");
	_tcscpy(txtDef, L"방어력");
	_tcscpy(txtMove, L"이동력");

	//bonus = 0;//밟은 땅에 따른 전투력 증감표시
	exp = 0;
	lv = 0;
	atk = 0;
	def = 0;
	movePoint = 0;
	
	fire = false;
	wind = false;
	earth = false;
	water = false;
	backToDir = DIRECTION_DN;

	backToPT = { 0,0 };
	unitImg = IMAGEMANAGER->findImage(L"보병");
	tileImg = IMAGEMANAGER->findImage(L"보병");
	drawLine = { 0,0,0,0 };
	drawMoveLine = { 0,0,0,0 };
	oPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	linePen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	
	buttonSetup();
	cmdBox = RectMakeCenter(0, 0, 110, 145);

	hpBar = new progressBar;
	mpBar = new progressBar;
	hpBar->init(L"체력바2", L"빈바2", unitImgRect.left, unitImgRect.top + FROFILEIMAGE + 5 + 75, 120, 9, L"ready");
	mpBar->init(L"마나바2", L"빈바2", unitImgRect.left, unitImgRect.top + FROFILEIMAGE + 5 + 75 + 9 + 10, 120, 9, L"ready");
}