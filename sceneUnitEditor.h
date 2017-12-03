#pragma once
#include "gameNode.h"
#include "Unit.h"
#include "button.h"
#include "editbox.h"


#define UPDATEPOSX 16
#define UPDATEPOSY 16

#define FILENAME_STARTX		UPDATEPOSX
#define FILENAME_STARTY		300
#define FILENAME_WIDTH		100
#define FILENAME_HEIGHT		30

#define RANGESIZEX	UNIT_ATTACK_RANGE_MAX
#define RANGESIZEY	UNIT_ATTACK_RANGE_MAX
#define TILEWIDTH	48
#define TILEHEIGHT	48

struct tagTeamInfo
{
	RECT rc;
	image* img;
	TCHAR str[100];
	bool clicked;
};


struct tagUnitFileInfo
{
	RECT rc;
	image* img;
	TCHAR str[100];
	bool clicked;
};


struct tagRange
{
	RECT rc;
	bool clicked;
};


enum UNITEDITOR_BUTTON
{
	UNITEDITOR_BUTTON_LABEL_FILELIST,

	UNITEDITOR_BUTTON_LABEL_NAME,		//이름
	
	UNITEDITOR_BUTTON_LABEL_FAMILY,
	UNITEDITOR_BUTTON_LABEL_AOS,

	UNITEDITOR_BUTTON_LABEL_INIT,

	UNITEDITOR_BUTTON_LABEL_HP,
	UNITEDITOR_BUTTON_LABEL_MP,

	UNITEDITOR_BUTTON_LABEL_ATK,
	UNITEDITOR_BUTTON_LABEL_DEP,
	UNITEDITOR_BUTTON_LABEL_RES,
	UNITEDITOR_BUTTON_LABEL_AGL,
	UNITEDITOR_BUTTON_LABEL_FIG,

	UNITEDITOR_BUTTON_LABEL_PWR,
	UNITEDITOR_BUTTON_LABEL_LDS,
	UNITEDITOR_BUTTON_LABEL_INT,
	UNITEDITOR_BUTTON_LABEL_DEX,
	UNITEDITOR_BUTTON_LABEL_LUK,


	UNITEDITOR_BUTTON_LABEL_ENTERSCENARIO,

	UNITEDITOR_BUTTON_LABEL_LV,
	UNITEDITOR_BUTTON_LABEL_MOVE,

	UNITEDITOR_BUTTON_LABEL_LVPER,

	UNITEDITOR_BUTTON_LABEL_LVPERHP,
	UNITEDITOR_BUTTON_LABEL_LVPERMP,

	UNITEDITOR_BUTTON_LABEL_LVPERATK,
	UNITEDITOR_BUTTON_LABEL_LVPERDEP,
	UNITEDITOR_BUTTON_LABEL_LVPERRES,
	UNITEDITOR_BUTTON_LABEL_LVPERAGL,
	UNITEDITOR_BUTTON_LABEL_LVPERFIG,

	UNITEDITOR_BUTTON_LABEL_LVPERPWR,
	UNITEDITOR_BUTTON_LABEL_LVPERLDS,
	UNITEDITOR_BUTTON_LABEL_LVPERINT,
	UNITEDITOR_BUTTON_LABEL_LVPERDEX,
	UNITEDITOR_BUTTON_LABEL_LVPERLUK,


	UNITEDITOR_BUTTON_LABEL_RANGE,


	//UNITEDITOR_BUTTON_LABEL_WEAPON,
	//UNITEDITOR_BUTTON_LABEL_ARMOR,
	//UNITEDITOR_BUTTON_LABEL_SUBITEM,


	UNITEDITOR_BUTTON_LABEL_FILENAME,


	UNITEDITOR_BUTTON_DATA_NEW,			//새 영웅 만들기
	UNITEDITOR_BUTTON_DATA_LOAD,		//영웅 데이터 불러오기
	UNITEDITOR_BUTTON_DATA_SAVE,		//영웅 데이터 저장하기
	UNITEDITOR_BUTTON_DATA_EXIT,		//메뉴로

	UNITEDITOR_BUTTON_FACE_PREV,		//얼굴 이전 이미지
	UNITEDITOR_BUTTON_FACE_NEXT,		//얼굴 다음 이미지

	//UNITEDITOR_BUTTON_NORMAL_PREV,		//대화 이전 이미지
	//UNITEDITOR_BUTTON_NORMAL_NEXT,		//대화 다음 이미지
	
	UNITEDITOR_BUTTON_COMBAT_PREV,		//전투 이전 이미지
	UNITEDITOR_BUTTON_COMBAT_NEXT,		//전투 다음 이미지
	
	//UNITEDITOR_BUTTON_WEAPON_PREV,		//무기 이전 이미지
	//UNITEDITOR_BUTTON_WEAPON_NEXT,		//무기 다음 이미지
	//
	//UNITEDITOR_BUTTON_ARMOR_PREV,		//방어구 이전 이미지
	//UNITEDITOR_BUTTON_ARMOR_NEXT,		//방어구 다음 이미지
	//
	//UNITEDITOR_BUTTON_SUBITEM_PREV,		//보조 이전 이미지
	//UNITEDITOR_BUTTON_SUBITEM_NEXT,		//보조 다음 이미지

	UNITEDITOR_BUTTON_MAX
};

//ctl + shift + u 대문자로
enum UNITEDITOR_NUMEDITBOX
{
	UNITEDITOR_NUMEDITBOX_DATA_HP,
	UNITEDITOR_NUMEDITBOX_DATA_MP,

	UNITEDITOR_NUMEDITBOX_DATA_ATK,
	UNITEDITOR_NUMEDITBOX_DATA_DEP,
	UNITEDITOR_NUMEDITBOX_DATA_RES,
	UNITEDITOR_NUMEDITBOX_DATA_AGL,
	UNITEDITOR_NUMEDITBOX_DATA_FIG,

	UNITEDITOR_NUMEDITBOX_DATA_PWR,
	UNITEDITOR_NUMEDITBOX_DATA_LDS,
	UNITEDITOR_NUMEDITBOX_DATA_INT,
	UNITEDITOR_NUMEDITBOX_DATA_DEX,
	UNITEDITOR_NUMEDITBOX_DATA_LUK,


	UNITEDITOR_NUMEDITBOX_DATA_ENTERSCENARIO,

	UNITEDITOR_NUMEDITBOX_DATA_LV,
	UNITEDITOR_NUMEDITBOX_DATA_MOVE,
	
	UNITEDITOR_NUMEDITBOX_DATA_LVPERHP,
	UNITEDITOR_NUMEDITBOX_DATA_LVPERMP,

	UNITEDITOR_NUMEDITBOX_DATA_LVPERATK,
	UNITEDITOR_NUMEDITBOX_DATA_LVPERDEP,
	UNITEDITOR_NUMEDITBOX_DATA_LVPERRES,
	UNITEDITOR_NUMEDITBOX_DATA_LVPERAGL,
	UNITEDITOR_NUMEDITBOX_DATA_LVPERFIG,

	UNITEDITOR_NUMEDITBOX_DATA_LVPERPWR,
	UNITEDITOR_NUMEDITBOX_DATA_LVPERLDS,
	UNITEDITOR_NUMEDITBOX_DATA_LVPERINT,
	UNITEDITOR_NUMEDITBOX_DATA_LVPERDEX,
	UNITEDITOR_NUMEDITBOX_DATA_LVPERLUK,


	UNITEDITOR_NUMEDITBOX_MAX
};

enum UNITEDITOR_STREDITBOX
{
	UNITEDITOR_STREDITBOX_DATA_NAME,
	UNITEDITOR_STREDITBOX_DATA_FAMILY,
	UNITEDITOR_STREDITBOX_DATA_AOS,

	UNITEDITOR_STREDITBOX_DATA_FILENAME,

	UNITEDITOR_STREDITBOX_MAX
};


class sceneUnitEditor : public gameNode
{
private:
	tagUnitSaveInfo	_unitInfo;
	//Unit* _unit;


	TEAM _team;
	tagTeamInfo _teamButton[TEAM_MAX];

	button* _ctrlButton[UNITEDITOR_BUTTON_MAX];
	
	editbox* _numEditBox[UNITEDITOR_NUMEDITBOX_MAX];
	editbox* _strEditBox[UNITEDITOR_STREDITBOX_MAX];

	TCHAR* _filename;

	tagRange _atkRange[RANGESIZEX][RANGESIZEY];

	image* _imgFace;
	image* _imgBattleAtk;
	image* _imgBattleIdle;
	image* _imgBattleSpc;

	image* _bgImage;

	bool _exit;


private:
	//기존 파일들 스캔
	vector<tagUnitFileInfo> _vUnits;
	void loadUnitFiles(void);
	HBRUSH hBrushNon;
	HBRUSH hBrushSelect;

	HBRUSH hBrushRange;
	HBRUSH hBrushPlayer;
	HBRUSH hBrushAttack;

	FONTVERSION _fontNum;
	FONTVERSION _labelFontNum;

private:
	int _faceNum;
	int _normalNum;
	int _combatNum;
	int _weaponNum;
	int _armorNum;
	int _subitemNum;


private:
	static void ctrlSelectDataNew(void* obj);
	static void ctrlSelectDataLoad(void* obj);
	static void ctrlSelectDataSave(void* obj);
	static void ctrlSelectExit(void* obj);

	static void ctrlSelectFacePrev(void* obj);
	static void ctrlSelectFaceNext(void* obj);

	static void ctrlSelectNormalPrev(void* obj);
	static void ctrlSelectNormalNext(void* obj);

	static void ctrlSelectCombatPrev(void* obj);
	static void ctrlSelectCombatNext(void* obj);

	static void ctrlSelectWeaponPrev(void* obj);
	static void ctrlSelectWeaponNext(void* obj);

	static void ctrlSelectArmorPrev(void* obj);
	static void ctrlSelectArmorNext(void* obj);

	static void ctrlSelectSubitemPrev(void* obj);
	static void ctrlSelectSubitemNext(void* obj);

	static void cbFuncChangeTeamPlayer(void* obj);
	static void cbFuncChangeTeamFriend(void* obj);
	static void cbFuncChangeTeamEnemy(void* obj);


public:
	sceneUnitEditor();
	~sceneUnitEditor();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void getChar(WPARAM wParam);

public:
	void initImage(void);
	void initButton(void);
	void initValues(void);
	void initEditbox(void);
	void initRangeRect(void);
	void initTeamButton(void);

public:
	void filesUpdate(void);
	void teamButtonUpdate(void);

public:
	void rectSketch(void);
	void editBoxRender(void);
	void unitImageRender(void);
	void atkRangeRender(void);
	void filesRender(void);
	void teamButtonRender(void);

	void newUnit(void);
	void loadUnit(void);
	void saveUnit(void);

	void selectImgFace(void);
	void selectImgBattleAtk(void);
	void selectImgBattleIdle(void);
	void selectImgBattleSpc(void);


public:
	inline void setFacePrev(void) { _faceNum = _faceNum == 0 ? FACE_MAX : _faceNum - 1; }
	inline void setFaceNext(void) { _faceNum = _faceNum == FACE_MAX ? 0 : _faceNum + 1; }

	inline void setNormalPrev(void) { _normalNum = _normalNum == 0 ? UNIT_BATTLE_IMAGE_MAX - 1 : _normalNum - 1; }
	inline void setNormalNext(void) { _normalNum = _normalNum == UNIT_BATTLE_IMAGE_MAX - 1 ? 0 : _normalNum + 1; }

	inline void setCombatPrev(void) { _combatNum = _combatNum == 0 ? COMBAT_IMAGE_MAX : _combatNum - 1; }
	inline void setCombatNext(void) { _combatNum = _combatNum == COMBAT_IMAGE_MAX ? 0 : _combatNum + 1; }

	inline void setWeaponPrev(void) { _weaponNum = _weaponNum == 0 ? WEAPON_IMAGE_MAX : _weaponNum - 1; }
	inline void setWeaponNext(void) { _weaponNum = _weaponNum == WEAPON_IMAGE_MAX ? 0 : _weaponNum + 1; }

	inline void setArmorPrev(void) { _armorNum = _armorNum == 0 ? ARMOR_IMAGE_MAX : _armorNum - 1; }
	inline void setArmorNext(void) { _armorNum = _armorNum == ARMOR_IMAGE_MAX ? 0 : _armorNum + 1; }

	inline void setSubitemPrev(void) { _subitemNum = _subitemNum == 0 ? SUBITEM_IMAGE_MAX : _subitemNum - 1; }
	inline void setSubitemNext(void) { _subitemNum = _subitemNum == SUBITEM_IMAGE_MAX ? 0 : _subitemNum + 1; }

	inline void setExit(void) { _exit = true; }
};

