#pragma once
#include "Component.h"
class GeunHee_Fps_Shoot :
	public Component
{
public:
	GeunHee_Fps_Shoot();
	virtual ~GeunHee_Fps_Shoot();

	// Component��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update() override;

	virtual void OnTriggerEnter(Collisions& _collision)override;
	virtual void OnTriggerStay(Collisions& _collision)override;
	virtual void OnTriggerExit(Collisions& _collision)override;
public:


};

