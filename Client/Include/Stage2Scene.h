#pragma once
#include "Scene.h"
class Stage2Scene :
	public Scene
{
public:
	Stage2Scene();
	~Stage2Scene();

	// Scene��(��) ���� ��ӵ�
	virtual void Initialize() override;

public:
	GameObject* m_StageManager = nullptr;
};

