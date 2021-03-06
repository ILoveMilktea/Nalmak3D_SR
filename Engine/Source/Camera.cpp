#include "Camera.h"
#include "Transform.h"
#include "ResourceManager.h"
#include "IRenderer.h"
#include "DepthStencil.h"
#include "CanvasRenderer.h"


#include "VIBufferRenderer.h"
USING(Nalmak)

Camera::Camera(Desc * _desc)
{
	m_fovY = _desc->fovY;
	
	m_zNear = _desc->zNear;
	m_zFar = _desc->zFar;
	m_mode = _desc->mode;
	
	

	
	if (_desc->width == 0)
		m_width = (float)RenderManager::GetInstance()->GetWindowWidth();
	else
		m_width = (float)_desc->width;
	if(_desc->height == 0)
		m_height = (float)RenderManager::GetInstance()->GetWindowHeight();
	else
		m_height = (float)_desc->height;
	
	m_aspect = m_width / m_height;
	m_renderTargets.assign(4, nullptr);
	m_renderingMode = _desc->renderMode;
	if (m_renderingMode == CAMERA_RENDERING_MODE_DEFERRED)
	{
			
	}
	UpdateProjMatrix();

	RenderManager::GetInstance()->AddCamera(this);
	
	UpdateProjMatrix();
}

void Camera::Initialize()
{

	
	m_handle = DeviceManager::GetInstance()->GetHWND();
}

void Camera::Update()
{
	
}

void Camera::LateUpdate()
{
}

void Camera::Release()
{
	RenderManager::GetInstance()->DeleteCamera(this);
}

void Camera::PreRender()
{
	UpdateFrustumPlane();
}

const Matrix Camera::GetViewMatrix() const
{
	Matrix matrix;
	Vector3 worldPos = m_transform->GetWorldPosition();
	if (m_mode == CAMERA_PROJECTION_MODE_PERSPECTIVE)
	{
		Quaternion rot = m_transform->GetWorldRotation();
		Matrix rotMatrix;
		D3DXMatrixRotationQuaternion(&rotMatrix, &rot);
		Vector3 eye = worldPos;
		Vector3 at =Vector3(0, 0, 1);
		D3DXVec3TransformCoord(&at, &at, &rotMatrix);
		at += worldPos;
		Vector3 up = Vector3(0, 1, 0);
		D3DXVec3TransformCoord(&up, &up, &rotMatrix);

	/*	Vector3 eye = worldPos;
		Vector3 at = worldPos + Vector3(0, 0, 1);
		Vector3 up = Vector3(0, 1, 0);*/

		D3DXMatrixLookAtLH(&matrix, &eye, &at, &up);
	}
	else if (m_mode == CAMERA_PROJECTION_MODE_ORTHOGRAPHIC)
	{
		Vector3 eye = worldPos;
		Vector3 at = worldPos + Vector3(0, 0, 1);
		Vector3 up = Vector3(0, 1, 0);

		D3DXMatrixLookAtLH(&matrix, &eye, &at, &up);
	}

	return matrix;
}

const Matrix Camera::GetViewportMatrix() const
{
	float halfWincx = RenderManager::GetInstance()->GetWindowWidth() * 0.5f;
	float halfWincy = RenderManager::GetInstance()->GetWindowHeight() * 0.5f;

	return Matrix
	{
		halfWincx, 0.f        , 0.f             , 0.f,
		0.f       , -halfWincy, 0.f             , 0.f,
		0.f       , 0.f        , m_zFar - m_zNear, 0.f,
		halfWincx, halfWincy , m_zNear         , 1.f
	};
}

Vector2 Camera::WorldToScreenPos(const Vector3 & _pos)
{
	float halfWincx = RenderManager::GetInstance()->GetWindowWidth() * 0.5f;
	float halfWincy = RenderManager::GetInstance()->GetWindowHeight() * 0.5f;

	Vector3 temp;
	D3DXVec3TransformCoord(&temp, &_pos, &GetViewMatrix());
	D3DXVec3TransformCoord(&temp, &temp, &GetProjMatrix());
	D3DXVec3TransformCoord(&temp, &temp, &GetViewportMatrix());

	return Vector2(temp.x - halfWincx, halfWincy - temp.y);
}



bool Camera::IsInFrustumCulling(IRenderer * _renderer)
{
	if (!_renderer->IsFrustumCulling())
		return true;

	RENDERER_TYPE type = _renderer->GetType();
	switch (type)
	{
	case RENDERER_TYPE_MESH:
	case RENDERER_TYPE_VIBUFFER:
	{
		float radius = _renderer->GetBoundingRadius() * 2;

		Transform* trs = _renderer->GetTransform();
		Vector3 Center = trs->GetWorldPosition() + _renderer->GetBoundingCenter();
		float scale = max(trs->scale.z, max(trs->scale.x, trs->scale.y));
		radius *= scale;
		for (int i = 0; i < 6; ++i)
		{
			float distance = Vector::Dot(Center, Vector3(m_frustumPlane[i].a, m_frustumPlane[i].b, m_frustumPlane[i].c)) + m_frustumPlane[i].d + radius;
			if (distance < 0)
			{
				return false;
			}
		}
		break;
	}
	case RENDERER_TYPE_PARTICLE:
	case RENDERER_TYPE_TRAIL:
		break;
	case RENDERER_TYPE_CANVAS:
		RECT* boundary = ((CanvasRenderer*)_renderer)->GetBoundary();
		if (boundary->left >= (LONG)RenderManager::GetInstance()->GetWindowWidth() ||
			boundary->right <= 0 ||
			boundary->top >= (LONG)RenderManager::GetInstance()->GetWindowHeight() ||
			boundary->bottom <= 0)
			return false;
		break;
	}

	return true;
}

bool Camera::IsInFrustumCulling(const Vector3 & _pos, float _radius)
{
	if (m_mode != CAMERA_PROJECTION_MODE_PERSPECTIVE)
		return true;

	Vector3 Center = _pos;
	float radius = _radius;
	for (int i = 0; i < 6; ++i)
	{
		float distance = Vector::Dot(Center, Vector3(m_frustumPlane[i].a, m_frustumPlane[i].b, m_frustumPlane[i].c)) + m_frustumPlane[i].d + radius;
		if (distance < 0)
		{
			return false;
		}
	}
	return true;
}

Vector3 Camera::GetCamToMouseWorldDirection()
{
	float wincx = (float)RenderManager::GetInstance()->GetWindowWidth();
	float wincy = (float)RenderManager::GetInstance()->GetWindowHeight();

	POINT point = {};
	GetCursorPos(&point);
	ScreenToClient(m_handle, &point);

	Vector2 screenPos;
	screenPos.x = (float)point.x;
	screenPos.y = (float)point.y;


	Vector3 camToScreenDirection_ViewSpace;
	Vector3 camToScreenDirection_WorldSpace;
	Matrix invView;
	camToScreenDirection_ViewSpace.x = (((2.0f * screenPos.x) / wincx) - 1.0f) / GetProjMatrix()._11;
	camToScreenDirection_ViewSpace.y = (((-2.0f * screenPos.y) / wincy) + 1.0f) / GetProjMatrix()._22;
	camToScreenDirection_ViewSpace.z = 1.0f;

	D3DXMatrixInverse(&invView, nullptr, &GetViewMatrix());

	D3DXVec3TransformCoord(&camToScreenDirection_WorldSpace, &camToScreenDirection_ViewSpace, &invView);
	return Vector::Normalize(camToScreenDirection_WorldSpace - m_transform->GetWorldPosition());

	
}



void Camera::SetRenderTarget(UINT _index, wstring  _rtName)
{
	if (_index > 3 || _index < 0)
	{
		assert(0 && L"Directx9 can only use 4 render targets at a time");
	}
	m_renderTargets[_index] = ResourceManager::GetInstance()->GetResource<RenderTarget>(_rtName);
}


void Camera::RecordRenderTarget()
{
	int i = 0;
	for (auto& rt : m_renderTargets)
	{
		if (rt)
			rt->StartRecord(i);
		++i;
	}
}

void Camera::EndRenderTarget()
{
	for (auto& rt : m_renderTargets)
	{
		if (rt)
			rt->EndRecord();
	}
}

void Camera::AllOnLayer()
{
	m_layer.AllOn();
}

void Camera::AllOffLayer()
{
	m_layer.AllOff();
}

void Camera::OnLayer(_RENDER_LAYER _layer)
{
	m_layer.On(_layer);
}

void Camera::OffLayer(_RENDER_LAYER _layer)
{
	m_layer.Off(_layer);
}

void Camera::UpdateFrustumPlane()
{
	Matrix comboMatrix = GetViewMatrix() * GetProjMatrix();

	m_frustumPlane[0].a = comboMatrix._14 + comboMatrix._11;
	m_frustumPlane[0].b = comboMatrix._24 + comboMatrix._21;
	m_frustumPlane[0].c = comboMatrix._34 + comboMatrix._31;
	m_frustumPlane[0].d = comboMatrix._44 + comboMatrix._41;

	m_frustumPlane[1].a = comboMatrix._14 - comboMatrix._11;
	m_frustumPlane[1].b = comboMatrix._24 - comboMatrix._21;
	m_frustumPlane[1].c = comboMatrix._34 - comboMatrix._31;
	m_frustumPlane[1].d = comboMatrix._44 - comboMatrix._41;

	m_frustumPlane[2].a = comboMatrix._14 - comboMatrix._12;
	m_frustumPlane[2].b = comboMatrix._24 - comboMatrix._22;
	m_frustumPlane[2].c = comboMatrix._34 - comboMatrix._32;
	m_frustumPlane[2].d = comboMatrix._44 - comboMatrix._42;

	m_frustumPlane[3].a = comboMatrix._14 + comboMatrix._12;
	m_frustumPlane[3].b = comboMatrix._24 + comboMatrix._22;
	m_frustumPlane[3].c = comboMatrix._34 + comboMatrix._32;
	m_frustumPlane[3].d = comboMatrix._44 + comboMatrix._42;

	m_frustumPlane[4].a = comboMatrix._13;
	m_frustumPlane[4].b = comboMatrix._23;
	m_frustumPlane[4].c = comboMatrix._33;
	m_frustumPlane[4].d = comboMatrix._43;

	m_frustumPlane[5].a = comboMatrix._14 - comboMatrix._13;
	m_frustumPlane[5].b = comboMatrix._24 - comboMatrix._23;
	m_frustumPlane[5].c = comboMatrix._34 - comboMatrix._33;
	m_frustumPlane[5].d = comboMatrix._44 - comboMatrix._43;
}

void Camera::UpdateProjMatrix()
{
	if (m_mode == CAMERA_PROJECTION_MODE_PERSPECTIVE)
	{
		D3DXMatrixPerspectiveFovLH(
			&m_projMatrix,
			m_fovY,
			m_aspect,
			m_zNear,
			m_zFar);
	}
	else if (m_mode == CAMERA_PROJECTION_MODE_ORTHOGRAPHIC)
	{
		D3DXMatrixOrthoLH(
			&m_projMatrix,
			m_width,
			m_height,
			m_zNear,
			m_zFar
		);
	}
}

