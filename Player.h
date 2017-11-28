#pragma once
#include "gameNode.h"
#include "Unit.h"

class Friend;
class Enemy;
class gameMap;
class infoCursor;

class Player : public gameNode
{
private:
	vUnits		_vUnitsInFile;		//���� �� ���ֵ����͵� ��ü
	vUnits		_vUnits;			//������ �����Ǵ� ���ֵ�

	Friend*		_friend;	//�Ʊ�
	Enemy*		_enemy;		//����
	gameMap*	_map;

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
	inline void setUnits(vUnits vunits) { _vUnits = vunits; }
	inline vUnits getUnitsInFile(void) { return _vUnitsInFile; }

	inline void setLinkAdressFriend(Friend* friends) { _friend = friends; }
	inline void setLinkAdressEnemy(Enemy* enemy) { _enemy = enemy; }
	inline void setLinkAdressMap(gameMap* map) { _map = map; }
	inline void setLinkCursor(infoCursor* cursor) { info = cursor; }
};

