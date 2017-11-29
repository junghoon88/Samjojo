#include "stdafx.h"
#include "scaneStorymap.h"


scaneStorymap::scaneStorymap()
	: sDl(NULL)
{
}


scaneStorymap::~scaneStorymap()
{

}
HRESULT scaneStorymap::init(void)
{
	storymap = IMAGEMANAGER->findImage(L"smap 0000");


	for (int i = 0; i < STILEY; i++)
	{
		for (int j = 0; j < STILEX; j++)
		{
			iso[i][j].x = 400 + STILESIZEXHALF*(j - i);
			iso[i][j].y = -200+ STILESIZEYHALF*(j + i);
	
			iso[i][j].poly[0] = { iso[i][j].x, iso[i][j].y - STILESIZEYHALF };
			iso[i][j].poly[1] = { iso[i][j].x + STILESIZEXHALF, iso[i][j].y };
			iso[i][j].poly[2] = { iso[i][j].x, iso[i][j].y + STILESIZEYHALF };
			iso[i][j].poly[3] = { iso[i][j].x - STILESIZEXHALF, iso[i][j].y };
	
			iso[i][j].region = CreatePolygonRgn(iso[i][j].poly, 4, ALTERNATE);

		}
	}
	
	img[0].x = 102; //동탁 위치       y가 작아지면 위로감
	img[0].y = 45;
	img[1].x = 85; //이유 위치        x가 작아지면 오른쪽으로감
	img[1].y = 45;
	img[2].x = 80; //문관1 위치
	img[2].y = 75;
	img[3].x = 80; //문관2 위치
	img[3].y = 90;
	img[4].x = 135; //모르는병사1 
	img[4].y = 90;
	img[5].x = 135; //모르는병사2
	img[5].y = 75;
	img[6].x = 116; //왕윤
	img[6].y = 108; 
	img[7].x = 95; //초선
	img[7].y = 108;
	img[8].x = 60; //병사
	img[8].y = 88;
	img[9].x = 85; //조조
	img[9].y = 55;
	img[10].x = 72; //원소
	img[10].y = 78;
	
	
	for (int i = 0; i < CHARMAX; i++)
	{
		TCHAR strKey[100];
		_stprintf(strKey, L"story_%02d", i);
		img[i].etc = IMAGEMANAGER->findImage(strKey);
		img[i].etc->setX(iso[img[i].x][img[i].y].x);
		img[i].etc->setY(iso[img[i].x][img[i].y].y);
	}
	
	
	
	

	return S_OK;
}
void scaneStorymap::release(void)
{
	for (int i = 0; i < STILEY; i++)
	{
		for (int j = 0; j < STILEY; j++)
		{
			DeleteObject(iso[i][j].region);
		}
	}
}

void scaneStorymap::update(void) 
{

	//if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	//{
	//	y++;
	//}
	//if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	//{
	//	y--;
	//}
	//if (KEYMANAGER->isStayKeyDown(VK_UP))
	//{
	//	x++;
	//}
	//if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	//{
	//	x--;
	//}
	
	//for (int i = 0; i < CHARMAX; i++)
	//{
	//	img[i].etc->setX(iso[img[i].x][img[i].y].x);
	//	img[i].etc->setY(iso[img[i].x][img[i].y].y);
	//}

}
void scaneStorymap::render(void)
{
	switch (sDl->getNext())
	{
	case 0: storymap = IMAGEMANAGER->findImage(L"smap 0000");
		break;
	case 1: case 2 : case 3 : storymap = IMAGEMANAGER->findImage(L"smap 0001");
		break;
	case 4 : storymap = IMAGEMANAGER->findImage(L"smap 0002");
		break;
	case 5: storymap = IMAGEMANAGER->findImage(L"smap 0003");
		break;

	}

	storymap->render(getMemDC(), 0, 0);

	for (int i = 0; i < STILEY; i++)
	{
		for (int j = 0; j < STILEX; j++)
		{
			if (KEYMANAGER->isStayKeyDown(VK_SPACE))
			{
				Polygon(getMemDC(), iso[i][j].poly, 4);

			}
		}
	}

	if (sDl->getNext() == 0)
	{		for (int i = 0; i < 6; i++)
		{
			img[i].etc->render(getMemDC(), img[i].etc->getX(), img[i].etc->getY());
		}
	}
	else if (sDl->getNext() == 1 || sDl->getNext() == 3)
	{
		for (int i = 6; i <= 7; i++)
		{
			img[i].etc->render(getMemDC(), img[i].etc->getX(), img[i].etc->getY());
		}
	}
	else if (sDl->getNext() == 2)
	{
		for (int i = 6; i <= 8; i++)
		{
			img[i].etc->render(getMemDC(), img[i].etc->getX(), img[i].etc->getY());
		}
	}
	else if (sDl->getNext() == 4)
	{
		for (int i = 9; i < 11; i++)
		{
			img[i].etc->render(getMemDC(), img[i].etc->getX(), img[i].etc->getY());
		}
	}
	
	for (int i = 0; i < STILEY; i++)
	{
		for (int j = 0; j < STILEX; j++)
		{
			
			if (PtInRegion(iso[i][j].region, _ptMouse.x, _ptMouse.y))
			{
				
				TCHAR tmpPOINT[1002];
				
				_stprintf(tmpPOINT, L" x축 %d 번째타일,y 축 %d 번째타일", i, j);

				TextOut(getMemDC(), 800, 0, tmpPOINT, _tcslen(tmpPOINT));
			}
		}
	}
}