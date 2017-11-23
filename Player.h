#pragma once
#include "gameNode.h"
#include "Unit.h"


class Player : public gameNode
{
private:
	vUnits _vUnits;

public:
	Player();
	~Player();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void loadUnits(void);

public:
	inline vUnits getUnits(void) { return _vUnits; }
};

