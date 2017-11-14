#pragma once
#include "gameNode.h"
#include "tileNode.h"
#include "tile.h"
#include "gameMap.h"

class aStar : public gameNode
{
private:
	typedef vector<tile*> vTile;
	typedef vector<tile*>::iterator viTile;

private:
	vTile _vTotalList;	// ��Ż Ÿ��
	vTile _vOpenList;	// �� �� �ִ� Ÿ��
	vTile _vCloseList;	// ���� ����� Ÿ��

	tile* _staTile;		// ���� Ÿ��
	tile* _endTile;		// ��   Ÿ��
	tile* _curTile;		// ���� Ÿ��

	bool _valid;

	gameMap* _map;

	int _findCnt;
	int _findCntMax;

public:
	aStar();
	~aStar();

	HRESULT init(void);

	//Ÿ�� ������ �Լ�
	void initTiles(void);
	void setTiles(POINT startPt, POINT endPt);

	//���� Ÿ�Ͽ��� ���� �ִ� �� ã�� �Լ�
	vector<tile*> addOpenList(tile* currentTile);
	//��� Ž�� �Լ�
	POINT pathFinder(tile* currentTile);

	void clearTiles(void);
	tile* getTile(POINT tilePt);


	void release(void);
	void update(void);
	void render(void);

	inline void setGameMapAddressLink(gameMap* map) { _map = map; }

};

