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
	enemyPhase // �� ������ ���� ����
};


class sceneBattle : public gameNode
{
private:
	Player*		_player;	//�÷��̾�
	Friend*		_friend;	//�Ʊ�
	Enemy*		_enemy;		//����

	gameMap*	_map;		//���� ��


	infoCursor* _cursor;	//Ŀ�� ����
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

