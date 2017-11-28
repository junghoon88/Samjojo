#include "stdafx.h"
#include "infoCursor.h"
#include "Player.h"
#include "Enemy.h"
#include "Friend.h"
#include "gameMap.h"
//전투씬 내에서 플레이어 인터페이스 제공 클래스로 쓸겁니다.

infoCursor::infoCursor()
	:_player(NULL), _friend(NULL), _enemy(NULL), findtile(NULL)
{}
infoCursor::~infoCursor(){}

HRESULT infoCursor::init(void) 
{
	isShow = false;
	isUnit = false;
	indexTile = 0;


	rc = { WINSIZEX - SIDEWINSIZE,0,WINSIZEX,WINSIZEY };//인터페이스 간이 렉트
	tileImgRect = RectMakeCenter(rc.left + SIDEWINSIZE / 2, 80, FROFILEIMAGE, FROFILEIMAGE);
	unitImgRect = RectMakeCenter(rc.left + SIDEWINSIZE / 2, WINSIZEY/2 , FROFILEIMAGE, FROFILEIMAGE);
	for (int i = 0; i < 4; i++)
	{
		element[i] = RectMakeCenter(rc.left + TILESIZE/2 + ((TILESIZE / 2 + (TILESIZE / 2 * 0.25)) * i), tileImgRect.bottom + TILESIZE / 2, TILESIZE / 2, TILESIZE / 2);
	}



	unit = L"유닛이름정보";
	tilename = L"타일이름정보";
	prop = L"지형속성정보";
	showExp = L"경험치";
	fire = false;
	wind = false;
	earth = false;
	water = false;

	unitImg = IMAGEMANAGER->findImage(L"보병");
	tileImg = IMAGEMANAGER->findImage(L"보병");
	drawLine = {0,0,0,0 };
	oPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	linePen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	return S_OK;
	
}
void infoCursor::release(void)
{

}
void infoCursor::update(void) 
{
	mouse_Scanning();//지형 타일 갱신
	mouse_moveCamera();
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON)) dataClean();  //윈도우 닫기
	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		if (isShow) dataClean();
		else mouse_Click();//지형 클릭 시 
	}
}
void infoCursor::render(void) 
{
	tileLineDraw(); //커서 타일 테두리 그림
	Rectangle(getMemDC(), rc.left, rc.top, rc.right, rc.bottom);
	if (isShow)
	{
		infoDraw();// 정보 표시
	}
}

void infoCursor::mouse_Scanning(void)
{
	if (!isShow)
	{
//		for (int i = 0; i < TILEX * TILEY; i++)
//		{
//			if (PtInRect(&findtile->getTile()[i].rc, _ptMouse))
//			{
//				drawLine = { findtile->getTile()[i].rc.left,findtile->getTile()[i].rc.top,findtile->getTile()[i].rc.right,findtile->getTile()[i].rc.bottom };
//			
//			}
//		}

	//for문을 현재 위치 기반으로 타일을 찾자 그냥 너무 부하가 큼
		indexTile = (((int)_ptMouse.x + MAINCAMERA->getCameraX())) / TILESIZE + (((int)_ptMouse.y + MAINCAMERA->getCameraY())) / TILESIZE * TILEX;

		if (PtInRect(&findtile->getTile()[indexTile].rc, _ptMouse))
		{
			drawLine = { findtile->getTile()[indexTile].rc.left,findtile->getTile()[indexTile].rc.top,findtile->getTile()[indexTile].rc.right,findtile->getTile()[indexTile].rc.bottom };
		}
	}

}

void infoCursor::mouse_Click(void)
{
	for (int i = 0; i < _player->getUnits().size(); i++)
	{
		if (PtInRect(&_player->getUnits()[i]->getRect(), _ptMouse))
		{
			isUnit = true;
			unit = _player->getUnits()[i]->getStatus().name;
			unitImg = _player->getUnits()[i]->getBattleState().imgBattleIdle;//여기
		}
	}

	for (int i = 0; i < _friend->getUnits().size(); i++)
	{
		if (PtInRect(&_friend->getUnits()[i]->getRect(), _ptMouse))
		{
			isUnit = true;
			unit = _friend->getUnits()[i]->getStatus().name;

		}
	}

	for (int i = 0; i < _enemy->getUnits().size(); i++)
	{
		if (PtInRect(&_enemy->getUnits()[i]->getRect(), _ptMouse))
		{
			isUnit = true;
			unit = _enemy->getUnits()[i]->getStatus().name;
			unitImg = _enemy->getUnits()[i]->getBattleState().imgBattleIdle;//여기
		}

	}


	//for (int i = 0; i < TILEX * TILEY; i++)
	//{
	//	tagTile* tile = findtile->getTile();
	//	if (PtInRect(&findtile->getTile()[i].rc, _ptMouse))
	//	{
	//
	//	}
	//}
	if (PtInRect(&findtile->getTile()[indexTile].rc, _ptMouse))
	{
			//지형정보 넣을 곳
			switch (findtile->getTile()[indexTile].terrain)
			{
			case TERRAIN_RIVER:
				tilename = L"강";
				prop = L"이동 불가";
				fire = false;
				water = false;
				wind = false;
				earth = false;
				break;
			case TERRAIN_BRIDGE:
				tilename = L"다리";
				prop = L"";
				fire = true;
				water = true;
				wind = true;
				earth = false;
				break;
			case TERRAIN_WATER:
				tilename = L"대하";
				prop = L"이동 불가";
				fire = true;
				water = true;
				wind = true;
				earth = false;
				break;

			case TERRAIN_DITCH:
				tilename = L"도랑";
				prop = L"이동 불가";
				fire = false;
				water = false;
				wind = false;
				earth = false;
				break;

			case TERRAIN_VILLAGE:
				tilename = L"마을";
				prop = L"회복 있음";
				fire = true;
				water = false;
				wind = false;
				earth = false;
				break;

			case TERRAIN_PREMISES:
				tilename = L"가옥";
				prop = L"";
				fire = true;
				water = false;
				wind = false;
				earth = false;
				break;

			case TERRAIN_ROCK:
				tilename = L"암벽";
				prop = L"이동 불가";
				fire = false;
				water = false;
				wind = false;
				earth = false;
				break;

			case TERRAIN_SHIP:
				tilename = L"배";
				prop = L"이동 불가";
				fire = false;
				water = false;
				wind = false;
				earth = false;
				break;

			case TERRAIN_BROW:
				tilename = L"벼랑";
				prop = L"이동 불가";
				fire = false;
				water = false;
				wind = false;
				earth = false;
				break;

			case TERRAIN_BARRACK:
				tilename = L"병영";
				prop = L"회복 있음";
				fire = true;
				water = false;
				wind = false;
				earth = false;
				break;

			case TERRAIN_WAREHOUSE:
				tilename = L"보급소";
				prop = L"회복 있음";
				fire = true;
				water = false;
				wind = false;
				earth = false;
				break;

			case TERRAIN_FIRE:
				tilename = L"불";
				prop = L"이동 불가";
				fire = false;
				water = false;
				wind = false;
				earth = false;
				break;

			case TERRAIN_MOUNTAIN:
				tilename = L"산";
				prop = L"";
				fire = false;
				water = false;
				wind = true;
				earth = true;
				break;

			case TERRAIN_SNOW:
				tilename = L"설원";
				prop = L"";
				fire = false;
				water = false;
				wind = false;
				earth = false;
				break;

			case TERRAIN_CASTLE:
				tilename = L"성";
				prop = L"회복 있음";
				fire = true;
				water = false;
				wind = false;
				earth = false;
				break;

			case TERRAIN_INCASTLE:
				tilename = L"성내";
				prop = L"";
				fire = true;
				water = false;
				wind = false;
				earth = false;
				break;

			case TERRAIN_CASTLEGATE:
				tilename = L"성문";
				prop = L"이동 불가";
				fire = false;
				water = false;
				wind = false;
				earth = false;
				break;

			case TERRAIN_RAMPART:
				tilename = L"성벽";
				prop = L"이동 불가";
				fire = false;
				water = false;
				wind = false;
				earth = false;
				break;

			case TERRAIN_FOREST:
				tilename = L"숲";
				prop = L"";
				fire = true;
				water = false;
				wind = false;
				earth = false;
				break;

			case TERRAIN_SWAMP:
				tilename = L"슾지";
				prop = L"";
				fire = false;
				water = true;
				wind = true;
				earth = false;
				break;

			case TERRAIN_FORD:
				tilename = L"여울";
				prop = L"";
				fire = false;
				water = true;
				wind = true;
				earth = false;
				break;

			case TERRAIN_POND:
				tilename = L"연못";
				prop = L"이동 불가";
				fire = false;
				water = false;
				wind = false;
				earth = false;
				break;

			case TERRAIN_STRONGHOLD:
				tilename = L"요새";
				prop = L"회복 있음";
				fire = true;
				water = false;
				wind = false;
				earth = false;
				break;

			case TERAAIN_FENCE:
				tilename = L"울타리";
				prop = L"이동 불가";
				fire = false;
				water = false;
				wind = false;
				earth = false;
				break;

			case TERRAIN_ALTER:
				tilename = L"제단";
				prop = L"";
				fire = false;
				water = false;
				wind = false;
				earth = false;
				break;

			case TERRAIN_UNDERGROUND:
				tilename = L"지하";
				prop = L"이동 불가";
				fire = false;
				water = false;
				wind = false;
				earth = false;
				break;

			case TERRAIN_GRASSLAND:
				tilename = L"초원";
				prop = L"";
				fire = true;
				water = false;
				wind = true;
				earth = false;
				break;

			case TERRAIN_FLAT:
				tilename = L"평지";
				prop = L"";
				fire = true;
				water = false;
				wind = true;
				earth = false;
				break;

			case TERRAIN_BADLANDS:
				tilename = L"황무지";
				prop = L"";
				fire = false;
				water = false;
				wind = true;
				earth = true;
				break;

			case TERRAIN_GATEWAY:
				tilename = L"관문";
				prop = L"회복 있음";
				fire = true;
				water = false;
				wind = false;
				earth = false;
				break;

			case TERRAIN_NONE:
				tilename = L"지형정보없음";
				prop = L"";
				fire = false;
				water = false;
				wind = false;
				earth = false;
				break;

			}
			tileNum = findtile->getTile()[indexTile].terrain;//해당번호를 키값으로 찾으면 된다. 이미지를!
													 //지형정보 스위치문!
			isShow = true;
		
	}

}

void infoCursor::mouse_moveCamera(void)
{
	if (_ptMouse.x > WINSIZEX - TILESIZE - 144 && _ptMouse.x <= WINSIZEX - 144 && MAINCAMERA->getCameraX() < TILEX * TILESIZE - TILESIZE * 20) MAINCAMERA->setCameraX(MAINCAMERA->getCameraX() + TILESIZE); // 마우스가 오른쪽  //화면 최대 조건 걸어야함.
	if (_ptMouse.x < TILESIZE && _ptMouse.x >= 0 && MAINCAMERA->getCameraX() > 0) MAINCAMERA->setCameraX(MAINCAMERA->getCameraX() - TILESIZE); //마우스가 왼쪽
	if (_ptMouse.y > WINSIZEY - TILESIZE && _ptMouse.y <= WINSIZEY && MAINCAMERA->getCameraY() <= TILEY * TILESIZE - TILESIZE * 20)MAINCAMERA->setCameraY(MAINCAMERA->getCameraY() + TILESIZE); //마우스가 화면 아래쪽
	if (_ptMouse.y < TILESIZE && _ptMouse.y >= 0 && MAINCAMERA->getCameraY() > 0) MAINCAMERA->setCameraY(MAINCAMERA->getCameraY() - TILESIZE); //마우스가 화면 윗쪽
}

void infoCursor::dataClean(void)//마우스 우클릭 시 현재 인터페이스의 정보를 초기화 해주는 역할을 할 것.
{
	isShow = false;
	isUnit = false;
	fire = false;
	wind = false;
	earth = false;
	water = false;
}
void infoCursor::tileLineDraw(void)
{
	SelectObject(getMemDC(), (HPEN)linePen);
	MoveToEx(getMemDC(), drawLine.left, drawLine.top, NULL); //현재 타일 테두리그림
	LineTo(getMemDC(), drawLine.right, drawLine.top);		 //현재 타일 테두리그림
	LineTo(getMemDC(), drawLine.right, drawLine.bottom);	 //현재 타일 테두리그림
	LineTo(getMemDC(), drawLine.left, drawLine.bottom);		 //현재 타일 테두리그림
	LineTo(getMemDC(), drawLine.left, drawLine.top);		 //현재 타일 테두리그림
	SelectObject(getMemDC(), (HPEN)oPen);
}
void infoCursor::infoDraw(void)
{

	if (isUnit) //유닛을 눌렀을때 표시할 것들
	{
		Rectangle(getMemDC(), unitImgRect.left, unitImgRect.top, unitImgRect.right, unitImgRect.bottom); // 디버그용 렉트출력
		unitImg->render(getMemDC(), unitImgRect.left, unitImgRect.top);
		TextOut(getMemDC(), unitImgRect.left, unitImgRect.bottom + 24, unit, _tcslen(unit));
	}
	Rectangle(getMemDC(), tileImgRect.left, tileImgRect.top, tileImgRect.right, tileImgRect.bottom); // 디버그용 렉트출력
	TextOut(getMemDC(), tileImgRect.left, tileImgRect.bottom + 50, tilename, _tcslen(tilename));
	TextOut(getMemDC(), tileImgRect.left, tileImgRect.bottom + 80, prop, _tcslen(prop));
	
	for (int i = 0; i < 4; i++) // 디버그용 렉트출력
	{
		Rectangle(getMemDC(), element[i].left, element[i].top, element[i].right, element[i].bottom);
	}

	if (fire) IMAGEMANAGER->findImage(L"화속성")->render(getMemDC(), element[0].left, element[0].top);
	else if(!fire) IMAGEMANAGER->findImage(L"화속성비활성")->render(getMemDC(), element[0].left, element[0].top);
	if (water) IMAGEMANAGER->findImage(L"수속성")->render(getMemDC(), element[1].left, element[1].top);
	else if (!water) IMAGEMANAGER->findImage(L"수속성비활성")->render(getMemDC(), element[1].left, element[1].top);
	if (wind) IMAGEMANAGER->findImage(L"풍속성")->render(getMemDC(), element[2].left, element[2].top);
	else if (!wind) IMAGEMANAGER->findImage(L"풍속성비활성")->render(getMemDC(), element[2].left, element[2].top);
	if (earth) IMAGEMANAGER->findImage(L"땅속성")->render(getMemDC(), element[3].left, element[3].top);
	else if (!earth) IMAGEMANAGER->findImage(L"땅속성비활성")->render(getMemDC(), element[3].left, element[3].top);
}