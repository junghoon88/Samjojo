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
	
	rc = { 0,0,0,0 };
	
	unit = L"�����";
	tilename = L"��";
	prop = L"��";

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
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON)) isShow = false; //������ �ݱ�


}
void infoCursor::render(void) 
{
	MoveToEx(getMemDC(), drawLine.left, drawLine.top, NULL); //���� Ÿ�� �׵θ��׸�
	LineTo(getMemDC(), drawLine.right, drawLine.top);		 //���� Ÿ�� �׵θ��׸�
	LineTo(getMemDC(), drawLine.right, drawLine.bottom);	 //���� Ÿ�� �׵θ��׸�
	LineTo(getMemDC(), drawLine.left, drawLine.bottom);		 //���� Ÿ�� �׵θ��׸�
	LineTo(getMemDC(), drawLine.left, drawLine.top);		 //���� Ÿ�� �׵θ��׸�

	if (isShow) //
	{
		Rectangle(getMemDC(), rc.left, rc.top, rc.right, rc.bottom);
		if (isUnit) //������ �������� ǥ���� �͵�
		{
			TextOut(getMemDC(), rc.left + 10, rc.top + 10, unit, _tcslen(unit));
		}
		else//������ �������� ǥ���� �͵�
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
				if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) Click(i);//���� Ŭ�� ��
			}
		}
	}

}

void infoCursor::Click(int num)
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
				prop = L"�̵� ����";
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
				fire = true;
				water = true;
				wind = true;
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
				wind = false;
				earth = false;
				break;

			case TERRAIN_SNOW:
				tilename = L"����";
				fire = false;
				water = false;
				wind = false;
				earth = false;
				break;

			case TERRAIN_CASTLE:
				tilename = L"��";
				fire = false;
				water = false;
				wind = false;
				earth = false;
				break;

			case TERRAIN_INCASTLE:
				tilename = L"����";
				fire = false;
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
				fire = false;
				water = false;
				wind = false;
				earth = false;
				break;

			case TERRAIN_SWAMP:
				tilename = L"����";
				fire = false;
				water = false;
				wind = false;
				earth = false;
				break;

			case TERRAIN_FORD:
				tilename = L"����";
				fire = false;
				water = false;
				wind = false;
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
				fire = false;
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
				fire = false;
				water = false;
				wind = false;
				earth = false;
				break;

			case TERRAIN_FLAT:
				tilename = L"����";
				fire = false;
				water = false;
				wind = false;
				earth = false;
				break;

			case TERRAIN_BADLANDS:
				tilename = L"Ȳ����";
				fire = false;
				water = false;
				wind = false;
				earth = false;
				break;

			case TERRAIN_GATEWAY: 
				tilename = L"����";
				fire = false;
				water = false;
				wind = false;
				earth = false;
				break;

			case TERRAIN_NONE:
				tilename = L"��";
				fire = false;
				water = false;
				wind = false;
				earth = false;
				break;

			}
			isUnit = false;//������ false��
			rc = RectMake(findtile->getTile()[i].rc.left, findtile->getTile()[i].rc.top, 40, 80);

		}
	}
	
	isShow = true;
}
