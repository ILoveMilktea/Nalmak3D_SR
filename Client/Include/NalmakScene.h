#pragma once
#include "Scene.h"
class NalmakScene :
	public Scene
{
public:
	NalmakScene();
	~NalmakScene();

	// Scene을(를) 통해 상속됨
	virtual void Initialize() override;
};

