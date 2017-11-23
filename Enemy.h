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

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void loadUnits(void);
	void deleteUnits(void);


public:
	inline vUnits getUnits(void) { return _vUnits; }
};

