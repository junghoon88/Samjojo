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
	SAFE_DELETE(_fp);

	if (fopen_s(&_fp, filename, "r") == EINVAL)
	{
		SAFE_DELETE(_fp);
	}

	return S_OK;
}

void scanDialog::release(void)
{
	SAFE_DELETE(_fp);
}

void scanDialog::update(void)
{
}

void scanDialog::render(void)
{
	wstring ss = convert_wc(_strName);
	int len = _tcslen(ss.c_str());

	TextOut(getMemDC(), 0, 0, ss.c_str(), len);

	for (int i = 0; i < _vScripts.size(); i++)
	{
		ss = convert_wc(_vScripts[i]);
		len = _tcslen(ss.c_str());
		TextOut(getMemDC(), 0, 50 * (i + 1), ss.c_str(), len);
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
		else if (str[0] == '=' && str[1] == '=')
		{
			return;
		}
	}

}