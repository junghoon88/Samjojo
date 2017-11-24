#include "stdafx.h"
#include "sceneMaptool.h"


sceneMaptool::sceneMaptool()
{
}


sceneMaptool::~sceneMaptool()
{

}

HRESULT sceneMaptool::init(void)
{
	setup();

	_selectSampleIndex = 0;
	
	_countX = _countY = 0;

	for (int i = 0; i < 6; i++)
	{
		_tileSizeX[i] = _tileSizeY[i] = 20 + i * 4;
	}

	_selectSizeX = _selectSizeY = 5;

	_alphaValue = 128;

	_mapView = false;
	_viewTERRAIN = false;
	_isload = false;

	_editBox = new editbox;
	_editBox->init();
	_editBox->setRect(RectMake(1050, 100, 100, 30));
	_editBox->setOnlyNum(TRUE);

	_alphaValueBox = new editbox;
	_alphaValueBox->init();
	_alphaValueBox->setRect(RectMake(1050, 180, 100, 30));
	_alphaValueBox->setOnlyNum(TRUE);

	_alphaValueBox->setStrNum(_alphaValue / 255 * 100);

	_stprintf(_saveSize, L"0 x 0");
	_stprintf(_fileName, L"�����");

	return S_OK;
}

void sceneMaptool::release(void)
{

}

void sceneMaptool::update(void)	
{
	//���̸� ���ϱ� or �ҷ����� �� �̸� ����
	_editBox->update();
	if (_editBox->getStrNum() > 57)	_editBox->setStrNum(57);
	else if (_editBox->getStrNum() < 0) _editBox->setStrNum(0);

	for (int i = 0; i < CTRL_END; i++)
	{
		_ctrlButton[i]->update();
	}

	for (int i = 0; i < OBJECTSELECT_MAX; i++)
	{
		_objectSelect[i]->update();
	}

	if (KEYMANAGER->isOnceKeyDown(MK_LBUTTON) || KEYMANAGER->isStayKeyDown(MK_LBUTTON))	setMap();

	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_countX--;
		if (_countX < 0) _countX = 0;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_countX++;
		if (_countX + 20 > _tileSizeX[_selectSizeX]) _countX = _tileSizeX[_selectSizeX] - 20;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_countY--;
		if (_countY < 0) _countY = 0;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_countY++;
		if (_countY + 20 > _tileSizeY[_selectSizeY]) _countY = _tileSizeY[_selectSizeY] - 20;
	}


	if (PtInRect(&RectMake(0, 0, 20 * TILESIZE, 20 * TILESIZE), _ptMouse))
	{
		//�ʻ����� ����(X��)
		if (!KEYMANAGER->isStayKeyDown(VK_SHIFT))
		{
			if (KEYMANAGER->isOnceKeyDown('0'))
			{
				_selectSizeX = 0;
				if (_countX + 20 > _tileSizeX[_selectSizeX]) _countX = _tileSizeX[_selectSizeX] - 20;
			}
			else if (KEYMANAGER->isOnceKeyDown('1'))
			{
				_selectSizeX = 1;
				if (_countX + 20 > _tileSizeX[_selectSizeX]) _countX = _tileSizeX[_selectSizeX] - 20;
			}
			else if (KEYMANAGER->isOnceKeyDown('2'))
			{
				_selectSizeX = 2;
				if (_countX + 20 > _tileSizeX[_selectSizeX]) _countX = _tileSizeX[_selectSizeX] - 20;
			}
			else if (KEYMANAGER->isOnceKeyDown('3'))
			{
				_selectSizeX = 3;
				if (_countX + 20 > _tileSizeX[_selectSizeX]) _countX = _tileSizeX[_selectSizeX] - 20;
			}
			else if (KEYMANAGER->isOnceKeyDown('4'))
			{
				_selectSizeX = 4;
				if (_countX + 20 > _tileSizeX[_selectSizeX]) _countX = _tileSizeX[_selectSizeX] - 20;
			}
			else if (KEYMANAGER->isOnceKeyDown('5'))
			{
				_selectSizeX = 5;
				if (_countX + 20 > _tileSizeX[_selectSizeX]) _countX = _tileSizeX[_selectSizeX] - 20;
			}
		}

		//�ʻ����� ����(Y��)
		else
		{
			if (KEYMANAGER->isOnceKeyDown('0'))
			{
				_selectSizeY = 0;
				if (_countY + 20 > _tileSizeY[_selectSizeY]) _countY = _tileSizeY[_selectSizeY] - 20;
			}
			else if (KEYMANAGER->isOnceKeyDown('1'))
			{
				_selectSizeY = 1;
				if (_countY + 20 > _tileSizeY[_selectSizeY]) _countY = _tileSizeY[_selectSizeY] - 20;
			}
			else if (KEYMANAGER->isOnceKeyDown('2'))
			{
				_selectSizeY = 2;
				if (_countY + 20 > _tileSizeY[_selectSizeY]) _countY = _tileSizeY[_selectSizeY] - 20;
			}
			else if (KEYMANAGER->isOnceKeyDown('3'))
			{
				_selectSizeY = 3;
				if (_countY + 20 > _tileSizeY[_selectSizeY]) _countY = _tileSizeY[_selectSizeY] - 20;
			}
			else if (KEYMANAGER->isOnceKeyDown('4'))
			{
				_selectSizeY = 4;
				if (_countY + 20 > _tileSizeY[_selectSizeY]) _countY = _tileSizeY[_selectSizeY] - 20;
			}
			else if (KEYMANAGER->isOnceKeyDown('5'))
			{
				_selectSizeY = 5;
				if (_countY + 20 > _tileSizeY[_selectSizeY]) _countY = _tileSizeY[_selectSizeY] - 20;
			}
		}
	}

	//���� �� ���� on/off && �׸��� �°� _selectSize���߱�
	if (KEYMANAGER->isOnceKeyDown(VK_TAB))
	{
		if (_mapView)	_mapView = false;
		else			_mapView = true;
	}

	//TERRAIN ���� on/off
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		if (_viewTERRAIN)	_viewTERRAIN = false;
		else				_viewTERRAIN = true;
	}

	//�����ʱ׸� X, Y ������Ʈ�ϱ�
	IMAGEMANAGER->findImage(_fileName)->setX(-(_countX * TILESIZE));
	IMAGEMANAGER->findImage(_fileName)->setY(-(_countY * TILESIZE));

	//���ĺ��� �� ����(���� �� ���⿡ ���)
	if (KEYMANAGER->isStayKeyDown('W'))	_alphaValue++;
	if (KEYMANAGER->isStayKeyDown('Q'))	_alphaValue--;
	if (_alphaValue > 255)	_alphaValue = 255;
	else if (_alphaValue < 80)	_alphaValue = 80;

	_alphaValueBox->update();
	if (_alphaValueBox->getStrNum() > 100) _alphaValueBox->setStrNum(100);
	else if (_alphaValueBox->getStrNum() < 0) _alphaValueBox->setStrNum(0);
	_alphaValue = (int)(((float)_alphaValueBox->getStrNum() / 100) * (float)255);
}

void sceneMaptool::render(void)	
{
	RectangleMake(getMemDC(), WINSIZEX - 3 * TILESIZE - 1, 0, TILESIZE * 3 + 1, TILESIZE * 10 + 1);

	//����Ÿ��
	if (_ctrSelect == CTRL_TERRAINDRAW)
	for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
	{
		if (_sampleTiles[i].img == NULL) continue;
		_sampleTiles[i].img->render(getMemDC(), _sampleTiles[i].rcTile.left, _sampleTiles[i].rcTile.top);
	}

	//������Ʈ Ÿ��
	if (_ctrSelect == CTRL_OBJDRAW)
	{
		if (_ctrObjectSelect == OBJECTSELECT_AILY)
				for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
				{
					if (_TroopObj[OBJECTSELECT_AILY][i].img == NULL || _TroopObj[OBJECTSELECT_AILY][i].obj == OBJECT_NONE) continue;
					_TroopObj[OBJECTSELECT_AILY][i].img->render(getMemDC(), _sampleTiles[i].rcTile.left, _sampleTiles[i].rcTile.top);
				}
		if (_ctrObjectSelect == OBJECTSELECT_ENEMY)
				for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
				{
					if (_TroopObj[OBJECTSELECT_ENEMY][i].img == NULL || _TroopObj[OBJECTSELECT_ENEMY][i].obj == OBJECT_NONE) continue;
					_TroopObj[OBJECTSELECT_ENEMY][i].img->render(getMemDC(), _sampleTiles[i].rcTile.left, _sampleTiles[i].rcTile.top);
				}
		if (_ctrObjectSelect == OBJECTSELECT_PLAYER)
				for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
				{
					if (_TroopObj[OBJECTSELECT_PLAYER][i].img == NULL || _TroopObj[OBJECTSELECT_PLAYER][i].obj == OBJECT_NONE) continue;
					_TroopObj[OBJECTSELECT_PLAYER][i].img->render(getMemDC(), _sampleTiles[i].rcTile.left, _sampleTiles[i].rcTile.top);
				}
	}

	//�����ڽ� �� ����
	TCHAR text[128];
	_stprintf(text, L"�� ��ȣ(0-57)");
	TextOut(getMemDC(), 1050, 80, text, wcslen(text));
	_editBox->render();

	_stprintf(text, L"�� ũ��");
	TextOut(getMemDC(), 1050, 0, text, wcslen(text));
	RectangleMake(getMemDC(), 1050, 20, 100, 30);

	if (_isload)
	{
		_stprintf(_saveSize, L"%d x %d", (int)IMAGEMANAGER->findImage(_fileName)->getWidth(), (int)IMAGEMANAGER->findImage(_fileName)->getHeight());
	}
	TextOut(getMemDC(), 1055, 23, _saveSize, wcslen(_saveSize));

	_stprintf(text, L"����(0-100(%%))");
	TextOut(getMemDC(), 1050, 160, text, wcslen(text));
	_alphaValueBox->render();

	//����
	for (int i = 0; i < TILEVIEWX; i++)
	{
		for (int j = 0; j < TILEVIEWY; j++)
		{
			IMAGEMANAGER->render(_sampleTiles[_tiles[(i + _countY) * TILEVIEWY * (TILEX / TILEVIEWY) + j + _countX].sampleTerrainIdx].strImgKey, getMemDC(), _tiles[i * TILEVIEWY * (TILEX / TILEVIEWY) + j].rc.left, _tiles[i * TILEVIEWY * (TILEX / TILEVIEWY) + j].rc.top);
		}
	}

	//������Ʈ
	for (int i = 0; i < TILEVIEWX; i++)
	{
		for (int j = 0; j < TILEVIEWY; j++)
		{
			if (_tiles[(i + _countY) * TILEVIEWY * (TILEX / TILEVIEWY) + j + _countX].obj == OBJECT_NONE) continue;

			IMAGEMANAGER->alphaRender(_TroopObj[_tiles[(i + _countY) * TILEVIEWY * (TILEX / TILEVIEWY) + j + _countX].sampleObjectSelectIdx][_tiles[(i + _countY) * TILEVIEWY * (TILEX / TILEVIEWY) + j + _countX].sampleObjectIdx].strImgKey, getMemDC(), _tiles[i * TILEVIEWY * (TILEX / TILEVIEWY) + j].rc.left, _tiles[i * TILEVIEWY * (TILEX / TILEVIEWY) + j].rc.top, 128);
		}
	}

	for (int i = 0; i < CTRL_END; i++)
	{
		_ctrlButton[i]->render();
		TextOut(getMemDC(), _ctrlButton[i]->getRect().left, _ctrlButton[i]->getRect().top, _strButton[i], _tcslen(_strButton[i]));
	}

	if (_ctrSelect == CTRL_OBJDRAW)
	{
		for (int i = 0; i < OBJECTSELECT_MAX; i++)
		{
			_objectSelect[i]->render();
			TextOut(getMemDC(), _objectSelect[i]->getRect().left, _objectSelect[i]->getRect().top, _strObjectSelect[i], _tcslen(_strObjectSelect[i]));
		}
	}

	//�����̽��� ������ TERRAIN ��ȣ �����ֱ�
	if (_viewTERRAIN)
	{
		for (int i = 0; i < TILEVIEWX; i++)
		{
			for (int j = 0; j < TILEVIEWY; j++)
			{
				TCHAR text[128];
				_stprintf_s(text, L"%d", _tiles[(i + _countY) * TILEVIEWY * (TILEX / TILEVIEWY) + j + _countX].terrain);
				TextOut(getMemDC(), _tiles[i * TILEVIEWY * (TILEX / TILEVIEWY) + j].rc.left, _tiles[i * TILEVIEWY * (TILEX / TILEVIEWY) + j].rc.top, text, wcslen(text));
			}
		}
	}

	//���� �� �Ǵ����� �����ϱ�
	if (_mapView)
	{
		IMAGEMANAGER->findImage(_fileName)->alphaRender(getMemDC(), 0, 0, _countX * 48, _countY * 48, 960, 960, _alphaValue);
	}
}

void sceneMaptool::getChar(WPARAM wParam)
{
	_editBox->getChar(wParam);
	_alphaValueBox->getChar(wParam);
}

//-----------------------------------------------------------------------------------------
//callback functions
void sceneMaptool::ctrlSelectSave(void* obj)
{
	sceneMaptool* maptool = (sceneMaptool*)obj;

	maptool->save();
}

void sceneMaptool::ctrlSelectLoad(void* obj)
{
	sceneMaptool* maptool = (sceneMaptool*)obj;

	maptool->load();
}

void sceneMaptool::ctrlSelectTerrain(void* obj)
{
	sceneMaptool* maptool = (sceneMaptool*)obj;

	maptool->setCtrlSelect(CTRL_TERRAINDRAW);
}

void sceneMaptool::ctrlSelectObject(void* obj)
{
	sceneMaptool* maptool = (sceneMaptool*)obj;

	maptool->setCtrlSelect(CTRL_OBJDRAW);
}

void sceneMaptool::ctrlSelectEraser(void* obj)
{
	sceneMaptool* maptool = (sceneMaptool*)obj;

	maptool->setCtrlSelect(CTRL_ERASER);
}

void sceneMaptool::ctrlObjectSelectAily(void * obj)
{
	sceneMaptool* maptool = (sceneMaptool*)obj;

	maptool->setCtrlObjectSelect(OBJECTSELECT_AILY);
}

void sceneMaptool::ctrlObjectSelectEnemy(void * obj)
{
	sceneMaptool* maptool = (sceneMaptool*)obj;

	maptool->setCtrlObjectSelect(OBJECTSELECT_ENEMY);
}

void sceneMaptool::ctrlObjectSelectPlayer(void * obj)
{
	sceneMaptool* maptool = (sceneMaptool*)obj;

	maptool->setCtrlObjectSelect(OBJECTSELECT_PLAYER);
}
//~callback functions
//-----------------------------------------------------------------------------------------

void sceneMaptool::setup(void)
{
	//��� ��ư ����
	_ctrlButton[CTRL_SAVE] = new button;
	_ctrlButton[CTRL_LOAD] = new button;
	_ctrlButton[CTRL_TERRAINDRAW] = new button;
	_ctrlButton[CTRL_OBJDRAW] = new button;
	_ctrlButton[CTRL_ERASER] = new button;
	
	_ctrlButton[CTRL_SAVE]->init(L"������ư",         1100, 300, { 0, 0 }, { 0, 1 }, ctrlSelectSave, this);
	_ctrlButton[CTRL_LOAD]->init(L"������ư",         1100, 400, { 0, 0 }, { 0, 1 }, ctrlSelectLoad, this);
	_ctrlButton[CTRL_TERRAINDRAW]->init(L"������ư",  1100, 500, { 0, 0 }, { 0, 1 }, ctrlSelectTerrain, this);
	_ctrlButton[CTRL_OBJDRAW]->init(L"������ư",      1100, 600, { 0, 0 }, { 0, 1 }, ctrlSelectObject, this);
	_ctrlButton[CTRL_ERASER]->init(L"������ư",       1100, 700, { 0, 0 }, { 0, 1 }, ctrlSelectEraser, this);

	
	_stprintf(_strButton[CTRL_SAVE], L"SAVE");
	_stprintf(_strButton[CTRL_LOAD], L"LOAD");
	_stprintf(_strButton[CTRL_TERRAINDRAW], L"TERRAIN");
	_stprintf(_strButton[CTRL_OBJDRAW], L"OBJECT");
	_stprintf(_strButton[CTRL_ERASER], L"ERASER");

	_ctrSelect = CTRL_TERRAINDRAW;

	//������Ʈ ��ư ����
	_objectSelect[OBJECTSELECT_AILY] = new button;
	_objectSelect[OBJECTSELECT_ENEMY] = new button;
	_objectSelect[OBJECTSELECT_PLAYER] = new button;

	_objectSelect[OBJECTSELECT_AILY]->init(L"������ư", WINSIZEX - TILESIZE * 3 - IMAGEMANAGER->findImage(L"������ư")->getWidth() / 2, 15, { 0, 0 }, { 0, 1 }, ctrlObjectSelectAily, this);
	_objectSelect[OBJECTSELECT_ENEMY]->init(L"������ư", WINSIZEX - TILESIZE * 3 - IMAGEMANAGER->findImage(L"������ư")->getWidth() / 2, 46, { 0, 0 }, { 0, 1 }, ctrlObjectSelectEnemy, this);
	_objectSelect[OBJECTSELECT_PLAYER]->init(L"������ư", WINSIZEX - TILESIZE * 3 - IMAGEMANAGER->findImage(L"������ư")->getWidth() / 2, 77, { 0, 0 }, { 0, 1 }, ctrlObjectSelectPlayer, this);

	_stprintf(_strObjectSelect[OBJECTSELECT_AILY], L"�Ʊ�");
	_stprintf(_strObjectSelect[OBJECTSELECT_ENEMY], L"����");
	_stprintf(_strObjectSelect[OBJECTSELECT_PLAYER], L"�÷��̾�");

	_ctrObjectSelect = OBJECTSELECT_PLAYER;

	//����Ÿ�� ������
	POINT ptSampleStart = { WINSIZEX - TILESIZE * SAMPLETILEX, 0 };

	//���� Ÿ�ϼ� ����
	for (int i = 0; i < SAMPLETILEY; i++)
	{
		for (int j = 0; j < SAMPLETILEX; j++)
		{
			int index = i * SAMPLETILEX + j;
			_stprintf(_sampleTiles[index].strImgKey, L"tile (%02d)", index + 1);

			_sampleTiles[index].img = IMAGEMANAGER->findImage(_sampleTiles[index].strImgKey);
			_sampleTiles[index].rcTile = RectMake(ptSampleStart.x + j*TILESIZE, ptSampleStart.y + i * TILESIZE, TILESIZE, TILESIZE);
		}
	}

	//������Ʈ Ÿ�ϼ� ����
	for (int i = 0; i < SAMPLETILEY; i++)
	{
		for (int j = 0; j < SAMPLETILEX; j++)
		{
			int index = i * SAMPLETILEX + j;
			_stprintf(_TroopObj[OBJECTSELECT_AILY][index].strImgKey, L"�Ʊ� (%02d)", index + 1);

			_TroopObj[OBJECTSELECT_AILY][index].img = IMAGEMANAGER->findImage(_TroopObj[OBJECTSELECT_AILY][index].strImgKey);
			_TroopObj[OBJECTSELECT_AILY][index].rcTile = RectMake(ptSampleStart.x + j*TILESIZE, ptSampleStart.y + i * TILESIZE, TILESIZE, TILESIZE);

			_stprintf(_TroopObj[OBJECTSELECT_ENEMY][index].strImgKey, L"���� (%02d)", index + 1);

			_TroopObj[OBJECTSELECT_ENEMY][index].img = IMAGEMANAGER->findImage(_TroopObj[OBJECTSELECT_ENEMY][index].strImgKey);
			_TroopObj[OBJECTSELECT_ENEMY][index].rcTile = RectMake(ptSampleStart.x + j*TILESIZE, ptSampleStart.y + i * TILESIZE, TILESIZE, TILESIZE);

			_stprintf(_TroopObj[OBJECTSELECT_PLAYER][index].strImgKey, L"�÷��̾� (%02d)", index + 1);

			_TroopObj[OBJECTSELECT_PLAYER][index].img = IMAGEMANAGER->findImage(_TroopObj[OBJECTSELECT_PLAYER][index].strImgKey);
			_TroopObj[OBJECTSELECT_PLAYER][index].rcTile = RectMake(ptSampleStart.x + j*TILESIZE, ptSampleStart.y + i * TILESIZE, TILESIZE, TILESIZE);
		}
	}

	//����Ÿ�� ������
	POINT ptTileStart = { 0, 0 };

	//Ÿ�� ���� ����
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			int index = i * TILEX + j;

			_tiles[index].rc = RectMake(ptTileStart.x + j * TILESIZE, ptTileStart.y + i * TILESIZE, TILESIZE, TILESIZE);
		}
	}

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		_tiles[i].sampleTerrainIdx = 0;
		_tiles[i].terrain = terrainSelect(_tiles[i].sampleTerrainIdx);
		_tiles[i].obj = OBJECT_NONE;
	}

	//����� �밡�ٴ� �����ϰ� ����
	for (int i = 0; i < OBJECTSELECT_MAX; i++)
	{
		_TroopObj[i][0].obj = OBJECT_INFANTRY;
		_TroopObj[i][1].obj = OBJECT_CAVALRY;
		_TroopObj[i][2].obj = OBJECT_ARCHER;
		_TroopObj[i][3].obj = OBJECT_HORSEARCHER;
		_TroopObj[i][4].obj = OBJECT_FIGHTER;
		_TroopObj[i][5].obj = OBJECT_THEIF;
		_TroopObj[i][6].obj = OBJECT_TACTICIAN;
		_TroopObj[i][7].obj = OBJECT_WIZARD;
		_TroopObj[i][8].obj = OBJECT_CATAPULT;
		_TroopObj[i][9].obj = OBJECT_NONE;
		_TroopObj[i][10].obj = OBJECT_NONE;
		_TroopObj[i][11].obj = OBJECT_NONE;
		_TroopObj[i][12].obj = OBJECT_HERO01;
		_TroopObj[i][13].obj = OBJECT_HERO02;
		_TroopObj[i][14].obj = OBJECT_HERO03;
		_TroopObj[i][15].obj = OBJECT_HERO04;
		_TroopObj[i][16].obj = OBJECT_HERO05;
		_TroopObj[i][17].obj = OBJECT_HERO06;
		_TroopObj[i][18].obj = OBJECT_HERO07;
		_TroopObj[i][19].obj = OBJECT_HERO08;
		_TroopObj[i][20].obj = OBJECT_HERO09;
		_TroopObj[i][21].obj = OBJECT_HERO10;
		_TroopObj[i][22].obj = OBJECT_NONE;
		_TroopObj[i][23].obj = OBJECT_NONE;
		_TroopObj[i][24].obj = OBJECT_NONE;
		_TroopObj[i][25].obj = OBJECT_NONE;
		_TroopObj[i][26].obj = OBJECT_NONE;
		_TroopObj[i][27].obj = OBJECT_NONE;
		_TroopObj[i][28].obj = OBJECT_NONE;
		_TroopObj[i][29].obj = OBJECT_NONE;
	}
}

void sceneMaptool::setMap(void)
{
	if (PtInRect(&RectMake(WINSIZEX - 3 * TILESIZE, 0, 3 * TILESIZE, 10 * TILESIZE), _ptMouse))
	{
		if (_ctrSelect == CTRL_TERRAINDRAW)
			for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
			{
				if (PtInRect(&_sampleTiles[i].rcTile, _ptMouse))
				{
					_selectSampleIndex = i;
					break;
				}
			}
		else if (_ctrSelect == CTRL_OBJDRAW)
			for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
			{
				if (_ctrObjectSelect == OBJECTSELECT_AILY)
				{
					if (PtInRect(&_TroopObj[OBJECTSELECT_AILY][i].rcTile, _ptMouse))
					{
						_selectSampleIndex = i;
						break;
					}
				}
				else if (_ctrObjectSelect == OBJECTSELECT_ENEMY)
				{
					if (PtInRect(&_TroopObj[OBJECTSELECT_ENEMY][i].rcTile, _ptMouse))
					{
						_selectSampleIndex = i;
						break;
					}
				}
				else if (_ctrObjectSelect == OBJECTSELECT_PLAYER)
				{
					if (PtInRect(&_TroopObj[OBJECTSELECT_PLAYER][i].rcTile, _ptMouse))
					{
						_selectSampleIndex = i;
						break;
					}
				}
			}
	}

	if (PtInRect(&RectMake(0, 0, 20 * TILESIZE, 20 * TILESIZE), _ptMouse))
	{
		for (int i = 0; i < TILEX; i++)
		{
			for (int j = 0; j < TILEY; j++)
			{
				if (PtInRect(&_tiles[i * 20 * (TILEX / 20) + j].rc, _ptMouse))
				{
					if (_ctrSelect == CTRL_TERRAINDRAW)
					{
						_tiles[(i + _countY) * 20 * (TILEX / 20) + j + _countX].sampleTerrainIdx = _selectSampleIndex;
						_tiles[(i + _countY) * 20 * (TILEX / 20) + j + _countX].terrain = (TERRAIN)_selectSampleIndex;
						//_tiles[(i + _countY) * 20 * (TILEX / 20) + j + _countX].terrain = terrainSelect(_tiles[(i + _countY) * 20 * (TILEX / 20) + j + _countX].sampleTerrainIdx);
					}
					else if (_ctrSelect == CTRL_OBJDRAW)
					{
						if (_ctrObjectSelect == OBJECTSELECT_AILY)
						{
							_tiles[(i + _countY) * 20 * (TILEX / 20) + j + _countX].sampleObjectSelectIdx = OBJECTSELECT_AILY;
							_tiles[(i + _countY) * 20 * (TILEX / 20) + j + _countX].sampleObjectIdx = _selectSampleIndex;
							_tiles[(i + _countY) * 20 * (TILEX / 20) + j + _countX].obj = _TroopObj[OBJECTSELECT_AILY][_selectSampleIndex].obj;
						}
						else if (_ctrObjectSelect == OBJECTSELECT_ENEMY)
						{
							_tiles[(i + _countY) * 20 * (TILEX / 20) + j + _countX].sampleObjectSelectIdx = OBJECTSELECT_ENEMY;
							_tiles[(i + _countY) * 20 * (TILEX / 20) + j + _countX].sampleObjectIdx = _selectSampleIndex;
							_tiles[(i + _countY) * 20 * (TILEX / 20) + j + _countX].obj = _TroopObj[OBJECTSELECT_ENEMY][_selectSampleIndex].obj;
						}
						else if (_ctrObjectSelect == OBJECTSELECT_PLAYER)
						{
							_tiles[(i + _countY) * 20 * (TILEX / 20) + j + _countX].sampleObjectSelectIdx = OBJECTSELECT_PLAYER;
							_tiles[(i + _countY) * 20 * (TILEX / 20) + j + _countX].sampleObjectIdx = _selectSampleIndex;
							_tiles[(i + _countY) * 20 * (TILEX / 20) + j + _countX].obj = _TroopObj[OBJECTSELECT_PLAYER][_selectSampleIndex].obj;
						}
					}
					else if (_ctrSelect == CTRL_ERASER)
					{
						//_tiles[(i + _countY) * 20 * (TILEX / 20) + j + _countX].sampleTerrainIdx = NULL;
						//_tiles[(i + _countY) * 20 * (TILEX / 20) + j + _countX].terrain = terrainSelect(_tiles[(i + _countY) * 20 * (TILEX / 20) + j + _countX].sampleTerrainIdx);
						_tiles[(i + _countY) * 20 * (TILEX / 20) + j + _countX].obj = OBJECT_NONE;
					}

					break;
				}
			}
		}
	}
}
					
void sceneMaptool::save(void)
{
	HANDLE file;
	DWORD write;

	int num = _editBox->getStrNum();
	TCHAR strFile[100];
	_stprintf(strFile, L"MapData/M%03d.map", num);

	file = CreateFile(strFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &write, NULL);

	CloseHandle(file);

}

void sceneMaptool::load(void)
{
	HANDLE file;
	DWORD read;

	int num = _editBox->getStrNum();
	TCHAR strFile[100];
	_stprintf(strFile, L"MapData/M%03d.map", num);

	file = CreateFile(strFile, GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);

	_stprintf(_fileName, L"M%03d", num);

	//�ʻ����� �׸��� �°� ����
	for (int i = 0; i < 6; i++)
	{
		if (IMAGEMANAGER->findImage(_fileName)->getWidth() / TILESIZE == _tileSizeX[i])		_selectSizeX = i;
		if (IMAGEMANAGER->findImage(_fileName)->getHeight() / TILESIZE == _tileSizeY[i])	_selectSizeY = i;
	}

	if (_countX + 20 > _tileSizeX[_selectSizeX]) _countX = _tileSizeX[_selectSizeX] - 20;
	if (_countY + 20 > _tileSizeY[_selectSizeY]) _countY = _tileSizeY[_selectSizeY] - 20;

	_isload = true;
	_mapView = false;

	CloseHandle(file);
}

TERRAIN sceneMaptool::terrainSelect(int index)
{

	return TERRAIN_NONE;
}

OBJECT sceneMaptool::objSelect(int index)
{

	return OBJECT_NONE;
}
