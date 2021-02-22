#pragma once
#include "Component.h"
class MouseOption :
	public Component
{

public:
	struct Desc
	{
		bool shadowCheck = false;
		Vector2 fixMousePos = Vector2(HALF_WINCX, HALF_WINCY);
	};
public:
	MouseOption(Desc* _desc);
	virtual ~MouseOption();

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;

private:

	bool m_mouseShadow = false;
	Vector2 m_fixMousePos;
};

