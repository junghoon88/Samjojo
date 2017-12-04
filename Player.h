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
	vUnits		_vUnitsInFile;		//폴더 내 유닛데이터들 전체
	vUnits		_vUnits;			//전투에 출전되는 유닛들
	vItems		_vItems;

	int			_kongNum;			//콩 개수

	Friend*		_friend;			//아군
	Enemy*		_enemy;				//적군
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
	void registUnit(Unit* unit);	//파일유닛중에서 출전할 유닛 등록
	void cancleUnit(int num);		//출전유닛중에서 취소할 유닛
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

