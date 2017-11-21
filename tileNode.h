#pragma once
#include "stdafx.h"


//한 타일의 규격
#define TILESIZE 48

//타일 갯수
#define TILEX 40
#define TILEY 40
#define TILEVIEWX 20
#define TILEVIEWY 20

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
	TERRAIN_RIVER,		//강(이동불가)
	TERRAIN_BRIDGE,		//다리(화, 수, 풍)
	TERRAIN_WATER,		//대하(이건 뭔지 도데체 모르겠다..., 아무튼 이동불가)
	TERRAIN_DITCH,		//도랑(이동불가)
	TERRAIN_VILLAGE,	//마을(화, 첫 점령시 하급 회복아이템 지급, 매턴 시작시 피 20%회복)
	TERRAIN_PREMISES,	//가옥(화)
	TERRAIN_ROCK,		//암벽(이동불가)
	TERRAIN_SHIP,		//배(사용 안할듯...?)
	TERRAIN_BROW,		//벼랑(이동불가)
	TERRAIN_BARRACK,	//병영(화, 첫 점령시 하급 회복아이템 지급, 매턴 시작시 피 20%회복)
	TERRAIN_WAREHOUSE,	//보급소(화, 첫 점령시 하급 회복아이템 지급)
	TERRAIN_FIRE,		//불(이동불가)
	TERRAIN_MOUNTAIN,	//산(지, 풍)
	TERRAIN_SNOW,		//설원(아직 모름, 안쓸꺼 같음)
	TERRAIN_CASTLE,		//성(화, 첫 점령시 상급 회복아이템 지급, 매턴 시작시 피 20%회복)
	TERRAIN_INCASTLE,	//성내(화)
	TERRAIN_CASTLEGATE,	//성문(이동불가)
	TERRAIN_RAMPART,	//성벽(이동불가)
	TERRAIN_FOREST,		//숲(화)
	TERRAIN_SWAMP,		//습지(수, 풍)
	TERRAIN_FORD,		//여울(수, 풍)
	TERRAIN_POND,		//연못(이동불가)
	TERRAIN_STRONGHOLD,	//요새(화, 첫 점령시 상급 회복아이템 지급, 매턴 시작시 피 20%회복)
	TERAAIN_FENCE,		//울타리(이동불가)
	TERRAIN_ALTER,		//제단(사용 안할듯...?)
	TERRAIN_UNDERGROUND,//지하(이동불가, 사용 안할듯...?)
	TERRAIN_GRASSLAND,	//초원(화, 풍)
	TERRAIN_FLAT,		//평지(화, 풍)
	TERRAIN_BADLANDS,	//황무지(지, 풍)
	TERRAIN_GATEWAY,	//관문(화, 첫 점령시 MP 회복아이템 지급, 매턴 시작시 MP 20%회복)
	TERRAIN_NONE,		//미설정 상태

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
