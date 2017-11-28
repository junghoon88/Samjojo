#pragma once
#include "sceneReadybase.h"
#include "Player.h"
#include "Enemy.h"
#include "Friend.h"

class sceneSell : public sceneReadybase
{
private:



public:
	sceneSell();
	~sceneSell();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

};

