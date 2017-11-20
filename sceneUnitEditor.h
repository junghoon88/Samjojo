#pragma once
#include "gameNode.h"
#include "Unit.h"
#include "button.h"
#include "editbox.h"

enum UNITEDITOR_BUTTON
{
	UNITEDITOR_BUTTON_LABEL_NAME,		//�̸�

	UNITEDITOR_BUTTON_DATA_NEW,			//�� ���� �����
	UNITEDITOR_BUTTON_DATA_LOAD,		//���� ������ �ҷ�����
	UNITEDITOR_BUTTON_DATA_SAVE,		//���� ������ �����ϱ�

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
enum UNITEDITOR_EDITBOX
{
	UNITEDITOR_EDITBOX_DATA_HP,
	UNITEDITOR_EDITBOX_DATA_MP,
	UNITEDITOR_EDITBOX_DATA_ATK,
	UNITEDITOR_EDITBOX_DATA_DEP,
	UNITEDITOR_EDITBOX_DATA_RES,
	UNITEDITOR_EDITBOX_DATA_AGL,
	UNITEDITOR_EDITBOX_DATA_FIG,
	UNITEDITOR_EDITBOX_DATA_PWR,
	UNITEDITOR_EDITBOX_DATA_LDS,
	UNITEDITOR_EDITBOX_DATA_INT,
	UNITEDITOR_EDITBOX_DATA_DEX,
	UNITEDITOR_EDITBOX_DATA_LUK,

	UNITEDITOR_EDITBOX_MAX
};

class sceneUnitEditor : public gameNode
{
private:
	Unit* _unit;

	button* _ctrlButton[UNITEDITOR_BUTTON_MAX];
	TCHAR _strButton[UNITEDITOR_BUTTON_MAX][100];


	//�ӽ�
	RECT _editBox[UNITEDITOR_EDITBOX_MAX];

	editbox* _editTest;


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

public:
	void initButton(void);
	void btnSetup(void);
	void rectSketch(void);

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

