#pragma once
#include "Scene.h"
class GarageScene :
	public Scene
{
public:
	GarageScene();
	~GarageScene();

	// Scene��(��) ���� ��ӵ�
	virtual void Initialize() override;

};

