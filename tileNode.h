#pragma once
#include "stdafx.h"


//�� Ÿ���� �԰�
#define TILESIZE 48

//Ÿ�� ����
#define TILEX 40
#define TILEY 40
#define TILEVIEWX 20
#define TILEVIEWY 20

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
	TERRAIN_RIVER,		//��(�̵��Ұ�)
	TERRAIN_BRIDGE,		//�ٸ�(ȭ, ��, ǳ)
	TERRAIN_WATER,		//����(�̰� ���� ����ü �𸣰ڴ�..., �ƹ�ư �̵��Ұ�)
	TERRAIN_DITCH,		//����(�̵��Ұ�)
	TERRAIN_VILLAGE,	//����(ȭ, ù ���ɽ� �ϱ� ȸ�������� ����, ���� ���۽� �� 20%ȸ��)
	TERRAIN_PREMISES,	//����(ȭ)
	TERRAIN_ROCK,		//�Ϻ�(�̵��Ұ�)
	TERRAIN_SHIP,		//��(��� ���ҵ�...?)
	TERRAIN_BROW,		//����(�̵��Ұ�)
	TERRAIN_BARRACK,	//����(ȭ, ù ���ɽ� �ϱ� ȸ�������� ����, ���� ���۽� �� 20%ȸ��)
	TERRAIN_WAREHOUSE,	//���޼�(ȭ, ù ���ɽ� �ϱ� ȸ�������� ����)
	TERRAIN_FIRE,		//��(�̵��Ұ�)
	TERRAIN_MOUNTAIN,	//��(��, ǳ)
	TERRAIN_SNOW,		//����(���� ��, �Ⱦ��� ����)
	TERRAIN_CASTLE,		//��(ȭ, ù ���ɽ� ��� ȸ�������� ����, ���� ���۽� �� 20%ȸ��)
	TERRAIN_INCASTLE,	//����(ȭ)
	TERRAIN_CASTLEGATE,	//����(�̵��Ұ�)
	TERRAIN_RAMPART,	//����(�̵��Ұ�)
	TERRAIN_FOREST,		//��(ȭ)
	TERRAIN_SWAMP,		//����(��, ǳ)
	TERRAIN_FORD,		//����(��, ǳ)
	TERRAIN_POND,		//����(�̵��Ұ�)
	TERRAIN_STRONGHOLD,	//���(ȭ, ù ���ɽ� ��� ȸ�������� ����, ���� ���۽� �� 20%ȸ��)
	TERAAIN_FENCE,		//��Ÿ��(�̵��Ұ�)
	TERRAIN_ALTER,		//����(��� ���ҵ�...?)
	TERRAIN_UNDERGROUND,//����(�̵��Ұ�, ��� ���ҵ�...?)
	TERRAIN_GRASSLAND,	//�ʿ�(ȭ, ǳ)
	TERRAIN_FLAT,		//����(ȭ, ǳ)
	TERRAIN_BADLANDS,	//Ȳ����(��, ǳ)
	TERRAIN_GATEWAY,	//����(ȭ, ù ���ɽ� MP ȸ�������� ����, ���� ���۽� MP 20%ȸ��)
	TERRAIN_NONE,		//�̼��� ����

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
