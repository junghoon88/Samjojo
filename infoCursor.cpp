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
	infoSetup();

	return S_OK;
}

void infoCursor::release(void)
{
}

void infoCursor::update(void) 
{
	if (!isCommand && !popUpMenu)
	{
		mouse_Scanning();//���� Ÿ�� ����
		if (!isShow)moveCamera();
		if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON)) dataClean();  //������ �ݱ�
		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
		{
			if (isShow && clickUnit == PLAYER && _player->getUnits()[vNum]->getUnitSequnce() == UNITSEQUENCE_TURNON &&  _player->getUnits()[vNum]->getBattleState().moved) mouse_ClickToAction(); // 
			else if (isShow) dataClean();
			else if (!isShow) mouse_ClickToTile();//���� Ŭ�� �� 
		}
	}
	else if (isCommand && !popUpMenu)//��� ���� �����̸� �ش� ������ ���������� ���ۺҰ�
	{
		if (UNITSEQUENCE_MOVE != _player->getUnits()[vNum]->getUnitSequnce()) 
		{
			//�̵����.
			_player->getUnits()[vNum]->setMoved(false);
			callToMenu();//�޴�ȭ���� ȣ��
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) dataClean();
			if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON)) mouse_ActionCancel();
		}
	}
	else if (popUpMenu)
	{
		callToMenu();
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
	indexTile = (int)(_ptMouse.x / TILESIZE) + (int)(_ptMouse.y / TILESIZE)  * TILEX;
	if (!isShow)
	{
		drawLine = { findtile->getTile()[indexTile].rc.left,findtile->getTile()[indexTile].rc.top,findtile->getTile()[indexTile].rc.right,findtile->getTile()[indexTile].rc.bottom };
	}
	else if (isShow && clickUnit == PLAYER)
	{
		int findIndex = indexTile + (MAINCAMERA->getCameraX() / TILESIZE) + (MAINCAMERA->getCameraY() / TILESIZE) * TILEX;
		if(_player->getUnits()[vNum]->isMovableArea(findIndex))drawMoveLine = { findtile->getTile()[indexTile].rc.left,findtile->getTile()[indexTile].rc.top,findtile->getTile()[indexTile].rc.right,findtile->getTile()[indexTile].rc.bottom };
		drawLine = _player->getUnits()[vNum]->getRect();
	}
}

void infoCursor::mouse_ClickToTile(void)
{
	int findIndex = indexTile + (MAINCAMERA->getCameraX() / TILESIZE) + (MAINCAMERA->getCameraY() / TILESIZE) * TILEX;

	if (findtile->getTeamInfo()[findIndex] == TEAM_PLAYER)
	{
		for (int i = 0; i < _player->getUnits().size(); i++)
		{
			if (findIndex == (int)(_player->getUnits()[i]->getBattleState().tilePt.x + _player->getUnits()[i]->getBattleState().tilePt.y * TILEX))
			{
				vNum = i;
				isUnit = true;
				clickUnit = PLAYER;
				factionName = L"�÷��̾�";
				unitName = _player->getUnits()[i]->getStatus().name;
				unitImg = _player->getUnits()[i]->getStatus().imgFace;
				_player->getUnits()[i]->findMoveArea();
				break;
			}
		}
	}
	else if (findtile->getTeamInfo()[findIndex] == TEAM_FRIEND)
	{
		for (int i = 0; i < _friend->getUnits().size(); i++)
		{
			if (findIndex == (int)(_friend->getUnits()[i]->getBattleState().tilePt.x + _friend->getUnits()[i]->getBattleState().tilePt.y * TILEX))
			{
				vNum = i;
				isUnit = true;
				clickUnit = FRIEND;
				factionName = L"�Ʊ�";
				unitName = _friend->getUnits()[i]->getStatus().name;
				unitImg = _friend->getUnits()[i]->getStatus().imgFace;
				_friend->getUnits()[i]->findMoveArea();
				break;
			}
		}
	}
	else if (findtile->getTeamInfo()[findIndex] == TEAM_ENEMY)
	{
		for (int i = 0; i < _enemy->getUnits().size(); i++)
		{
			if (findIndex == (int)(_enemy->getUnits()[i]->getBattleState().tilePt.x + _enemy->getUnits()[i]->getBattleState().tilePt.y * TILEX))
			{
				vNum = i;
				isUnit = true;
				clickUnit = ENEMY;
				factionName = L"����";
				unitName = _enemy->getUnits()[i]->getStatus().name;
				unitImg = _enemy->getUnits()[i]->getStatus().imgFace;
				_enemy->getUnits()[i]->findMoveArea();
				break;
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

void infoCursor::mouse_ClickToAction(void)//�ൿ������ �÷��̾� ������ ���������϶� Ŭ���ϸ� ������ �׼ǵ�
{
	int setindex = (int)(_ptMouse.x / TILESIZE) + (int)(_ptMouse.y / TILESIZE)  * TILEX;
	int findIndex = setindex + (MAINCAMERA->getCameraX() / TILESIZE) + (MAINCAMERA->getCameraY() / TILESIZE) * TILEX;
	//_player->getUnits()[vNum]->getBattleState().rc.right;//�׼� �޴� ��Ʈ�� �̰� ��������..
	POINT goToTile;
	goToTile.x = (findtile->getTile()[findIndex].rc.left ) / TILESIZE ;
	goToTile.y = (findtile->getTile()[findIndex].rc.top ) / TILESIZE;

	//�ش����� �ѹ� �� Ŭ���ϸ�
	if (findIndex == (int)(_player->getUnits()[vNum]->getBattleState().tilePt.x + _player->getUnits()[vNum]->getBattleState().tilePt.y * TILEX) && _player->getUnits()[vNum]->getUnitSequnce() == UNITSEQUENCE_TURNON)
	{
		callToMenu();//�ൿ���� ��ư ���.
	}
	//�� ���� Ŭ�� ��
	if (findtile->getTeamInfo()[findIndex] == TEAM_ENEMY  && _player->getUnits()[vNum]->getUnitSequnce() == UNITSEQUENCE_TURNON)
	{
		mouse_ClickToAttack();
	}
	else if (_player->getUnits()[vNum]->isMovableArea(findIndex) && _player->getUnits()[vNum]->getBattleState().moved)//������ �ƴϰ� �� ������ 
	{

		backToPT.x = _player->getUnits()[vNum]->getBattleState().pt.x;
		backToPT.y = _player->getUnits()[vNum]->getBattleState().pt.y;
		backToDir = _player->getUnits()[vNum]->getBattleState().dir;
		_player->getUnits()[vNum]->moveTo(goToTile);
		_player->getUnits()[vNum]->setUnitSequnce(UNITSEQUENCE_MOVE);
		isCommand = true;
	}
	else dataClean();
}
void infoCursor::mouse_ClickToAttack(void)
{
	int setindex = (int)(_ptMouse.x / TILESIZE) + (int)(_ptMouse.y / TILESIZE)  * TILEX;
	int findIndex = setindex + (MAINCAMERA->getCameraX() / TILESIZE) + (MAINCAMERA->getCameraY() / TILESIZE) * TILEX;

	
	for (int i = 0; i < _enemy->getUnits().size(); i++)
	{
		if (findIndex == (int)(_enemy->getUnits()[i]->getBattleState().tilePt.x + _enemy->getUnits()[i]->getBattleState().tilePt.y * TILEX) && _enemy->getUnits()[i]->isAttackTarget(findIndex))
		{
				_player->getUnits()[vNum]->attack(_enemy->getUnits()[i]);
		}
	}

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

	switch (clickUnit)
	{
	case PLAYER:
		_player->getUnits()[vNum]->clearMoveArea();
		break;
	case FRIEND:
		_friend->getUnits()[vNum]->clearMoveArea();
		break;
	case ENEMY:
		_enemy->getUnits()[vNum]->clearMoveArea();
		break;
	}
	clickUnit = NONE;
	isCommand = false;
	drawMoveLine = { 0,0,0,0 };
}
void infoCursor::callToMenu(void)
{
	_player->getUnits()[vNum]->clearMoveArea();
}

void infoCursor::tileLineDraw(void)
{
	SelectObject(getMemDC(), (HPEN)linePen);
	MoveToEx(getMemDC(), drawLine.left, drawLine.top, NULL); //���� Ÿ�� �׵θ��׸�
	LineTo(getMemDC(), drawLine.right, drawLine.top);		 //���� Ÿ�� �׵θ��׸�
	LineTo(getMemDC(), drawLine.right, drawLine.bottom);	 //���� Ÿ�� �׵θ��׸�
	LineTo(getMemDC(), drawLine.left, drawLine.bottom);		 //���� Ÿ�� �׵θ��׸�
	LineTo(getMemDC(), drawLine.left, drawLine.top);		 //���� Ÿ�� �׵θ��׸�

		MoveToEx(getMemDC(), drawMoveLine.left, drawMoveLine.top, NULL); //�̵� Ÿ��
		LineTo(getMemDC(), drawMoveLine.right, drawMoveLine.top);		 //�̵� Ÿ�� �׵θ��׸�
		LineTo(getMemDC(), drawMoveLine.right, drawMoveLine.bottom);	 //�̵� Ÿ�� �׵θ��׸�
		LineTo(getMemDC(), drawMoveLine.left, drawMoveLine.bottom);		 //�̵� Ÿ�� �׵θ��׸�
		LineTo(getMemDC(), drawMoveLine.left, drawMoveLine.top);		 //�̵� Ÿ�� �׵θ��׸�
		SelectObject(getMemDC(), (HPEN)oPen);
}

void infoCursor::infoDraw(void)
{
	if (isUnit) //������ �������� ǥ���� �͵�
	{
		Rectangle(getMemDC(), unitImgRect.left, unitImgRect.top, unitImgRect.right, unitImgRect.bottom); // ����׿� ��Ʈ���
		unitImg->render(getMemDC(), unitImgRect.left, unitImgRect.top);
		TextOut(getMemDC(), unitImgRect.left, unitImgRect.bottom + 48, unitName, _tcslen(unitName));
		TextOut(getMemDC(), unitImgRect.left, unitImgRect.bottom + 24, factionName, _tcslen(factionName));
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

void infoCursor::mouse_ActionCancel(void)//�̵���� ��ҿ�
{
	_player->getUnits()[vNum]->moveBack(backToPT);
	_player->getUnits()[vNum]->setUnitSequnce(UNITSEQUENCE_TURNON);
	_player->getUnits()[vNum]->setMoved(true);
	_player->getUnits()[vNum]->setDir(backToDir);
	isCommand = false;
	dataClean();
}

void infoCursor::buttonSetup(void)
{
	for (int i = 0; i < BTN_MAX; i++)
	{
		switch (i)
		{
		case BTN_ATTACK:
			actionBtn[i] = new button;
			actionBtn[i]->init(L"SELECT-���ù�ư", L"����", 50, 150, { 0,0 }, { 0,1 }, cb_attack, this);
			break;
		case BTN_SKILL:
			actionBtn[i] = new button;
			actionBtn[i]->init(L"SELECT-���ù�ư", L"����", 50, 200, { 0,0 }, { 0,1 }, cb_item, this);
			break;
		case BTN_ITEM:
			actionBtn[i] = new button;
			actionBtn[i]->init(L"SELECT-���ù�ư", L"���", 50, 250, { 0,0 }, { 0,1 }, cb_wait, this);
			break;
		case BTN_WAIT:
			actionBtn[i] = new button;
			actionBtn[i]->init(L"SELECT-���ù�ư", L"���", 50, 300, { 0,0 }, { 0,1 }, cb_cancel, this);
			break;
		}
	}
}

void infoCursor::cb_attack(void* obj)
{
	infoCursor* cursor = (infoCursor*)obj;
	cursor->cmd_atk();
}
void infoCursor::cb_item(void* obj)
{
	infoCursor* cursor = (infoCursor*)obj;
	cursor->cmd_item();
}
void infoCursor::cb_wait(void* obj)
{
	infoCursor* cursor = (infoCursor*)obj;
	cursor->cmd_wait();
}
void infoCursor::cb_cancel(void* obj)
{
	infoCursor* cursor = (infoCursor*)obj;
	cursor->cmd_cancel();
}

void infoCursor::cmd_atk(void)
{
	popUpMenu = false;
}
void infoCursor::cmd_item(void)	 
{
	//������ ����� �ҷ��ͼ� ����.
}
void infoCursor::cmd_wait(void)	 
{
	_player->getUnits()[vNum]->setUnitSequnce(UNITSEQUENCE_TURNOFF);
	dataClean();
}
void infoCursor::cmd_cancel(void)
{

}

void infoCursor::infoSetup(void)
{
	isShow = false;
	isUnit = false;
	targetAttack = false;
	isCommand = false;
	indexTile = 0;
	popUpMenu = false;
	for (int i = 0; i < BTN_MAX; i++)
	{
		actionBtn[i] = NULL;
	}

	rc = { WINSIZEX - SIDEWINSIZE,0,WINSIZEX,WINSIZEY };//�������̽� ���� ��Ʈ
	tileImgRect = RectMakeCenter(rc.left + SIDEWINSIZE / 2, 80, FROFILEIMAGE, FROFILEIMAGE);
	unitImgRect = RectMakeCenter(rc.left + SIDEWINSIZE / 2, WINSIZEY / 2, FROFILEIMAGE, FROFILEIMAGE);
	for (int i = 0; i < 4; i++)
	{
		element[i] = RectMakeCenter(rc.left + TILESIZE / 2 + ((TILESIZE / 2 + (TILESIZE / 2 * 0.25)) * i), tileImgRect.bottom + TILESIZE / 2, TILESIZE / 2, TILESIZE / 2);
	}
	clickUnit = NONE;
	vNum = 0;
	factionName = L"��������";
	unitName = L"�����̸�����";
	tilename = L"Ÿ���̸�����";
	prop = L"�����Ӽ�����";
	showExp = L"����ġ";
	fire = false;
	wind = false;
	earth = false;
	water = false;
	backToDir = DIRECTION_DN;

	backToPT = { 0,0 };
	unitImg = IMAGEMANAGER->findImage(L"����");
	tileImg = IMAGEMANAGER->findImage(L"����");
	drawLine = { 0,0,0,0 };
	drawMoveLine = { 0,0,0,0 };
	oPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	linePen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	
	buttonSetup();
	cmdBox = RectMakeCenter(0, 0, 110, 250);

}