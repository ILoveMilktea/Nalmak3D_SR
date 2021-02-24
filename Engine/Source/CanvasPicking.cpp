#include "..\Include\CanvasPicking.h"

#include "CanvasRenderer.h"
#include "Transform.h"
#include "DrawGizmo_2D.h"
#include "RenderManager.h"
#include "PositionHandle_2D.h"

CanvasPicking::CanvasPicking(Desc * _desc)
{
}

void CanvasPicking::Initialize()
{
	m_renderer = GetComponent<CanvasRenderer>();
	m_gizmo = GetComponent<DrawGizmo_2D>();
	m_handle = GetComponent<PositionHandle_2D>();
}

void CanvasPicking::Update()
{
	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_LEFT_MOUSE))
	{
		if (m_gizmo)
		{
			if (m_renderer->IsCursorOnRect())
			{
				m_gizmo->SetActiveHandles(true);
			}
			else
			{
				if (!m_gizmo->CheckHandlePicked())
				{
					m_gizmo->SetActiveHandles(false);
				}
			}
		}
		else if (m_handle)
		{
			if (m_renderer->IsCursorOnRect())
			{
				m_handle->PickHandle(true);
			}
		}
	}

	if (InputManager::GetInstance()->GetKeyUp(KEY_STATE_LEFT_MOUSE))
	{
		if (m_handle)
		{
			m_handle->PickHandle(false);
		}
	}
}