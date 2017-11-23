#pragma once
#include "gameNode.h"
#include "button.h"
#include "Player.h"
#include "Enemy.h"
#include "Friend.h"

enum SELECTLEVEL
{
	SELECTLEVEL1,
	SELECTLEVEL2
};

enum BTNSELECT1
{
	BTNSELECT1_GAMESTART,
	BTNSELECT1_MAPTOOL,
	BTNSELECT1_UNITEDITOR,
	BTNSELECT1_EXIT,

	BTNSELECT1_MAX
};

#define SCENARIO_MAX 58

class sceneSelect : public gameNode
{
private:
	image*		_background;						//배경이미지
	SELECTLEVEL	_selectLevel;						//선택화면 레벨


	button*		_button1[BTNSELECT1_MAX];
	TCHAR		_strButton1[BTNSELECT1_MAX][100];
		
	button*		_button2[SCENARIO_MAX + 1];
	TCHAR		_strButton2[SCENARIO_MAX + 1][100];

		
			
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

	void selectScenario(void);

public:
	inline void setLinkAdressPlayer(Player* player) { _player = player; }
	inline void setLinkAdressEnemy(Enemy* enemy) { _enemy = enemy; }
	inline void setLinkAdressFriend(Friend* friends) { _friend = friends; }

	inline void setNextLevel(void) { _selectLevel = SELECTLEVEL2; }
	inline void setPrevLevel(void) { _selectLevel = SELECTLEVEL1; }


public:
	//level1
	static void cbFuncGameStart(void* obj);
	static void cbFuncMaptool(void* obj);
	static void cbFuncUnitEditor(void* obj);
	static void cbFuncGameExit(void* obj);

	//level2
	static void cbFuncSelect(void* obj);
	static void cbFuncPrev(void* obj);
};

