#pragma once
#include "gameNode.h"
#include "Unit.h"
#include "Item.h"
#define ENTRANT_MAX	7

class Friend;
class Enemy;
class gameMap;
class battleSceneInterface;

class Player : public gameNode
{
private:
	typedef vector<Item*>	vItems;
	typedef vector<Item*>::iterator	viItems;

private:
	vUnits		_vUnitsInFile;		//���� �� ���ֵ����͵� ��ü
	vUnits		_vUnits;			//������ �����Ǵ� ���ֵ�
	vItems		_vItems;

	int			_kongNum;			//�� ����

	Friend*		_friend;			//�Ʊ�
	Enemy*		_enemy;				//����
	gameMap*	_map;

	battleSceneInterface* info;

	int _gold;

public:
	Player();
	~Player();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void loadUnits(void);
	void registUnitAll(void);
	void registUnitBasic(void);
	void registUnit(Unit* unit);	//���������߿��� ������ ���� ���
	void cancleUnit(int num);		//���������߿��� ����� ����
	void locateUnits(void);
	void deleteUnits(void);

	void eatKong(Unit* player, Unit* opponent);

private:
	Unit* findUnit(TCHAR* name);
	void UnitLiveCheck(void);

public:
	inline vUnits getUnits(void) { return _vUnits; }
	inline void setUnits(vUnits vunits) { _vUnits = vunits; }
	inline vUnits getUnitsInFile(void) { return _vUnitsInFile; }
	inline vItems getItems(void) { return _vItems; }
	inline void setItems(vItems items) { _vItems = items; }
	inline void setLinkAdressFriend(Friend* friends) { _friend = friends; }
	inline void setLinkAdressEnemy(Enemy* enemy) { _enemy = enemy; }
	inline void setLinkAdressMap(gameMap* map) { _map = map; }
	inline void setLinkAdressUI(battleSceneInterface* cursor) { info = cursor; }
	inline int getGold(void) { return _gold; }
	inline void setGold(int gold) { _gold = gold; }
	inline int getKong(void) { return _kongNum; }
	inline void setKong(int kong) { _kongNum = kong; }
};

