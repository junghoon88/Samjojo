#pragma once
#include "gameNode.h"

enum BUTTONTYPE
{
	save, load,
	inven, unit,
	turnEnd
};

struct tagButton
{
	RECT rc;
	BUTTONTYPE type;
	bool onOff;
};


class sideInterface : public gameNode
{
private:
	RECT rc;
	tagButton button[5];

	

public:
	sideInterface();
	~sideInterface();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void saveSequence(void);//키값을 받아서 세이브 로드 할 수 있게 하면 될 듯?
	void loadSequence(void);//키값을 받아서 세이브 로드 할 수 있게 하면 될 듯?
	void inventory(void);
	void unitList(void);
	void turnEndSequence(void);

	void setBattleScene(void);
	void setScenarioScene(void);
	void setShopScene(void);

};

