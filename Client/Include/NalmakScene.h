#pragma once
#include "Scene.h"
class NalmakScene :
	public Scene
{
public:
	NalmakScene();
	~NalmakScene();

	// Scene��(��) ���� ��ӵ�
	virtual void Initialize() override;
};

