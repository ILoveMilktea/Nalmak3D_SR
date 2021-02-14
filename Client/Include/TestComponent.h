#pragma once
#include "Component.h"
class TestComponent :
	public Component
{
public:
	struct Desc
	{

	};
	TestComponent(Desc* _desc);
	~TestComponent();
private:
	virtual void Initialize() override;
	virtual void Update() override;

};

