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
void Item::copyItem(Item * item)
{
	_wNum = item->_wNum;
	_aNum = item->_aNum;
	_sNum = item->_sNum;

	_tcscpy(_name, item->_name);
	_img16 = item->_img16;
	_img32 = item->_img32;

	_wcls = item->_wcls;
	_acls = item->_acls;
	_cls = item->_cls;

	_hp = item->_hp;
	_mp = item->_mp;
	_atk = item->_atk;
	_dep = item->_dep;
	_res = item->_res;

}
////////////////


ItemWeapon::ItemWeapon()
{

}


ItemWeapon::~ItemWeapon()
{
}

HRESULT ItemWeapon::init(ITEM_CLASS icls,ITEMW_CLASS cls, const TCHAR *name, int atk, int dep, int res, int hp, int mp) {
	
	_cls = icls;
	_wcls = cls;
	_tcscpy(_name, name);
	TCHAR tmp[32], tmp2[32];
	_tcscpy(tmp, name);
	_tcscat(tmp, L"16");
	_img16 = IMAGEMANAGER->findImage(tmp);
	_tcscpy(tmp2, name);
	_tcscat(tmp2, L"32");
	_img32 = IMAGEMANAGER->findImage(tmp2);
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

HRESULT ItemArmor::init(ITEM_CLASS icls, ITEMA_CLASS cls, const TCHAR *name,int atk, int dep, int res, int hp, int mp){

	_cls = icls;
	_acls = cls;
	_tcscpy(_name, name);
	TCHAR tmp[32], tmp2[32];
	_tcscpy(tmp, name);
	_tcscat(tmp, L"16");
	_img16 = IMAGEMANAGER->findImage(tmp);
	_tcscpy(tmp2, name);
	_tcscat(tmp2, L"32");
	_img32 = IMAGEMANAGER->findImage(tmp2);

	_atk = atk;
	_dep = dep;
	_res = res;
	_hp = hp;
	_mp = mp;

	return S_OK;
}









ItemSpecial::ItemSpecial()
{
}

ItemSpecial::~ItemSpecial()
{
}

HRESULT ItemSpecial::init(ITEM_CLASS icls, const TCHAR *name,int atk, int dep, int res, int hp, int mp) {
	
	_cls = icls;
	_tcscpy(_name, name);
	TCHAR tmp[32], tmp2[32];
	_tcscpy(tmp, name);
	_tcscat(tmp, L"16");
	_img16 = IMAGEMANAGER->findImage(tmp);
	_tcscpy(tmp2, name);
	_tcscat(tmp2, L"32");
	_img32 = IMAGEMANAGER->findImage(tmp2);

	_atk = atk;
	_dep = dep;
	_res = res;
	_hp = hp;
	_mp = mp;

	return S_OK;
}