#pragma once
#include "gameNode.h"
#include "button.h"
#include "Player.h"
#include "Enemy.h"
#include "Friend.h"

enum BTNSELECT1
{
	BTNSELECT1_GAMESTART,
	BTNSELECT1_MAPTOOL,
	BTNSELECT1_UNITEDITOR,
	BTNSELECT1_EXIT,

	BTNSELECT1_MAX
};

enum BTNSELECT2
{
	BTNSELECT2_SCENARIO1,
	BTNSELECT2_MAX
};

class sceneSelect : public gameNode
{
private:
	image*		_background;						//배경이미지
	int			_selectLevel;						//선택화면 레벨


	button*		_button1[BTNSELECT1_MAX];
	TCHAR		_strButton1[BTNSELECT1_MAX][100];
		
	button*		_button2[BTNSELECT2_MAX];
	TCHAR		_strButton2[BTNSELECT2_MAX][100];

		
		
	int			_scenarioNum;	//선택 시나리오 번호
		
	Player*		_player;	//플레이어
	Friend*		_friend;	//아군
	Enemy*		_enemy;		//적군

	
private:
	void setuptButtons(void);

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	sceneSelect();
	~sceneSelect();

public:
	inline void setLinkAdressPlayer(Player* player) { _player = player; }
	inline void setLinkAdressEnemy(Enemy* enemy) { _enemy = enemy; }
	inline void setLinkAdressFriend(Friend* friends) { _friend = friends; }

	inline void setNextLevel(void) { _selectLevel = 1; }
	inline void setPrevLevel(void) { _selectLevel = 0; }


public:
	static void cbFuncGameStart(void* obj);
	static void cbFuncMaptool(void* obj);
	static void cbFuncUnitEditor(void* obj);
	static void cbFuncGameExit(void* obj);
};

