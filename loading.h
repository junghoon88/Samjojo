#pragma once
#include "gameNode.h"
#include "progressBar.h"

enum LOAD_KIND
{
	LOAD_KIND_IMAGE_0,		//이미지 초기화에 따른 열거
	LOAD_KIND_IMAGE_1,
	LOAD_KIND_IMAGE_2,
	LOAD_KIND_FRAMEIMAGE_0,
	LOAD_KIND_FRAMEIMAGE_1,
	LOAD_KIND_SOUND,
	LOAD_KIND_END
};

struct tagImageResource
{
	wstring keyName;
	const TCHAR* fileName;
	float x, y;
	int width, height;
	int frameX, frameY;
	bool trans;
	COLORREF transColor;
	bool blend;
};

class loadItem
{
private:
	LOAD_KIND _kind;
	tagImageResource _imageResource;

public:

	HRESULT initForImage(wstring keyName, int width, int height, bool blend = FALSE);
	HRESULT initForImage(wstring keyName, const TCHAR* fileName, int width, int height, BOOL trans = FALSE, COLORREF transColor = FALSE, bool blend = FALSE);
	HRESULT initForImage(wstring keyName, const TCHAR* fileName, float x, float y, int width, int height, BOOL trans = FALSE, COLORREF transColor = FALSE, bool blend = FALSE);

	HRESULT initForFrameImage(wstring keyName, const TCHAR* fileName, int width, int height, int frameX, int frameY, BOOL trans = FALSE, COLORREF transColor = FALSE, bool blend = FALSE);
	HRESULT initForFrameImage(wstring keyName, const TCHAR* fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL trans = FALSE, COLORREF transColor = FALSE, bool blend = FALSE);

	LOAD_KIND getLoadingKind() { return _kind; }

	tagImageResource getImageResource(void) { return _imageResource; }

	loadItem();
	~loadItem();
};

class loading : public gameNode
{
private:
	typedef vector<loadItem*> arrLoadItem;
	typedef vector<loadItem*>::iterator arrLoadItemIter;

private:
	arrLoadItem _vLoadImage;


	image* _background;
	progressBar* _loadingBar;

	int _currentGauge;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void loadImage(wstring keyName, int width, int height, bool blend = FALSE);
	void loadImage(wstring keyName, const TCHAR* fileName, int width, int height, BOOL trans = FALSE, COLORREF transColor = FALSE, bool blend = FALSE);
	void loadImage(wstring keyName, const TCHAR* fileName, float x, float y, int width, int height, BOOL trans = FALSE, COLORREF transColor = FALSE, bool blend = FALSE);
	void loadFrameImage(wstring keyName, const TCHAR* fileName, int width, int height, int frameX, int frameY, BOOL trans = FALSE, COLORREF transColor = FALSE, bool blend = FALSE);
	void loadFrameImage(wstring keyName, const TCHAR* fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL trans = FALSE, COLORREF transColor = FALSE, bool blend = FALSE);

	BOOL loadingImageDone();

	vector<loadItem*> getLoadItem() { return _vLoadImage; }


	loading();
	~loading();
};

