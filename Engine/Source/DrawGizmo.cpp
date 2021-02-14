#include "..\Include\DrawGizmo.h"
#include "Transform.h"



DrawGizmo::DrawGizmo(Desc * _desc)
{
}

DrawGizmo::~DrawGizmo()
{
}

void DrawGizmo::Initialize()
{
	m_line = LineManager::GetInstance();
}

void DrawGizmo::Update()
{

}

void DrawGizmo::LateUpdate()
{
	Matrix world = m_transform->GetNoneScaleWorldMatrix();
	m_line->DrawLine(m_transform->position, m_transform->position + Vector3(world._11, world._12, world._13), DEBUG_COLOR_RED);
	m_line->DrawLine(m_transform->position, m_transform->position + Vector3(world._21, world._22, world._23), DEBUG_COLOR_GREEN);
	m_line->DrawLine(m_transform->position, m_transform->position + Vector3(world._31, world._32, world._33), DEBUG_COLOR_BLUE);

}
