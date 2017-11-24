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

	RECT rc;//���� ������ �ڽ�
	RECT drawLine;//Ÿ�� �׵θ� ǥ�ÿ�
	HPEN linePen,oPen;

	RECT tileImgRect;
	RECT unitImgRect;
	
	//���� ���� ǥ�ÿ�
	TCHAR* unit;
	TCHAR* utype;//Ŭ����
	TCHAR* faction;//����(�Ʊ�����)
	TCHAR* land;//������ ���� ��
	TCHAR* showExp;//�÷��̾�� �Ʊ�������� ����ġ ǥ�õ�
	
	int bonus;//���� ���� ���� ������ ����ǥ��
	int exp;
	int lv;
	int curHp, maxHp;
	int curMp, maxMp;
	//���� ���� ǥ�ÿ�

	//���� ���� ǥ�ÿ�
	TCHAR* tilename;
	TCHAR* prop;
	bool fire;
	bool wind;
	bool earth;
	bool water;
	//���� ���� ǥ�ÿ�


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
	void Scanning(void);
	void Click(void);
};

