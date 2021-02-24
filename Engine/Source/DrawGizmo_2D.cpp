#include "DrawGizmo_2D.h"
#include "Transform.h"
#include "CanvasRenderer.h"
#include "CanvasPicking.h"
#include "PositionHandle_2D.h"
#include "SingleImage.h"


DrawGizmo_2D::DrawGizmo_2D(Desc * _desc)
{
}

DrawGizmo_2D::~DrawGizmo_2D()
{
}


void DrawGizmo_2D::SetActiveHandles(bool _value)
{
	m_rightHandle->SetActive(_value);
	m_upHandle->SetActive(_value);
}

bool DrawGizmo_2D::CheckHandlePicked()
{
	PositionHandle_2D* rightHandle = m_rightHandle->GetComponent<PositionHandle_2D>();
	if (rightHandle)
	{
		if(rightHandle->CheckPicked())
			return true;
	}

	PositionHandle_2D* upHandle = m_upHandle->GetComponent<PositionHandle_2D>();
	if (upHandle)
	{
		if (upHandle->CheckPicked())
			return true;
	}
	
	return false;
}

void DrawGizmo_2D::ResetingHandlePosition()
{
	m_rightHandle->GetComponent<PositionHandle_2D>()->ResetingPosition();
	m_upHandle->GetComponent<PositionHandle_2D>()->ResetingPosition();
}

void DrawGizmo_2D::Initialize()
{
	m_line = LineManager::GetInstance();

	CanvasRenderer::Desc desc_cr;
	PositionHandle_2D::Desc desc_ph;

	//desc_cr.mtrlName = L"UI_red";
	desc_ph.dir = PositionHandle_2D::RIGHT;
	desc_ph.target = m_transform;
	m_rightHandle =
		INSTANTIATE()->
		AddComponent<CanvasRenderer>(&desc_cr)->
		AddComponent<SingleImage>()->
		AddComponent<CanvasPicking>()->
		AddComponent<PositionHandle_2D>(&desc_ph)->
		SetScale(20.f, 20.f);
	//m_rightHandle->SetParents(m_gameObject);
	m_rightHandle->GetComponent<CanvasRenderer>()->SetColor({ 1.f,0.f,0.f,1.f });

	//desc_cr.mtrlName = L"UI_green";
	desc_ph.dir = PositionHandle_2D::UP;
	m_upHandle =
		INSTANTIATE()->
		AddComponent<CanvasRenderer>(&desc_cr)->
		AddComponent<SingleImage>()->
		AddComponent<CanvasPicking>()->
		AddComponent<PositionHandle_2D>(&desc_ph)->
		SetScale(20.f, 20.f);
	//m_upHandle->SetParents(m_gameObject);
	m_upHandle->GetComponent<CanvasRenderer>()->SetColor({ 0.f,1.f,0.f,1.f });
}

void DrawGizmo_2D::Update()
{
}

void DrawGizmo_2D::LateUpdate()
{
	//Matrix world = m_transform->GetNoneScaleWorldMatrix();
	//m_line->DrawLine(m_transform->position, m_transform->position + Vector3(world._11, world._12, world._13), DEBUG_COLOR_RED);		// right
	//m_line->DrawLine(m_transform->position, m_transform->position + Vector3(world._21, world._22, world._23), DEBUG_COLOR_GREEN);	// up

}
