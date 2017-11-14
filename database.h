#pragma once
#include "singletonBase.h"
#include <vector>
#include <map>

class elements
{
public:
	int currentHP;


	elements(){};
	~elements(){};
};

class database : public singletonBase<database>
{
private:
	typedef vector<wstring> arrElements;
	typedef vector<wstring>::iterator iterElements;

	typedef map<wstring, elements*> arrElement;
	typedef map<wstring, elements*>::iterator iterElement;

private:
	arrElement _mTotalElement;

public:
	HRESULT init();
	void release();

	void loadDatabase(wstring name);

	//속성에 대한 접근자
	elements* getElementData(wstring str) { return _mTotalElement.find(str)->second; }

	//설정자
	void setElementDataCurrentHP(wstring str, float ch);


	database();
	~database();
};

