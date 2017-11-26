#pragma once
#include "gameNode.h"
#include "tileNode.h"

class gameMap : public gameNode
{
private:
	tagTile _tiles[TILEX * TILEY];	 // Ÿ��
	DWORD _attribute[TILEX * TILEY]; // Ÿ�� �Ӽ�

	TCHAR _strSampleImgKey[SAMPLETILEX * SAMPLETILEY][100];

	TCHAR _objImage[OBJECTSELECT_MAX][100];

	int _pos[2];


public:
	gameMap();
	~gameMap();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//�������� �׸� �� �ε��Լ�
	void load();

	//Ÿ�� ���� ������
	tagTile* getTile(void) { return _tiles; }
	DWORD* getAttribute(void) { return _attribute; }

	//1p, 2p ������ 
	int getPosFirst() { return _pos[0]; }
	int getPosSecond() { return _pos[1]; }

};

