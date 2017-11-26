#pragma once
#include "gameNode.h"
#include "Unit.h"
#include "aStar.h"

class infoCursor; //벡터정보 직접 전달용

class Enemy : public gameNode
{
private:
	vUnits _vUnits;

	infoCursor* info;

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
	inline void setLinkCursor(infoCursor* cursor) { info = cursor; }
};

