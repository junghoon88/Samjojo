#pragma once
#include "gameNode.h"
#include "tileNode.h"
#include "tile.h"
#include "gameMap.h"

//1. �̵������� Ÿ���� ã�´�. (�� Ÿ�Ϻ��� �Ҹ��� �ִ´�.)
//2. �̵������� Ÿ�� �߿��� �� ��ġ���� ������ �� �ִ� Ÿ���� ã�´�.
//3. ���� ������ Ÿ���߿��� ����� ���� HP�� ���� ���� �ָ� �����Ѵ�.


class aStar : public gameNode
{
private:
	typedef vector<tile*> vTile;
	typedef vector<tile*>::iterator viTile;

	typedef map<int, tile*> mTile;
	typedef map<int, tile*>::iterator miTile;

private:
	vTile _vTotalList;	// ��Ż Ÿ��
	vTile _vOpenList;	// �� �� �ִ� Ÿ��
	mTile _mAttackList;	// ���� ������ ��ġ, �� Ÿ��

	tile* _staTile;		// ���� Ÿ��

	BOOL  _atkRange[UNIT_ATTACK_RANGE_MAX][UNIT_ATTACK_RANGE_MAX];


	gameMap* _map;

	int _cost;
	int _costMax;

	POINT _tileMax;

private:
	tile* findTile(int idX, int idY);

public:
	aStar();
	~aStar();

	HRESULT init(gameMap* map);
	void release(void);
	void update(void);
	void render(void);


	//Ÿ�� ������ �Լ�
	void initTiles(void);
	void resetTilesAttr(void);
	void setTiles(POINT startPt, int costMax);

	//���� Ÿ�Ͽ��� ���� �ִ� �� ã�� �Լ�
	vector<tile*> addOpenList(tile* currentTile);
	//��� Ž�� �Լ�
	void findOpenList(tile* currentTile, int cost = 0);

	//���� Ÿ�Ͽ��� ���� �������� ã�� �Լ�
	void addAtkList(TEAM myTeam, tile* currentTile);
	bool findAtkPos(TEAM myTeam, POINT* myPos, POINT* enemyPos);

	POINT findCloseTile(POINT st, POINT ed);

	void clearTiles(void);
	tile* getTile(POINT tilePt);

public:
	inline vector<tile*> getOpenList(void) { return _vOpenList; }
	inline void setAtkRange(BOOL atk, int x, int y) { _atkRange[x][y] = atk; }
	inline void resetAtkRange(void) { ZeroMemory(&_atkRange, sizeof(BOOL)*UNIT_ATTACK_RANGE_MAX*UNIT_ATTACK_RANGE_MAX); }
};

