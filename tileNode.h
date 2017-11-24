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
#define ATTR_UNMOVE		0x00000001	//여기로는 못가요
#define ATTR_SWAMP		0x00000002	//수, 풍계 공격만 가능해요, 이동력 절반으로 깍여요
#define ATTR_FLAT		0x00000004	//화, 풍계 공격만 가능해요
#define ATTR_BADLANDS	0x00000008	//지, 풍계 공격만 가능해요, 이동력 절반으로 깍여요
#define ATTR_VILLAGE	0x00000010	//화계공격만 가능해요, 이동력 절반으로 깍여요
#define ATTR_CASTLE		0x00000020	//화계공격만 가능해요, 여기에서는 피20%회복이 가능해요, 첫 점령시 상급 회복템 드랍해요
#define ATTR_BRIDGE		0x00000040	//화, 수, 풍계 공격만 가능해요
#define	ATTR_BARRACK	0x00000080	//화계 공격만 가능해요, 여기서는 피20%회복이 가능해요, 첫 점령시 하급 회복템 드랍해요
#define	ATTR_GATEWAY	0x00000100	//화계 공격만 가능해요, 여기서는 MP20%회복이 가능해요, 첫 점령시 MP 회복템 드랍해요
#define	ATTR_WAREHOUSE	0x00000200	//화계 공격만 가능해요, 첫 점령시 하급 회복템 드랍해요
#define ATTR_INCASTLE	0x00000400	//화계 공격만 가능해요
#define ATTR_MOUNTAIN	0x00000800	//지, 풍계 공격만 가능해요, 이동력이 절반으로 깍여요

//지형의 대한 정의
enum TERRAIN
{
	TERRAIN_NONE = -1,	//미설정 상태
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

	TERRAIN_MAX			//이거 나오면 이상한거임 나올수가 없음
};

//오브젝트의 대한 정의
enum OBJECT
{
	OBJECT_NONE = -1,
	OBJECT_INFANTRY,		//보병
	OBJECT_CAVALRY,			//기병
	OBJECT_ARCHER,			//궁병
	OBJECT_HORSEARCHER,		//궁기병
	OBJECT_FIGHTER,			//무도가
	OBJECT_THEIF,			//도적
	OBJECT_TACTICIAN,		//책사
	OBJECT_WIZARD,			//도사
	OBJECT_CATAPULT,		//투석기
	
	OBJECT_HERO01 = 0,		//영웅
	OBJECT_HERO02,
	OBJECT_HERO03,
	OBJECT_HERO04,
	OBJECT_HERO05,
	OBJECT_HERO06,
	OBJECT_HERO07,
	OBJECT_HERO08,
	OBJECT_HERO09,
	OBJECT_HERO10,

	OBJECT_MAX
};

enum OBJECTSELECT
{
	OBJECTSELECT_ENEMY,
	OBJECTSELECT_AILY,
	OBJECTSELECT_PLAYER,

	OBJECTSELECT_MAX
};

//타일 구조체
struct tagTile
{
	TERRAIN terrain;
	OBJECT obj;
	RECT rc;

	int sampleTerrainIdx;		//샘플 터레인 인덱스
	int sampleObjectSelectIdx;	//오브젝트 case 인덱스
	int sampleObjectIdx;		//샘플 오브젝트 인덱스
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
	OBJECT obj;
};

struct tagCurrentTile
{
	int x;
	int y;
};
