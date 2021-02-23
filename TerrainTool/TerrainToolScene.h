#pragma once
#include "Scene.h"
class TerrainToolScene :
	public Scene
{
public:
	TerrainToolScene();
	~TerrainToolScene();

	// Scene을(를) 통해 상속됨
	virtual void Initialize() override;
};

