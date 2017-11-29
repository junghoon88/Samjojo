#include "stdafx.h"
#include "infoCursor.h"
#include "Player.h"
#include "Enemy.h"
#include "Friend.h"
#include "gameMap.h"
//������ ������ �÷��̾� �������̽� ���� Ŭ������ ���̴ϴ�.

infoCursor::infoCursor()
	:_player(NULL), _friend(NULL), _enemy(NULL), findtile(NULL)
{}
infoCursor::~infoCursor(){}

HRESULT infoCursor::init(void) 
{
	isShow = false;
	isUnit = false;
	indexTile = 0;
	scanPoint = { 0,0 };

	rc = { WINSIZEX - SIDEWINSIZE,0,WINSIZEX,WINSIZEY };//�������̽� ���� ��Ʈ
	tileImgRect = RectMakeCenter(rc.left + SIDEWINSIZE / 2, 80, FROFILEIMAGE, FROFILEIMAGE);
	unitImgRect = RectMakeCenter(rc.left + SIDEWINSIZE / 2, WINSIZEY/2 , FROFILEIMAGE, FROFILEIMAGE);
	for (int i = 0; i < 4; i++)
	{
		element[i] = RectMakeCenter(rc.left + TILESIZE/2 + ((TILESIZE / 2 + (TILESIZE / 2 * 0.25)) * i), tileImgRect.bottom + TILESIZE / 2, TILESIZE / 2, TILESIZE / 2);
	}


	factionName = L"��������";
	unitName = L"�����̸�����";
	tilename = L"Ÿ���̸�����";
	prop = L"�����Ӽ�����";
	showExp = L"����ġ";
	fire = false;
	wind = false;
	earth = false;
	water = false;

	unitImg = IMAGEMANAGER->findImage(L"����");
	tileImg = IMAGEMANAGER->findImage(L"����");
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
	mouse_Scanning();//���� Ÿ�� ����
	if(!isShow)moveCamera();
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON)) dataClean();  //������ �ݱ�
	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		if (isShow) dataClean();
		else mouse_Click();//���� Ŭ�� �� 
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

void infoCursor::mouse_Scanning(void)
{
	if (!isShow)
	{
		scanPoint.x = (int)_ptMouse.x + MAINCAMERA->getCameraX();
		scanPoint.y = (int)_ptMouse.y + MAINCAMERA->getCameraY();
		indexTile = (int)(_ptMouse.x / TILESIZE) + (int)(_ptMouse.y / TILESIZE)  * TILEX ;
		drawLine = { findtile->getTile()[indexTile].rc.left,findtile->getTile()[indexTile].rc.top,findtile->getTile()[indexTile].rc.right,findtile->getTile()[indexTile].rc.bottom };
	}

}

void infoCursor::mouse_Click(void)
{
	findtile->scanUnitsPos();
//	int findIndex = (int)(indexTile + MAINCAMERA->getCameraX()) / TILESIZE + (int)(MAINCAMERA->getCameraY() / TILESIZE) * TILEX;
	int findIndex = indexTile + (MAINCAMERA->getCameraX() / TILESIZE) + (MAINCAMERA->getCameraY() / TILESIZE) * TILEX;

	if (findtile->getTeamInfo()[findIndex] == TEAM_PLAYER)
	{
		for (int i = 0; i < _player->getUnits().size(); i++)
		{
			if (PtInRect(&_player->getUnits()[i]->getRect(), scanPoint))
			{
				isUnit = true;
				factionName = L"�÷��̾�";
				unitName = _player->getUnits()[i]->getStatus().name;
				unitImg = _player->getUnits()[i]->getBattleState().imgBattleIdle;//����
			}
		}
	}
	else if (findtile->getTeamInfo()[findIndex * TILESIZE] == TEAM_FRIEND)
	{
		//factionName = L"�Ʊ�";
		//isUnit = true;
		//unitName = _friend->getUnits()[findIndex]->getStatus().name;
	}
	else if (findtile->getTeamInfo()[findIndex * TILESIZE / TILEX] == TEAM_ENEMY)
	{

		for (int i = 0; i < _enemy->getUnits().size(); i++)
		{
			if (PtInRect(&_enemy->getUnits()[i]->getRect(), scanPoint))
			{
				isUnit = true;
				factionName = L"����";
				unitName = _enemy->getUnits()[i]->getStatus().name;
				unitImg = _enemy->getUnits()[i]->getBattleState().imgBattleIdle;//����
			}
		}
	}

	tileNum = findtile->getTile()[findIndex].terrain;//�ش��ȣ�� Ű������ ã���� �ȴ�. �̹�����!
	switch (findtile->getTile()[findIndex].terrain)
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
	isShow = true;
}

void infoCursor::moveCamera(void)
{
	if (_ptMouse.x > WINSIZEX - TILESIZE/2 - 144 && _ptMouse.x <= WINSIZEX - 144 && MAINCAMERA->getCameraX() < findtile->getTileSizeX() * TILESIZE - TILESIZE * 20)// ���콺�� ������ 
		MAINCAMERA->setCameraX(MAINCAMERA->getCameraX() + TILESIZE ); 
	if (_ptMouse.x < TILESIZE/2 && _ptMouse.x >= 0 && MAINCAMERA->getCameraX() > 0)//���콺�� ����
		MAINCAMERA->setCameraX(MAINCAMERA->getCameraX() - TILESIZE); 
	if (_ptMouse.y > WINSIZEY - TILESIZE/2 && _ptMouse.y < WINSIZEY && MAINCAMERA->getCameraY() < findtile->getTileSizeY() * TILESIZE - TILESIZE * 20)//���콺�� ȭ�� �Ʒ���
		MAINCAMERA->setCameraY(MAINCAMERA->getCameraY() + TILESIZE); 
	if (_ptMouse.y < TILESIZE/2 && _ptMouse.y >= 0 && MAINCAMERA->getCameraY() > 0)//���콺�� ȭ�� ����
		MAINCAMERA->setCameraY(MAINCAMERA->getCameraY() - TILESIZE); 

	if(KEYMANAGER->isOnceKeyDown(VK_LEFT) && MAINCAMERA->getCameraX() > 0)//����
		MAINCAMERA->setCameraX(MAINCAMERA->getCameraX() - TILESIZE);
	if (KEYMANAGER->isOnceKeyDown(VK_UP) && MAINCAMERA->getCameraY() > 0)//����
		MAINCAMERA->setCameraY(MAINCAMERA->getCameraY() - TILESIZE);
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT) && MAINCAMERA->getCameraX() < findtile->getTileSizeX() * TILESIZE - TILESIZE * 20)//������
		MAINCAMERA->setCameraX(MAINCAMERA->getCameraX() + TILESIZE);
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN) && MAINCAMERA->getCameraY() < findtile->getTileSizeY() * TILESIZE - TILESIZE * 20)//�Ʒ�  
		MAINCAMERA->setCameraY(MAINCAMERA->getCameraY() + TILESIZE);
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
		Rectangle(getMemDC(), unitImgRect.left, unitImgRect.top, unitImgRect.right, unitImgRect.bottom); // ����׿� ��Ʈ���
		unitImg->render(getMemDC(), unitImgRect.left, unitImgRect.top);
		TextOut(getMemDC(), unitImgRect.left, unitImgRect.bottom + 24, unitName, _tcslen(unitName));
		TextOut(getMemDC(), unitImgRect.left, unitImgRect.bottom + 72, factionName, _tcslen(factionName));
	}
	Rectangle(getMemDC(), tileImgRect.left, tileImgRect.top, tileImgRect.right, tileImgRect.bottom); // ����׿� ��Ʈ���
	TextOut(getMemDC(), tileImgRect.left, tileImgRect.bottom + 50, tilename, _tcslen(tilename));
	TextOut(getMemDC(), tileImgRect.left, tileImgRect.bottom + 80, prop, _tcslen(prop));

	
	
	//for (int i = 0; i < 4; i++) // ����׿� ��Ʈ���
	//{
	//	Rectangle(getMemDC(), element[i].left, element[i].top, element[i].right, element[i].bottom);
	//}

	if (fire) IMAGEMANAGER->findImage(L"ȭ�Ӽ�")->render(getMemDC(), element[0].left, element[0].top);
	else if(!fire) IMAGEMANAGER->findImage(L"ȭ�Ӽ���Ȱ��")->render(getMemDC(), element[0].left, element[0].top);
	if (water) IMAGEMANAGER->findImage(L"���Ӽ�")->render(getMemDC(), element[1].left, element[1].top);
	else if (!water) IMAGEMANAGER->findImage(L"���Ӽ���Ȱ��")->render(getMemDC(), element[1].left, element[1].top);
	if (wind) IMAGEMANAGER->findImage(L"ǳ�Ӽ�")->render(getMemDC(), element[2].left, element[2].top);
	else if (!wind) IMAGEMANAGER->findImage(L"ǳ�Ӽ���Ȱ��")->render(getMemDC(), element[2].left, element[2].top);
	if (earth) IMAGEMANAGER->findImage(L"���Ӽ�")->render(getMemDC(), element[3].left, element[3].top);
	else if (!earth) IMAGEMANAGER->findImage(L"���Ӽ���Ȱ��")->render(getMemDC(), element[3].left, element[3].top);
}