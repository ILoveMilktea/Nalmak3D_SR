#pragma once
#include "Component.h"
class Homing :
	public Component
{
public:
	struct Desc
	{


	};
public:
	Homing(Desc* _desc);
	virtual ~Homing();

	// Component��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update() override;
};

