#pragma once
#include "gameNode.h"
#include "Unit.h"
#include "button.h"
#include "editbox.h"


#define UPDATEPOSX 100
#define UPDATEPOSY 0

#define FILENAME_STARTX		0
#define FILENAME_STARTY		100
#define FILENAME_WIDTH		100
#define FILENAME_HEIGHT		30

struct tagUnitFileInfo
{
	RECT rc;
	image* img;
	TCHAR str[100];
	bool clicked;
};


enum UNITEDITOR_BUTTON
{
	UNITEDITOR_BUTTON_LABEL_NAME,		//�̸�
	
	UNITEDITOR_BUTTON_LABEL_FAMILY,
	UNITEDITOR_BUTTON_LABEL_AOS,

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


	UNITEDITOR_BUTTON_LABEL_WEAPON,
	UNITEDITOR_BUTTON_LABEL_ARMOR,
	UNITEDITOR_BUTTON_LABEL_SUBITEM,


	UNITEDITOR_BUTTON_DATA_NEW,			//�� ���� �����
	UNITEDITOR_BUTTON_DATA_LOAD,		//���� ������ �ҷ�����
	UNITEDITOR_BUTTON_DATA_SAVE,		//���� ������ �����ϱ�
	UNITEDITOR_BUTTON_DATA_EXIT,		//�޴���

	UNITEDITOR_BUTTON_FACE_PREV,		//�� ���� �̹���
	UNITEDITOR_BUTTON_FACE_NEXT,		//�� ���� �̹���

	UNITEDITOR_BUTTON_NORMAL_PREV,		//��ȭ ���� �̹���
	UNITEDITOR_BUTTON_NORMAL_NEXT,		//��ȭ ���� �̹���
	
	UNITEDITOR_BUTTON_COMBAT_PREV,		//���� ���� �̹���
	UNITEDITOR_BUTTON_COMBAT_NEXT,		//���� ���� �̹���
	
	UNITEDITOR_BUTTON_WEAPON_PREV,		//���� ���� �̹���
	UNITEDITOR_BUTTON_WEAPON_NEXT,		//���� ���� �̹���
	
	UNITEDITOR_BUTTON_ARMOR_PREV,		//�� ���� �̹���
	UNITEDITOR_BUTTON_ARMOR_NEXT,		//�� ���� �̹���
	
	UNITEDITOR_BUTTON_SUBITEM_PREV,		//���� ���� �̹���
	UNITEDITOR_BUTTON_SUBITEM_NEXT,		//���� ���� �̹���

	UNITEDITOR_BUTTON_MAX
};

//ctl + shift + u �빮�ڷ�
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

	UNITEDITOR_STREDITBOX_MAX
};


class sceneUnitEditor : public gameNode
{
private:
	Unit* _unit;

	tagStatus _tempStatus;

	button* _ctrlButton[UNITEDITOR_BUTTON_MAX];
	TCHAR _strButton[UNITEDITOR_BUTTON_MAX][100];
	

	editbox* _numEditBox[UNITEDITOR_NUMEDITBOX_MAX];
	editbox* _strEditBox[UNITEDITOR_STREDITBOX_MAX];

	TCHAR* _filename;

private:
	//���� ���ϵ� ��ĵ
	vector<tagUnitFileInfo> _vUnits;
	void loadUnitFiles(void);
	HBRUSH hBrushWhite;
	HBRUSH hBrushBlue;

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


public:
	sceneUnitEditor();
	~sceneUnitEditor();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void getChar(WPARAM wParam);

public:
	void initButton(void);
	void initValues(void);
	void initEditbox(void);

public:
	void btnSetup(void);
	void rectSketch(void);
	void editBoxRender(void);
	void unitImageRender(void);

	void newUnit(void);
	void loadUnit(void);
	void saveUnit(void);

public:
	inline void setFacePrev(void) { _faceNum = _faceNum == 0 ? FACE_MAX : _faceNum - 1; }
	inline void setFaceNext(void) { _faceNum = _faceNum == FACE_MAX ? 0 : _faceNum + 1; }

	inline void setNormalPrev(void) { _normalNum = _normalNum == 0 ? NORMAL_IMAGE_MAX : _normalNum - 1; }
	inline void setNormalNext(void) { _normalNum = _normalNum == NORMAL_IMAGE_MAX ? 0 : _normalNum + 1; }

	inline void setCombatPrev(void) { _combatNum = _combatNum == 0 ? COMBAT_IMAGE_MAX : _combatNum - 1; }
	inline void setCombatNext(void) { _combatNum = _combatNum == COMBAT_IMAGE_MAX ? 0 : _combatNum + 1; }

	inline void setWeaponPrev(void) { _weaponNum = _weaponNum == 0 ? WEAPON_IMAGE_MAX : _weaponNum - 1; }
	inline void setWeaponNext(void) { _weaponNum = _weaponNum == WEAPON_IMAGE_MAX ? 0 : _weaponNum + 1; }

	inline void setArmorPrev(void) { _armorNum = _armorNum == 0 ? ARMOR_IMAGE_MAX : _armorNum - 1; }
	inline void setArmorNext(void) { _armorNum = _armorNum == ARMOR_IMAGE_MAX ? 0 : _armorNum + 1; }

	inline void setSubitemPrev(void) { _subitemNum = _subitemNum == 0 ? SUBITEM_IMAGE_MAX : _subitemNum - 1; }
	inline void setSubitemNext(void) { _subitemNum = _subitemNum == SUBITEM_IMAGE_MAX ? 0 : _subitemNum + 1; }
};

