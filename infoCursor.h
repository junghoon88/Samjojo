#pragma once
#include "tileNode.h"
#include "gameNode.h"
#include "progressBar.h"

#define FROFILEIMAGE 120

class Player;
class Enemy;
class Friend;
class gameMap;

enum clickFW
{
	NONE,PLAYER,FRIEND,ENEMY
};

class infoCursor : public gameNode
{
private:
	Player*		_player;
	Friend*		_friend;
	Enemy*		_enemy;
	gameMap* findtile;
	clickFW clickUnit;

	RECT rc;//���� ������ �ڽ�
	RECT drawLine;//Ÿ�� �׵θ� ǥ�ÿ�
	HPEN linePen,oPen;
	RECT tileImgRect;
	image* tileImg;
	RECT unitImgRect;
	image* unitImg;
	RECT element[4];
	

	//Ÿ�� �����//
	int indexTile;
	//Ÿ�� �����//


	//���� ���� ǥ�ÿ�
	TCHAR* unitName;
	TCHAR* utype;//Ŭ����
	TCHAR* factionName;//����(�Ʊ�����)
	TCHAR* showExp;//�÷��̾�� �Ʊ�������� ����ġ ǥ�õ�
	TCHAR* showAtk;//A.K.A ���ݷ�
	
	int vNum;// v�ѹ�
	int bonus;//���� ���� ���� ������ ����ǥ��
	int exp;
	int lv;
	progressBar hpBar;
	int curHp, maxHp;
	progressBar mpBar;
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
	//�÷��̾� ���� Ŭ���� ǥ���� ����,����,��ų,����,���,���
	RECT infoBox;
	



	//�÷��̾� ���� Ŭ���� ǥ���� ����,����,��ų,����,���,���


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
	void moveCamera(void);
	void mouse_Scanning(void);
	void mouse_MovetileScanning(void);//�÷��̾� ���� Ŭ�� �� �̵����� Ÿ�� �˻���
	void mouse_ClickToTile(void);
	void mouse_ClickToAction(void);

public:
	inline void setLinkPlyer(Player* player) { _player = player; }
	inline void setLinkEnemy(Enemy* enm) { _enemy = enm; }
	inline void setLinkFriend(Friend* fri) { _friend = fri; }
	inline void setLinkAdressMap(gameMap* tile) { findtile = tile; }

};

