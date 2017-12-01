#pragma once
#include "gameNode.h"
#include "Player.h"
#include "Enemy.h"
#include "Friend.h"
#include "button.h"
struct tagPos {
	TCHAR name[32];
	RECT posRC;
	bool isPos;
};

class scenePos : public gameNode
{
private:
	image* _posImg;
	image* _chosang;
	TCHAR _name[32];
	TCHAR _aos[32];
	int _level;
	int _pwr;		//무력
	int _lds;		//통솔
	int _int;		//지력
	int _dex;		//민첩
	int _luk;		//행운

	int _hpMax;
	int _mpMax;
	int _exp;
	int _atk;		//공격력
	int _dep;		//방어력
	int _res;		//정신력
	int _agl;		//순발력
	int _fig;		//사기
	int _move;      //이동력


	POINT _pt;

	RECT _rcCancel;
	RECT _rcOK;

	vUnits _vUnits;
	vUnits _vUnitsInFile;

	tagPos _posUnits[7];
	RECT posRC2[7];  //출진리스트에서 제거하기위한 클릭용 rect

	Player* _player;

	bool _availableOK;
	bool _okClicking;
	bool _cancelClicking;


public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

public:
	void setLinkAdressPlayer(Player* player) { _player = player; }

	scenePos();
	~scenePos();
};

