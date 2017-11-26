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
#define ATTR_UNMOVE		0x00000001	//����δ� ������
#define ATTR_SWAMP		0x00000002	//��, ǳ�� ���ݸ� �����ؿ�, �̵��� �������� �￩��
#define ATTR_FLAT		0x00000004	//ȭ, ǳ�� ���ݸ� �����ؿ�
#define ATTR_BADLANDS	0x00000008	//��, ǳ�� ���ݸ� �����ؿ�, �̵��� �������� �￩��
#define ATTR_VILLAGE	0x00000010	//ȭ����ݸ� �����ؿ�, �̵��� �������� �￩��
#define ATTR_CASTLE		0x00000020	//ȭ����ݸ� �����ؿ�, ���⿡���� ��20%ȸ���� �����ؿ�, ù ���ɽ� ��� ȸ���� ����ؿ�
#define ATTR_BRIDGE		0x00000040	//ȭ, ��, ǳ�� ���ݸ� �����ؿ�
#define	ATTR_BARRACK	0x00000080	//ȭ�� ���ݸ� �����ؿ�, ���⼭�� ��20%ȸ���� �����ؿ�, ù ���ɽ� �ϱ� ȸ���� ����ؿ�
#define	ATTR_GATEWAY	0x00000100	//ȭ�� ���ݸ� �����ؿ�, ���⼭�� MP20%ȸ���� �����ؿ�, ù ���ɽ� MP ȸ���� ����ؿ�
#define	ATTR_WAREHOUSE	0x00000200	//ȭ�� ���ݸ� �����ؿ�, ù ���ɽ� �ϱ� ȸ���� ����ؿ�
#define ATTR_INCASTLE	0x00000400	//ȭ�� ���ݸ� �����ؿ�
#define ATTR_MOUNTAIN	0x00000800	//��, ǳ�� ���ݸ� �����ؿ�, �̵����� �������� �￩��

//������ ���� ����
enum TERRAIN
{
	TERRAIN_NONE = -1,	//�̼��� ����
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

	TERRAIN_MAX			//�̰� ������ �̻��Ѱ��� ���ü��� ����
};

//������Ʈ ����
enum OBJECTSELECT
{
	OBJECTSELECT_NONE = -1,
	OBJECTSELECT_ENEMY,
	OBJECTSELECT_AILY,
	OBJECTSELECT_PLAYER,

	OBJECTSELECT_MAX
};

//Ÿ�� ����ü
struct tagTile
{
	TERRAIN terrain;
	TCHAR obj[128];
	RECT rc;

	int sampleTerrainIdx;		//���� �ͷ��� �ε���
	int sampleObjectSelectIdx;	//������Ʈ case �ε���
	bool isClick;				//������Ʈ �����ߴ�?
};

struct tagSampleTile
{
	RECT rcTile;
	image* img;
	TCHAR strImgKey[100];
};

struct tagSampleObject
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
