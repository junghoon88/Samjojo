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
	time = 0;

	for (int i = 0; i < STILEY; i++)
	{
		for (int j = 0; j < STILEX; j++)
		{
			iso[i][j].x = 400 + STILESIZEXHALF*(j - i);
			iso[i][j].y = -200+ STILESIZEYHALF*(j + i);
	
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
	x = img[9].x = 85; //조조
	y = img[9].y = 55;
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
	
	img[9].etc->setFrameX(iso[x][y].y);
	img[9].etc->setFrameY(iso[x][y].y);
	img[9].etc->setFrameY(0);
	
	SOUNDMANAGER->play(L"Se_b_05", 1.0f);
	return S_OK;
}
void scaneStorymap::release(void)
{
	//for (int i = 0; i < STILEY; i++)
	//{
	//	for (int j = 0; j < STILEY; j++)
	//	{
	//		DeleteObject(iso[i][j].region);
	//	}
	//}
}

void scaneStorymap::update(void) 
{
	switch(sDl->getDirection())
	{
	//case 0: dir = STORY_DIRECTION_UP;
	//	break;
	//case 1: dir = STORY_DIRECTION_DOWN;
	//	break;
	case 2: dir = STORY_DIRECTION_LEFT;
		break;
	case 3: dir = STORY_DIRECTION_RIGHT;
		break;
	case 4: dir = STORY_MOVE;
		break;
	}
	switch (dir)
	{
		//case  STORY_DIRECTION_UP :
		//	break;
		//case  STORY_DIRECTION_DOWN:
		//	break;
	case  STORY_DIRECTION_LEFT:img[9].etc = IMAGEMANAGER->findImage(L"story_09");
		break;
	case  STORY_DIRECTION_RIGHT:img[9].etc = IMAGEMANAGER->findImage(L"story_11");
		break;
	case STORY_MOVE:
			{
				img[9].etc = IMAGEMANAGER->findImage(L"story jojo");
				time += TIMEMANAGER->getElapsedTime();
				if (time > 0.2f)
				{
					if (img[9].etc->getFrameY() >= img[9].etc->getMaxFrameY())
					{
						img[9].etc->setFrameY(0);
					}
					else img[9].etc->setFrameY(img[9].etc->getFrameY() + 1);
					time = 0;
				}
			}
	break;
	}
	
	jojomove();
	
	img[9].etc->setX(iso[x][y].x);
	img[9].etc->setY(iso[x][y].y);
	
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

		if (sDl->getNext() == 0)
	{		for (int i = 0; i < 6; i++)
		{
			img[i].etc->render(getMemDC(), img[i].etc->getX(), img[i].etc->getY());
		}
	}
	else if (sDl->getNext() == 1 || sDl->getNext() == 3 )
	{
		for (int i = 6; i <= 7; i++)
		{
			img[i].etc->render(getMemDC(), img[i].etc->getX(), img[i].etc->getY());
		}
	}
	else if (sDl->getNext() == 4 && sDl->getDirection() == 4)
	{
		img[9].etc->frameRender(getMemDC(), img[9].etc->getX(), img[9].etc->getY());
		img[10].etc->render(getMemDC(), img[10].etc->getX(), img[10].etc->getY());
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

}
void scaneStorymap::jojomove(void)
{
	if (sDl->getDirection()==4&& x<=180)
	{
		x++;
		if (x >= 180)
		{
			sDl->setDirection(0);
		}
	}
}