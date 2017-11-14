#include "stdafx.h"
#include "button.h"


button::button()
{
}


button::~button()
{

}

HRESULT button::init(const TCHAR* imageName, int x, int y,
	POINT btnDownFramePoint, POINT btnUpFramePoint,
	CALLBACK_FUNCTION cbFunction)
{
	_obj = NULL;
	_callbackFunction = static_cast<CALLBACK_FUNCTION>(cbFunction);
	_callbackFunctionParameter = NULL;

	_direction = BUTTONDIRECTION_NULL;

	_x = x;
	_y = y;

	_btnUpFramePoint = btnUpFramePoint;
	_btnDownFramePoint = btnDownFramePoint;

	_imageName = imageName;
	_image = IMAGEMANAGER->findImage(imageName);

	_rc = RectMakeCenter(x, y, _image->getFrameWidth(), _image->getFrameHeight());

	return S_OK;
}

HRESULT button::init(const TCHAR* imageName, int x, int y,
	POINT btnDownFramePoint, POINT btnUpFramePoint,
	void* cbFunction, void* obj)
{
	_obj = obj;
	_callbackFunction = NULL;
	_callbackFunctionParameter = static_cast<CALLBACK_FUNCTION_PARAMETER>(cbFunction);

	_direction = BUTTONDIRECTION_NULL;

	_x = x;
	_y = y;

	_btnUpFramePoint = btnUpFramePoint;
	_btnDownFramePoint = btnDownFramePoint;

	_imageName = imageName;
	_image = IMAGEMANAGER->findImage(imageName);

	_rc = RectMakeCenter(x, y, _image->getFrameWidth(), _image->getFrameHeight());

	return S_OK;

}

void button::release(void)
{

}

void button::update(void)
{
	if (PtInRect(&_rc, _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_direction = BUTTONDIRECTION_DOWN;
			
		}
		else if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON) && _direction == BUTTONDIRECTION_DOWN)
		{
			_direction = BUTTONDIRECTION_UP;

			if (_callbackFunction != NULL)
			{
				_callbackFunction();
			}
			else if (_callbackFunctionParameter != NULL && _obj != NULL)
			{
				_callbackFunctionParameter(_obj);
			}
		}
	}
	else _direction = BUTTONDIRECTION_NULL;
}

void button::render(void) 
{
	switch (_direction)
	{
		case BUTTONDIRECTION_NULL: case BUTTONDIRECTION_UP:
			_image->frameRender(getMemDC(), _rc.left, _rc.top,
				_btnUpFramePoint.x, _btnUpFramePoint.y);
		break;
		case BUTTONDIRECTION_DOWN:
			_image->frameRender(getMemDC(), _rc.left, _rc.top,
				_btnDownFramePoint.x, _btnDownFramePoint.y);
		break;
	}
}
