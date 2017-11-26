#pragma once
#include "gameNode.h"
#include "loading.h"
#include "tileNode.h"

#define UNITSIZE_ATKX 256
#define UNITSIZE_ATKY 256
#define UNITFRAME_ATKX 4
#define UNITFRAME_ATKY 4

#define UNITSIZE_IDLEX 240
#define UNITSIZE_IDLEY 96
#define UNITFRAME_IDLEX 4
#define UNITFRAME_IDLEY 2

#define UNITSIZE_SPCX 288
#define UNITSIZE_SPCY 48
#define UNITFRAME_SPCX 6
#define UNITFRAME_SPCY 1



class sceneInit : public gameNode
{
private:
	loading* _loading;

private:
	void initImage(void);
	void initSound(void);


	void initImageSlect(void);
	void initImageMapTool(void);
	void initImageUnitEditor(void);

	void initImageStory(void);

	void initImageUnits(void);

	void initImageUI(void);

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);


	sceneInit();
	~sceneInit();
};

