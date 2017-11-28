#pragma once
#include "gameNode.h"

#define STRING_MAX 1024


class scanDialog : public gameNode
{
private:
	FILE* _fp;
	char _strName[100];
	vector<string> _vScripts;
	RECT story;
	image* _story;
	image* _face;
	

	int next;
	char tmpName[100];
public:
	scanDialog();
	~scanDialog();

	HRESULT init(const char* filename);
	void release(void);
	void update(void);
	void render(void);

	void loadDialog(void);
	void nextDialog(void);
	void nextFile(const char* filename);


public:
	
	
	inline int getNext(void) { return next; }

	

};

