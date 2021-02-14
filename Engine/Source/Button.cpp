#include "..\Include\Button.h"
#include "Transform.h"

Button::Button(Desc * _desc)
{
	m_event += _desc->eventFunc;
}

void Button::Initialize()
{
	m_input = InputManager::GetInstance();
}

void Button::Update()
{
	if (m_input->GetKeyDown(KEY_STATE_LEFT_MOUSE))
	{
		if (IsClick())
		{
			m_event.NotifyHandlers();
		}
	}
}

void Button::LateUpdate()
{
}

void Button::Release()
{
	m_event.Release();
}

bool Button::IsClick()
{
	Vector2 mousePos = m_input->GetMouseScreenPos();

	if (m_transform->position.x - m_transform->scale.x * 0.5f < mousePos.x &&
		m_transform->position.x + m_transform->scale.x  * 0.5f > mousePos.x &&
		m_transform->position.y - m_transform->scale.y  * 0.5f < mousePos.y &&
		m_transform->position.y + m_transform->scale.y  * 0.5f > mousePos.y)
		return true;

	return false;
}
