#include "..\Include\Toggle.h"
#include "SingleImage.h"
#include "CanvasRenderer.h"
#include "Transform.h"

Toggle::Toggle(Desc * _desc)
	:Button(&Button::Desc())
{
	if (_desc->desc_button)
		Button(_desc->desc_button);

	// dont switch two code lines
	if (_desc->offEventFunc != nullptr)
	m_changeEvent += _desc->offEventFunc;
	if (_desc->onEventFunc != nullptr)
	m_changeEvent += _desc->onEventFunc;
	// dont switch two code lines


	SingleImage::Desc desc_img;
	desc_img.textureName = _desc->offImage;
	m_toggleImage =
		INSTANTIATE()->
		AddComponent<SingleImage>(&desc_img);

	m_waitSprite = ResourceManager::GetInstance()->
		GetResource<Texture>(_desc->onImage)->GetTexure(0);
}

void Toggle::Initialize()
{
	Button::Initialize();

	m_isOn = false;


	m_toggleImage->SetParents(m_gameObject);
	m_toggleImage->SetPosition(0.f, 0.f, 0.f);
}

void Toggle::Update()
{
	Button::Update();
}

void Toggle::LateUpdate()
{
	// click operation
	if (m_renderer->IsPickingBlocked())
		return;

	if (m_renderer->MouseClickUp_InRect())
	{
		if (m_renderer->IsInteractive())
		{
			m_isOn = !m_isOn;

			IDirect3DBaseTexture9* swap = m_toggleImage->GetComponent<SingleImage>()->GetTexture();
			m_toggleImage->GetComponent<SingleImage>()->SetTexture(m_waitSprite);
			m_waitSprite = swap;

			// 1. value change event
			m_changeEvent[(int)m_isOn];

			// 2. button event
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

void Toggle::Release()
{
	Button::Release();
	m_changeEvent.Release();
}
