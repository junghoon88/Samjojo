#pragma once
#include "gameNode.h"

class sceneStory : public gameNode
{
public:
	sceneStory();
	~sceneStory();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

};

