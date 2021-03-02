#pragma once
#include "Component.h"
class ScaleDampingDeffender :
	public Component
{
public:
	struct Desc
	{
		float dampingSpeed;
		float maximumScale;
		Vector3 axisDir;
		float	m_retainTime = 5.f;
	};

public:
	ScaleDampingDeffender(Desc* _desc);
	virtual ~ScaleDampingDeffender();

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate()override;

	virtual void OnTriggerEnter(Collisions& _collision)override;
	virtual void OnTriggerStay(Collisions& _collision)override;
	virtual void OnTriggerExit(Collisions& _collision)override;
	
	void AxisRotate(Vector3 _axis);
private:
	float	m_dampingSpeed = 0.f;
	float	m_maximumScale = 0.f;
	float	m_retainTime = 0.f;

	Vector3	 m_axis;
private:
	SphereCollider* m_spherCollider;

};

