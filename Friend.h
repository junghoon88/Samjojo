#pragma once
#include "gameNode.h"
#include "Unit.h"

class Friend : public gameNode
{
private:
	vUnits _vUnits;

public:
	Friend();
	~Friend();

public:
	inline vUnits getUnits(void) { return _vUnits; }
};

