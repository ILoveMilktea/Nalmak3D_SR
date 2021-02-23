#pragma once
#include "Button.h"

class NALMAK_DLL Toggle :
	public Button
{
public:
	struct Desc
	{
		Button::Desc* desc_button = nullptr;

		EventHandler onEventFunc = nullptr;
		EventHandler offEventFunc = nullptr;
		wstring offImage = L"empty";
		wstring onImage = L"checkmark";
	};

public:
	Toggle(Desc* _desc);

private:
	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;


private:
	bool m_isOn;

	GameObject* m_toggleImage = nullptr;
	IDirect3DBaseTexture9* m_waitSprite = nullptr;
	Event m_changeEvent;
	

	// toggle group
};

