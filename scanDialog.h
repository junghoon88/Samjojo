#pragma once
#include "gameNode.h"

#define STRING_MAX 1024

class scanDialog : public gameNode
{
private:
	FILE* _fp;
	char _strName[100];
	vector</*char[STRING_MAX]*/string> _vScripts;

public:
	scanDialog();
	~scanDialog();

	HRESULT init(const char* filename);
	void release(void);
	void update(void);
	void render(void);

	void loadDialog(void);

};

