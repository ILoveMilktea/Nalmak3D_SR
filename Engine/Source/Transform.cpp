#include "Transform.h"

USING(Nalmak)


Transform::Transform(Desc * _desc)
{

}


Transform::~Transform()
{
	
}

void Transform::Initialize()
{
	UpdateMatrix();
}

void Transform::Update()
{
}

void Transform::LateUpdate()
{
}

void Transform::Release()
{
	if (m_parents)
	{
		m_parents->DeleteChild(this);
		m_parents = nullptr;
	}

	
	for (auto& child : m_childs)
	{
		child->DeleteParent();
	}
}

void Transform::UpdateMatrix()
{
	Matrix matTrans, matRot, matScale;
	D3DXMatrixTranslation(&matTrans, position.x, position.y, position.z);
	D3DXMatrixRotationQuaternion(&matRot, &rotation);
	D3DXMatrixScaling(&matScale, scale.x, scale.y, scale.z);

	if (m_parents)
		worldMatrix = matScale * matRot * matTrans * m_parents->GetNoneScaleWorldMatrix();
	else
		worldMatrix = matScale * matRot * matTrans;
}

const Matrix & Transform::GetWorldMatrix()
{
	if (!m_gameObject->IsStatic())
		UpdateMatrix();
	return worldMatrix;
}

const Matrix & Transform::GetNoneScaleWorldMatrix()
{
	Matrix matTrans, matRot;
	D3DXMatrixTranslation(&matTrans, position.x, position.y, position.z);
	D3DXMatrixRotationQuaternion(&matRot, &rotation);

	if (m_parents)
		noneScaleWorldMatrix = matRot * matTrans * m_parents->GetNoneScaleWorldMatrix();
	else
		noneScaleWorldMatrix = matRot * matTrans;

	return noneScaleWorldMatrix;
}

Vector3 Transform::GetWorldPosition()
{
	if (!m_gameObject->IsStatic())
		UpdateMatrix();

	return Vector3(worldMatrix._41, worldMatrix._42, worldMatrix._43);
}

Quaternion Transform::GetWorldRotation()
{
	if (m_parents)
		return rotation * m_parents->GetWorldRotation();
	else
		 return rotation;
}

Vector3 Transform::GetForward()
{
	if (!m_gameObject->IsStatic())
		UpdateMatrix();
	Vector3 dir = Nalmak_Math::Normalize(Vector3(worldMatrix._31, worldMatrix._32, worldMatrix._33));
	return dir;

}

Vector3 Transform::GetRight()
{
	if (!m_gameObject->IsStatic())
		UpdateMatrix();
	Vector3 dir = Nalmak_Math::Normalize(Vector3(worldMatrix._11, worldMatrix._12, worldMatrix._13));
	return dir;
}

Vector3 Transform::GetUp()
{
	if (!m_gameObject->IsStatic())
		UpdateMatrix();
	Vector3 dir = Nalmak_Math::Normalize(Vector3(worldMatrix._21, worldMatrix._22, worldMatrix._23));
	return dir;
}


void Transform::SetRotation(float _ex, float _ey, float _ez)
{
	D3DXQuaternionRotationYawPitchRoll(&rotation, Deg2Rad *_ey, Deg2Rad * _ex, Deg2Rad * _ez);

	//D3DXQuaternionIdentity(&rotation);
	//RotateX(_ex);
	//RotateY(_ey);
	//RotateZ(_ez);
}

void Transform::SetRotationX(float _ex)
{
	Vector3 CurrentAngle = Nalmak_Math::QuaternionToEuler(rotation);
	RotateX(-CurrentAngle.x);
	RotateX(_ex);
}

void Transform::SetRotationY(float _ey)
{
	Vector3 CurrentAngle = Nalmak_Math::QuaternionToEuler(rotation);
	RotateY(-CurrentAngle.y);
	RotateY(_ey);
}

void Transform::SetRotationZ(float _ez)
{
	Vector3 CurrentAngle = Nalmak_Math::QuaternionToEuler(rotation);
	RotateZ(-CurrentAngle.z);
	RotateZ(_ez);
}

void Transform::RotateX(float _ex)
{
	Quaternion rot;
	D3DXQuaternionIdentity(&rot);
	D3DXQuaternionRotationAxis(&rot, &Vector3(1.f, 0.f, 0.f), Deg2Rad * _ex); // radian

	rotation *= rot;
}

void Transform::RotateY(float _ey)
{
	//D3DXQuaternionRotationAxis(&rotation, &GetUp(), _ey);
	Quaternion rot;
	D3DXQuaternionIdentity(&rot);
	D3DXQuaternionRotationAxis(&rot, &Vector3(0.f, 1.f, 0.f), Deg2Rad * _ey); // radian

	rotation *= rot;

}

void Transform::RotateZ(float _ez)
{
	//D3DXQuaternionRotationAxis(&rotation, &GetForward(), _ez);
	Quaternion rot;
	D3DXQuaternionIdentity(&rot);
	D3DXQuaternionRotationAxis(&rot, &Vector3(0.f, 0.f, 1.f), Deg2Rad * _ez); // radian

	rotation *= rot;
}


Vector3 Transform::GetEulerRotation()
{
	return Nalmak_Math::QuaternionToEuler(rotation);
}

void Transform::RotateRollPitchYaw(float _x, float _y, float _z)
{
	Quaternion rot;
	D3DXQuaternionRotationYawPitchRoll(&rot, _y, _x, _z);
	m_transform->rotation *= rot;
}

Quaternion Transform::RotateAxis(const Vector3 & _axis, float _angle)
{
	Quaternion rot;
	D3DXQuaternionRotationAxis(&rot, &_axis, _angle);
	return rot;
}

void Transform::ResetRelative()
{
	m_parents = nullptr;
	m_childs.clear();
}



Transform * Transform::GetChild(int _index)
{
	int i = 0;
	for (auto iter = m_childs.begin(); iter != m_childs.end(); ++iter, ++i)
	{
		if (i == _index)
			return *iter;
	}

	return nullptr;
}

size_t Transform::GetChildCount()
{
	return m_childs.size();
}


void Transform::SetParents(Transform * _parents)
{
	assert("parents is nullptr" && _parents);

	m_parents = _parents;
	_parents->AddChild(this);
}

void Transform::SetParents(GameObject * _parents)
{
	Transform* parents = _parents->GetTransform();
	assert("parent is nullptr" && parents);
	assert("parents are themselves" && !(parents == this));

	m_parents = _parents->GetTransform();
	_parents->GetTransform()->AddChild(this);
}

void Transform::AddChild(Transform * _child)
{
	m_childs.emplace_back(_child);
}

void Transform::DeleteChild(Transform * _child)
{
	for (auto iter = m_childs.begin(); iter != m_childs.end(); ++iter)
	{
		if ((*iter) == _child)
		{
			m_childs.erase(iter);
			return;
		}
	}
}

void Transform::DeleteParent()
{
	m_parents = nullptr;
}

Transform * Transform::GetParents()
{
	return m_parents;
}

void Transform::SetTransform(Transform * _transform)
{
	m_transform = this;
}
