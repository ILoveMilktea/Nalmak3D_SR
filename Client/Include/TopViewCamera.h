#pragma once

#include "Component.h"

class TopViewCamera :
	public Component
{
public:
	TopViewCamera();
	virtual ~TopViewCamera();

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
};

