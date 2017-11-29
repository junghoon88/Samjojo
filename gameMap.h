#pragma once
#include "gameNode.h"
#include "tileNode.h"

class Unit;
class Player;
class Friend;
class Enemy;
class infoCursor;

class gameMap : public gameNode
{
private:
	tagTile _tiles[TILEX * TILEY];	 // Ÿ��
	DWORD _attribute[TILEX * TILEY]; // Ÿ�� �Ӽ�
	TEAM _teamInfo[TILEX * TILEY]; // Ÿ�Ͽ� ���� ��ġ����

	TCHAR _strSampleImgKey[SAMPLETILEX * SAMPLETILEY][100];

	TCHAR _objImage[OBJECTSELECT_MAX][100];

	image*		_imgMap;		//���� ������ ��
	int			_tilesizeX;		//Ÿ��ũ��(�ʿ� Ÿ���� �� �����)
	int			_tilesizeY;		//Ÿ��ũ��(�ʿ� Ÿ���� �� �����)

	Player*		_player;	//�÷��̾�
	Friend*		_friend;	//�Ʊ�
	Enemy*		_enemy;		//����
	infoCursor* _cursor;

public:
	gameMap();
	~gameMap();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//�������� �׸� �� �ε��Լ�
	void loadData(int num);
	//���ֵ��� ��ġ�� �ҷ��´�.
	void scanUnitsPos(void);

	Unit* findEnemyUnit(TEAM myTeam, POINT tilePt);

public:
	inline void setLinkAdressPlayer(Player* player) { _player = player; }
	inline void setLinkAdressFriend(Friend* friends) { _friend = friends; }
	inline void setLinkAdressEnemy(Enemy* enemy) { _enemy = enemy; }
	inline void setLinkAdressCursor(infoCursor* info) { _cursor = info; }

	//Ÿ�� ���� ������
	inline tagTile* getTile(void) { return _tiles; }
	inline DWORD* getAttribute(void) { return _attribute; }
	inline TEAM* getTeamInfo(void) { return _teamInfo; }


	inline int getTileSizeX(void) { return _tilesizeX; }
	inline int getTileSizeY(void) { return _tilesizeY; }

};

