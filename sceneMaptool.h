#pragma once
#include "gameNode.h"
#include "tileNode.h"
#include "button.h"
#include "editbox.h"

enum CTRL
{
	CTRL_NONE = -1,
	CTRL_SAVE,
	CTRL_LOAD,
	CTRL_TERRAINDRAW,
	CTRL_OBJDRAW,
	CTRL_ERASER,

	CTRL_END
};

enum MAPTOOLEDITBOX
{

};

class sceneMaptool : public gameNode
{
private:
	int _selectSampleIndex;
	tagSampleTile _sampleTiles[SAMPLETILEX * SAMPLETILEY];
	tagSampleObject _objTiles[OBJECTSELECT_MAX];
	tagTile _tiles[TILEX * TILEY];

	button* _ctrlButton[CTRL_END];
	button* _objectSelect[OBJECTSELECT_MAX];
	TCHAR _strButton[CTRL_END][100];
	TCHAR _strObjectSelect[OBJECTSELECT_MAX][100];
	TCHAR _fileName[100];
	TCHAR _saveSize[100];

	editbox* _editBox;
	editbox* _alphaValueBox;
	editbox* _tileObj;

	int _ctrSelect;
	int _ctrObjectSelect;

	int _countX;
	int _countY;

	int _tileSizeX[6];
	int _tileSizeY[6];

	int _selectSizeX, _selectSizeY;

	float _alphaValue;

	bool _mapView;
	bool _viewTERRAIN;
	bool _isload;

private:
	static void ctrlSelectSave(void* obj);
	static void ctrlSelectLoad(void* obj);
	static void ctrlSelectTerrain(void* obj);
	static void ctrlSelectObject(void* obj);
	static void ctrlSelectEraser(void* obj);

	static void ctrlObjectSelectAily(void* obj);
	static void ctrlObjectSelectEnemy(void* obj);
	static void ctrlObjectSelectPlayer(void* obj);

	void setup(void);
	void setMap(void);


public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void getChar(WPARAM wParam);

	sceneMaptool();
	~sceneMaptool();


	void save(void);
	void load(void);

	TERRAIN terrainSelect(int index);
	OBJECT objSelect(int index);

	inline int getCtrlSelect(void) { return _ctrSelect; }
	inline void setCtrlSelect(int select) { _ctrSelect = select; }

	inline int getCtrlObjectSelect(void) { return _ctrObjectSelect; }
	inline void setCtrlObjectSelect(int ObjectSelect) { _ctrObjectSelect = ObjectSelect; }

	inline tagSampleTile* getSampleTile(void) { return _sampleTiles; }
};

