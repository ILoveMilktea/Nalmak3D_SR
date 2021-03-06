#pragma once
#include "Component.h"
class DeadTimer :
	public Component
{
public:
	struct Desc
	{
		float timer = 3.f;
	};
public:
	DeadTimer(Desc* _desc);
	virtual ~DeadTimer();

	virtual void Initialize() override;
	virtual void Update() override;
private:
	float m_timer;
};

