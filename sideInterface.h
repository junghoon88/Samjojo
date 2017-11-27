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

	void saveSequence(void);//Ű���� �޾Ƽ� ���̺� �ε� �� �� �ְ� �ϸ� �� ��?
	void loadSequence(void);//Ű���� �޾Ƽ� ���̺� �ε� �� �� �ְ� �ϸ� �� ��?
	void inventory(void);
	void unitList(void);
	void turnEndSequence(void);

	void setBattleScene(void);
	void setScenarioScene(void);
	void setShopScene(void);

};

