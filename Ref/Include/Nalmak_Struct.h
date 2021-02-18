#pragma once

#ifndef __NALMAK_STRUCT_H__
#define __NALMAK_STRUCT_H__

#include "Nalmak_Include.h"


struct BaseLightInfo
{
	Vector3 color = Vector3(1,1,1);
	float ambientIntensity = 0.01f;
	float diffuseIntensity = 0.2f;
};

struct PointLightInfo
{
	BaseLightInfo base;

	Vector3 position;

	float constant;
	float linearRatio;
	float exp;

};

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

//struct DirectionalLightInfo
//{
//	BaseLightInfo base;
//	Vector3 Direction;
//};


struct ConstantBuffer
{
	Matrix viewProj;
	Matrix invView;
	Matrix invProj;
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