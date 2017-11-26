#include "stdafx.h"
#include "infoCursor.h"

//������ ������ �÷��̾� �������̽� ���� Ŭ������ ���̴ϴ�.




infoCursor::infoCursor(){}
infoCursor::~infoCursor(){}

HRESULT infoCursor::init(void) 
{
	findtile = new gameMap;
	findtile->init();
	isShow = false;
	isUnit = false;

	rc = { WINSIZEX - SIDEWINSIZE,0,WINSIZEX,WINSIZEY };//�������̽� ���� ��Ʈ
	tileImgRect = RectMakeCenter(rc.left + SIDEWINSIZE / 2, 80, SIDEWINSIZE - SIDEWINSIZE/10, SIDEWINSIZE - SIDEWINSIZE/10);
	unitImgRect = RectMakeCenter(rc.left + SIDEWINSIZE / 2, WINSIZEY/2 , SIDEWINSIZE - SIDEWINSIZE/10, SIDEWINSIZE - SIDEWINSIZE/10);


	unit = L"�����̸�����";
	tilename = L"Ÿ���̸�����";
	prop = L"�����Ӽ�����";

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
	Scanning();//���� Ÿ�� ���� �� Ŭ�� ��ȣ ���� ��.

	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON)) dataClean();  //������ �ݱ�
	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		if (isShow) dataClean();
		else Click();//���� Ŭ�� �� 
	}
}
void infoCursor::render(void) 
{
	tileLineDraw(); //Ŀ�� Ÿ�� �׵θ� �׸�
	Rectangle(getMemDC(), rc.left, rc.top, rc.right, rc.bottom);
	if (isShow)
	{

		infoDraw();// ���� ǥ��
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
	for (int i = 0; i < TILEX * TILEY; i++)//�ѹ� �� ������ ���� = ���ÿ� Ÿ�ϸ� ���鼭 �׵θ��׸��ٰ� Ŭ���������� ������ �ִ��� �ѹ� �� üũ�ϱ� ����?
	{
		if (PtInRect(&findtile->getTile()[i].rc, _ptMouse))//�� ���� ���� �������� ����. ������ ���� �� ���� �����ϰ�
		{
			//�������� ���� ��
			switch (findtile->getTile()[i].terrain)
			{
			case TERRAIN_RIVER:
				tilename = L"��";
				prop = L"�̵� �Ұ�";
				fire = false;
				water = false;
				wind = false;
				earth = false;
				break;
			case TERRAIN_BRIDGE:
				tilename = L"�ٸ�";
				prop = L"";
				fire = true;
				water = true;
				wind = true;
				earth = false;
				break;
			case TERRAIN_WATER:
				tilename = L"����";
				prop = L"�̵� �Ұ�";
				fire = true;
				water = true;
				wind = true;
				earth = false;
				break;

			case TERRAIN_DITCH:
				tilename = L"����";
				prop = L"�̵� �Ұ�";
				fire = false;
				water = false;
				wind = false;
				earth = false;
				break;

			case TERRAIN_VILLAGE:
				tilename = L"����";
				prop = L"ȸ�� ����";
				fire = true;
				water = false;
				wind = false;
				earth = false;
				break;

			case TERRAIN_PREMISES:
				tilename = L"����";
				prop = L"";
				fire = true;
				water = false;
				wind = false;
				earth = false;
				break;

			case TERRAIN_ROCK:
				tilename = L"�Ϻ�";
				prop = L"�̵� �Ұ�";
				fire = false;
				water = false;
				wind = false;
				earth = false;
				break;

			case TERRAIN_SHIP:
				tilename = L"��";
				prop = L"�̵� �Ұ�";
				fire = false;
				water = false;
				wind = false;
				earth = false;
				break;

			case TERRAIN_BROW:
				tilename = L"����";
				prop = L"�̵� �Ұ�";
				fire = false;
				water = false;
				wind = false;
				earth = false;
				break;

			case TERRAIN_BARRACK:
				tilename = L"����";
				prop = L"ȸ�� ����";
				fire = true;
				water = false;
				wind = false;
				earth = false;
				break;

			case TERRAIN_WAREHOUSE:
				tilename = L"���޼�";
				prop = L"ȸ�� ����";
				fire = true;
				water = false;
				wind = false;
				earth = false;
				break;

			case TERRAIN_FIRE:
				tilename = L"��";
				prop = L"�̵� �Ұ�";
				fire = false;
				water = false;
				wind = false;
				earth = false;
				break;

			case TERRAIN_MOUNTAIN:
				tilename = L"��";
				prop = L"";
				fire = false;
				water = false;
				wind = true;
				earth = true;
				break;

			case TERRAIN_SNOW:
				tilename = L"����";
				prop = L"";
				fire = false;
				water = false;
				wind = false;
				earth = false;
				break;

			case TERRAIN_CASTLE:
				tilename = L"��";
				prop = L"ȸ�� ����";
				fire = true;
				water = false;
				wind = false;
				earth = false;
				break;

			case TERRAIN_INCASTLE:
				tilename = L"����";
				prop = L"";
				fire = true;
				water = false;
				wind = false;
				earth = false;
				break;

			case TERRAIN_CASTLEGATE:
				tilename = L"����";
				prop = L"�̵� �Ұ�";
				fire = false;
				water = false;
				wind = false;
				earth = false;
				break;

			case TERRAIN_RAMPART:
				tilename = L"����";
				prop = L"�̵� �Ұ�";
				fire = false;
				water = false;
				wind = false;
				earth = false;
				break;

			case TERRAIN_FOREST:
				tilename = L"��";
				prop = L"";
				fire = true;
				water = false;
				wind = false;
				earth = false;
				break;

			case TERRAIN_SWAMP:
				tilename = L"����";
				prop = L"";
				fire = false;
				water = true;
				wind = true;
				earth = false;
				break;

			case TERRAIN_FORD:
				tilename = L"����";
				prop = L"";
				fire = false;
				water = true;
				wind = true;
				earth = false;
				break;

			case TERRAIN_POND:
				tilename = L"����";
				prop = L"�̵� �Ұ�";
				fire = false;
				water = false;
				wind = false;
				earth = false;
				break;

			case TERRAIN_STRONGHOLD:
				tilename = L"���";
				prop = L"ȸ�� ����";
				fire = true;
				water = false;
				wind = false;
				earth = false;
				break;

			case TERAAIN_FENCE:
				tilename = L"��Ÿ��";
				prop = L"�̵� �Ұ�";
				fire = false;
				water = false;
				wind = false;
				earth = false;
				break;

			case TERRAIN_ALTER:
				tilename = L"����";
				prop = L"";
				fire = false;
				water = false;
				wind = false;
				earth = false;
				break;

			case TERRAIN_UNDERGROUND:
				tilename = L"����";
				prop = L"�̵� �Ұ�";
				fire = false;
				water = false;
				wind = false;
				earth = false;
				break;

			case TERRAIN_GRASSLAND:
				tilename = L"�ʿ�";
				prop = L"";
				fire = true;
				water = false;
				wind = true;
				earth = false;
				break;

			case TERRAIN_FLAT:
				tilename = L"����";
				prop = L"";
				fire = true;
				water = false;
				wind = true;
				earth = false;
				break;

			case TERRAIN_BADLANDS:
				tilename = L"Ȳ����";
				prop = L"";
				fire = false;
				water = false;
				wind = true;
				earth = true;
				break;

			case TERRAIN_GATEWAY:
				tilename = L"����";
				prop = L"ȸ�� ����";
				fire = true;
				water = false;
				wind = false;
				earth = false;
				break;

			case TERRAIN_NONE:
				tilename = L"������������";
				prop = L"";
				fire = false;
				water = false;
				wind = false;
				earth = false;
				break;

			}
			isUnit = false;//������ false��
		}
	}
	isShow = true;
}

void infoCursor::dataClean(void)//���콺 ��Ŭ�� �� ���� �������̽��� ������ �ʱ�ȭ ���ִ� ������ �� ��.
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
	MoveToEx(getMemDC(), drawLine.left, drawLine.top, NULL); //���� Ÿ�� �׵θ��׸�
	LineTo(getMemDC(), drawLine.right, drawLine.top);		 //���� Ÿ�� �׵θ��׸�
	LineTo(getMemDC(), drawLine.right, drawLine.bottom);	 //���� Ÿ�� �׵θ��׸�
	LineTo(getMemDC(), drawLine.left, drawLine.bottom);		 //���� Ÿ�� �׵θ��׸�
	LineTo(getMemDC(), drawLine.left, drawLine.top);		 //���� Ÿ�� �׵θ��׸�
	SelectObject(getMemDC(), (HPEN)oPen);
}
void infoCursor::infoDraw(void)
{

		if (isUnit) //������ �������� ǥ���� �͵�
		{
			Rectangle(getMemDC(), tileImgRect.left, tileImgRect.top, tileImgRect.right, tileImgRect.bottom);
			Rectangle(getMemDC(), unitImgRect.left, unitImgRect.top, unitImgRect.right, unitImgRect.bottom);
			TextOut(getMemDC(), unitImgRect.left, unitImgRect.bottom + 20, unit, _tcslen(unit));
			TextOut(getMemDC(), tileImgRect.left, tileImgRect.bottom + 20, tilename, _tcslen(tilename));
			TextOut(getMemDC(), tileImgRect.left, tileImgRect.bottom + 40, prop, _tcslen(prop));
		}
		else//������ �������� ǥ���� �͵�
		{
			Rectangle(getMemDC(), tileImgRect.left, tileImgRect.top, tileImgRect.right, tileImgRect.bottom);
			TextOut(getMemDC(), tileImgRect.left, tileImgRect.bottom + 20, tilename, _tcslen(tilename));
			TextOut(getMemDC(), tileImgRect.left, tileImgRect.bottom + 40, prop, _tcslen(prop));
		}


}