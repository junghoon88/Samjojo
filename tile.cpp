#include "stdafx.h"
#include "tile.h"
#include "tileNode.h"


tile::tile()
	: _idX(0), _idY(0), 
	_totalCost(0), _costFromStart(0), _costToGoal(0),
	_parentNode(NULL)
{
}


tile::~tile()
{
}

HRESULT tile::init(int idX, int idY)
{
	_color = RGB(250, 150, 0);
	_brush = CreateSolidBrush(_color);
	_pen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));

	_center = PointMake(idX * TILESIZE + (TILESIZE / 2), idY*TILESIZE + (TILESIZE / 2));

	_idX = idX;
	_idY = idY;

	_rc = RectMakeCenter(_center.x, _center.y, TILESIZE, TILESIZE);

	return S_OK;
}

HRESULT tile::init(int idX, int idY, RECT rc)
{
	_idX = idX;
	_idY = idY;
	_rc = rc;
	_center = PointMake((rc.left + rc.right) / 2, (rc.top + rc.bottom) / 2);

	_color = RGB(250, 150, 0);
	_brush = CreateSolidBrush(_color);
	_pen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));

	return S_OK;
}

void tile::release(void)
{
	DeleteObject(_brush);
	DeleteObject(_pen);
}

void tile::update()
{

}

void tile::render()
{
	SelectObject(getMemDC(), (HBRUSH)_brush);
	FillRect(getMemDC(), &_rc, _brush);

	SelectObject(getMemDC(), (HPEN)_pen);
	RectangleMake(getMemDC(), _rc.left, _rc.top, TILESIZE, TILESIZE);
}
