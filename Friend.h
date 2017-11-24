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

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void loadUnits(void);
	void deleteUnits(void);


public:
	inline vUnits getUnits(void) { return _vUnits; }
};

