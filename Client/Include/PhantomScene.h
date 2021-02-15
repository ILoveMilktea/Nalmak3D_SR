#pragma once
#include "Scene.h"
class PhantomScene :
	public Scene
{
public:
	PhantomScene();
	~PhantomScene();

	// Scene을(를) 통해 상속됨
	virtual void Initialize() override;
};

