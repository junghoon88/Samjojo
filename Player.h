#pragma once
#include "gameNode.h"
#include "Unit.h"

class infoCursor;
class Player : public gameNode
{
private:
	vUnits _vUnits;

	infoCursor* info;
public:
	Player();
	~Player();

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

