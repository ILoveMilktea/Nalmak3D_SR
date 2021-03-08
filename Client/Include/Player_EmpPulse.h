#pragma once
#include "Component.h"
class Player_EmpPulse :
	public Component
{
public:
	struct Desc
	{
		float max_Radius;
	};
	
public:
	Player_EmpPulse(Desc* _desc);
	virtual ~Player_EmpPulse();

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void OnTriggerEnter(Collisions& _collision)override;
	virtual void OnTriggerStay(Collisions& _collision)override;
	virtual void OnTriggerExit(Collisions& _collision)override;

public:

public:
	void Bloat();
	void Shrink();
	void Destroy();
private:
	float	m_fMaxRadius;
	float	m_fCurRadius = 0.5f;
	float	m_bShrink = false;
	float m_distanceToCam;
private:
	Material* m_empMaterial;
	Transform* m_cam;
};

