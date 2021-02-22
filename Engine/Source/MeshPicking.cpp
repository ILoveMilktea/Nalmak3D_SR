#include "MeshPicking.h"
#include "MeshRenderer.h"
#include "Transform.h"
#include "Camera.h"
#include "DrawGizmo.h"
#include "RenderManager.h"
#include "PositionHandle.h"

MeshPicking::MeshPicking(Desc* _desc)
{
}


void MeshPicking::Initialize()
{
	m_renderer = GetComponent<MeshRenderer>();
	m_gizmo = GetComponent<DrawGizmo>();
	m_mainCam = RenderManager::GetInstance()->GetMainCamera();
}

void MeshPicking::Update()
{
	DEBUG_LOG(L"test", L"test");
	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_LEFT_MOUSE))
	{
		if (IsMousePicking())
		{
			if (m_gizmo)
			{
				m_gizmo->SetActiveHandles(true);
			}

			auto handle = GetComponent<PositionHandle>();
			if (handle)
			{
				handle->ActHandle(true);
			}
		}
		else
		{
			if (m_gizmo && m_gizmo->CheckHandlePicked())
			{
				m_gizmo->SetActiveHandles(false);
			}
		}
	}

	if (InputManager::GetInstance()->GetKeyUp(KEY_STATE_LEFT_MOUSE))
	{
		auto handle = GetComponent<PositionHandle>();
		if (handle)
		{
			handle->ActHandle(false);
		}
	}
}

void MeshPicking::OnTriggerEnter(Collisions & _collision)
{
	DEBUG_LOG(L"enter", L"collision");
}

void MeshPicking::OnTriggerStay(Collisions & _collision)
{
	DEBUG_LOG(L"stay", L"collision");
}

void MeshPicking::OnTriggerExit(Collisions & _collision)
{
	DEBUG_LOG(L"enter", L"collision");
}

bool MeshPicking::IsMousePicking()
{
	Matrix worldMat = m_transform->GetWorldMatrix();
	Vector3 rayPoint = m_mainCam->GetTransform()->GetWorldPosition();
	Vector3 rayDir = m_mainCam->GetCamToMouseWorldDirection();	// look
	
	VIBuffer* vibuffer = m_renderer->GetVIBuffer();
	int figureCount = vibuffer->GetFigureCount();
	INPUT_LAYOUT_POSITION_NORMAL_UV* vertices = vibuffer->GetVertices();
	short* indices = vibuffer->GetIndices();

	for (int i = 0; i < figureCount * 3; i += 3)
	{
		Vector3 v0;
		Vector3 v1;
		Vector3 v2;
		D3DXVec3TransformCoord(&v0, &vertices[indices[i]].position, &worldMat);
		D3DXVec3TransformCoord(&v1, &vertices[indices[i + 1]].position, &worldMat);
		D3DXVec3TransformCoord(&v2, &vertices[indices[i + 2]].position, &worldMat);
		Vector3 intersectPoint;
		if (Nalmak_Math::IsIntersectTriangle(
			rayPoint,
			rayDir,
			v0, 
			v1, 
			v2, 
			&intersectPoint))
		{
			return true;
		}
	}
	return false;
}
