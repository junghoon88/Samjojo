#include "stdafx.h"
#include "Item.h"

Item::Item()
{
}

Item::~Item()
{
}
HRESULT Item::init(void){


	return S_OK;
}
////////////////


ItemWeapon::ItemWeapon()
{
}


ItemWeapon::~ItemWeapon()
{
}

HRESULT ItemWeapon::init(ITEM_CLASS icls,ITEMW_CLASS cls, const TCHAR *name, const TCHAR *img32key, const TCHAR *img16key, int atk, int dep, int res, int hp, int mp) {
	
	_cls = icls;
	_wcls = cls;
	_tcscpy(_name, name);
	_img32 = IMAGEMANAGER->findImage(img32key);
	_img16 = IMAGEMANAGER->findImage(img16key);

	_atk = atk;
	_dep = dep;
	_res = res;
	_hp = hp;
	_mp = mp;

	return S_OK;
}
////////////////








ItemArmor::ItemArmor()
{
}

ItemArmor::~ItemArmor()
{
}

HRESULT ItemArmor::init(ITEM_CLASS icls, ITEMA_CLASS cls, const TCHAR *name, const TCHAR *img32key, const TCHAR *img16key, int atk, int dep, int res, int hp, int mp){

	_cls = icls;
	_atk = atk;
	_dep = dep;
	_res = res;
	_hp = hp;
	_mp = mp;

	_acls = cls;
	return S_OK;
}









ItemSpecial::ItemSpecial()
{
}

ItemSpecial::~ItemSpecial()
{
}

HRESULT ItemSpecial::init(int atk, int dep, int res, int hp, int mp) {

	_atk = atk;
	_dep = dep;
	_res = res;
	_hp = hp;
	_mp = mp;

	return S_OK;
}