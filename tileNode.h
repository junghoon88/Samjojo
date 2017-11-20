#pragma once
#include "stdafx.h"


//�� Ÿ���� �԰�
#define TILESIZE 48

//Ÿ�� ����
#define TILEX 60
#define TILEY 60

//Ÿ�ϼ�(�׷��� Ÿ�� ����)�� ����
#define SAMPLETILEX 3
#define SAMPLETILEY 10

//��Ʈ�ʵ� Ÿ�� �Ӽ�
#define ATTR_UNMOVE		0x00000001
#define ATTR_SWAMP		0x00000002
#define ATTR_FLAT		0x00000004
#define ATTR_BADLANDS	0x00000008
#define ATTR_VILLAGE	0x00000010
#define ATTR_CASTLE		0x00000020

//������ ���� ����
enum TERRAIN
{
	TERRAIN_NONE,
	TERRAIN_GRASSLAND,
	TERRAIN_SWAMP,
	TERRAIN_FLAT,
	TERRAIN_BADLANDS,
	TERRAIN_MOUNTAIN,
	TERRAIN_VILLAGE,
	TERRAIN_CASTLE,
	TERRAIN_UNMOVE,

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
