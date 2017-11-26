#pragma once
#include "gameNode.h"
#include "scanDialog.h"

//Ÿ�� �԰�
#define STILESIZEX 16
#define STILESIZEY 10

//Ÿ�ϰ���
#define STILEX 100
#define STILEY 100

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

public:
	scaneStorymap();
	~scaneStorymap();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

};

