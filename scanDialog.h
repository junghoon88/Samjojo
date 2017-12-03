#pragma once
#include "gameNode.h"

#define STRING_MAX 1024
//전투씬 전방선언
class sceneBattle;
class scanDialog : public gameNode
{
private:
	FILE* _fp;
	char _strName[100];
	vector<string> _vScripts;
	RECT story;
	image* _story;
	image* _face;
	image* Nebi;
	image* Nebi2;
	image* mouse;
	FONTVERSION _fontNum, _fontNum2;

	sceneBattle* _sB;
	float time; //안내창 등장 시간
	float Mtime; //마우스 프레임 시간
	int next;
	bool isleft;
	int Direction;
	char tmpName[100];
public:
	scanDialog();
	~scanDialog();

	HRESULT init(const char* filename);
	void release(void);
	void update(void);
	void render(void);

	void loadDialog(void);
	
	void nextFile(const char* filename);


public:
	
	void setAddressLinkBattle(sceneBattle* _sb) { _sB = _sb; }
	inline int getNext(void) { return next; }
	inline void setNext(int nt) { next = nt; }
	inline float getTime(void) { return time; }
	inline int getDirection(void){ return Direction; }
	inline void setDirection(int dr) { Direction = dr; }
};

