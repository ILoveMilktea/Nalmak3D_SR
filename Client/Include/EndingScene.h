#pragma once
#include "Scene.h"
class EndingScene :
	public Scene
{
public:
	EndingScene();
	virtual ~EndingScene();

	// Scene을(를) 통해 상속됨
	virtual void Initialize() override;
};

