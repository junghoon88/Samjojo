#pragma once
#include "gameNode.h"
#include "tileNode.h"

class Player;
class Friend;
class Enemy;

class gameMap : public gameNode
{
private:
	tagTile _tiles[TILEX * TILEY];	 // Ÿ��
	DWORD _attribute[TILEX * TILEY]; // Ÿ�� �Ӽ�

	TCHAR _strSampleImgKey[SAMPLETILEX * SAMPLETILEY][100];

	TCHAR _objImage[OBJECTSELECT_MAX][100];

	image*		_imgMap;		//���� ������ ��
	int			_tilesizeX;		//Ÿ��ũ��(�ʿ� Ÿ���� �� �����)
	int			_tilesizeY;		//Ÿ��ũ��(�ʿ� Ÿ���� �� �����)


	Player*		_player;	//�÷��̾�
	Friend*		_friend;	//�Ʊ�
	Enemy*		_enemy;		//����


public:
	gameMap();
	~gameMap();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//�������� �׸� �� �ε��Լ�
	void loadData(int num);

	//Ÿ�� ���� ������
	tagTile* getTile(void) { return _tiles; }
	DWORD* getAttribute(void) { return _attribute; }


public:
	inline void setLinkAdressPlayer(Player* player) { _player = player; }
	inline void setLinkAdressFriend(Friend* friends) { _friend = friends; }
	inline void setLinkAdressEnemy(Enemy* enemy) { _enemy = enemy; }

	inline int getTileSizeX(void) { return _tilesizeX; }
	inline int getTileSizeY(void) { return _tilesizeY; }
};

