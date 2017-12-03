#pragma once
#include "gameNode.h"

class sceneResult : public gameNode
{
private:
	image* _background;

public:
	sceneResult();
	~sceneResult();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};

