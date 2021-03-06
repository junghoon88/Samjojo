#pragma once

#define BTN_PLAYER_UP 		VK_UP		   //
#define BTN_PLAYER_DOWN		VK_DOWN		   //
#define BTN_PLAYER_LEFT		VK_LEFT		   //
#define BTN_PLAYER_RIGHT	VK_RIGHT	   //

#define CAMERA_SPEED		24

#define MAP_WIDTH			WINSIZEX
#define MAP_HEIGHT			WINSIZEY


#define FACE_MAX			300
#define NORMAL_IMAGE_MAX	1
#define COMBAT_IMAGE_MAX	26
#define WEAPON_IMAGE_MAX	1
#define ARMOR_IMAGE_MAX		1
#define SUBITEM_IMAGE_MAX	1

#define UNIT_ATTACK_RANGE_MAX	7

typedef enum DIRECTION
{
	DIRECTION_DN,
	DIRECTION_UP,
	DIRECTION_LF,
	DIRECTION_RG,
};

enum ATTACK_RANGE
{
	ATTACK_RANGE_MELEE4,	//1ĭ�� 4����
	ATTACK_RANGE_MELEE8,	//1ĭ�� 8����
	ATTACK_RANGE_ARROW2,	//2ĭ
};

enum TEAM
{
	TEAM_NONE = -1,

	TEAM_PLAYER,
	TEAM_FRIEND,
	TEAM_ENEMY,

	TEAM_MAX
};


enum UNIT_BATTLE_IMAGE
{
	UNIT_BATTLE_IMAGE_JOJO,		//����
	UNIT_BATTLE_IMAGE_HAHU,		//���ĵ�
	UNIT_BATTLE_IMAGE_YUPO,		//����
	UNIT_BATTLE_IMAGE1,			//����
	UNIT_BATTLE_IMAGE2,			//�⺴
	UNIT_BATTLE_IMAGE3,			//�ú�
	UNIT_BATTLE_IMAGE4,			//�ñ⺴
	UNIT_BATTLE_IMAGE5,			//����
	UNIT_BATTLE_IMAGE6,			//����
	UNIT_BATTLE_IMAGE7,			//������
	UNIT_BATTLE_IMAGE8,			//����

	UNIT_BATTLE_IMAGE_MAX,
};

enum FONTVERSION
{
	FONTVERSION_SAMJOJO,
	FONTVERSION_STORY,
	FONTVERSION_SAMJOJO_AJINJI,
	FONTVERSION_SAMJOJO_ASEJONG,
	FONTVERSION_SAMJOJO_HEE,
	FONTVERSION_BATTLETURN,

	FONTVERSION_MAX
};

enum BRUSHVERSION
{
	BRUSHVERSION_WHITE,
	BRUSHVERSION_GRAY,
	BRUSHVERSION_MARGENTA,
	BRUSHVERSION_TILE,


	BRUSHVERSION_MAX
};