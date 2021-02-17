#pragma once

#ifndef __NALMAK_STRUCT_H__
#define __NALMAK_STRUCT_H__

#include "Nalmak_Include.h"

struct DirectionalLightInfo
{
	DirectionalLightInfo() = default;
	DirectionalLightInfo(Vector3 _dir, Vector3 _color, float _intensity)
	{
		direction = _dir;
		color = _color;
		intensity = _intensity;
	}
	Vector3 direction = Vector3(0, -0.6f, 0.3f);
	Vector3 color = Vector3(0.97f, 0.95f, 0.85f);
	float intensity = 1.f;
};

struct ConstantBuffer
{
	Matrix viewProj;
	Vector3 worldCamPos;

	int wincx;
	int wincy;

	int isDirectionalLight = 0;
	DirectionalLightInfo directionalLight;
};

struct INPUT_LAYOUT_POSITION_UV
{
	Vector3 position;
	Vector2 uv;
};

struct INPUT_LAYOUT_SKYBOX
{
	Vector3 position;
	Vector3 uvw;
};

struct INPUT_LAYOUT_POSITION
{
	Vector3 position;
};

struct INPUT_LAYOUT_POSITION_NORMAL_UV
{
	Vector3 position;
	Vector3 normal;
	Vector2 uv;
};

struct INPUT_LAYOUT_PARTICLE
{
	Matrix worldMatrix;
	Vector4 color;
};

struct INPUT_LAYOUT_STATIC_MESH
{
	Matrix worldMatrix;
};

struct TextureBuffer
{
	PDIRECT3DTEXTURE9 name;
	Vector4 color;
	Vector2 uvScaling;
};

struct Line
{
	Vector3 start, end;
};


#endif