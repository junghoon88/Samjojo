#pragma once
#include "gameNode.h"
#include "Player.h"
#include "Enemy.h"
#include "Friend.h"
#include "gameMap.h"
#include "infoCursor.h"

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
	tagPhase Phase;

private:
	void initImage(void);
	void initSound(void);

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);


	sceneBattle();
	~sceneBattle();

public:
	void setLinkAdressPlayer(Player* player) { _player = player; }
	void setLinkAdressEnemy(Enemy* enemy) { _enemy = enemy; }
	void setLinkAdressFriend(Friend* friends) { _friend = friends; }

	void phaseControl(void);

};

