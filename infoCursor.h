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

	RECT rc;//���� ������ �ڽ�
	RECT drawLine;//Ÿ�� �׵θ� ǥ�ÿ�
	TCHAR* unit;
	TCHAR* tilename;
	TCHAR* prop;

	//���� ������ ǥ�ÿ� ���� ����
	bool fire;
	bool wind;
	bool earth;
	bool water;
	//���� ������ ǥ�ÿ�


	bool isUnit;//Unit�� true. ������ false
	bool isShow;//Ŭ���ϸ� true��

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

