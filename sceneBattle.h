#pragma once
#include "gameNode.h"
#include "Player.h"
#include "Enemy.h"
#include "Friend.h"
#include "gameMap.h"
#include "infoCursor.h"
#include "aStar.h"
#include "scanDialog.h"

enum tagPhase
{
	PLAYERPHASE,
	FRIENDPHASE,
	ENEMYPHASE // �� ������ ���� ����
};


class sceneBattle : public gameNode
{
private:
	Player*		_player;	//�÷��̾�
	Friend*		_friend;	//�Ʊ�
	Enemy*		_enemy;		//����
	gameMap*	_map;		//���� ��
	infoCursor* _cursor;	//Ŀ�� ����

	

	tagPhase	_phase;
	int _turn; //�� �����Ȳ


	aStar*		_astar;		//a* �� �������� �������� �����ϰ�, �� ���ֿ��� �Ҵ�޾Ƽ� ���� ������ ����.
	scanDialog* _sDL;
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
	void friendAction(void);
	void enemyAction(void);
	void phaseCheck(void);
	void linkClass(void);
};

