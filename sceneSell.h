#pragma once
#include "gameNode.h"
#include "Player.h"
#include "Enemy.h"
#include "Friend.h"
#include "button.h"

class sceneBuy;

class sceneSell : public gameNode
{
private:
	typedef vector<Item*>	vItems;
	typedef vector<Item*>::iterator	viItems;

	sceneBuy* _sBuy;
	Player* _player;
	image* _baseUI;
	image* _baseUI2;

	POINT _pt;
	FONTVERSION _fontNum;

	button* _EXIT;
	vItems _vItems;           //±¸¸ÅÇÑ³ðµé

	RECT _baseRC[2];
	RECT _listRC[12];

	float _messageTime;

	bool _sold;
	bool _base1;
	int _gold;
public:
	sceneSell();
	~sceneSell();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	static void selectExit(void* obj);

	void setLinkAdressPlayer(Player* player) { _player = player; }
	void setLinkAdressSceneBuy(sceneBuy* sbuy) { _sBuy = sbuy; }
	void exit(void);
};

