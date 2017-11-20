#pragma once
#include "stdafx.h"


//한 타일의 규격
#define TILESIZE 48

//타일 갯수
#define TILEX 60
#define TILEY 60

//타일셋(그려올 타일 샘플)의 갯수
#define SAMPLETILEX 3
#define SAMPLETILEY 10

//비트필드 타일 속성
#define ATTR_UNMOVE		0x00000001
#define ATTR_SWAMP		0x00000002
#define ATTR_FLAT		0x00000004
#define ATTR_BADLANDS	0x00000008
#define ATTR_VILLAGE	0x00000010
#define ATTR_CASTLE		0x00000020

//지형의 대한 정의
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

//오브젝트의 대한 정의
enum OBJECT
{
	OBJECT_NONE,

	OBJECT_MAX
};

//타일 구조체
struct tagTile
{
	TERRAIN terrain;
	OBJECT obj;
	RECT rc;

	int sampleTerrainIdx;	//샘플 터레인 인덱스
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
