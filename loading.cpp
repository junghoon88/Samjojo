#include "stdafx.h"
#include "loading.h"

loadItem::loadItem(){}
loadItem::~loadItem(){}

HRESULT loadItem::initForImage(wstring keyName, int width, int height, bool blend)
{
	_kind = LOAD_KIND_IMAGE_0;

	memset(&_imageResource, 0, sizeof(tagImageResource));

	//_imageResource.keyName = keyName;
	_stprintf(_imageResource.keyName, L"%s", keyName.c_str());
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.blend = blend;

	return S_OK;
}

HRESULT loadItem::initForImage(wstring keyName, const TCHAR* fileName, int width, int height, BOOL trans, COLORREF transColor, bool blend)
{
	_kind = LOAD_KIND_IMAGE_1;

	memset(&_imageResource, 0, sizeof(tagImageResource));

	//_imageResource.keyName = keyName;
	 _stprintf(_imageResource.keyName, L"%s", keyName.c_str());
	//_imageResource.fileName = fileName;
	_stprintf(_imageResource.fileName, L"%s", fileName);
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.trans = trans;
	_imageResource.transColor = transColor;
	_imageResource.blend = blend;

	return S_OK;
}

HRESULT loadItem::initForImage(wstring keyName, const TCHAR* fileName, float x, float y, int width, int height, BOOL trans, COLORREF transColor, bool blend)
{
	_kind = LOAD_KIND_IMAGE_2;

	memset(&_imageResource, 0, sizeof(tagImageResource));

	//_imageResource.keyName = keyName;
	 _stprintf(_imageResource.keyName, L"%s", keyName.c_str());
	//_imageResource.fileName = fileName;
	_stprintf(_imageResource.fileName, L"%s", fileName);
	_imageResource.x = x;
	_imageResource.y = y;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.trans = trans;
	_imageResource.transColor = transColor;
	_imageResource.blend = blend;

	return S_OK;
}

HRESULT loadItem::initForFrameImage(wstring keyName, const TCHAR* fileName, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor, bool blend)
{
	_kind = LOAD_KIND_FRAMEIMAGE_0;

	memset(&_imageResource, 0, sizeof(tagImageResource));

	//_imageResource.keyName = keyName;
	 _stprintf(_imageResource.keyName, L"%s", keyName.c_str());
	//_imageResource.fileName = fileName;
	_stprintf(_imageResource.fileName, L"%s", fileName);
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.frameX = frameX;
	_imageResource.frameY = frameY;
	_imageResource.trans = trans;
	_imageResource.transColor = transColor;
	_imageResource.blend = blend;

	return S_OK;
}

HRESULT loadItem::initForFrameImage(wstring keyName, const TCHAR* fileName, float x, float y, int width, int height,
	int frameX, int frameY, BOOL trans, COLORREF transColor, bool blend)
{
	_kind = LOAD_KIND_FRAMEIMAGE_1;

	memset(&_imageResource, 0, sizeof(tagImageResource));

	//_imageResource.keyName = keyName;
	 _stprintf(_imageResource.keyName, L"%s", keyName.c_str());
	//_imageResource.fileName = fileName;
	_stprintf(_imageResource.fileName, L"%s", fileName);
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.x = x;
	_imageResource.y = y;
	_imageResource.frameX = frameX;
	_imageResource.frameY = frameY;
	_imageResource.trans = trans;
	_imageResource.transColor = transColor;
	_imageResource.blend = blend;

	return S_OK;
}


loading::loading()
{
}


loading::~loading()
{

}

HRESULT loading::init()
{
	_background = IMAGEMANAGER->addImage(L"로딩백그라운드", L"image/loading/loadingBG.bmp", 640, 400);

	_loadingBar = new progressBar;
	_loadingBar->init(L"progressbarT", L"progressbarB", WINSIZEX2 / 2, WINSIZEY2 - 70, 500, 30);
	_loadingBar->setGauge(0, 0);

	_currentGauge = 0;

	return S_OK;
}

void loading::release()
{
	SAFE_DELETE(_loadingBar);
}

void loading::update() 
{
	_loadingBar->update();
}

void loading::render() 
{
	if(_background)	_background->render(getMemDC(), 0, 0);
	_loadingBar->render();
}


void loading::loadImage(wstring keyName, int width, int height, bool blend)
{
	loadItem* item = new loadItem;
	item->initForImage(keyName, width, height, blend);

	_vLoadImage.push_back(item);
}

void loading::loadImage(wstring keyName, const TCHAR* fileName, int width, int height, BOOL trans, COLORREF transColor, bool blend)
{
	loadItem* item = new loadItem;
	item->initForImage(keyName, fileName, width, height, trans, transColor, blend);

	_vLoadImage.push_back(item);
}

void loading::loadImage(wstring keyName, const TCHAR* fileName, float x, float y, int width, int height, BOOL trans, COLORREF transColor, bool blend)
{
	loadItem* item = new loadItem;
	item->initForImage(keyName, fileName, x, y, width, height, trans, transColor, blend);

	_vLoadImage.push_back(item);
}

void loading::loadFrameImage(wstring keyName, const TCHAR* fileName, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor, bool blend)
{
	loadItem* item = new loadItem;
	item->initForFrameImage(keyName, fileName, width, height, frameX, frameY, trans, transColor, blend);

	_vLoadImage.push_back(item);
}

void loading::loadFrameImage(wstring keyName, const TCHAR* fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor, bool blend)
{
	loadItem* item = new loadItem;
	item->initForFrameImage(keyName, fileName, x, y, width, height, frameX, frameY, trans, transColor, blend);

	_vLoadImage.push_back(item);
}


BOOL loading::loadingImageDone()
{
	//로딩이 끝났으면 다됐다고 전해라~
	if (_currentGauge >= _vLoadImage.size())
	{
		return TRUE;
	}

	loadItem* item = _vLoadImage[_currentGauge];

	switch (item->getLoadingKind())
	{
		case LOAD_KIND_IMAGE_0:
		{
			tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addImage(img.keyName, img.width, img.height, img.blend);
		}
		break;
		case LOAD_KIND_IMAGE_1:
		{
			tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addImage(img.keyName, img.fileName, img.width, img.height, img.trans, img.transColor, img.blend);
		}
		break;
		case LOAD_KIND_IMAGE_2:
		{
			tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addImage(img.keyName, img.fileName, img.x, img.y, img.width, img.height, img.trans, img.transColor, img.blend);
		}
		break;
		case LOAD_KIND_FRAMEIMAGE_0:
		{
			tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addFrameImage(img.keyName, img.fileName, img.width, img.height, img.frameX, img.frameY, img.trans, img.transColor, img.blend);
		}
		break;
		case LOAD_KIND_FRAMEIMAGE_1:
		{
			tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addFrameImage(img.keyName, img.fileName, img.x, img.y, img.width, img.height, img.frameX, img.frameY, img.trans, img.transColor, img.blend);
		}
		break;
		case LOAD_KIND_SOUND:
		{
			//쉬우니 완성해볼 것.
		}
		break;
	}

	_loadingBar->setGauge(_currentGauge, _vLoadImage.size());
	_currentGauge++;

	return FALSE;
}
