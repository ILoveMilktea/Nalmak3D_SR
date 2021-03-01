#pragma once
#ifndef __NALMAK_ENUM_H__
#define __NALMAK_ENUM_H__

enum VERTEX_INPUT_LAYOUT
{
	VERTEX_INPUT_LAYOUT_POSITION,
	VERTEX_INPUT_LAYOUT_POSITION_UV,
	VERTEX_INPUT_LAYOUT_POSITION_NORMAL_UV,
	VERTEX_INPUT_LAYOUT_SKYBOX,
	VERTEX_INPUT_LAYOUT_PARTICLE,
	VERTEX_INPUT_LAYOUT_MAX
};

enum DRAW_PRIMITIVE_TYPE
{
	DRAW_PRIMITIVE_TYPE_POINTLIST,
	DRAW_PRIMITIVE_TYPE_LINELIST,
	DRAW_PRIMITIVE_TYPE_TRIANGLELIST,
};

enum RENDERING_MODE
{
	RENDERING_MODE_BACKGROUND,
	RENDERING_MODE_OPAQUE,
	RENDERING_MODE_CUTOUT,
	RENDERING_MODE_TRANSPARENT,
	RENDERING_MODE_MAX
};

enum BLENDING_MODE
{
	BLENDING_MODE_DEFAULT,
	BLENDING_MODE_ADDITIVE,
	BLENDING_MODE_SUBTRACTIVE,
	BLENDING_MODE_MULTIPLY,
	BLENDING_MODE_MAX
};

enum TEXTURE_FORMAT
{
	TEXTURE_FORMAT_A8R8G8B8,
	TEXTURE_FORMAT_D24S8,
	TEXTURE_FORMAT_G32R32F,
	TEXTURE_FORMAT_A32B32G32R32F,
	TEXTURE_FORMAT_MAX,
};

enum DEPTH_STENCIL_FORMAT
{
	DEPTH_STENCIL_FORMAT_D16,
	DEPTH_STENCIL_FORMAT_D24S8,
	DEPTH_STENCIL_FORMAT_D32,
	DEPTH_STENCIL_FORMAT_MAX
};

enum FILL_MODE
{
	FILL_MODE_SOLID,
	FILL_MODE_WIREFRAME,
	FILL_MODE_POINT,
	FILL_MODE_MAX
};

enum LIGHT_MODE
{
	LIGHT_MODE_DIRECTIONAL,
	LIGHT_MODE_POINT,
	LIGHT_MODE_SPOT,
	LIGHT_MODE_MAX
};
enum CAMERA_PROJECTION_MODE
{
	CAMERA_PROJECTION_MODE_PERSPECTIVE,
	CAMERA_PROJECTION_MODE_ORTHOGRAPHIC,
	CAMERA_PROJECTION_MODE_MAX
};

enum CAMERA_RENDERING_MODE
{
	CAMERA_RENDERING_MODE_DEFERRED,
	CAMERA_RENDERING_MODE_FORWARD,
	CAMERA_RENDERING_MODE_MAX
};

enum CAMERA_CLEAR_FLAGS
{
	CAMERA_CLEAR_FLAGS_SOLID,
	CAMERA_CLEAR_FLAGS_SKYBOX,
	CAMERA_CLEAR_FLAGS_DEPTHONLY,
	CAMERA_CLEAR_FLAGS_MAX
};
enum KEY_STATE
{
	KEY_STATE_LEFT_MOUSE,
	KEY_STATE_RIGHT_MOUSE,
	KEY_STATE_LEFT_ARROW,
	KEY_STATE_RIGHT_ARROW,
	KEY_STATE_DOWN_ARROW,
	KEY_STATE_UP_ARROW,
	KEY_STATE_WHEEL_MOUSE,
	KEY_STATE_ALT,
	KEY_STATE_TAB,
	KEY_STATE_ENTER,
	KEY_STATE_SHIFT,
	KEY_STATE_W,
	KEY_STATE_A,
	KEY_STATE_S,
	KEY_STATE_D,
	KEY_STATE_F,
	KEY_STATE_Q,
	KEY_STATE_O,
	KEY_STATE_K,
	KEY_STATE_L,
	KEY_STATE_P,
	KEY_STATE_E,
	KEY_STATE_R,
	KEY_STATE_C,
	KEY_STATE_F1,
	KEY_STATE_F2,
	KEY_STATE_F3,
	KEY_STATE_F4,
	KEY_STATE_1,
	KEY_STATE_2,
	KEY_STATE_3,
	KEY_STATE_SPACE,
	KEY_STATE_ESC,
	KEY_STATE_X,
	KEY_STATE_MAX
};

enum INTERPOLATION_TYPE
{
	INTERPOLATION_TYPE_ACCELERATE_DECELERTAE,
	INTERPOLATION_TYPE_ACCELERATE,
	INTERPOLATION_TYPE_DECELERATE,
	INTERPOLATION_TYPE_LINEAR,
	INTERPOLATION_TYPE_ANTICIPATE,
	INTERPOLATION_TYPE_OVERSHOOT,
	INTERPOLATION_TYPE_DECELERATE_ACCELERATE
};

enum PARTICLE_EMIT_SHAPE
{
	PARTICLE_EMIT_SHAPE_SPHERE,
	PARTICLE_EMIT_SHAPE_CIRCLE,
	PARTICLE_EMIT_SHAPE_BOX,
	PARTICLE_EMIT_SHAPE_CONE,
	PARTICLE_EMIT_SHAPE_MAX
};

enum COLLIDER_TYPE
{
	COLLIDER_TYPE_SPHERE,
	COLLIDER_TYPE_MAX
};

enum DEBUG_COLOR
{
	DEBUG_COLOR_RED,
	DEBUG_COLOR_GREEN,
	DEBUG_COLOR_BLUE,
	DEBUG_COLOR_MAX
};

enum BUTTON_TRANSITION
{
	BUTTON_TRANSITION_NONE,
	BUTTON_TRANSITION_COLOR,
	BUTTON_TRANSITION_SWAP,
	BUTTON_TRANSITION_MAX
};

enum BUTTON_STATE
{
	BUTTON_STATE_NORMAL,
	BUTTON_STATE_HIGHLIGHT,
	BUTTON_STATE_PRESSED,
	BUTTON_STATE_DISABLE,
	BUTTON_STATE_MAX
};

enum RENDERER_TYPE
{
	RENDERER_TYPE_MESH,
	RENDERER_TYPE_CANVAS,
	RENDERER_TYPE_PARTICLE,
	RENDERER_TYPE_MAX
};

#endif