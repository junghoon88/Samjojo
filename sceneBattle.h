#pragma once
#include "gameNode.h"
#include "Player.h"
#include "Enemy.h"
#include "Friend.h"
#include "gameMap.h"
#include "infoCursor.h"
#include "aStar.h"

enum tagPhase
{
	playerPhase,
	alliPhase,
	enemyPhase // 이 순으로 전투 진행
};


class sceneBattle : public gameNode
{
private:
	Player*		_player;	//플레이어
	Friend*		_friend;	//아군
	Enemy*		_enemy;		//적군
	gameMap*	_map;		//게임 맵
	infoCursor* _cursor;	//커서 정보



	tagPhase	_phase;
	int _turn; //턴 진행상황


	aStar*		_astar;		//a* 을 전투씬에 공용으로 선언하고, 각 유닛에서 할당받아서 쓰고 싶을때 쓴다.

private:
	void initImage(void);
	void initSound(void);

public:
	sceneBattle();
	~sceneBattle();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

private:
	POINT findCloseEnemyPos(Unit* unit);
public:


public:
	inline void setLinkAdressPlayer(Player* player) { _player = player; }
	inline void setLinkAdressEnemy(Enemy* enemy) { _enemy = enemy; }
	inline void setLinkAdressFriend(Friend* friends) { _friend = friends; }
	inline void setLinkAdressMap(gameMap* map) { _map = map; }

	Unit* findUnit(TEAM team, POINT pt);
	void phaseControl(void);
	void linkClass(void);
};

