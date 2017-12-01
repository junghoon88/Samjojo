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
	int _pwr;		//����
	int _lds;		//���
	int _int;		//����
	int _dex;		//��ø
	int _luk;		//���

	int _hpMax;
	int _mpMax;
	int _exp;
	int _atk;		//���ݷ�
	int _dep;		//����
	int _res;		//���ŷ�
	int _agl;		//���߷�
	int _fig;		//���
	int _move;      //�̵���


	POINT _pt;

	RECT _rcCancel;
	RECT _rcOK;

	vUnits _vUnits;
	vUnits _vUnitsInFile;

	tagPos _posUnits[7];
	RECT posRC2[7];  //��������Ʈ���� �����ϱ����� Ŭ���� rect

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

