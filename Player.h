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

public:
	inline vUnits getUnits(void) { return _vUnits; }
};

