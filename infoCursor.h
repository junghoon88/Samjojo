#pragma once
#include "tileNode.h"
#include "gameNode.h"
#include "gameMap.h"

#define INTERFACESIZEX 200
#define INTERFACESIZEY 150

class infoCursor : public gameNode
{
private:
	gameMap* findtile;

	RECT rc;//정보 제공용 박스
	RECT drawLine;//타일 테두리 표시용
	HPEN linePen,oPen;

	RECT tileImgRect;
	RECT unitImgRect;
	
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
	void Scanning(void);
	void Click(void);
};

