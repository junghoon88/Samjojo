#pragma once
#include "gameNode.h"

#include "Player.h"
#include "Friend.h"
#include "Enemy.h"
#include "gameMap.h"

class mainGame : public gameNode
{
private:
	Player*		_player;	//플레이어
	Friend*		_friend;	//아군
	Enemy*		_enemy;		//적군
	gameMap*	_map;

	bool		_stop;
	POINT		_winsize;

	float		_FPS;


private:
	void initScene(void);
	void checkWindowSize(void);
	void controlFPS(void);
	void playBGM(void);


public:
	virtual HRESULT init(void);		//초기화
	virtual void release(void);		//메모리 해제
	virtual void update(void);		//연산관련(타이머)
	virtual void render(void);	//그려주는 함수
	virtual void getChar(WPARAM wParam);

	mainGame();
	~mainGame();

	void setWindowResize(POINT size);

public:
	inline bool getStop(void) { return _stop; }
	inline void setStop(bool stop) { _stop = stop; }
	inline POINT getWinSize(void) { return _winsize; }

	inline float getFPS(void) { return _FPS; }
};

