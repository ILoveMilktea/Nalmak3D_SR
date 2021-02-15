#pragma once
#include "Scene.h"
class Stage2Scene :
	public Scene
{
public:
	Stage2Scene();
	~Stage2Scene();

	// Scene을(를) 통해 상속됨
	virtual void Initialize() override;
};

