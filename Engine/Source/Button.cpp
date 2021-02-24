#include "..\Include\Button.h"
#include "Transform.h"
#include "CanvasRenderer.h"
#include "ResourceManager.h"

Button::Button(Desc * _desc)
{
	if (_desc->eventFunc != nullptr)
		m_event += _desc->eventFunc;

	m_normalColor = { 1.f,1.f,1.f,1.f };
	m_highlightColor = { 0.8f,0.8f,0.8f,1.f };
	m_pressedColor = { 0.5f,0.5f,0.5f,1.f };
	m_disableColor = { 0.2f,0.2f,0.2f,1.f };

	m_resource = ResourceManager::GetInstance();
	m_normalImage = m_resource->GetResource<Texture>(_desc->normalImage)->GetTexure(0);
	m_highlightImage = m_resource->GetResource<Texture>(_desc->highlightImage)->GetTexure(0);
	m_pressedImage = m_resource->GetResource<Texture>(_desc->pressedImage)->GetTexure(0);
	m_disableImage = m_resource->GetResource<Texture>(_desc->disableImage)->GetTexure(0);
}

void Button::Initialize()
{
	m_currentTransition = BUTTON_TRANSITION_COLOR;
	m_currentState = BUTTON_STATE_NORMAL;
	m_targetImage = &m_normalImage;
	m_targetColor = &m_normalColor;

	m_renderer = GetComponent<CanvasRenderer>();
	if (m_renderer)
		m_renderer->SetImage(m_normalImage);
	//m_renderer->SetActive(false);
}

void Button::Update()
{
	// interactive(highlight) operation
	if (m_renderer->IsPickingBlocked())
		return;
	if (!m_renderer->IsInteractive())
	{
		if (BUTTON_STATE_DISABLE != m_currentState)
			ChangeState(BUTTON_STATE_DISABLE);
		return;
	}

	if (m_renderer->IsCursorOnRect())
	{
		if (BUTTON_STATE_NORMAL == m_currentState)
			ChangeState(BUTTON_STATE_HIGHLIGHT);
	}
	else
	{
		if (BUTTON_STATE_HIGHLIGHT == m_currentState)
			ChangeState(BUTTON_STATE_NORMAL);
	}
}

void Button::LateUpdate()
{
	// click operation
	if (m_renderer->IsPickingBlocked())
		return;


	if (m_renderer->MouseClickUp_InRect())
	{
		if (m_renderer->IsInteractive())
		{
			m_event.NotifyHandlers();
		}

		ChangeState(BUTTON_STATE_NORMAL);
	}
	else if (m_renderer->MouseClickDown())
	{
		ChangeState(BUTTON_STATE_PRESSED);
	}
	else if (m_renderer->MouseClickUp_OutRect())
	{
		ChangeState(BUTTON_STATE_NORMAL);
	}
}

void Button::Release()
{
	m_event.Release();
}

void Button::ChangeTransition(BUTTON_TRANSITION _transition)
{
	switch (_transition)
	{
	case BUTTON_TRANSITION_NONE:
		m_renderer->SetActive(false);
		break;
	case BUTTON_TRANSITION_COLOR:
		m_renderer->SetActive(false);
		break;
	case BUTTON_TRANSITION_SWAP:
		m_renderer->SetActive(true);
		break;
	}
	m_currentTransition = _transition;
	ChangeState(BUTTON_STATE_NORMAL);
}

void Button::ChangeState(BUTTON_STATE _state)
{
	if (m_currentState == _state)
		return;

	switch (m_currentTransition)
	{
	case BUTTON_TRANSITION_NONE:
		break;
	case BUTTON_TRANSITION_COLOR:
		switch (_state)
		{
		case BUTTON_STATE_NORMAL:
			m_targetColor = &m_normalColor;
			break;
		case BUTTON_STATE_HIGHLIGHT:
			m_targetColor = &m_highlightColor;
			break;
		case BUTTON_STATE_PRESSED:
			m_targetColor = &m_pressedColor;
			break;
		case BUTTON_STATE_DISABLE:
			m_targetColor = &m_disableColor;
			break;
		}
		m_renderer->SetColor(*m_targetColor);
		break;
	case BUTTON_TRANSITION_SWAP:
		switch (_state)
		{
		case BUTTON_STATE_NORMAL:
			m_targetImage = &m_normalImage;
			break;
		case BUTTON_STATE_HIGHLIGHT:
			m_targetImage = &m_highlightImage;
			break;
		case BUTTON_STATE_PRESSED:
			m_targetImage = &m_pressedImage;
			break;
		case BUTTON_STATE_DISABLE:
			m_targetImage = &m_disableImage;
			break;
		}
		m_renderer->SetImage((*m_targetImage));
		break;
	}

	m_currentState = _state;
}

void Button::ChangeAllColor(Vector4 _color)
{
	ChangeNormalColor(_color);
	ChangeHighlightColor(_color);
	ChangePressedColor(_color);
	ChangeDisableColor(_color);

}

void Button::ChangeAllTexture(wstring _name)
{
	ChangeNormalTexture(_name);
	ChangeHighlightTexture(_name);
	ChangePressedTexture(_name);
	ChangeDisableTexture(_name);
}

void Button::ChangeNormalTexture(wstring _name)
{
	m_normalImage = m_resource->GetResource<Texture>(_name)->GetTexure(0);
}

void Button::ChangeHighlightTexture(wstring _name)
{
	m_highlightImage = m_resource->GetResource<Texture>(_name)->GetTexure(0);
}

void Button::ChangePressedTexture(wstring _name)
{
	m_pressedImage = m_resource->GetResource<Texture>(_name)->GetTexure(0);
}

void Button::ChangeDisableTexture(wstring _name)
{
	m_disableImage = m_resource->GetResource<Texture>(_name)->GetTexure(0);
}

void Button::AddEventHandler(EventHandler _eventFunc)
{
	m_event += _eventFunc;
}

void Button::GetEventHandler(int _index)
{
	m_event.GetHandler(_index);
}

void Button::RemoveEventHandler(EventHandler _eventFunc)
{
	m_event -= _eventFunc;
}

void Button::RemoveEventHandler(int _index)
{
	m_event.RemoveHandler(_index);
}