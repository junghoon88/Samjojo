#include "stdafx.h"
#include "infoCursor.h"

//전투씬 내에서 플레이어 인터페이스 제공 클래스로 쓸겁니다.




infoCursor::infoCursor(){}
infoCursor::~infoCursor(){}

HRESULT infoCursor::init(void) 
{
	findtile = new gameMap;
	findtile->init();
	isShow = false;
	isUnit = false;

	rc = { WINSIZEX - SIDEWINSIZE,0,WINSIZEX,WINSIZEY };//인터페이스 간이 렉트
	tileImgRect = RectMakeCenter(rc.left + SIDEWINSIZE / 2, 80, SIDEWINSIZE - SIDEWINSIZE/10, SIDEWINSIZE - SIDEWINSIZE/10);
	unitImgRect = RectMakeCenter(rc.left + SIDEWINSIZE / 2, WINSIZEY/2 , SIDEWINSIZE - SIDEWINSIZE/10, SIDEWINSIZE - SIDEWINSIZE/10);


	unit = L"유닛이름정보";
	tilename = L"타일이름정보";
	prop = L"지형속성정보";

	fire = false;
	wind = false;
	earth = false;
	water = false;


	drawLine = { findtile->getTile()[0].rc.left,findtile->getTile()[0].rc.top,findtile->getTile()[0].rc.right,findtile->getTile()[0].rc.bottom };
	oPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	linePen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	return S_OK;
}
void infoCursor::release(void)
{

}
void infoCursor::update(void) 
{
	Scanning();//지형 타일 갱신 및 클릭 신호 받을 곳.

	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON)) dataClean();  //윈도우 닫기
	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		if (isShow) dataClean();
		else Click();//지형 클릭 시 
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

void infoCursor::Scanning(void)
{
	if (!isShow)
	{
		for (int i = 0; i < TILEX * TILEY; i++)
		{
			if (PtInRect(&findtile->getTile()[i].rc, _ptMouse))
			{
				drawLine = { findtile->getTile()[i].rc.left,findtile->getTile()[i].rc.top,findtile->getTile()[i].rc.right,findtile->getTile()[i].rc.bottom };
				
			}
		}
	}

}

void infoCursor::Click(void)
{
	for (int i = 0; i < TILEX * TILEY; i++)//한번 더 돌리는 이유 = 평상시에 타일만 돌면서 테두리그리다가 클릭했을때만 유닛이 있는지 한번 더 체크하기 위해?
	{
		if (PtInRect(&findtile->getTile()[i].rc, _ptMouse))//이 조건 위에 유닛조건 걸자. 유닛이 없을 시 지형 검출하게
		{
			//지형정보 넣을 곳
			switch (findtile->getTile()[i].terrain)
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
			isUnit = false;//지형은 false로
		}
	}
	isShow = true;
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
			Rectangle(getMemDC(), tileImgRect.left, tileImgRect.top, tileImgRect.right, tileImgRect.bottom);
			Rectangle(getMemDC(), unitImgRect.left, unitImgRect.top, unitImgRect.right, unitImgRect.bottom);
			TextOut(getMemDC(), unitImgRect.left, unitImgRect.bottom + 20, unit, _tcslen(unit));
			TextOut(getMemDC(), tileImgRect.left, tileImgRect.bottom + 20, tilename, _tcslen(tilename));
			TextOut(getMemDC(), tileImgRect.left, tileImgRect.bottom + 40, prop, _tcslen(prop));
		}
		else//지형을 눌렀을때 표시할 것들
		{
			Rectangle(getMemDC(), tileImgRect.left, tileImgRect.top, tileImgRect.right, tileImgRect.bottom);
			TextOut(getMemDC(), tileImgRect.left, tileImgRect.bottom + 20, tilename, _tcslen(tilename));
			TextOut(getMemDC(), tileImgRect.left, tileImgRect.bottom + 40, prop, _tcslen(prop));
		}


}