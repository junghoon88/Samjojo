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
	//타일 셋팅
	_tileMax.x = _map->getTileSizeX();
	_tileMax.y = _map->getTileSizeY();

	initTiles();

	_cost = 0;
	_costMax = 5;

	return S_OK;
}

void aStar::initTiles(void)
{
	//최대 타일은 40x40 이지만
	//실제 맵크기 타일은 28x20 처럼 적기 때문에
	//쓸데없는 계산을 안하도록함
	for (int i = 0; i < _tileMax.y; i++)
	{
		for (int j = 0; j < _tileMax.x; j++)
		{
			tile* node = new tile;
			node->init(j, i, _map->getTile()[i * TILEX + j].rc);
			
			//타일 속성 셋팅
			DWORD attr = _map->getAttribute()[i * TILEX + j];
			if ((attr & ATTR_UNMOVE) == ATTR_UNMOVE)
			{
				node->setAttribute(L"unmove");
			}

			_vTotalList.push_back(node);
		}
	}
}


//타일 셋팅할 함수
void aStar::setTiles(POINT startPt, int costMax)
{
	_costMax = costMax;

	bool staCheck = false;

	for (int i = 0; i < _vTotalList.size(); i++)
	{
		POINT pt;
		pt.x = _vTotalList[i]->getIdX();
		pt.y = _vTotalList[i]->getIdY();

		//시작위치 설정
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



//현재 타일에서 갈수 있는 길 찾는 함수
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

			if (node->getIsOpen()) continue; //이미 열었으면
			if (node->getAttribute() == L"start") continue;
			if (node->getAttribute() == L"unmove") continue;

			//유닛이 있으면 건너뛰기
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

			if (addObj == false) continue; //이미 벡터에 있으면 계속

			//_vOpenList.push_back(node);
			newOpenList.push_back(node);
		}
	}

	//return _vOpenList;
	return newOpenList;
}


//경로 탐색 함수
//cost 가 같은 타일에서만 찾는다.
void aStar::findOpenList(tile* currentTile, int cost)
{
	//이미 find 했던 타일은 넘긴다.
	if (currentTile->getIsFind())
	{
		return;
	}

	//행동력이 최대를 넘어가면 찾지 않는다.
	if (currentTile->getTotalCost() >= _costMax)
	{
		return;
	}

	//시작 기준으로 퍼져나가도록 OpenTile 을 증가시킨다.
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

	//더이상 못찾았으면 끝낸다.
	if (newOpenList.size() == 0)
		return;

	for (int i = 0; i < newOpenList.size(); i++)
	{
		int cost = currentTile->getTotalCost();
		//타일 속성별로 cost 값을 다르게 준다.
		//if(currentTile->getAttribute() == ) 
		{
			cost += 1;
		}
		newOpenList[i]->setTotalCost(cost);
		newOpenList[i]->setIsOpen(true);

		//새로 찾은 OpenTile 을 맴버변수에 업데이트 해준다.
		_vOpenList.push_back(newOpenList[i]);
	}



	//재귀함수!!
	//현재 열려있는 타일을 기준으로 뻗어나간다.
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

			//적팀이 맞는지 체크
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
				//이미 맵 안에 있으면 넘긴다.
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

///TEAM myTeam : 자기 자신의 팀
///POINT * pos : 현재 위치를 받아서, 적을 공격할 수 있는 위치 중에 가장 가까운 위치로 변경해준다.
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
	//1차 직접 찾아보고
	int index = idX + idY * _tileMax.x;
	if (idX == _vTotalList[index]->getIdX() && idY == _vTotalList[index]->getIdY())
	{
		return _vTotalList[index];
	}

	//안찾아지면 2차로 전체 훑어보고
	for (int i = 0; i < _vTotalList.size(); i++)
	{
		if (idX == _vTotalList[i]->getIdX() && idY == _vTotalList[i]->getIdY())
		{
			return _vTotalList[i];
		}
	}

	//그래도 없으면 NULL
	return NULL;
}
