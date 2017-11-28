#pragma once
#include "gameNode.h"
#include "tileNode.h"
#include "button.h"
#include "editbox.h"
#include <list>

enum CTRL
{
	CTRL_NONE = -1,
	CTRL_SAVE,
	CTRL_LOAD,
	CTRL_ERASER,
	CTRL_TERRAINDRAW,
	CTRL_OBJDRAW,

	CTRL_END = 3
};

struct CTRLSAVE
{
	tagTile tile[TILEX * TILEY];
	TCHAR fileName[100];
	TCHAR saveSize[100];

	int ctrSelect;
	int ctrObjectSelect;
	int selectSampleIndex;

	int countMapX;
	int countMapY;

	int selectSizeX, selectSizeY;

	float alphaValue;

	bool mapView;
	bool viewTERRAIN;
	bool isMapLoad;
};

class sceneMaptool : public gameNode
{
private:
	tagSampleTile _sampleTiles[SAMPLETILEX * SAMPLETILEY];
	tagSampleObject _objTiles[CTRL_END];
	tagTile _tiles[TILEX * TILEY];

	button* _ctrlButton[CTRL_END];
	button* _exit;
	TCHAR _fileName[100];
	TCHAR _saveSize[100];

	editbox* _editBox;
	editbox* _alphaValueBox;
	editbox* _tileObj;

	int _selectSampleIndex;

	int _ctrSelect;
	int _ctrObjectSelect;

	int _countMapX;
	int _countMapY;

	int _tileSizeX[6];
	int _tileSizeY[6];

	int _selectSizeX, _selectSizeY;

	float _alphaValue;

	bool _mapView;
	bool _viewTERRAIN;
	bool _isMapLoad;

	list<CTRLSAVE> _lSave;
	list<CTRLSAVE>::iterator _liSave;

	list<CTRLSAVE> _lBackUp;
	list<CTRLSAVE>::iterator _liBackUp;

private:
	static void ctrlSelectSave(void* obj);
	static void ctrlSelectLoad(void* obj);
	static void ctrlSelectTerrain(void* obj);
	static void ctrlSelectObject(void* obj);
	static void ctrlSelectEraser(void* obj);
	static void exit(void* obj);

	void setup(void);
	void setMap(void);

	void ctrlSave(void);
	void ctrlZ(void);
	void ctrlY(void);


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

	inline int getCtrlSelect(void) { return _ctrSelect; }
	inline void setCtrlSelect(int select) { _ctrSelect = select; }

	inline int getCtrlObjectSelect(void) { return _ctrObjectSelect; }
	inline void setCtrlObjectSelect(int ObjectSelect) { _ctrObjectSelect = ObjectSelect; }

	inline tagSampleTile* getSampleTile(void) { return _sampleTiles; }
};

