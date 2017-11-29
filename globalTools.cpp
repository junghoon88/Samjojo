#include "stdafx.h"
#include "globalTools.h"


globalTools::globalTools()
{
}


globalTools::~globalTools()
{
}

void globalTools::setFontAll(void)
{
	for (int i = 0; i < FONTVERSION_MAX; i++)
	{
		switch (i)
		{
		case FONTVERSION_SAMJOJO:
			_gFont[i] = CreateFont(
				17,						//������
				0,						//���� ����
				0,						//���� ����(������ ���ڰ� ������ ���)
				0,						//���� ����
				400,					//���� ����(��Ʈ ũ��)
				false,					//bool ���� ����
				false,					//bool ���� ����
				false,					//bool ���� ��Ҽ�(������Ű�� ����)
				HANGUL_CHARSET,			//���� ����
				OUT_DEFAULT_PRECIS,		//��� ��Ȯ��
				CLIP_DEFAULT_PRECIS,	//Ŭ���� ��Ȯ��
				DEFAULT_QUALITY,		//����� ����Ƽ
				FF_DONTCARE,			//�ڰ�
				TEXT("�ü�"));			//��Ʈ
			break;
		case FONTVERSION_SAMJOJO_AJINJI:
			_gFont[i] = CreateFont(
				15,						//������
				0,						//���� ����
				0,						//���� ����(������ ���ڰ� ������ ���)
				0,						//���� ����
				400,					//���� ����(��Ʈ ũ��)
				false,					//bool ���� ����
				false,					//bool ���� ����
				false,					//bool ���� ��Ҽ�(������Ű�� ����)
				HANGUL_CHARSET,			//���� ����
				OUT_DEFAULT_PRECIS,		//��� ��Ȯ��
				CLIP_DEFAULT_PRECIS,	//Ŭ���� ��Ȯ��
				DEFAULT_QUALITY,		//����� ����Ƽ
				FF_DONTCARE,			//�ڰ�
				TEXT("a�����ü�"));		//��Ʈ
			break;
		case FONTVERSION_SAMJOJO_ASEJONG:
			_gFont[i] = CreateFont(
				15,						//������
				0,						//���� ����
				0,						//���� ����(������ ���ڰ� ������ ���)
				0,						//���� ����
				400,					//���� ����(��Ʈ ũ��)
				false,					//bool ���� ����
				false,					//bool ���� ����
				false,					//bool ���� ��Ҽ�(������Ű�� ����)
				HANGUL_CHARSET,			//���� ����
				OUT_DEFAULT_PRECIS,		//��� ��Ȯ��
				CLIP_DEFAULT_PRECIS,	//Ŭ���� ��Ȯ��
				DEFAULT_QUALITY,		//����� ����Ƽ
				FF_DONTCARE,			//�ڰ�
				TEXT("a�����Ƿ�M"));		//��Ʈ
			break;
		case FONTVERSION_STORY:
			_gFont[i] = CreateFont(
				14,						
				8,						
				0,						
				0,						
				300,					
				false,					
				false,					
				false,					
				HANGUL_CHARSET,			
				OUT_DEFAULT_PRECIS,		
				CLIP_DEFAULT_PRECIS,	
				DEFAULT_QUALITY,		
				FF_DONTCARE,			
				TEXT("����ü"));			
			break;
		}
	}
}
void globalTools::deleteFontAll(void)
{
	for (int i = 0; i < FONTVERSION_MAX; i++)
	{
		DeleteObject(_gFont[i]);
	}
}
void globalTools::setBrushAll(void)
{
	for (int i = 0; i < BRUSHVERSION_MAX; i++)
	{
		switch (i)
		{
			case BRUSHVERSION_WHITE:
				_gBrush[i] = CreateSolidBrush(RGB(255, 255, 255));
				break;
			case BRUSHVERSION_GRAY:
				_gBrush[i] = CreateSolidBrush(RGB(200, 200, 200));
				break;
			case BRUSHVERSION_MARGENTA:
				_gBrush[i] = CreateSolidBrush(RGB(255, 0, 255));
				break;
			case BRUSHVERSION_TILE:
				_gBrush[i] = CreateSolidBrush(RGB(250, 150, 0));
				break;
		}
	}
}
void globalTools::deleteBrushAll(void)
{
	for (int i = 0; i < BRUSHVERSION_MAX; i++)
	{
		DeleteObject(_gBrush[i]);
	}
}
