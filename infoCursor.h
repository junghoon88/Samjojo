#pragma once
#include "tileNode.h"
#include "gameNode.h"
#include "gameMap.h"

#define BOXSIZEX 80
#define BOXSIZEY 150

class infoCursor : public gameNode
{
private:
	gameMap* findtile;

	RECT rc;//정보 제공용 박스
	RECT drawLine;//타일 테두리 표시용
	
	//유닛 정보 표시용
	TCHAR* unit;
	TCHAR* utype;//클래스
	TCHAR* faction;//진영(아군적군)
	TCHAR* land;//유닛이 밟은 땅
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

	void Scanning(void);
	void Click(int num);
};

