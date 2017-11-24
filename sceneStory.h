#pragma once
#include "gameNode.h"
#include "scanDialog.h"

class sceneStory : public gameNode
{
private:
	scanDialog* _dialog;

public:
	sceneStory();
	~sceneStory();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

};

