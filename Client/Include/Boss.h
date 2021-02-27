#pragma once
#include "Component.h"
class Boss :
	public Component
{
public:
	Boss();
	virtual ~Boss();

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
};

