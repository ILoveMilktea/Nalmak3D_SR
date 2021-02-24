#pragma once
#include "Component.h"
class RevolvesToTarget :
	public Component
{
public:
	struct Desc
	{
		GameObject* targetParent = nullptr;
		float roationSpeed = 5.f;
		float distanceLenght = 15.f;
		float yOffSetDistance = 5.f;
		Vector3 addingPos = {};

	};
public:
	RevolvesToTarget(Desc* _desc);
	virtual ~RevolvesToTarget();


public:
	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;


private:


private:
	float m_roationSpeed = 0.f;
	float m_distanceLenght = 0.f;
	float m_yOffSetDistance = 0.f;
	Vector3 m_addingPos = {};

private:
	GameObject* m_targetParent = nullptr;

private:
	GameObject* m_target = nullptr;
private:
	Quaternion m_lookDir = {};
	Vector3 m_targetPos = {};

};

