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
};

