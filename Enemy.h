#pragma once
#include "gameNode.h"
#include "Unit.h"
#include "aStar.h"

class Player;
class Friend;
class gameMap;

class Enemy : public gameNode
{
private:
	vUnits		_vUnitsInFile;		//���� �� ���ֵ����͵� ��ü
	vUnits		_vUnits;			//������ �����Ǵ� ���ֵ�

	Player*		_player;	//�÷��̾�
	Friend*		_friend;	//�Ʊ�
	gameMap*	_map;

public:
	Enemy();
	~Enemy();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void loadUnits(void);
	void locateUnits(void);
	void deleteUnits(void);


public:
	inline vUnits getUnits(void) { return _vUnits; }

	inline void setLinkAdressPlayer(Player* player) { _player = player; }
	inline void setLinkAdressFriend(Friend* friends) { _friend = friends; }
	inline void setLinkAdressMap(gameMap* map) { _map = map; }
};

