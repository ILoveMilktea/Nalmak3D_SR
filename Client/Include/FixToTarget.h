#pragma once
#include "Component.h"
class FixToTarget :
	public Component
{
public:
	struct Desc
	{
		GameObject * obj = Core::GetInstance()->FindObjectByName(OBJECT_TAG_CAMERA, L"mainCamera");
	
		float followDistance = 20;
		float height = 10;
		float distanceAngle = 25;

	};
public:
	FixToTarget(Desc* _desc);
	virtual ~FixToTarget();

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;

private:
	GameObject* m_fromObject = nullptr;

private:
	float m_followDistance;
	float m_height;
	float m_distanceAngle;

};

