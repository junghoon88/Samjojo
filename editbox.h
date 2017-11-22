#pragma once
#include "gameNode.h"
#include "mainGame.h"

class editbox : public gameNode
{
private:
	RECT _rc;
	TCHAR _str[100];
	bool _clicked;
	bool _onlyNum;
	image* _img;
	HBRUSH _hBrushGray;
	HBRUSH _hBrushWhite;
	int _minNum;
	int _maxNum;

public:
	editbox();
	~editbox();

	HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(int textOffsetX = 0, int textOffsetY = 0);
	virtual void getChar(WPARAM wParam);

	bool scanNum(void);
	bool scanChar(void);
	void scanDelete(void);
	void scanAll(void);



public:
	inline void setRect(RECT rc) { _rc = rc; }
	inline RECT getRect(void) { return _rc; }
	inline TCHAR* getStr(void) { return _str; }
	inline int getStrNum(void) { return _wtoi(_str); }
	inline bool getClicked(void) { return _clicked; }
	inline void setClicked(bool click) { _clicked = click; }
	inline void setOnlyNum(bool onlynum) { _onlyNum = onlynum; }
	inline void setImage(image* img) { _img = img; }
	inline image* getImage(void) { return _img; }
	inline void clearStr(void) { _stprintf(_str, L""); }

	inline void setMin(int num) { _minNum = num; }
	inline void setMax(int num) { _maxNum = num; }
	inline void setMinMax(int min, int max) { _minNum = min; _maxNum = max; }

	
};

