#pragma once

#ifndef _HEE_TEST_SCENE_H_
#define _HEE_TEST_SCENE_H_

#include "Scene.h"

class HeeTestScene : public Scene
{
public:
	HeeTestScene();
	~HeeTestScene();

	// Scene��(��) ���� ��ӵ�
	virtual void Initialize() override;
};

#endif