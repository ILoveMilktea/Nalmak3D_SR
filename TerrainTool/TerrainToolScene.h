#pragma once
#include "Scene.h"
class TerrainToolScene :
	public Scene
{
public:
	TerrainToolScene();
	~TerrainToolScene();

	// Scene��(��) ���� ��ӵ�
	virtual void Initialize() override;
};

