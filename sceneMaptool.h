#pragma once
#include "gameNode.h"
#include "tileNode.h"
#include "button.h"

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

class sceneMaptool : public gameNode
{
private:
	int _selectSampleIndex;
	tagSampleTile _sampleTiles[SAMPLETILEX * SAMPLETILEY];
	tagTile _tiles[TILEX * TILEY];

	button* _ctrlButton[CTRL_END];
	TCHAR _strButton[CTRL_END][100];
	int _ctrSelect;

private:
	static void ctrlSelectSave(void* obj);
	static void ctrlSelectLoad(void* obj);
	static void ctrlSelectTerrain(void* obj);
	static void ctrlSelectObject(void* obj);
	static void ctrlSelectEraser(void* obj);


	void setup(void);
	void setMap(void);


public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	sceneMaptool();
	~sceneMaptool();


	void save(void);
	void load(void);

	TERRAIN terrainSelect(int index);
	OBJECT objSelect(int index);

	inline int getCtrlSelect(void) { return _ctrSelect; }
	inline void setCtrlSelect(int select) { _ctrSelect = select; }

	inline tagSampleTile* getSampleTile(void) { return _sampleTiles; }
};

