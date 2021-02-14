#pragma once
#include "Scene.h"
class TestScene :
	public Scene
{
public:
	TestScene();
	~TestScene();

	// Scene을(를) 통해 상속됨
	virtual void Initialize() override;
};

