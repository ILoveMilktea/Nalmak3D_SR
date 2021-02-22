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
// ���� ��� ����
// ���̴��� �ٲ� �� ���� ���������� �� �����ʹ� ������ ������
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
// INPUT LAYOUT �߰� �� �� �ؾ��Ұ�!!
//  1. VERTEX_INPUT_LAYOUT enum �߰� 
//  2. Shader Initialize inputLayout���� �б⹮ �߰�
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


// �ϴ� �Ⱦ�
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