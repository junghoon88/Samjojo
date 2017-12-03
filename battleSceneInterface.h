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
	BTN_NONE = -1,
	BTN_ATTACK,
	BTN_ITEM,
	BTN_WAIT,
	BTN_CANCEL,
	BTN_MAX
};

enum uiBtnName
{
	UIBTN_NONE = -1,
	UIBTN_SAVE,
	UIBTN_LOAD,
	UIBTN_UNIT,
	UIBTN_INVEN,
	UIBTN_MAX
};

enum clickFN
{
	NONE,PLAYER,FRIEND,ENEMY
};

class battleSceneInterface : public gameNode
{
private:
	Player*		_player;
	Friend*		_friend;
	Enemy*		_enemy;
	gameMap* findtile;
	clickFN clickUnit;

	RECT rc;//���� ������ �ڽ�
	RECT drawLine;//Ÿ�� �׵θ� ǥ�ÿ�
	RECT drawMoveLine;
	HPEN linePen,oPen;
	RECT tileImgRect;
	image* tileImg;
	TCHAR tileKey[100];
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
	TCHAR txtExp[100];
	TCHAR txtAtk[100];//A.K.A ���ݷ�
	TCHAR txtDef[100];
	TCHAR txtMove[100];
	
	int vNum;// v�ѹ�
	int bonus;//���� ���� ���� ������ ����ǥ��
	int exp;
	int lv;
	int atk;
	int def;
	int movePoint;

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
	//================================���� �ϴ� UI ǥ�ÿ�==============================
	uiBtnName uiBtn_name;
	button* uiBtn[UIBTN_MAX];

	static void cb_save(void* obj);
	static void cb_load(void* obj);
	static void cb_unit(void* obj);
	static void cb_inven(void* obj);


	//======================================���� �ϴ� UI ǥ�ÿ�=================================
	
	bool isUnit;//Unit�� true. ������ false
	bool isShow;//Ŭ���ϸ� true��
	bool popUpMenu;
	bool targetAttack;
public:
	battleSceneInterface();
	~battleSceneInterface();
	void buttonSetup(void);

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void infoSetup(void);// == init
	void dataClean(void);//���콺 ��Ŭ���� Ŭ���� ��
	void tileLineDraw(void);
	void infoDraw(void);
	void cmdDraw(void);
	void moveCamera(void);
	void chaseCamera(POINT tilePt);
	void mouse_Scanning(void);
	void mouse_ClickToTile(void);
	void mouse_ClickToAction(void);
	void mouse_ActionCancel(void);
	void mouse_ClickToAttack(void);
	void setUnit(TEAM faction ,int vectorNum);
	void callToMenu(int x,int y);

public:
	inline void setLinkPlyer(Player* player) { _player = player; }
	inline void setLinkEnemy(Enemy* enm) { _enemy = enm; }
	inline void setLinkFriend(Friend* fri) { _friend = fri; }
	inline void setLinkAdressMap(gameMap* tile) { findtile = tile; }

};

