#pragma once
#include "Scene.h"
class PhantomScene :
	public Scene
{
public:
	PhantomScene();
	~PhantomScene();

	// Scene��(��) ���� ��ӵ�
	virtual void Initialize() override;

public:

private:

	Camera* m_pMainCamera = nullptr;
	GameObject*	m_Player = nullptr;

};

