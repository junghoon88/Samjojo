#pragma once
#include "stdafx.h"


//�� Ÿ���� �԰�
#define TILESIZE 48

//Ÿ�� ���� (X�� 20��, Y�� 20��)
#define TILEX 20
#define TILEY 20

//Ÿ�ϼ�(�׷��� Ÿ�� ����)�� ����
#define SAMPLETILEX 3
#define SAMPLETILEY 10

//��Ʈ�ʵ� Ÿ�� �Ӽ�
#define ATTR_UNMOVE		0x00000001
#define ATTR_SWAMP		0x00000002
#define ATTR_POISION	0x00000004

//������ ���� ����
enum TERRAIN
{
	TERRAIN_NONE, 


	TERRAIN_MAX
};

//������Ʈ�� ���� ����
enum OBJECT
{
	OBJECT_NONE,

	OBJECT_MAX
};

//Ÿ�� ����ü
struct tagTile
{
	TERRAIN terrain;
	OBJECT obj;
	RECT rc;

	int sampleTerrainIdx;	//���� �ͷ��� �ε���
};

struct tagSampleTile
{
	RECT rcTile;
	image* img;
	TCHAR strImgKey[100];
};

struct tagCurrentTile
{
	int x;
	int y;
};
