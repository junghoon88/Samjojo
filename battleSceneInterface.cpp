#include "stdafx.h"
#include "battleSceneInterface.h"
#include "Player.h"
#include "Enemy.h"
#include "Friend.h"
#include "gameMap.h"
//������ ������ �÷��̾� �������̽� ���� Ŭ������ ���̴ϴ�.

battleSceneInterface::battleSceneInterface()
	:_player(NULL), _friend(NULL), _enemy(NULL), findtile(NULL)
{
	for (int i = 0; i < BTN_MAX; i++)
	{
		actionBtn[i] = NULL;
	}
}
battleSceneInterface::~battleSceneInterface(){}

HRESULT battleSceneInterface::init(void) 
{
	infoSetup();

	return S_OK;
}

void battleSceneInterface::release(void)
{
}

void battleSceneInterface::update() 
{
	if (!isCommand && !popUpMenu) //��� ����
	{
		mouse_Scanning();//���� Ÿ�� ����
		if (!isShow)moveCamera();
		else if (isShow)
		{
			//hpBar->update();
			//mpBar->update();
		}
		if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
		{
			if(clickUnit == PLAYER && !_player->getUnits()[vNum]->getBattleState().moveable //���� Ŭ���� ������ �̵��ѵڿ� ���� �ȳ������� ��Ŭ���� �̵� ���
				&& _player->getUnits()[vNum]->getUnitSequnce() != UNITSEQUENCE_TURNOFF) mouse_ActionCancel();
			else dataClean();  //������ �ݱ�
		}
		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
		{
	
			if (isShow && clickUnit == PLAYER && _player->getUnits()[vNum]->getUnitSequnce() == UNITSEQUENCE_TURNON) mouse_ClickToAction(); // 
			else if (!isShow) mouse_ClickToTile();//���� Ŭ�� �� 
		}
	}
	else if (isCommand)//��� ���� �����̸� �ش� ������ ���������� ���ۺҰ�
	{
		if (UNITSEQUENCE_MOVE != _player->getUnits()[vNum]->getUnitSequnce()) 
		{
			//�̵����.

			//chaseCamera(_player->getUnits()[vNum]->getRect());
			_player->getUnits()[vNum]->setMoveable(false);
			callToMenu(_player->getUnits()[vNum]->getRect().left, _player->getUnits()[vNum]->getRect().top);//�޴�ȭ���� ȣ��
			isCommand = false;
		}
	}
	else if (popUpMenu) //Ŀ�ǵ� ����� Ȱ��ȭ ������
	{
		for (int i = 0; i < BTN_MAX; i++) // Ŀ�ǵ� ��ư ������Ʈ
		{
			if(actionBtn[i]) actionBtn[i]->update();
		}
	}
}

void battleSceneInterface::render(void) 
{
	tileLineDraw(); //Ŀ�� Ÿ�� �׵θ� �׸�
	//Rectangle(getMemDC(), rc.left, rc.top, rc.right, rc.bottom);
	IMAGEMANAGER->findImage(L"��ũ��")->render(getMemDC(), rc.left, rc.top);
	if (isShow)
	{
		infoDraw();// ���� ǥ��
	}
	if (popUpMenu)
	{
		cmdDraw();
	}
}

void battleSceneInterface::mouse_Scanning(void)
{
	indexTile = (int)(_ptMouse.x / TILESIZE) + (int)(_ptMouse.y / TILESIZE)  * TILEX;
	if (!isShow)
	{
		drawLine = { findtile->getTile()[indexTile].rc.left,findtile->getTile()[indexTile].rc.top,findtile->getTile()[indexTile].rc.right,findtile->getTile()[indexTile].rc.bottom };
	}
	else
	{
		int findIndex = indexTile + (MAINCAMERA->getCameraX() / TILESIZE) + (MAINCAMERA->getCameraY() / TILESIZE) * TILEX;
		if(_player->getUnits()[vNum]->isMovableArea(findIndex))drawMoveLine = { findtile->getTile()[indexTile].rc.left,findtile->getTile()[indexTile].rc.top,findtile->getTile()[indexTile].rc.right,findtile->getTile()[indexTile].rc.bottom };
		else drawMoveLine = { WINSIZEX,WINSIZEY,WINSIZEX,WINSIZEY };
		drawLine = _player->getUnits()[vNum]->getRect();
	}
}

void battleSceneInterface::mouse_ClickToTile(void)
{
	int findIndex = indexTile + (MAINCAMERA->getCameraX() / TILESIZE) + (MAINCAMERA->getCameraY() / TILESIZE) * TILEX;

	if (findtile->getTeamInfo()[findIndex] == TEAM_PLAYER)
	{
		for (int i = 0; i < _player->getUnits().size(); i++)
		{
			if (findIndex == (int)(_player->getUnits()[i]->getBattleState().tilePt.x + _player->getUnits()[i]->getBattleState().tilePt.y * TILEX))
			{
				setUnit(TEAM_PLAYER, i);
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
				setUnit(TEAM_FRIEND, i);
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
				setUnit(TEAM_ENEMY, i);
				break;
			}
		}
	}

	tileNum = findtile->getTile()[findIndex].terrain + 1;//�ش��ȣ�� Ű������ ã���� �ȴ�. �̹�����!	
	_stprintf(tileKey, L"tile (%02d)", tileNum);
	tileImg = IMAGEMANAGER->findImage(tileKey);
	switch (findtile->getTile()[findIndex].terrain)
	{
	case TERRAIN_RIVER:
		_tcscpy(tilename, L"��");
		_tcscpy(prop, L"�̵� �Ұ�");
		fire = false;
		water = false;
		wind = false;
		earth = false;
		break;
	case TERRAIN_BRIDGE:
		_tcscpy(tilename, L"�ٸ�");
		_tcscpy(prop, L"");
		fire = true;
		water = true;
		wind = true;
		earth = false;
		break;
	case TERRAIN_WATER:
		_tcscpy(tilename, L"����");
		_tcscpy(prop, L"�̵� �Ұ�");
		fire = true;
		water = true;
		wind = true;
		earth = false;
		break;

	case TERRAIN_DITCH:
		_tcscpy(tilename, L"����");
		_tcscpy(prop, L"�̵� �Ұ�");
		fire = false;
		water = false;
		wind = false;
		earth = false;
		break;

	case TERRAIN_VILLAGE:
		_tcscpy(tilename, L"����");
		_tcscpy(prop, L"ȸ�� ����");
		fire = true;
		water = false;
		wind = false;
		earth = false;
		break;

	case TERRAIN_PREMISES:
		_tcscpy(tilename, L"����");
		_tcscpy(prop, L"");
		fire = true;
		water = false;
		wind = false;
		earth = false;
		break;

	case TERRAIN_ROCK:
		_tcscpy(tilename, L"�Ϻ�");
		_tcscpy(prop, L"�̵� �Ұ�");
		fire = false;
		water = false;
		wind = false;
		earth = false;
		break;

	case TERRAIN_SHIP:
		_tcscpy(tilename, L"��");
		_tcscpy(prop, L"�̵� �Ұ�");
		fire = false;
		water = false;
		wind = false;
		earth = false;
		break;

	case TERRAIN_BROW:
		_tcscpy(tilename, L"����");
		_tcscpy(prop, L"�̵� �Ұ�");
		fire = false;
		water = false;
		wind = false;
		earth = false;
		break;

	case TERRAIN_BARRACK:
		_tcscpy(tilename, L"����");
		_tcscpy(prop, L"ȸ�� ����");
		fire = true;
		water = false;
		wind = false;
		earth = false;
		break;

	case TERRAIN_WAREHOUSE:
		_tcscpy(tilename, L"���޼�");
		_tcscpy(prop, L"ȸ�� ����");
		fire = true;
		water = false;
		wind = false;
		earth = false;
		break;

	case TERRAIN_FIRE:
		_tcscpy(tilename, L"��");
		_tcscpy(prop, L"�̵� �Ұ�");
		fire = false;
		water = false;
		wind = false;
		earth = false;
		break;

	case TERRAIN_MOUNTAIN:
		_tcscpy(tilename, L"��");
		_tcscpy(prop, L"");
		fire = false;
		water = false;
		wind = true;
		earth = true;
		break;

	case TERRAIN_SNOW:
		_tcscpy(tilename, L"����");
		_tcscpy(prop, L"");
		fire = false;
		water = false;
		wind = false;
		earth = false;
		break;

	case TERRAIN_CASTLE:
		_tcscpy(tilename, L"��");
		_tcscpy(prop, L"ȸ�� ����");
		fire = true;
		water = false;
		wind = false;
		earth = false;
		break;

	case TERRAIN_INCASTLE:
		_tcscpy(tilename, L"����");
		_tcscpy(prop, L"");
		fire = true;
		water = false;
		wind = false;
		earth = false;
		break;

	case TERRAIN_CASTLEGATE:
		_tcscpy(tilename, L"����");
		_tcscpy(prop, L"�̵� �Ұ�");
		fire = false;
		water = false;
		wind = false;
		earth = false;
		break;

	case TERRAIN_RAMPART:
		_tcscpy(tilename, L"����");
		_tcscpy(prop, L"�̵� �Ұ�");
		fire = false;
		water = false;
		wind = false;
		earth = false;
		break;

	case TERRAIN_FOREST:
		_tcscpy(tilename, L"��");
		_tcscpy(prop, L"");
		fire = true;
		water = false;
		wind = false;
		earth = false;
		break;

	case TERRAIN_SWAMP:
		_tcscpy(tilename, L"����");
		_tcscpy(prop, L"");
		fire = false;
		water = true;
		wind = true;
		earth = false;
		break;

	case TERRAIN_FORD:
		_tcscpy(tilename, L"����");
		_tcscpy(prop, L"");
		fire = false;
		water = true;
		wind = true;
		earth = false;
		break;

	case TERRAIN_POND:
		_tcscpy(tilename, L"����");
		_tcscpy(prop, L"�̵� �Ұ�");
		fire = false;
		water = false;
		wind = false;
		earth = false;
		break;

	case TERRAIN_STRONGHOLD:
		_tcscpy(tilename, L"���");
		_tcscpy(prop, L"ȸ�� ����");
		fire = true;
		water = false;
		wind = false;
		earth = false;
		break;

	case TERAAIN_FENCE:
		_tcscpy(tilename, L"��Ÿ��");
		_tcscpy(prop, L"�̵� �Ұ�");
		fire = false;
		water = false;
		wind = false;
		earth = false;
		break;

	case TERRAIN_ALTER:
		_tcscpy(tilename, L"����");
		_tcscpy(prop, L"");
		fire = false;
		water = false;
		wind = false;
		earth = false;
		break;

	case TERRAIN_UNDERGROUND:
		_tcscpy(tilename, L"����");
		_tcscpy(prop, L"�̵� �Ұ�");
		fire = false;
		water = false;
		wind = false;
		earth = false;
		break;

	case TERRAIN_GRASSLAND:
		_tcscpy(tilename, L"�ʿ�");
		_tcscpy(prop, L"");
		fire = true;
		water = false;
		wind = true;
		earth = false;
		break;

	case TERRAIN_FLAT:
		_tcscpy(tilename, L"����");
		_tcscpy(prop, L"");
		fire = true;
		water = false;
		wind = true;
		earth = false;
		break;

	case TERRAIN_BADLANDS:
		_tcscpy(tilename, L"Ȳ����");
		_tcscpy(prop, L"");
		fire = false;
		water = false;
		wind = true;
		earth = true;
		break;

	case TERRAIN_GATEWAY:
		_tcscpy(tilename, L"����");
		_tcscpy(prop, L"ȸ�� ����");
		fire = true;
		water = false;
		wind = false;
		earth = false;
		break;

	case TERRAIN_NONE:
		_tcscpy(tilename, L"������������");
		_tcscpy(prop, L"");
		fire = false;
		water = false;
		wind = false;
		earth = false;
		break;

	}
	isShow = true;
}

void battleSceneInterface::setUnit(TEAM faction, int vectorNum)
{
	if (faction == TEAM_PLAYER)
	{
		vNum = vectorNum;
		isUnit = true;
		clickUnit = PLAYER;
		exp = _player->getUnits()[vectorNum]->getStatus().exp;
		lv = _player->getUnits()[vectorNum]->getStatus().level;
		atk = _player->getUnits()[vectorNum]->getStatus().Atk;
		def = _player->getUnits()[vectorNum]->getStatus().Dep;
		curHp = _player->getUnits()[vectorNum]->getStatus().HP;
		maxHp = _player->getUnits()[vectorNum]->getStatus().HPMax;
		curMp = _player->getUnits()[vectorNum]->getStatus().MP;
		maxMp = _player->getUnits()[vectorNum]->getStatus().MPMax;
		movePoint = _player->getUnits()[vectorNum]->getStatus().movePoint;
		hpBar->setGauge(curHp, maxHp);
		mpBar->setGauge(curMp, maxMp);
		_tcscpy(factionName, L"�÷��̾�");
		_tcscpy(unitName, _player->getUnits()[vectorNum]->getStatus().name);
		_stprintf(txtAtk, L"���ݷ� %d", atk);
		_stprintf(txtDef, L"���� %d", def);
		_stprintf(txtMove, L"�̵��� (%02d)", movePoint);
		unitImg = _player->getUnits()[vectorNum]->getStatus().imgFace;
		_player->getUnits()[vectorNum]->findMoveArea();
	}
	else if (faction == TEAM_FRIEND)
	{
		vNum = vectorNum;
		isUnit = true;
		clickUnit = FRIEND;
		exp = _friend->getUnits()[vectorNum]->getStatus().exp;
		lv = _friend->getUnits()[vectorNum]->getStatus().level;
		atk = _friend->getUnits()[vectorNum]->getStatus().Atk;
		def = _friend->getUnits()[vectorNum]->getStatus().Dep;
		curHp = _friend->getUnits()[vectorNum]->getStatus().HP;
		maxHp = _friend->getUnits()[vectorNum]->getStatus().HPMax;
		curMp = _friend->getUnits()[vectorNum]->getStatus().MP;
		maxMp = _friend->getUnits()[vectorNum]->getStatus().MPMax;
		movePoint;
		_tcscpy(factionName, L"�Ʊ�");
		_tcscpy(unitName, _friend->getUnits()[vectorNum]->getStatus().name);
		_stprintf(txtAtk, L"���ݷ� (%02d)", atk);
		_stprintf(txtDef, L"���� (%02d)", def);
		_stprintf(txtMove, L"�̵��� (%02d)", movePoint);
		unitImg = _friend->getUnits()[vectorNum]->getStatus().imgFace;
		_friend->getUnits()[vectorNum]->findMoveArea();
	}
	else if (faction == TEAM_ENEMY)
	{
		vNum = vectorNum;
		isUnit = true;
		clickUnit = ENEMY;
		exp = _enemy->getUnits()[vectorNum]->getStatus().exp;
		lv = _enemy->getUnits()[vectorNum]->getStatus().level;
		atk = _enemy->getUnits()[vectorNum]->getStatus().Atk;
		def = _enemy->getUnits()[vectorNum]->getStatus().Dep;
		curHp = _enemy->getUnits()[vectorNum]->getStatus().HP;
		maxHp = _enemy->getUnits()[vectorNum]->getStatus().HPMax;
		curMp = _enemy->getUnits()[vectorNum]->getStatus().MP;
		maxMp = _enemy->getUnits()[vectorNum]->getStatus().MPMax;
		movePoint;
		_tcscpy(factionName, L"����");
		_tcscpy(unitName, _enemy->getUnits()[vectorNum]->getStatus().name);
		_stprintf(txtAtk, L"���ݷ� (%02d)", atk);
		_stprintf(txtDef, L"���� (%02d)", def);
		_stprintf(txtMove, L"�̵��� (%02d)", movePoint);
		unitImg = _enemy->getUnits()[vectorNum]->getStatus().imgFace;
		_enemy->getUnits()[vectorNum]->findMoveArea();
	}
}
void battleSceneInterface::mouse_ClickToAction(void)//�ൿ������ �÷��̾� ������ ���������϶� Ŭ���ϸ� ������ �׼ǵ�
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
		callToMenu(_player->getUnits()[vNum]->getRect().left, _player->getUnits()[vNum]->getRect().top);//�ൿ���� ��ư ���.
	}
	//�� ���� Ŭ�� ��
	if (findtile->getTeamInfo()[findIndex] == TEAM_ENEMY)
	{
		mouse_ClickToAttack();
	}
	else if (_player->getUnits()[vNum]->isMovableArea(findIndex) && _player->getUnits()[vNum]->getBattleState().moveable)//������ �ƴϰ� �� ������ 
	{

		backToPT.x = _player->getUnits()[vNum]->getBattleState().pt.x;
		backToPT.y = _player->getUnits()[vNum]->getBattleState().pt.y;
		backToDir = _player->getUnits()[vNum]->getBattleState().dir;
		_player->getUnits()[vNum]->moveTo(goToTile);
		_player->getUnits()[vNum]->setUnitSequnce(UNITSEQUENCE_MOVE);
		isCommand = true;
	}
	else if(_player->getUnits()[vNum]->getBattleState().moveable) dataClean();
}

void battleSceneInterface::mouse_ClickToAttack(void)
{
	int setindex = (int)(_ptMouse.x / TILESIZE) + (int)(_ptMouse.y / TILESIZE)  * TILEX;
	int findIndex = setindex + (MAINCAMERA->getCameraX() / TILESIZE) + (MAINCAMERA->getCameraY() / TILESIZE) * TILEX;

//	_player->getUnits()[vNum]->attack(_enemy->getUnits()[1]);

	if (_player->getUnits()[vNum]->isAttackTarget(findIndex) == FALSE)
		return;

	for (int i = 0; i < _enemy->getUnits().size(); i++)
	{
		if (findIndex == (int)(_enemy->getUnits()[i]->getBattleState().tilePt.x + _enemy->getUnits()[i]->getBattleState().tilePt.y * TILEX))//
		{
			POINT tilePtEnemy = { _enemy->getUnits()[i]->getBattleState().tilePt.x, _enemy->getUnits()[i]->getBattleState().tilePt.y };
			_player->getUnits()[vNum]->setOpponent(_enemy->getUnits()[i]);
			_player->getUnits()[vNum]->setOpponentTilePt(tilePtEnemy);

			int dirX = _enemy->getUnits()[i]->getBattleState().tilePt.x - _player->getUnits()[vNum]->getBattleState().tilePt.x;
			int dirY = _enemy->getUnits()[i]->getBattleState().tilePt.y - _player->getUnits()[vNum]->getBattleState().tilePt.y;

			if (abs(dirX) >= abs(dirY))
			{
				if (dirX > 0)	_player->getUnits()[vNum]->setDir(DIRECTION_RG);
				else			_player->getUnits()[vNum]->setDir(DIRECTION_LF);
			}
			else
			{
				if (dirY > 0)	_player->getUnits()[vNum]->setDir(DIRECTION_UP);
				else			_player->getUnits()[vNum]->setDir(DIRECTION_DN);
			}



			_player->getUnits()[vNum]->setUnitSequnce(UNITSEQUENCE_ATTACK);
			dataClean();
			break;
		}
	}

}

void battleSceneInterface::mouse_ActionCancel(void)//�̵���� ��ҿ�
{
	_player->getUnits()[vNum]->moveBack(backToPT);
	_player->getUnits()[vNum]->setDir(backToDir);
	_player->getUnits()[vNum]->setUnitSequnce(UNITSEQUENCE_TURNON);

	//chaseCamera(_player->getUnits()[vNum]->getRect());

	_player->getUnits()[vNum]->setMoveable(true);

	isCommand = false;
}

void battleSceneInterface::moveCamera(void)
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

void battleSceneInterface::chaseCamera(POINT tilePt)
{
	int index = tilePt.x + tilePt.y * TILEX;
	
	if (findtile->getTile()[index].rc.left - WINSIZEX / 2 > 0
		&& findtile->getTile()[index].rc.left - WINSIZEX / 2 < findtile->getTileSizeX() * TILESIZE - TILESIZE * 20)	MAINCAMERA->setCameraX(findtile->getTile()[index].rc.left - WINSIZEX / 2);
	else if (findtile->getTile()[index].rc.left - WINSIZEX / 2 < WINSIZEX) MAINCAMERA->setCameraX(0);
	else if (findtile->getTile()[index].rc.left - WINSIZEX / 2 < findtile->getTileSizeX() * TILESIZE - TILESIZE * 20)
	if (findtile->getTile()[index].rc.top - WINSIZEY / 2 > 0 
		&& findtile->getTile()[index].rc.top - WINSIZEY / 2 < findtile->getTileSizeY() * TILESIZE - TILESIZE * 20) 	MAINCAMERA->setCameraY(findtile->getTile()[index].rc.top - WINSIZEY / 2);


}

void battleSceneInterface::dataClean(void)//���콺 ��Ŭ�� �� ���� �������̽��� ������ �ʱ�ȭ ���ִ� ������ �� ��.
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
void battleSceneInterface::callToMenu(int x,int y)
{
	popUpMenu = true;
	if (y <= WINSIZEY / 2)
	{
		if (x < WINSIZEX / 2)
		{
			cmdBox = RectMake(x + TILESIZE, y, 110, 250);//�˾��޴��� ������ �Ʒ��� ��������
		}
		else if (x >= WINSIZEX)
		{
			cmdBox = RectMake(x - TILESIZE, y, 110, 250);;//���� �Ʒ�
		}
	}
	if (y > WINSIZEY / 2)
	{
		if (x < WINSIZEX / 2)
		{
		cmdBox = RectMake(x + TILESIZE, y - 250, 110, 250);//�˾��޴��� ������ ��
		}
		else if (x >= WINSIZEX)
		{
			cmdBox = RectMake(x - TILESIZE, y - 250, 110, 250);//���� ��
		}
	}
	for (int i = 0; i < BTN_MAX; i++)
	{
		actionBtn[i]->setRect(cmdBox.left + 5, cmdBox.top + i * 35);
	}
}

void battleSceneInterface::tileLineDraw(void)
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
void battleSceneInterface::cmdDraw(void)
{
	for (int i = 0; i < BTN_MAX; i++)
	{
		if (actionBtn[i] == NULL) continue;
		actionBtn[i]->render();
	}
}
void battleSceneInterface::infoDraw(void)
{
	
	if (isUnit) //������ �������� ǥ���� �͵�
	{
		Rectangle(getMemDC(), unitImgRect.left, unitImgRect.top, unitImgRect.right, unitImgRect.bottom); // ����׿� ��Ʈ���
		unitImg->render(getMemDC(), unitImgRect.left, unitImgRect.top);
		TextOut(getMemDC(), unitImgRect.left, unitImgRect.bottom + 24, factionName, _tcslen(factionName));
		TextOut(getMemDC(), unitImgRect.left, unitImgRect.bottom + 48, unitName, _tcslen(unitName));
		TextOut(getMemDC(), unitImgRect.left, unitImgRect.bottom + 72, txtAtk, _tcslen(factionName));
		TextOut(getMemDC(), unitImgRect.left, unitImgRect.bottom + 96, txtDef, _tcslen(factionName));
		TextOut(getMemDC(), unitImgRect.left, unitImgRect.bottom + 120, txtMove, _tcslen(factionName));
		hpBar->render();
		mpBar->render();
	}
	Rectangle(getMemDC(), tileImgRect.left, tileImgRect.top, tileImgRect.right, tileImgRect.bottom); // ����׿� ��Ʈ���
	tileImg->render(getMemDC(),tileImgRect.left, tileImgRect.top);
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



void battleSceneInterface::buttonSetup(void)
{
	for (int i = 0; i < BTN_MAX; i++)
	{
		switch (i)
		{
		case BTN_ATTACK:
			actionBtn[i] = new button;
			actionBtn[i]->init(L"SELECT-���ù�ư", L"�� ��", cmdBox.left + 5, cmdBox.top + 5, { 0,0 }, { 0,1 }, cb_attack, this);
			break;
		case BTN_ITEM:
			actionBtn[i] = new button;
			actionBtn[i]->init(L"SELECT-���ù�ư", L"�� ��", cmdBox.left + 5, cmdBox.top + 5 + 35, { 0,0 }, { 0,1 }, cb_item, this);
			break;
		case BTN_WAIT:
			actionBtn[i] = new button;
			actionBtn[i]->init(L"SELECT-���ù�ư", L"�� ��", cmdBox.left + 5, cmdBox.top + 5 + 35 + 35, { 0,0 }, { 0,1 }, cb_wait, this);
			break;
		case BTN_CANCEL:
			actionBtn[i] = new button;
			actionBtn[i]->init(L"SELECT-���ù�ư", L"�� ��", cmdBox.left + 5, cmdBox.top + 5 + 35 + 35 + 35, { 0,0 }, { 0,1 }, cb_cancel, this);
			break;

		}
	}
	for (int i = 0; i < BTN_MAX; i++)
	{
	}
}

void battleSceneInterface::cb_attack(void* obj)
{
	battleSceneInterface* cursor = (battleSceneInterface*)obj;
	cursor->cmd_atk();
}
void battleSceneInterface::cb_item(void* obj)
{
	battleSceneInterface* cursor = (battleSceneInterface*)obj;
	cursor->cmd_item();
}
void battleSceneInterface::cb_wait(void* obj)
{
	battleSceneInterface* cursor = (battleSceneInterface*)obj;
	cursor->cmd_wait();
}
void battleSceneInterface::cb_cancel(void* obj)
{
	battleSceneInterface* cursor = (battleSceneInterface*)obj;
	cursor->cmd_cancel();
}

void battleSceneInterface::cmd_atk(void)
{
	popUpMenu = false;
}
void battleSceneInterface::cmd_item(void)	 
{
	//������ ����� �ҷ��ͼ� ����.
}
void battleSceneInterface::cmd_wait(void)	 
{
	_player->getUnits()[vNum]->setUnitSequnce(UNITSEQUENCE_TURNOFF);
	dataClean();
	popUpMenu = false;
}
void battleSceneInterface::cmd_cancel(void)
{
	popUpMenu = false;
	mouse_ActionCancel();
}

void battleSceneInterface::infoSetup(void)
{
	isShow = false;
	isUnit = false;
	targetAttack = false;
	isCommand = false;
	indexTile = 0;
	popUpMenu = false;


	rc = { WINSIZEX - SIDEWINSIZE,0,WINSIZEX,WINSIZEY };//�������̽� ���� ��Ʈ
	tileImgRect = RectMakeCenter(rc.left + SIDEWINSIZE / 2, 80, FROFILEIMAGE, FROFILEIMAGE);
	unitImgRect = RectMakeCenter(rc.left + SIDEWINSIZE / 2, tileImgRect.bottom + TILESIZE*4, FROFILEIMAGE, FROFILEIMAGE);
	for (int i = 0; i < 4; i++)
	{
		element[i] = RectMakeCenter(rc.left + TILESIZE / 2 + ((TILESIZE / 2 + (TILESIZE / 2 * 0.25)) * i), tileImgRect.bottom + TILESIZE / 2, TILESIZE / 2, TILESIZE / 2);
	}
	clickUnit = NONE;
	vNum = 0;
	_tcscpy(factionName, L"��������");
	_stprintf(unitName, L"�����̸�����");
	_tcscpy(tilename, L"Ÿ���̸�����");
	_tcscpy(prop, L"�����Ӽ�����");
	_tcscpy(txtExp, L"Exp");
	_tcscpy(txtAtk, L"���ݷ�");
	_tcscpy(txtDef, L"����");
	_tcscpy(txtMove, L"�̵���");

	//bonus = 0;//���� ���� ���� ������ ����ǥ��
	exp = 0;
	lv = 0;
	atk = 0;
	def = 0;
	movePoint = 0;
	
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
	cmdBox = RectMakeCenter(100, 100, 110, 245);
	buttonSetup();


	hpBar = new progressBar;
	mpBar = new progressBar;
	hpBar->init(L"ü�¹�2", L"���2", unitImgRect.left, unitImgRect.top + FROFILEIMAGE + 5 + 75, 120, 9, L"ready");
	mpBar->init(L"������2", L"���2", unitImgRect.left, unitImgRect.top + FROFILEIMAGE + 5 + 75 + 9 + 10, 120, 9, L"ready");
}