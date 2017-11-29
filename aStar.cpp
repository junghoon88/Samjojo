#include "stdafx.h"
#include "aStar.h"



aStar::aStar()
	: _map(NULL)
{
}


aStar::~aStar()
{
}

HRESULT aStar::init(gameMap* map)
{
	_map = map;
	//Ÿ�� ����
	_tileMax.x = _map->getTileSizeX();
	_tileMax.y = _map->getTileSizeY();

	initTiles();

	_cost = 0;
	_costMax = 5;

	return S_OK;
}

void aStar::initTiles(void)
{
	//�ִ� Ÿ���� 40x40 ������
	//���� ��ũ�� Ÿ���� 28x20 ó�� ���� ������
	//�������� ����� ���ϵ�����
	for (int i = 0; i < _tileMax.y; i++)
	{
		for (int j = 0; j < _tileMax.x; j++)
		{
			tile* node = new tile;
			node->init(j, i, _map->getTile()[i * TILEX + j].rc);
			
			//Ÿ�� �Ӽ� ����
			DWORD attr = _map->getAttribute()[i * TILEX + j];
			if ((attr & ATTR_UNMOVE) == ATTR_UNMOVE)
			{
				node->setAttribute(L"unmove");
			}

			_vTotalList.push_back(node);
		}
	}
}


//Ÿ�� ������ �Լ�
void aStar::setTiles(POINT startPt, int costMax)
{
	_costMax = costMax;

	bool staCheck = false;

	for (int i = 0; i < _vTotalList.size(); i++)
	{
		POINT pt;
		pt.x = _vTotalList[i]->getIdX();
		pt.y = _vTotalList[i]->getIdY();

		//������ġ ����
		if (pt.x == startPt.x && pt.y == startPt.y)
		{
			_staTile = _vTotalList[i];
			_staTile->setAttribute(L"start");
			staCheck = true;
		}
		else
		{

		}
	}
}



//���� Ÿ�Ͽ��� ���� �ִ� �� ã�� �Լ�
vector<tile*> aStar::addOpenList(tile* currentTile)
{
	vector<tile*> newOpenList;
	newOpenList.clear();

	int startX = currentTile->getIdX() - 1;
	int startY = currentTile->getIdY() - 1;

	for (int i = 0; i < 3; i++) //y
	{
		for (int j = 0; j < 3; j++) //x
		{
			if (i == 0 && j == 0) continue;
			if (i == 0 && j == 2) continue;
			//if (i == 1 && j == 1) continue;
			if (i == 2 && j == 0) continue;
			if (i == 2 && j == 2) continue;

			int targetX = startX + j;
			int targetY = startY + i;

			if (targetX < 0) continue;
			if (targetX >= _tileMax.x) continue;
			if (targetY < 0) continue;
			if (targetY >= _tileMax.y) continue;


			tile* node = findTile(targetX, targetY);
			if (node == NULL) continue;

			if (node->getIsOpen()) continue; //�̹� ��������
			if (node->getAttribute() == L"start") continue;
			if (node->getAttribute() == L"unmove") continue;

			//������ ������ �ǳʶٱ�
			if (_map->getTeamInfo()[targetX + targetY * TILESIZE] != TEAM_NONE) continue;


			bool addObj = true;

			for (viTile _viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
			{
				if (*_viOpenList == node)
				{
					addObj = false;
					break;
				}
			}

			if (addObj == false) continue; //�̹� ���Ϳ� ������ ���

			//_vOpenList.push_back(node);
			newOpenList.push_back(node);
		}
	}

	//return _vOpenList;
	return newOpenList;
}


//��� Ž�� �Լ�
//cost �� ���� Ÿ�Ͽ����� ã�´�.
void aStar::findOpenList(tile* currentTile, int cost)
{
	//�̹� find �ߴ� Ÿ���� �ѱ��.
	if (currentTile->getIsFind())
	{
		return;
	}

	//�ൿ���� �ִ븦 �Ѿ�� ã�� �ʴ´�.
	if (currentTile->getTotalCost() >= _costMax)
	{
		return;
	}

	//���� �������� ������������ OpenTile �� ������Ų��.
	vector<tile*> newOpenList;
	if (currentTile->getTotalCost() == 0)
	{
		newOpenList = addOpenList(currentTile);
		currentTile->setIsFind(true);
	}
	else if (currentTile->getTotalCost() == cost)
	{
		newOpenList = addOpenList(currentTile);
		currentTile->setIsFind(true);
	}
	else
	{
		return;
	}

	//���̻� ��ã������ ������.
	if (newOpenList.size() == 0)
		return;

	for (int i = 0; i < newOpenList.size(); i++)
	{
		int cost = currentTile->getTotalCost();
		//Ÿ�� �Ӽ����� cost ���� �ٸ��� �ش�.
		//if(currentTile->getAttribute() == ) 
		{
			cost += 1;
		}
		newOpenList[i]->setTotalCost(cost);
		newOpenList[i]->setIsOpen(true);

		//���� ã�� OpenTile �� �ɹ������� ������Ʈ ���ش�.
		_vOpenList.push_back(newOpenList[i]);
	}



	//����Լ�!!
	//���� �����ִ� Ÿ���� �������� �������.
	while (_cost < _costMax)
	{
		for (int i = 0; i < _vOpenList.size(); i++)
		{
			findOpenList(_vOpenList[i], _cost);
		}
		_cost++;
	}
}

void aStar::addAtkList(TEAM myTeam, tile* currentTile)
{
	int range = int(UNIT_ATTACK_RANGE_MAX / 2);
	
	int startX = currentTile->getIdX() - range;
	int startY = currentTile->getIdY() - range;

	for (int i = 0; i < UNIT_ATTACK_RANGE_MAX; i++) //y
	{
		for (int j = 0; j < UNIT_ATTACK_RANGE_MAX; j++) //x
		{
			if (_atkRange[j][i] == FALSE) continue;

			if (startX + j < 0) continue;
			if (startX + j >= _tileMax.x) continue;
			if (startY + i < 0) continue;
			if (startY + i >= _tileMax.y) continue;

			tile* node = findTile(startX + j, startY + i);
			if (node == NULL) continue;

			//������ �´��� üũ
			if (myTeam == TEAM_FRIEND)
			{
				TEAM eteam = _map->getTeamInfo()[node->getIdX() + node->getIdY() * TILESIZE];
				if (eteam != TEAM_ENEMY)
					continue;
			}
			else if (myTeam == TEAM_ENEMY)
			{
				TEAM eteam = _map->getTeamInfo()[node->getIdX() + node->getIdY() * TILESIZE];
				if (eteam != TEAM_PLAYER && eteam != TEAM_FRIEND)
					continue;
			}
			else continue;

			for (miTile iter = _mAttackList.begin(); iter != _mAttackList.end(); ++iter)
			{
				//�̹� �� �ȿ� ������ �ѱ��.
				if ((*iter).second == node)
				{
					continue;
				}
			}

			int index = node->getIdX() + node->getIdY() * TILESIZE;
			//_mAttackList.insert(pair<POINT, tile*>(pt, node));
			_mAttackList.insert(make_pair(index, currentTile));
			return;
		}
	}
}

///TEAM myTeam : �ڱ� �ڽ��� ��
///POINT * pos : ���� ��ġ�� �޾Ƽ�, ���� ������ �� �ִ� ��ġ �߿� ���� ����� ��ġ�� �������ش�.
bool aStar::findAtkPos(TEAM myTeam, POINT* myPos, POINT* enemyPos)
{
	addAtkList(myTeam, findTile(myPos->x, myPos->y));

	for (viTile iter = _vOpenList.begin(); iter != _vOpenList.end(); ++iter)
	{
		addAtkList(myTeam, (*iter));
	}

	if (_mAttackList.size() > 0)
	{
		miTile iterMin = _mAttackList.begin();
		int costMin = 1000;

		for (miTile iter = _mAttackList.begin(); iter != _mAttackList.end(); ++iter)
		{
			int cost = (*iter).second->getTotalCost();
			if (costMin > cost)
			{
				iterMin = iter;
				costMin = cost;
			}
		}

		*myPos = { (*iterMin).second->getIdX(), (*iterMin).second->getIdY() };
		*enemyPos = { (*iterMin).first % TILESIZE, (*iterMin).first / TILESIZE };
		return true;
	}

	return false;
}

POINT aStar::findCloseTile(POINT st, POINT ed)
{
	POINT tarPt = st;

	float distMin = 1000.0f;

	for (viTile iter = _vOpenList.begin(); iter != _vOpenList.end(); ++iter)
	{
		POINT tempPt = { (*iter)->getIdX(), (*iter)->getIdY() };

		float dist = getDistance(tempPt.x, tempPt.y, ed.x, ed.y);
		if (distMin > dist)
		{
			tarPt = tempPt;
			distMin = dist;
		}
	}

	return tarPt;
}

void aStar::release(void)
{
	viTile iter = _vTotalList.begin();
	for (; iter != _vTotalList.end();)
	{
		if ((*iter) != NULL)
		{
			(*iter)->release();
			SAFE_DELETE((*iter));
		}
		else ++iter;
	}
	_vTotalList.clear();
}

void aStar::update(void)
{

}

void aStar::render(void)
{
	//for (int i = 0; i < _vOpenList.size(); i++)
	//{
	//	if (_vOpenList[i] == NULL) continue;

	//	int x = _vOpenList[i]->getIdX();
	//	int y = _vOpenList[i]->getIdY();

	//	int cost = (int)_vOpenList[i]->getTotalCost();
	//	TCHAR str[10];
	//	_stprintf(str, L"%d", cost);
	//	TextOut(getMemDC(), x * TILESIZE + 20, y * TILESIZE + 20, str, _tcslen(str));
	//}
}

void aStar::clearTiles(void)
{
	_mAttackList.clear();
	_vOpenList.clear();

	for (int i = 0; i < _vTotalList.size(); i++)
	{
		_vTotalList[i]->setIsOpen(false);
		_vTotalList[i]->setIsFind(false);
		_vTotalList[i]->setTotalCost(0);
	}

	resetTilesAttr();

	_cost = 0;
}

void aStar::resetTilesAttr(void)
{
	for (int i = 0; i < _vTotalList.size(); i++)
	{
		int idX = _vTotalList[i]->getIdX();
		int idY = _vTotalList[i]->getIdY();

		DWORD attr = _map->getAttribute()[idX * TILEX + idY];

		_vTotalList[i]->setAttribute(L"");
		//if ((attr & ATTR_UNMOVE) == ATTR_UNMOVE)
		//{
		//	_vTotalList[i]->setAttribute(L"unmove");
		//}
	}
}


tile* aStar::getTile(POINT tilePt)
{
	for (int i = 0; i < _vTotalList.size(); i++)
	{
		if (tilePt.x == _vTotalList[i]->getIdX() && tilePt.y == _vTotalList[i]->getIdY())
		{
			return _vTotalList[i];
		}
	}

	return NULL;
}


tile* aStar::findTile(int idX, int idY)
{
	//1�� ���� ã�ƺ���
	int index = idX + idY * _tileMax.x;
	if (idX == _vTotalList[index]->getIdX() && idY == _vTotalList[index]->getIdY())
	{
		return _vTotalList[index];
	}

	//��ã������ 2���� ��ü �Ⱦ��
	for (int i = 0; i < _vTotalList.size(); i++)
	{
		if (idX == _vTotalList[i]->getIdX() && idY == _vTotalList[i]->getIdY())
		{
			return _vTotalList[i];
		}
	}

	//�׷��� ������ NULL
	return NULL;
}
