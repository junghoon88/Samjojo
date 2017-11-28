#include "stdafx.h"
#include "sideInterface.h"


sideInterface::sideInterface()
{
}


sideInterface::~sideInterface()
{
}

HRESULT sideInterface::init(void)
{
	for (int i = 0; i < 5; i++)
	{
		button[i].onOff = false;
		button[i].rc = RectMakeCenter(WINSIZEX - SIDEWINSIZE / 2, WINSIZEY / 2 + 100, SIDEWINSIZE - SIDEWINSIZE / 10, 50);
	}

	button[0].type = turnEnd;
	button[1].type = unit;
	button[2].type = inven;
	button[3].type = save;
	button[4].type = load;

	return S_OK;
}
void sideInterface::release(void)
{

}
void sideInterface::update(void) 
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < 5; i++)
		{
			if (!button[i].onOff) continue;
			if (PtInRect(&button[i].rc, _ptMouse))
			{
				switch (button[i].type)
				{
				case turnEnd:
					break;
				case unit:
					break;
				case inven:
					break;
				case save:
					break;
				case load:
					break;
				default:
					break;
				}
			}
		}
	}
}
void sideInterface::render(void) 
{

}


void sideInterface::setBattleScene(void)
{
	for (int i = 0; i < 5; i++)
	{
		button[i].onOff = true;
	}

}
void sideInterface::setScenarioScene(void)
{
	for (int i = 0; i < 5; i++)
	{
		button[i].onOff = false;
	}
}
void sideInterface::setShopScene(void)
{
	for (int i = 0; i < 5; i++)
	{
		button[i].onOff = false;
	}
}