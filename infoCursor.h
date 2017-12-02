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

	RECT rc;//정보 제공용 박스
	RECT drawLine;//타일 테두리 표시용
	RECT drawMoveLine;
	HPEN linePen,oPen;
	RECT tileImgRect;
	image* tileImg;
	RECT unitImgRect;
	image* unitImg;
	RECT element[4];
	

	//타일 검출용//
	int indexTile;
	//타일 검출용//


	//유닛 정보 표시용
	TCHAR unitName[100];
	TCHAR utype[100];//클래스
	TCHAR factionName[100];//진영(아군적군)
	TCHAR showExp[100];//플레이어는 아군적군대신 경험치 표시됨
	TCHAR showAtk[100];//A.K.A 공격력
	
	int vNum;// v넘버
	int bonus;//밟은 땅에 따른 전투력 증감표시
	int exp;
	int lv;
	progressBar* hpBar;
	int curHp, maxHp;
	progressBar* mpBar;
	int curMp, maxMp;
	//유닛 정보 표시용

	//지형 정보 표시용
	TCHAR tilename[100];
	TCHAR prop[100];
	int tileNum;
	bool fire;
	bool wind;
	bool earth;
	bool water;
	//지형 정보 표시용
	//플레이어 유닛 클릭시 표시할 정보,공격,스킬,도구,대기,취소
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
	//플레이어 유닛 클릭시 표시할 정보,공격,스킬,도구,대기,취소


	bool isUnit;//Unit은 true. 지형은 false
	bool isShow;//클릭하면 true로
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
	void dataClean(void);//마우스 우클릭시 클리어 용
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

