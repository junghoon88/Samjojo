#pragma once
#include "gameNode.h"
#include "scanDialog.h"

//타일 규격
#define STILESIZEX 8
#define STILESIZEY 4

#define CHARMAX 11
//타일갯수
#define STILEX 200
#define STILEY 200

#define STILESIZEXHALF STILESIZEX/2
#define STILESIZEYHALF STILESIZEY/2
enum Direction
{
	STORY_DIRECTION_UP,
	STORY_DIRECTION_DOWN,
	STORY_DIRECTION_LEFT,
	STORY_DIRECTION_RIGHT,
	STORY_MOVE
};
struct tagIso
{
	int x;
	int y;
};
struct tagChar
{
	int x;
	int y;
	image* etc;
};
class scaneStorymap : public gameNode
{

private:
	
	scanDialog* sDl;


	tagIso iso[STILEX][STILEY];
	image* storymap;
	tagChar img[CHARMAX];
	Direction dir;
	float time;
	int x, y;
	
public:
	scaneStorymap();
	~scaneStorymap();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void jojomove(void);
	void setAdreessLinkDialog(scanDialog* sD) { sDl = sD; }
};

