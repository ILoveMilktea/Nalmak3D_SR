#pragma once
#include "Component.h"
class Boss :
	public Component
{
public:
	Boss();
	virtual ~Boss();

	// Component��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update() override;
};

