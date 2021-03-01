#pragma once
#include "Scene.h"
class GarageScene :
	public Scene
{
public:
	GarageScene();
	~GarageScene();

	// Scene을(를) 통해 상속됨
	virtual void Initialize() override;

};

