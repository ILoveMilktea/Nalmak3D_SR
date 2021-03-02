#pragma once
#ifndef  __INPUTMANAGER_H__
#define __INPUTMANAGER_H__

#include "Nalmak_Include.h"
class NALMAK_DLL InputManager
{
	DECLARE_SINGLETON(InputManager)
public:
	InputManager();
	~InputManager();
public:
	void Initialize();
	void Update();
	void Release();

private:
	/*
	vector<pair<bool, short>> m_isButtonDown;
	vector<pair<bool, short>> m_isButtonPress;
	vector<pair<bool, short>> m_isButtonUp;*/
	bool m_bButtonDown[KEY_STATE_MAX] = {};
	bool m_bButtonPress[KEY_STATE_MAX] = {};
	bool m_bButtonUp[KEY_STATE_MAX] = {};

public:
	bool GetKeyDown(KEY_STATE _ks) { return m_bButtonDown[_ks]; }
	bool GetKeyPress(KEY_STATE _ks) { return m_bButtonPress[_ks]; }
	bool GetKeyUp(KEY_STATE _ks) { return m_bButtonUp[_ks]; }

	Vector2 GetMouseScreenPos() { return m_mouseScreenPosition; }
	Vector2 GetMouseMoveDir() { return m_mouseScreenPosition - m_prevMouseScreenPosition; }	/* 추가 */
private:
	Vector2 m_mouseScreenPosition;
	Vector2 m_prevMouseScreenPosition;	/* 추가 */
public:
	void SetWheelScroll(int _amount) { m_wheelScroll = _amount; } /* 추가 */
	void AddWheelScroll(int _amount) {
		m_wheelScroll += _amount;
	} /* 추가 */
	const int& GetWheelScroll() { return m_wheelScroll; } /* 추가 */
private:
	int m_wheelScroll = 0; /* 추가 */
	int m_wheelDT = 0;

private:
	void ProcessMouseScreenPosition();
	void ProcessKeyState();
};

#endif // ! __INPUTMANAGER_H__
