#pragma once


enum ITEMW_NUMBER //무기 아이템 고유번호
{
	ITEMW_NUMBER_NONE = -1,
};

enum ITEMA_NUMBER //방어구 아이템 고유번호
{
	ITEMA_NUMBER_NONE = -1,
};

enum ITEMS_NUMBER //소비 아이템 고유번호
{
	ITEMS_NUMBER_NONE = -1,
	ITEMS_NUMBER_KONG = 1
};


class Item
{
protected:
	ITEMW_NUMBER _wNum;
	ITEMA_NUMBER _aNum;
	ITEMS_NUMBER _sNum;

	TCHAR _name[128];
	image* _img;
	RECT _rc;


public:
	Item();
	~Item();
};


class ItemWeapon : public Item
{
private:

public:
	ItemWeapon();
	~ItemWeapon();
};


class ItemArmor : public Item
{
private:

public:
	ItemArmor();
	~ItemArmor();
};


class ItemSpecial : public Item
{
private:

public:
	ItemSpecial();
	~ItemSpecial();
};

