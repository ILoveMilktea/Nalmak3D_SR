#pragma once
#include "Scene.h"
class EndingScene :
	public Scene
{
public:
	EndingScene();
	virtual ~EndingScene();

	// Scene��(��) ���� ��ӵ�
	virtual void Initialize() override;
};

