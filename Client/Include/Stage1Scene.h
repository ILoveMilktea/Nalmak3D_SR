#pragma once
#include "Scene.h"
class Stage1Scene :
	public Scene
{
public:
	virtual void Initialize() override;

private:
	
	Camera* m_pMainCamera = nullptr;

	class StageManager* m_StageManager = nullptr;
};

