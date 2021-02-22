#pragma once

#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__

#include "Nalmak_Include.h"
#include "Component.h"
BEGIN(Nalmak)
class RenderManager;
class NALMAK_DLL Transform : public Component
{
public:
	struct Desc
	{

	};
public:
	Transform(Desc* _desc);
	~Transform();
private:
	// ComponentÀ»(¸¦) ÅëÇØ »ó¼ÓµÊ
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;
public:
	void UpdateMatrix();
	void UpdateUIMatrix();
public:
	Vector3		position = { 0,0,0 };
	Quaternion	rotation = { 0,0,0,1 };
	Vector3		scale = { 1,1,1 };
private:
	Matrix		worldMatrix;
	Matrix		noneScaleWorldMatrix;

public: /* For Rendering */
	const Matrix& GetWorldMatrix();
	const Matrix& GetUIWorldMatrix();
	const Matrix& GetNoneScaleWorldMatrix();
	Vector3 GetWorldPosition();
	Quaternion GetWorldRotation();
	Vector3 GetForward();
	Vector3 GetRight();
	Vector3 GetUp();

public:
	void GetRotationX(Vector3* _out, Vector3 _in);	// Radian
	void GetRotationY(Vector3* _out, Vector3 _in);	// Radian
	void GetRotationZ(Vector3* _out, Vector3 _in);	// Radian

public:	/* For Rotate*/
	void SetRotation(float _ex, float _ey, float _ez);
	void SetRotationX(float _ex);
	void SetRotationY(float _ey);
	void SetRotationZ(float _ez);

public:
	void RotateX(float _ex);
	void RotateY(float _ey);
	void RotateZ(float _ez);

	Vector3 GetEulerRotation();
	void RotateRollPitchYaw(float _x, float _y, float _z);
	Quaternion RotateAxis(const Vector3& _axis, float _angle);
	void ResetRelative();

	void LookAt(GameObject* _Target, float _Spd, Quaternion* _qOut); // transform 받는거로 아래 추가?
private:
	list<Transform*>   m_childs;
	Transform * m_parents = nullptr;
public:
	Transform* GetChild(int _index);
	size_t GetChildCount();
	void SetParents(Transform* _parents);
	void SetParents(GameObject* _parents);
	void AddChild(Transform* _child);
	void DeleteChild(Transform* _child);
	void DeleteParent();
	Transform* GetParents();

private:
	virtual void SetTransform(Transform* _transform) override;

	RenderManager* m_renderManager;

};

END

#endif // !__TRANSFORM_H__
