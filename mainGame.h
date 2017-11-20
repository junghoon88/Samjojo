#pragma once
#include "gameNode.h"


#include "Player.h"
#include "Friend.h"
#include "Enemy.h"

class mainGame : public gameNode
{
private:
	Player*		_player;	//�÷��̾�
	Friend*		_friend;	//�Ʊ�
	Enemy*		_enemy;		//����

private:
	void initScene(void);

public:
	virtual HRESULT init(void);		//�ʱ�ȭ
	virtual void release(void);		//�޸� ����
	virtual void update(void);		//�������(Ÿ�̸�)
	virtual void render(void);	//�׷��ִ� �Լ�
	
	mainGame();
	~mainGame();
};

