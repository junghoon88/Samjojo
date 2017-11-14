#pragma once
#include "gameNode.h"
#include "Unit.h"
#include "aStar.h"

class Enemy : public gameNode
{
private:
	vUnits _vUnits;

public:
	Enemy();
	~Enemy();

public:
	inline vUnits getUnits(void) { return _vUnits; }
};

