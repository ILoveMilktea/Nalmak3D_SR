#pragma once

enum OBJECT_TAG
{
	OBJECT_TAG_DEFAULT,
	OBJECT_TAG_CAMERA,
	OBJECT_TAG_TARGET,
	OBJECT_TAG_PLAYER,
	OBJECT_TAG_BULLET_PLAYER,
	OBJECT_TAG_ENEMY,
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
	CANVAS_GROUP_MAX,
};


enum ENEMY_STATE
{
	IDLE,
	CHASE,
	HOLD,
	DROP,
	DEATH,
	ENEMY_STATE_MAX
};

enum ITEMTYPE {
	ITEMTYPE_MISSILE,
	ITEMTYPE_CANNON,
	ITEMTYPE_MAX

};
