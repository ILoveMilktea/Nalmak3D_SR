#pragma once
#include "Component.h"
class PrintInfo :
	public Component
{
public:
	struct Desc
	{

	};
public:
	PrintInfo(Desc* _desc);
	~PrintInfo();

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
};

