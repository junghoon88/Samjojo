#include "stdafx.h"
#include "editbox.h"


editbox::editbox()
	: _img(NULL)
{
}


editbox::~editbox()
{
}

HRESULT editbox::init(void)
{
	_rc = RectMake(0, 0, 0, 0);
	_stprintf(_str, L"");
	_clicked = false;
	_onlyNum = false;

	_hBrushGray = CreateSolidBrush(RGB(200, 200, 200));
	_hBrushWhite = CreateSolidBrush(RGB(255, 255, 255));

	_minNum = 0;
	_maxNum = 99999;


	return S_OK;
}

void editbox::release(void)
{
	DeleteObject(_hBrushGray);
	DeleteObject(_hBrushWhite);
}

void editbox::update(void)
{
	if (PtInRect(&_rc, _ptMouse))
	{
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
		{
			_clicked = true;
		}
	}
	else
	{
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
		{
			_clicked = false;
			if (_onlyNum)
			{
				if (this->getStrNum() < _minNum)
				{
					_stprintf(_str, L"%d", _minNum);
				}
				else if (this->getStrNum() > _maxNum)
				{
					_stprintf(_str, L"%d", _maxNum);
				}
			}
		}
	}
}

void editbox::render(int textOffsetX, int textOffsetY)
{
	if (_img)
	{
		_img->frameRender(getMemDC(), _rc.left, _rc.top, 0, (int)_clicked);
	}
	else
	{
		HBRUSH oldBrush;
		if (_clicked)
		{
			oldBrush = (HBRUSH)SelectObject(getMemDC(), _hBrushGray);
		}
		else
		{
			oldBrush = (HBRUSH)SelectObject(getMemDC(), _hBrushWhite);
		}
		Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
		SelectObject(getMemDC(), oldBrush);
	}

	TextOut(getMemDC(), _rc.left + textOffsetX, _rc.top + textOffsetY, _str, _tcslen(_str));
}

#if 0 //»¹ÁþÀÇÇöÈ²
bool editbox::scanNum(void)
{
	if (!_clicked) return false;

	for (int i = 0; i < 10; i++)
	{
		if (KEYMANAGER->isOnceKeyDown('0' + i))
		{
			TCHAR str[10];
			_stprintf(str, L"%d", i);
			_tcscat(_str, str);
			return true;
		}

		if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD0 + i))
		{
			TCHAR str[10];
			_stprintf(str, L"%d", i);
			_tcscat(_str, str);
			return true;
		}
	}

	return false;
}

bool editbox::scanChar(void)
{
	if (!_clicked) return false;
	if (_onlyNum) return false;

	TCHAR str[10];

	for (char s = 'A'; s <= 'Z'; s++)
	{
		if (KEYMANAGER->isOnceKeyDown(s))
		{
			if (KEYMANAGER->isStayKeyDown(VK_SHIFT))
			{
				_stprintf(str, L"%c", s);
				_tcscat(_str, str);
			}
			else
			{
				_stprintf(str, L"%c", s - ('A' - 'a'));
				_tcscat(_str, str);
			}
			return true;
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_tcscat(_str, L" ");
		return true;
	}
	//if (KEYMANAGER->isOnceKeyDown('.'))
	//{
	//	_tcscat(_str, L".");
	//	return true;
	//}
	//if (KEYMANAGER->isOnceKeyDown('-'))
	//{
	//	_tcscat(_str, L"-");
	//	return true;
	//}
	//if (KEYMANAGER->isOnceKeyDown('_'))
	//{
	//	_tcscat(_str, L"_");
	//	return true;
	//}

	return false;
}

void editbox::scanDelete(void)
{
	int len = _tcslen(_str);
	if (len == 0) return;

	if (KEYMANAGER->isOnceKeyDown(VK_DELETE) || KEYMANAGER->isOnceKeyDown(VK_BACK))
	{
		TCHAR str[128] = L"";
		_tcsncpy(str, _str, len - 1);
		_tcscpy(_str, str);
	}

}

void editbox::scanAll(void)
{
	if (!_clicked) return;

	//scanDelete();

	//if (scanNum())
	//	return;
	//if (scanChar())
	//	return;
}
#endif


void editbox::getChar(WPARAM wParam)
{
	if (!_clicked) return;

	int len = _tcslen(_str);


	if (wParam == VK_BACK)// || wParam == VK_DELETE) //VK_DELETE¶û '.'ÀÌ¶û °ªÀÌ °°´Ù..;;
	{
		if (len == 0) return;

		TCHAR str[128] = L"";
		_tcsncpy(str, _str, len - 1);
		_tcscpy(_str, str);
	}
	else
	{
		if (_onlyNum)
		{
			if ((wParam >= '0' && wParam <= '9') /*|| (wParam >= VK_NUMPAD0 && wParam <= VK_NUMPAD9)*/)
			{
				_str[len] = wParam;
				_str[len + 1] = 0;
			}
		}
		else
		{
			_str[len] = wParam;
			_str[len + 1] = 0;
		}
	}
}