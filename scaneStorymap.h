#pragma once
#include "gameNode.h"
#include "scanDialog.h"

//Ÿ�� �԰�
#define STILESIZEX 8
#define STILESIZEY 4

//Ÿ�ϰ���
#define STILEX 200
#define STILEY 200

#define STILESIZEXHALF STILESIZEX/2
#define STILESIZEYHALF STILESIZEY/2

struct tagIso
{
	int x;
	int y;
	POINT poly[4];
	HRGN region;
};
class scaneStorymap : public gameNode
{

private:
	
	scanDialog* sDl;


	tagIso iso[STILEX][STILEY];
	image* storymap;
	image* test;
	image* test1;

	int x, y;
public:
	scaneStorymap();
	~scaneStorymap();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void setAdreessLinkDialog(scanDialog* sD) { sDl = sD; }
};

