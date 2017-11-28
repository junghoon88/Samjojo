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
	_story = IMAGEMANAGER->findImage(L"좌대화창");
	_face = IMAGEMANAGER->findImage(L"face 00000");
	next = 0;
	
	_face->setX(story.left);
	_face->setY(story.top);
	return S_OK;
}

void scanDialog::release(void)
{
	fclose(_fp);
	_fp = NULL;
}
 
void scanDialog::update(void)
{
	

	_face->setX(_face->getX());
	_face->setY(_face->getY());

	if (_tcscmp(_story->getFileName(), L"image/좌측대화창.bmp")==0)
	{
		_face->setX(story.left);
		_face->setY(story.top);
	
	}
	else if (_tcscmp(_story->getFileName(), L"image/우측대화창.bmp")==0)
	{
		_face->setX(story.right - 120);
		_face->setY(story.top);
	}
	

	

}

void scanDialog::render(void)
{
	wstring ss = convert_wc(_strName);
	int len = _tcslen(ss.c_str());

	
	if(strlen(_strName)>=1)
	{
		_story->render(getMemDC(), story.left, story.top);
		_face->render(getMemDC(), _face->getX(), _face->getY());
	}

	if (_tcscmp(_story->getFileName(), L"image/좌측대화창.bmp") == 0)
	{
		TextOut(getMemDC(), story.left + 150, story.top + 30, ss.c_str(), len);
		for (int i = 0; i < _vScripts.size(); i++)
		{
			ss = convert_wc(_vScripts[i]);
			len = _tcslen(ss.c_str());

			TextOut(getMemDC(), story.left + 150, story.top + 35 + 15 * (i + 1), ss.c_str(), len);
		}

	}
	else if (_tcscmp(_story->getFileName(), L"image/우측대화창.bmp") == 0)
	{
		TextOut(getMemDC(), story.left+10, story.top + 30, ss.c_str(), len);
		for (int i = 0; i < _vScripts.size(); i++)
		{
			ss = convert_wc(_vScripts[i]);
			len = _tcslen(ss.c_str());

			TextOut(getMemDC(), story.left +10 , story.top + 35 + 15 * (i + 1), ss.c_str(), len);
		}
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
			story = RectMake(posx, posy, 464, 120);
			printf("");
		}
		
		/////페이스 결정전
		if (strcmp(_strName, "동탁") == 0)
		{
			_face = IMAGEMANAGER->findImage(L"face 00135");
			_story = IMAGEMANAGER->findImage(L"좌대화창");
		}
		else if (strcmp(_strName, "이유") == 0)
		{
			_face = IMAGEMANAGER->findImage(L"face 00140");
			_story = IMAGEMANAGER->findImage(L"좌대화창");
		}
		else if (strcmp(_strName, "문관1") == 0)
		{
			_face = IMAGEMANAGER->findImage(L"face 00176");
			_story = IMAGEMANAGER->findImage(L"우대화창");
		}
		else if (strcmp(_strName, "문관2") == 0)
		{
			_face = IMAGEMANAGER->findImage(L"face 00177");
			_story = IMAGEMANAGER->findImage(L"우대화창");
		}
		else if (strcmp(_strName, "왕윤") == 0)
		{
			_face = IMAGEMANAGER->findImage(L"face 00161");
			_story = IMAGEMANAGER->findImage(L"좌대화창");
		}
		else if (strcmp(_strName, "초선") == 0)
		{
			_face = IMAGEMANAGER->findImage(L"face 00025");
			_story = IMAGEMANAGER->findImage(L"우대화창");
		}
		else if (strcmp(_strName, "병사") == 0)
		{
			_face = IMAGEMANAGER->findImage(L"face 00181");
			_story = IMAGEMANAGER->findImage(L"우대화창");
		}
		else if (strcmp(_strName, "원소") == 0)
		{
			_face = IMAGEMANAGER->findImage(L"face 00109");
			_story = IMAGEMANAGER->findImage(L"우대화창");
		}
	}
}

void scanDialog::nextDialog(void)
{

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


