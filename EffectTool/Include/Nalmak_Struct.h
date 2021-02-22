#pragma once

#ifndef __NALMAK_STRUCT_H__
#define __NALMAK_STRUCT_H__

#include "Nalmak_Include.h"

#pragma region LIGHT INFO

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
	float radius;
};

struct DirectionalLightInfo
{
	DirectionalLightInfo() = default;
	DirectionalLightInfo(Vector3 _direction, Vector3 _color, float _intensity ,float _ambientIntensity)
	{
		direction = _direction;

		base.color = _color;
		base.diffuseIntensity = _intensity;
		base.ambientIntensity = _ambientIntensity;
	}
	BaseLightInfo base;

	Vector3 direction;
};
#pragma endregion LIGHT INFO



/////////////////////////////////////////////////////////////////////////////////
// 공용 상수 버퍼
// 쉐이더가 바뀔 때 마다 공통적으로 이 데이터는 정보를 보내줌
#pragma region Constant Buffer

struct ConstantBuffer
{
	Matrix viewProj;
	Matrix invView;
	Matrix invProj;
	Vector3 worldCamPos;
};
#pragma endregion Constant Buffer
//
/////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////
// INPUT LAYOUT 추가 시 꼭 해야할것!!
//  1. VERTEX_INPUT_LAYOUT enum 추가 
//  2. Shader Initialize inputLayout마다 분기문 추가
#pragma region INPUT_LAYOUT
struct INPUT_LAYOUT_POSITION
{
	Vector3 position;
};

struct INPUT_LAYOUT_POSITION_UV
{
	Vector3 position;
	Vector2 uv;
};

struct INPUT_LAYOUT_POSITION_NORMAL_UV
{
	Vector3 position;
	Vector3 normal;
	Vector2 uv;
};

struct INPUT_LAYOUT_SKYBOX
{
	Vector3 position;
	Vector3 uvw;
};

struct INPUT_LAYOUT_PARTICLE
{
	Matrix worldMatrix;
	Vector4 color;
};


// 일단 안씀
//struct INPUT_LAYOUT_STATIC_MESH
//{
//	Matrix worldMatrix;
//};

#pragma endregion INPUT_LAYOUT
//
/////////////////////////////////////////////////////////////////////////////////

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