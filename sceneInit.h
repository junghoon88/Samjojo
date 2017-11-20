#pragma once
#include "gameNode.h"
#include "tileNode.h"

class sceneInit : public gameNode
{
private:
	void initImage(void);
	void initSound(void);


	void initImageMapTool(void);
	void initImageUnitEditor(void);

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);


	sceneInit();
	~sceneInit();
};

