#pragma once

#include "Component.h"

class TopViewCamera :
	public Component
{
public:
	TopViewCamera();
	virtual ~TopViewCamera();

	// Component��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update() override;
};

