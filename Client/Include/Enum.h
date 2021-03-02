#pragma once

enum OBJECT_TAG
{
	OBJECT_TAG_DEFAULT,
	OBJECT_TAG_CAMERA,
	OBJECT_TAG_TARGET,
	OBJECT_TAG_PLAYER,
	OBJECT_TAG_PLAYER_SHIELD,
	OBJECT_TAG_ENEMY,
	OBJECT_TAG_BOSS,
	OBJECT_TAG_BULLET_PLAYER,
	OBJECT_TAG_BULLET_ENEMY,
	OBJECT_TAG_GARAGE_OBJECT,
	OBJECT_TAG_DEBUG,
	OBJECT_TAG_UI,
	OBJECT_TAG_MAX
};

enum COLLISION_LAYER
{
	COLLISION_LAYER_DEFAULT,
	COLLISION_LAYER_PLAYER,
	COLLISION_LAYER_SHIELD,
	COLLISION_LAYER_BULLET_PLAYER,
	COLLISION_LAYER_ENEMY,
	COLLISION_LAYER_BULLET_ENEMY,
	COLLISION_LAYER_MAX
};

enum RENDER_LAYER
{
	RENDER_LAYER_DEFAULT,
	RENDER_LAYER_UI,
	RENDER_LAYER_DEBUG,
	RENDER_LAYER_MAX
};

enum CANVAS_GROUP
{
	CANVAS_GROUP_NONE,
	CANVAS_GROUP_G1,
	CANVAS_GROUP_G2,
	CANVAS_GROUP_G3,
	CANVAS_GROUP_MAINWND,
	CANVAS_GROUP_MAINWND_MAIN,
	CANVAS_GROUP_MAINWND_SHOP,
	CANVAS_GROUP_MAINWND_EQUIP,
	CANVAS_GROUP_STAGEWND,
	CANVAS_GROUP_STAGE1,
	CANVAS_GROUP_BOSSHP,
	CANVAS_GROUP_MAX,
};


enum ENEMY_STATE
{
	IDLE,
	CHASE,
	HOLD,
	DROP,
	EXPLOSION,
	FALLING,
	DEATH,
	ENEMY_STATE_MAX
};

enum ENEMY_EVASION_STATE
{
	SLIDE,
	DIAGONAL,
	CROSSFIRE,
	LOOK,
	CIRCLE,
	PRYMIDE,
	AIRFIRE,
	EVASION_STATE_MAX
};

enum ITEMTYPE {
	ITEMTYPE_MISSILE,
	ITEMTYPE_CANNON,
	ITEMTYPE_MAX

};

enum PARTS_NUM
{
	FIRST_PARTS,
	SECOND_PARTS,
	THIRD_PARTS,
	PARTS_MAX
};

enum MOVE_PATTERN
{
	MOVE_AXISDIR,
	MOVE_GUIDE,
	MOVE_MAX
};

