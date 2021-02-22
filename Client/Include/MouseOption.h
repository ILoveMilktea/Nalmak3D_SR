#pragma once
#include "Component.h"
class MouseOption :
	public Component
{

public:
	struct Desc
	{
		bool shadowCheck = false;
	};
public:
	MouseOption(Desc* _desc);
	virtual ~MouseOption();

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;

public:
	Vector2 GetMouseMoveDir() { return m_curMousePoint - m_preMousePoint; }	/* 추가 */
private:
	bool m_mouseShadow = false;
private:
	Vector2 m_curMousePoint = {};
	Vector2 m_preMousePoint = {};

	InputManager* m_inputManager;
	Core* m_core;
};

