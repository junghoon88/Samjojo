#pragma once
#include "tileNode.h"
#include "gameNode.h"
#include "progressBar.h"
#include "button.h"

#define FROFILEIMAGE 120

class Player;
class Enemy;
class Friend;
class gameMap;

enum btnName
{
	BTN_NONE,
	BTN_SKILL,
	BTN_ATTACK,
	BTN_ITEM,
	BTN_WAIT,
	BTN_MAX
};

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
	RECT drawMoveLine;
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
	TCHAR unitName[100];
	TCHAR utype[100];//Ŭ����
	TCHAR factionName[100];//����(�Ʊ�����)
	TCHAR showExp[100];//�÷��̾�� �Ʊ�������� ����ġ ǥ�õ�
	TCHAR showAtk[100];//A.K.A ���ݷ�
	
	int vNum;// v�ѹ�
	int bonus;//���� ���� ���� ������ ����ǥ��
	int exp;
	int lv;
	progressBar* hpBar;
	int curHp, maxHp;
	progressBar* mpBar;
	int curMp, maxMp;
	//���� ���� ǥ�ÿ�

	//���� ���� ǥ�ÿ�
	TCHAR tilename[100];
	TCHAR prop[100];
	int tileNum;
	bool fire;
	bool wind;
	bool earth;
	bool water;
	//���� ���� ǥ�ÿ�
	//�÷��̾� ���� Ŭ���� ǥ���� ����,����,��ų,����,���,���
	RECT cmdBox;
	button* actionBtn[BTN_MAX];
	btnName btName;
	POINT backToPT;
	bool isCommand;
	DIRECTION backToDir;
	static void cb_attack(void* obj);
	static void cb_item(void* obj);
	static void cb_wait(void* obj);
	static void cb_cancel(void* obj);

	void cmd_atk(void);
	void cmd_item(void);
	void cmd_wait(void);
	void cmd_cancel(void);
	//�÷��̾� ���� Ŭ���� ǥ���� ����,����,��ų,����,���,���


	bool isUnit;//Unit�� true. ������ false
	bool isShow;//Ŭ���ϸ� true��
	bool popUpMenu;
public:
	infoCursor();
	~infoCursor();
	void buttonSetup(void);

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void infoSetup(void);// == init
	void dataClean(void);//���콺 ��Ŭ���� Ŭ���� ��
	void tileLineDraw(void);
	void infoDraw(void);
	void moveCamera(void);
	void mouse_Scanning(void);
	void mouse_ClickToTile(void);
	void mouse_ClickToAction(void);
	void mouse_ActionCancel(void);
	void callToMenu(void);
public:
	inline void setLinkPlyer(Player* player) { _player = player; }
	inline void setLinkEnemy(Enemy* enm) { _enemy = enm; }
	inline void setLinkFriend(Friend* fri) { _friend = fri; }
	inline void setLinkAdressMap(gameMap* tile) { findtile = tile; }

};

