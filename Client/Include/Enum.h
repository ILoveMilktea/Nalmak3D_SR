#pragma once

enum OBJECT_TAG
{
	OBJECT_TAG_DEFAULT,
	OBJECT_TAG_CAMERA,
	OBJECT_TAG_TARGET,
	OBJECT_TAG_BULLET,
	OBJECT_TAG_PLAYER,
	OBJECT_TAG_ENEMY,
	OBJECT_TAG_GARAGE_OBJECT,
	OBJECT_TAG_DEBUG,
	OBJECT_TAG_UI,
	OBJECT_TAG_MAX
};

enum COLLISION_LAYER
{
	COLLISION_LAYER_DEFAULT,
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
	CANVAS_GROUP_MAX,
};

