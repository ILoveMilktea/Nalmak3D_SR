#pragma once
#include "Scene.h"
class StageSelectScene :
	public Scene
{
public:
	StageSelectScene();
	~StageSelectScene();

	// Scene��(��) ���� ��ӵ�
	virtual void Initialize() override;
};

