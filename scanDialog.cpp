#include "stdafx.h"
#include "scanDialog.h"


scanDialog::scanDialog()
	: _fp(NULL)
{
	sprintf(_strName, "");
}


scanDialog::~scanDialog()
{
}

HRESULT scanDialog::init(const char* filename)
{
	if (fopen_s(&_fp, filename, "r") == EINVAL)
	{
		_fp = NULL;
	}

	story = RectMake(100, 100, 464, 120);

	Nebi = IMAGEMANAGER->findImage(L"nebi 00");
	Nebi2 = IMAGEMANAGER->findImage(L"nebi 03");
	_story = IMAGEMANAGER->findImage(L"좌대화창");
	_face = IMAGEMANAGER->findImage(L"face 00000");
	mouse = IMAGEMANAGER->findImage(L"마우스2");
	mouse->setFrameX(0);
	next = 0;
	Direction = 0;
	_fontNum = FONTVERSION_SAMJOJO;
	_fontNum2 = FONTVERSION_STORY;
	_face->setX(story.left);
	_face->setY(story.top);
	time = 0;
	Mtime = 0;
	ShowCursor(false);
	return S_OK;
}

void scanDialog::release(void)
{
	_vScripts.clear();
	fclose(_fp);
	_fp = NULL;
	ShowCursor(true);
}
 
void scanDialog::update(void)
{
		
	time += TIMEMANAGER->getElapsedTime();
	Mtime += TIMEMANAGER->getElapsedTime();
	
	if (isleft)
	{
		_story = IMAGEMANAGER->findImage(L"좌대화창");
		_face->setX(story.left);
		_face->setY(story.top);
	}
	
	else
	{	
		_story = IMAGEMANAGER->findImage(L"우대화창");
		_face->setX(story.right - 120);
		_face->setY(story.top);
	}
	
	if (Mtime > 0.3f)
	{
		
		if (mouse->getFrameX() >= mouse->getMaxFrameX())
		{
			mouse->setFrameX(0);
		}
		else mouse->setFrameX(mouse->getFrameX() + 1);
		Mtime = 0;
	}

}

void scanDialog::render(void)
{
	wstring ss = convert_wc(_strName);
	int len = _tcslen(ss.c_str());

	
	if(strlen(_strName)>=1)
	{
		_story->render(getMemDC(), story.left, story.top);
		_face->render(getMemDC());
	}

	if (isleft)
	{
		SetBkMode(getMemDC(), TRANSPARENT);
		HFONT oldFont = (HFONT)SelectObject(getMemDC(), _gFont[_fontNum]);
		SetTextColor(getMemDC(), RGB(0, 0, 255));
		TextOut(getMemDC(), story.left + 150, story.top + 30, ss.c_str(), len);
		SelectObject(getMemDC(), oldFont);
		for (int i = 0; i < _vScripts.size(); i++)
		{
			SetTextColor(getMemDC(), RGB(0, 0, 0));
			ss = convert_wc(_vScripts[i]);
			len = _tcslen(ss.c_str());
			SetBkMode(getMemDC(), TRANSPARENT);
			HFONT oldFont = (HFONT)SelectObject(getMemDC(), _gFont[_fontNum2]);
			
			TextOut(getMemDC(), story.left + 150, story.top + 35 + 15 * (i + 1), ss.c_str(), len);
			SelectObject(getMemDC(), oldFont);
		}
	}
	else  
	{
		SetBkMode(getMemDC(), TRANSPARENT);
		HFONT oldFont = (HFONT)SelectObject(getMemDC(), _gFont[_fontNum]);
		SetTextColor(getMemDC(), RGB(0, 0, 255));
		TextOut(getMemDC(), story.left+10, story.top + 30, ss.c_str(), len);
		SelectObject(getMemDC(), oldFont);
		for (int i = 0; i < _vScripts.size(); i++)
		{
			ss = convert_wc(_vScripts[i]);
			len = _tcslen(ss.c_str());
			SetBkMode(getMemDC(), TRANSPARENT);
			HFONT oldFont = (HFONT)SelectObject(getMemDC(), _gFont[_fontNum2]);
			SetTextColor(getMemDC(), RGB(0, 0, 0));
			TextOut(getMemDC(), story.left +10 , story.top + 35 + 15 * (i + 1), ss.c_str(), len);
			SelectObject(getMemDC(), oldFont);
		}
	}
	switch (next)
	{	
		case 0: 
		{
			if (time < 2.0f) {
				
				mouse->render(getMemDC(), _ptMouse.x, _ptMouse.y);
				Nebi->render(getMemDC(), WINSIZEX2 / 2 - Nebi->getWidth() / 2, 150);
			}
			else if (time > 2.0f && time < 4.0f)
			{
				Nebi = IMAGEMANAGER->findImage(L"nebi 01");
				Nebi->render(getMemDC(), WINSIZEX2 / 2 - Nebi->getWidth() / 2, 150);
				mouse->render(getMemDC(), _ptMouse.x, _ptMouse.y);
			}
			else 
			{
				mouse = IMAGEMANAGER->findImage(L"마우스");
				mouse->frameRender(getMemDC(), _ptMouse.x - mouse->getFrameWidth() / 2, _ptMouse.y - mouse->getFrameHeight() / 2);
			}
		}
			break;
		case 1:
			{
				Nebi = IMAGEMANAGER->findImage(L"nebi 02");
				if (time < 2.0f)
				{
					mouse = IMAGEMANAGER->findImage(L"마우스2");
					mouse->render(getMemDC(), _ptMouse.x, _ptMouse.y);
					Nebi->render(getMemDC(), WINSIZEX2 / 2 - Nebi->getWidth() / 2, 150);
				}
				else if (time > 2.0f)
				{
					mouse = IMAGEMANAGER->findImage(L"마우스");
					mouse->frameRender(getMemDC(), _ptMouse.x - mouse->getFrameWidth() / 2, _ptMouse.y - mouse->getFrameHeight() / 2);
				}
			}
		break;
		case 2 : case 3 :{
			mouse->frameRender(getMemDC(), _ptMouse.x - mouse->getFrameWidth() / 2, _ptMouse.y - mouse->getFrameHeight() / 2);
				}
				break;
		case 4:
			{			
			if (time < 2.0f)
				{
					Nebi2 = IMAGEMANAGER->findImage(L"nebi 03");
					mouse = IMAGEMANAGER->findImage(L"마우스2");
					mouse->render(getMemDC(), _ptMouse.x, _ptMouse.y); 
					Nebi2->render(getMemDC(), WINSIZEX2 / 2 - Nebi2->getWidth() / 2, 150);
				}
				else
				{
					mouse = IMAGEMANAGER->findImage(L"마우스");
					mouse->frameRender(getMemDC(), _ptMouse.x - mouse->getFrameWidth() / 2, _ptMouse.y - mouse->getFrameHeight() / 2);
				}
			}
			break;
		case 5:
		{
			if (time < 2.0f)
			{
				Nebi2 = IMAGEMANAGER->findImage(L"nebi 04");
				mouse = IMAGEMANAGER->findImage(L"마우스2");
				mouse->render(getMemDC(), _ptMouse.x, _ptMouse.y);
				Nebi2->render(getMemDC(), WINSIZEX2 / 2 - Nebi2->getWidth() / 2, 150);
			}
			else
			{
				mouse = IMAGEMANAGER->findImage(L"마우스");
				mouse->frameRender(getMemDC(), _ptMouse.x - mouse->getFrameWidth() / 2, _ptMouse.y - mouse->getFrameHeight() / 2);
			}
		}
		break;
	}
}

void scanDialog::loadDialog(void)
{
	if (_fp == NULL) return;

	sprintf(_strName, "");
	_vScripts.clear();

	while (1)
	{
		char str[STRING_MAX] = "";
		fgets(str, STRING_MAX, _fp);
		if (strlen(str) == 0)
			return;
		
		if (str[0] == '[')
		{
			int len = strlen(str);
		
			for (int i = 0; i < len; i++)
			{
				if (str[i + 1] == ']')
				{
					_strName[i] = '\0';
					break;
				}
				 
				_strName[i] = str[i + 1];
			}
		
		}
		else if (str[0] == '-')
		{
			char script[STRING_MAX] = "";
			int len = strlen(str);
			 
			for (int i = 0; i < len; i++)
			{
				if (str[i + 1] == '\n' || str[i + 1] == '\0')
				{
					script[i] = '\0';
					_vScripts.push_back(script);
					break;
				}

				script[i] = str[i + 1];
			}
		}
		else if (str[0] == '/')
		{
			
			next++;
			time = 0;
		}
		else if (str[0] == '=')
		{
			if (str[1] == '=')
			{
				return;
			}
			else if (str[1] == '>')
			{
				int len = strlen(str);
				char temp[100] = "";
				char nextFileName[100] = "scripts/";
				for (int i = 0; i < len; i++)
				{
					if (str[i + 2] == '\n' || str[i + 2] == '\0')
					{
						temp[i] = '\0';
						break;
					}
					temp[i] = str[i + 2];
				}
				strcat(nextFileName, temp);

				nextFile(nextFileName);

				return;
			}
		}
		else if (str[0] == '*')
		{
			char *temp;
			temp = strtok(str, "*"); //문자열분리
			temp = strtok(temp, ",");
			int posx = atoi(temp);
			temp = strtok(NULL, ",");
			int posy = atoi(temp);
			temp = strtok(NULL, ",");
			int isLeft = atoi(temp);
			temp = strtok(NULL, ",");
			int isDirection = atoi(temp);
			isleft = isLeft;
			Direction = isDirection;
			story = RectMake(posx, posy, 464, 120);
			printf("");
		}
		
		/////페이스 결정전
		if (strcmp(_strName, "동탁") == 0)
		{
			_face = IMAGEMANAGER->findImage(L"face 00135");
		}
		else if (strcmp(_strName, "이유") == 0)
		{
			_face = IMAGEMANAGER->findImage(L"face 00140");
		}
		else if (strcmp(_strName, "문관1") == 0)
		{
			_face = IMAGEMANAGER->findImage(L"face 00176");
		}
		else if (strcmp(_strName, "문관2") == 0)
		{
			_face = IMAGEMANAGER->findImage(L"face 00177");
		}
		else if (strcmp(_strName, "왕윤") == 0)
		{
			_face = IMAGEMANAGER->findImage(L"face 00161");
		}
		else if (strcmp(_strName, "초선") == 0)
		{
			_face = IMAGEMANAGER->findImage(L"face 00025");
		}
		else if (strcmp(_strName, "병사") == 0)
		{
			_face = IMAGEMANAGER->findImage(L"face 00181");
		}
		else if (strcmp(_strName, "원소") == 0)
		{
			_face = IMAGEMANAGER->findImage(L"face 00109");
		}
		else if (strcmp(_strName, "조조") == 0)
		{
			_face = IMAGEMANAGER->findImage(L"face 00001");
		}
	}
}


void scanDialog::nextFile(const char * filename)
{
	fclose(_fp);
	_fp = NULL;
	if (fopen_s(&_fp, filename, "r") == EINVAL)
	{
		_fp = NULL;
	}
}


