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

	RECT rc;//정보 제공용 박스
	RECT drawLine;//타일 테두리 표시용
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
	TCHAR* unitName;
	TCHAR* utype;//클래스
	TCHAR* factionName;//진영(아군적군)
	TCHAR* showExp;//플레이어는 아군적군대신 경험치 표시됨
	TCHAR* showAtk;//A.K.A 공격력
	
	int vNum;// v넘버
	int bonus;//밟은 땅에 따른 전투력 증감표시
	int exp;
	int lv;
	progressBar hpBar;
	int curHp, maxHp;
	progressBar mpBar;
	int curMp, maxMp;
	//유닛 정보 표시용

	//지형 정보 표시용
	TCHAR* tilename;
	TCHAR* prop;
	int tileNum;
	bool fire;
	bool wind;
	bool earth;
	bool water;
	//지형 정보 표시용
	//플레이어 유닛 클릭시 표시할 정보,공격,스킬,도구,대기,취소
	RECT infoBox;
	



	//플레이어 유닛 클릭시 표시할 정보,공격,스킬,도구,대기,취소


	bool isUnit;//Unit은 true. 지형은 false
	bool isShow;//클릭하면 true로

public:
	infoCursor();
	~infoCursor();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void dataClean(void);//마우스 우클릭시 클리어 용
	void tileLineDraw(void);
	void infoDraw(void);
	void moveCamera(void);
	void mouse_Scanning(void);
	void mouse_MovetileScanning(void);//플레이어 유닛 클릭 시 이동가능 타일 검색용
	void mouse_ClickToTile(void);
	void mouse_ClickToAction(void);

public:
	inline void setLinkPlyer(Player* player) { _player = player; }
	inline void setLinkEnemy(Enemy* enm) { _enemy = enm; }
	inline void setLinkFriend(Friend* fri) { _friend = fri; }
	inline void setLinkAdressMap(gameMap* tile) { findtile = tile; }

};

