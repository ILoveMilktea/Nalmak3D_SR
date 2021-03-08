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

public:

private:

	Camera* m_pMainCamera = nullptr;
	GameObject*	m_Player = nullptr;

};

