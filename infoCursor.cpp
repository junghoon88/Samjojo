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
	
	rc = { 0,0,0,0 };
	
	unit = L"빈공간";
	tilename = L"널";
	prop = L"널";

	fire = false;
	wind = false;
	earth = false;
	water = false;

	drawLine = { findtile->getTile()[0].rc.left,findtile->getTile()[0].rc.top,findtile->getTile()[0].rc.right,findtile->getTile()[0].rc.bottom };

	return S_OK;
}
void infoCursor::release(void)
{

}
void infoCursor::update(void) 
{

	Scanning();
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON)) isShow = false; //윈도우 닫기


}
void infoCursor::render(void) 
{
	MoveToEx(getMemDC(), drawLine.left, drawLine.top, NULL); //현재 타일 테두리그림
	LineTo(getMemDC(), drawLine.right, drawLine.top);		 //현재 타일 테두리그림
	LineTo(getMemDC(), drawLine.right, drawLine.bottom);	 //현재 타일 테두리그림
	LineTo(getMemDC(), drawLine.left, drawLine.bottom);		 //현재 타일 테두리그림
	LineTo(getMemDC(), drawLine.left, drawLine.top);		 //현재 타일 테두리그림

	if (isShow) //
	{
		Rectangle(getMemDC(), rc.left, rc.top, rc.right, rc.bottom);
		if (isUnit) //유닛을 눌렀을때 표시할 것들
		{
			TextOut(getMemDC(), rc.left + 10, rc.top + 10, unit, _tcslen(unit));
		}
		else//지형을 눌렀을때 표시할 것들
		{
			TextOut(getMemDC(), rc.left + 10, rc.top + 10, unit, _tcslen(tilename));
		}
			
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
				if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) Click(i);//지형 클릭 시
			}
		}
	}

}

void infoCursor::Click(int num)
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
				prop = L"이동 가능";
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
				fire = true;
				water = true;
				wind = true;
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
				wind = false;
				earth = false;
				break;

			case TERRAIN_SNOW:
				tilename = L"설원";
				fire = false;
				water = false;
				wind = false;
				earth = false;
				break;

			case TERRAIN_CASTLE:
				tilename = L"성";
				fire = false;
				water = false;
				wind = false;
				earth = false;
				break;

			case TERRAIN_INCASTLE:
				tilename = L"성내";
				fire = false;
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
				fire = false;
				water = false;
				wind = false;
				earth = false;
				break;

			case TERRAIN_SWAMP:
				tilename = L"슾지";
				fire = false;
				water = false;
				wind = false;
				earth = false;
				break;

			case TERRAIN_FORD:
				tilename = L"여울";
				fire = false;
				water = false;
				wind = false;
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
				fire = false;
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
				fire = false;
				water = false;
				wind = false;
				earth = false;
				break;

			case TERRAIN_FLAT:
				tilename = L"평지";
				fire = false;
				water = false;
				wind = false;
				earth = false;
				break;

			case TERRAIN_BADLANDS:
				tilename = L"황무지";
				fire = false;
				water = false;
				wind = false;
				earth = false;
				break;

			case TERRAIN_GATEWAY: 
				tilename = L"관문";
				fire = false;
				water = false;
				wind = false;
				earth = false;
				break;

			case TERRAIN_NONE:
				tilename = L"논";
				fire = false;
				water = false;
				wind = false;
				earth = false;
				break;

			}
			isUnit = false;//지형은 false로
			rc = RectMake(findtile->getTile()[i].rc.left, findtile->getTile()[i].rc.top, 40, 80);

		}
	}
	
	isShow = true;
}
