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

	RECT rc;//정보 제공용 박스
	RECT drawLine;//타일 테두리 표시용
	HPEN linePen,oPen;

	RECT tileImgRect;
	image* tileImg;
	RECT unitImgRect;
	image* unitImg;
	RECT element[4];
	

	//유닛 정보 표시용
	TCHAR* unit;
	TCHAR* utype;//클래스
	TCHAR* faction;//진영(아군적군)
	TCHAR* land;//유닛이 밟은 땅
	TCHAR* showExp;//플레이어는 아군적군대신 경험치 표시됨
	
	int bonus;//밟은 땅에 따른 전투력 증감표시
	int exp;
	int lv;
	int curHp, maxHp;
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
	void mouse_moveCamera(void);
	void mouse_Scanning(void);
	void mouse_Click(void);

public:
	inline void setLinkPlyer(Player* player) { _player = player; }
	inline void setLinkEnemy(Enemy* enm) { _enemy = enm; }
	inline void setLinkFriend(Friend* fri) { _friend = fri; }
	inline void setLinkAdressMap(gameMap* tile) { findtile = tile; }

};

