#pragma once
#include "gameNode.h"
#include "Player.h"
#include "Enemy.h"
#include "Friend.h"
#include "gameMap.h"
#include "battleSceneInterface.h"
#include "aStar.h"
#include "scanDialog.h"

enum BATTLEPHASE
{
	BATTLEPHASE_NONE = -1,
	BATTLEPHASE_PLAYER,
	BATTLEPHASE_FRIEND,
	BATTLEPHASE_ENEMY, // �� ������ ���� ����

	BATTLEPHASE_VICTORY,
	BATTLEPHASE_DEFEAT,

	BATTLEPHASE_MAX
};
enum BATLLESTORY
{
	BATTLESTORY_1,
	BATTLESTORY_2,
	BATTLESTORY_3,
	BATTLESTORY_4,
	BATTLESTORY_5,

	BATTLESTORY_MAX
};

class sceneBattle : public gameNode
{
private:
	Player*		_player;	//�÷��̾�
	Friend*		_friend;	//�Ʊ�
	Enemy*		_enemy;		//����
	gameMap*	_map;		//���� ��
	battleSceneInterface* _interface;	//Ŀ�� ����


	BATTLEPHASE	_phase;
	int _turn; //�� �����Ȳ
	int _eventAcc;
	bool		_phaseChanging;
	float		_phaseChangeTime;


	aStar*		_astar;		//a* �� �������� �������� �����ϰ�, �� ���ֿ��� �Ҵ�޾Ƽ� ���� ������ ����.
	scanDialog* _sDL;

	BATLLESTORY _battlestory;
	bool		_isDialog;
	bool		_loadDialog;
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
	inline void setDialog(bool isDialog) { _isDialog = isDialog; }
	
	Unit* findUnit(TEAM team, POINT pt);
	void friendAction(void);
	void enemyAction(void);
	void phaseCheck(void);
	void linkClass(void);
	void setUpBattle(void);
	void checkEvent(void);
	void unhideEnemy(void);
};

