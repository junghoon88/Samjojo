#pragma once


enum ITEMW_NUMBER //���� ������ ������ȣ
{
	ITEMW_NUMBER_NONE = -1,
};

enum ITEMA_NUMBER //�� ������ ������ȣ
{
	ITEMA_NUMBER_NONE = -1,
};

enum ITEMS_NUMBER //�Һ� ������ ������ȣ
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

