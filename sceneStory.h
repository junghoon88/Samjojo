#pragma once
#include "gameNode.h"
#include "scanDialog.h"
#include "scaneStorymap.h"

class sceneStory : public gameNode
{
private:
	scanDialog* _dialog;
	scaneStorymap* _sSmap;
	
	

public:
	sceneStory();
	~sceneStory();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

};

