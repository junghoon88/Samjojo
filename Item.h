#pragma once
#include "gameNode.h"

enum ITEMW_CLASS {
	HSWORD,
	SWORD,
	BOW,
	SPEAR
};
enum ITEMA_CLASS {
	ARMOR,
	SHILED
};
enum ITEM_CLASS {
	WEAPON,
	DEFENCE,
	SPECIAL
};
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


class Item :public gameNode
{
protected:
	ITEMW_NUMBER _wNum;
	ITEMA_NUMBER _aNum;
	ITEMS_NUMBER _sNum;

	TCHAR _name[128];
	image* _img16;
	image* _img32;

	RECT _rc;

	ITEMW_CLASS _wcls;
	ITEMA_CLASS _acls;
	ITEM_CLASS _cls;

	int _hp;   //보조용
	int _mp;   //

	int _atk;
	int _dep;

	int _res;  //명검용

	int _price; //가격

public:
	HRESULT init(void);

	void copyItem(Item* item);

	inline int getHP(void) { return _hp; }
	inline int getMP(void) { return _mp; }
	inline int getAtk(void) { return _atk; }
	inline int getDep(void) { return _dep; }
	inline int getRes(void) { return _res; }

	inline TCHAR* getName(void) { return _name; }
	inline image* getImg32(void) { return _img32; }
	inline image* getImg16(void) { return _img16; }
	inline ITEMW_CLASS getWclass(void) { return _wcls; }
	inline ITEMA_CLASS getAclass(void) { return _acls; }
	inline ITEM_CLASS getIclass(void) { return _cls; }
	inline int getPrice(void) { return _price; }
	//void release(void);
	//void update(void);
	//void render(void);
	Item();
	~Item();
};


class ItemWeapon : public Item
{
private:

public:
	HRESULT init(ITEM_CLASS icls,ITEMW_CLASS cls, const TCHAR *name,int atk, int dep, int res, int hp, int mp, int price);

	ItemWeapon();
	~ItemWeapon();
};


class ItemArmor : public Item
{
private:

public:
	HRESULT init(ITEM_CLASS icls, ITEMA_CLASS cls, const TCHAR *name,int atk, int dep, int res, int hp, int mp, int price);
	ItemArmor();
	~ItemArmor();
};


class ItemSpecial : public Item
{
private:

public:
	HRESULT init(ITEM_CLASS icls, const TCHAR *name,int atk, int dep, int res, int hp, int mp, int price);
	ItemSpecial();
	~ItemSpecial();
};

