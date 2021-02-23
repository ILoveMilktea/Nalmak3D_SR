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

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
};

