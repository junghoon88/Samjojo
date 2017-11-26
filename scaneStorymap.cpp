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
	sDl = new scanDialog;
	storymap = IMAGEMANAGER->findImage(L"smap 0000");
	
	for (int i = 0; i < STILEY; i++)
	{
		for (int j = 0; j < STILEX; j++)
		{
			iso[i][j].x = 400 + STILESIZEXHALF*(j - i);
			iso[i][j].y =  -200 +STILESIZEYHALF*(j + i);
	
			iso[i][j].poly[0] = { iso[i][j].x, iso[i][j].y - STILESIZEYHALF };
			iso[i][j].poly[1] = { iso[i][j].x + STILESIZEXHALF, iso[i][j].y };
			iso[i][j].poly[2] = { iso[i][j].x, iso[i][j].y + STILESIZEYHALF };
			iso[i][j].poly[3] = { iso[i][j].x - STILESIZEXHALF, iso[i][j].y };
	
			iso[i][j].region = CreatePolygonRgn(iso[i][j].poly, 4, ALTERNATE);
		}
	}


	return S_OK;
}
void scaneStorymap::release(void)
{

}
void scaneStorymap::update(void) 
{
	if (sDl->getNext() == 0)
	{
		storymap = IMAGEMANAGER->findImage(L"smap 0000");
	}
	if (sDl->getNext() == 1)
	{
		storymap = IMAGEMANAGER->findImage(L"smap 0001");
	}
}
void scaneStorymap::render(void) 
{

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

	
}