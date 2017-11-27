#include "stdafx.h"
#include "scaneStorymap.h"


scaneStorymap::scaneStorymap()
{
}


scaneStorymap::~scaneStorymap()
{

}
HRESULT scaneStorymap::init(void)
{
	
	storymap = IMAGEMANAGER->findImage(L"smap 0000");
	test = IMAGEMANAGER->findImage(L"리동탁");
	test1 = IMAGEMANAGER->findImage(L"테스트");
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

	x = 105;
	y = 45;
	test->setX(iso[x][y].x);
	test->setY(iso[x][y].y);

	return S_OK;
}
void scaneStorymap::release(void)
{

}
void scaneStorymap::update(void) 
{

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		y++;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		y--;
	}
	test->setX(iso[x][y].x);
	test->setY(iso[x][y].y);
}
void scaneStorymap::render(void) 
{
	switch (sDl->getNext())
	{
	case 0: storymap = IMAGEMANAGER->findImage(L"smap 0000");
		break;
	case 1: storymap = IMAGEMANAGER->findImage(L"smap 0001");
		break;
	case 2: storymap = IMAGEMANAGER->findImage(L"smap 0002");
		break;
	case 3: storymap = IMAGEMANAGER->findImage(L"smap 0003");
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
	test->render(getMemDC(), test->getX(), test->getY());
	test1->render(getMemDC(), iso[16][19].x, iso[16][19].y);
	test1->render(getMemDC(), iso[16][27].x, iso[16][27].y);
	

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