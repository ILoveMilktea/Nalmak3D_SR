#pragma once

#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "Component.h"
#include "EventHandler.h"
#include "Event.h"
#include "Nalmak_Include.h"

class Texture;
class InputManager;
class CanvasRenderer;
class ResourceManager;
class  NALMAK_DLL Button :
	public Component
{
public:
	struct Desc
	{
		EventHandler eventFunc = nullptr;

		wstring normalImage = L"UIWhite";
		wstring highlightImage = L"UIRed";
		wstring pressedImage = L"UIBlue";
		wstring disableImage = L"UIGrey";
	};
	Button(Desc* _desc);
protected:
	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;

	void ChangeTransition(BUTTON_TRANSITION _transition);
	void ChangeState(BUTTON_STATE _state);

	void ChangeAllColor(Vector4 _color);
	void ChangeNormalColor(Vector4 _color) { m_normalColor = _color; }
	void ChangeHighlightColor(Vector4 _color) { m_normalColor = _color; }
	void ChangePressedColor(Vector4 _color) { m_normalColor = _color; }
	void ChangeDisableColor(Vector4 _color) { m_normalColor = _color; }

	void ChangeAllTexture(wstring _name);
	void ChangeNormalTexture(wstring _name);
	void ChangeHighlightTexture(wstring _name);
	void ChangePressedTexture(wstring _name);
	void ChangeDisableTexture(wstring _name);

private:
	bool CheckCursorPosition();

public:
	BUTTON_TRANSITION GetTransition() { return m_currentTransition; }

	void SetTransition(BUTTON_TRANSITION _tr) { m_currentTransition = _tr; }
	void SetInteraction(bool _value);

public:
	void AddEventHandler(EventHandler _eventFunc);

	void GetEventHandler(int _index);
	void RemoveEventHandler(EventHandler _eventFunc);
	void RemoveEventHandler(int _index);

protected:
	Event m_event;
	ResourceManager* m_resource;
	InputManager* m_input;
	CanvasRenderer* m_renderer;

protected:
	bool m_interactive;	// off시 disable상태
	bool m_isCursorOnButton;
	BUTTON_TRANSITION m_currentTransition;
	BUTTON_STATE m_currentState;

	Texture** m_targetImage = nullptr;
	Vector4* m_targetColor = nullptr;

	Vector4 m_normalColor;
	Vector4 m_highlightColor;
	Vector4 m_pressedColor;
	Vector4 m_disableColor;

	Texture* m_normalImage = nullptr;
	Texture* m_highlightImage = nullptr;
	Texture* m_pressedImage = nullptr;
	Texture* m_disableImage = nullptr;
};

#endif