#pragma once
#include "Scene.h"
class StageSelectScene :
	public Scene
{
public:
	StageSelectScene();
	~StageSelectScene();

	// Scene을(를) 통해 상속됨
	virtual void Initialize() override;
};

