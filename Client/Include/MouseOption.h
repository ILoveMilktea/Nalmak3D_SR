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

	// Component��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;

public:
	Vector2 GetMouseMoveDir() { return m_curMousePoint - m_preMousePoint; }	/* �߰� */
private:
	bool m_mouseShadow = false;
private:
	Vector2 m_curMousePoint = {};
	Vector2 m_preMousePoint = {};

	InputManager* m_inputManager;
	Core* m_core;
};

