#pragma once
#include "Scene.h"
class StageScene :
	public Scene
{
public:
	virtual void Initialize() override;

private:
	GameObject* m_StageManager = nullptr;
};

