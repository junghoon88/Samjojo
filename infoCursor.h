#pragma once
#include "tileNode.h"
#include "gameNode.h"


#define INTERFACESIZEY 150
#define FROFILEIMAGE 120

class Player;
class Enemy;
class Friend;
class gameMap;

class infoCursor : public gameNode
{
private:
	Player*		_player;
	Friend*		_friend;
	Enemy*		_enemy;
	gameMap* findtile;

	RECT rc;//���� ������ �ڽ�
	RECT drawLine;//Ÿ�� �׵θ� ǥ�ÿ�
	HPEN linePen,oPen;

	RECT tileImgRect;
	image* tileImg;
	RECT unitImgRect;
	image* unitImg;
	RECT element[4];
	

	//���� ���� ǥ�ÿ�
	TCHAR* unit;
	TCHAR* utype;//Ŭ����
	TCHAR* faction;//����(�Ʊ�����)
	TCHAR* land;//������ ���� ��
	TCHAR* showExp;//�÷��̾�� �Ʊ�������� ����ġ ǥ�õ�
	
	int bonus;//���� ���� ���� ������ ����ǥ��
	int exp;
	int lv;
	int curHp, maxHp;
	int curMp, maxMp;
	//���� ���� ǥ�ÿ�

	//���� ���� ǥ�ÿ�
	TCHAR* tilename;
	TCHAR* prop;
	int tileNum;
	bool fire;
	bool wind;
	bool earth;
	bool water;
	//���� ���� ǥ�ÿ�


	bool isUnit;//Unit�� true. ������ false
	bool isShow;//Ŭ���ϸ� true��

public:
	infoCursor();
	~infoCursor();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void dataClean(void);//���콺 ��Ŭ���� Ŭ���� ��
	void tileLineDraw(void);
	void infoDraw(void);
	void mouse_moveCamera(void);
	void mouse_Scanning(void);
	void mouse_Click(void);

public:
	inline void setLinkPlyer(Player* player) { _player = player; }
	inline void setLinkEnemy(Enemy* enm) { _enemy = enm; }
	inline void setLinkFriend(Friend* fri) { _friend = fri; }
	inline void setLinkAdressMap(gameMap* tile) { findtile = tile; }

};

