#pragma once
#include "stdafx.h"


//한 타일의 규격
#define TILESIZE 32

//타일 갯수 (X축 20개, Y축 20개)
#define TILEX 20
#define TILEY 20

//타일 총 사이즈
#define TILESIZEX TILESIZE * TILEX
#define TILESIZEY TILESIZE * TILEY

//타일셋(그려올 타일 샘플)의 갯수
#define SAMPLETILEX 20
#define SAMPLETILEY 9

//비트필드 타일 속성
#define ATTR_UNMOVE		0x00000001
#define ATTR_SWAMP		0x00000002
#define ATTR_POISION	0x00000004

//지형의 대한 정의
enum TERRAIN
{
	// 시멘트   모래       잔디      물
	TR_CEMENT, TR_DESERT, TR_GRASS, TR_WATER, TR_END
};

//오브젝트의 대한 정의
enum OBJECT
{
	OBJ_BLOCK1, OBJ_BLOCK3, OBJ_BLOCKS,	//한방 맞으면 박살나는 벽돌, 3방, 안깨지는 벽돌
	OBJ_FLAG1, OBJ_FLAG2,				//1P 진영, 2P 진영
	OBJ_TANK1, OBJ_TANK2, OBJ_NONE		//1P 탱크 리스폰위치, 2P 탱크 리스폰위치
};

//나올 포지션(after Index)
enum POS
{
	POS_FLAG1, POS_FLAG2, POS_TANK1, POS_TANK2
};

//타일 구조체
struct tagTile
{
	TERRAIN terrain;
	OBJECT obj;
	RECT rc;
	int terrainFrameX;
	int terrainFrameY;
	int objFrameX;
	int objFrameY;
};

struct tagSampleTile
{
	RECT rcTile;
	int terrainFrameX;
	int terrainFrameY;
};

struct tagCurrentTile
{
	int x;
	int y;
};
