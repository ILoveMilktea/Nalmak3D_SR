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

	
	void AxisRotate();
private:
	float	m_dampingSpeed = 0.f;
	float	m_maximumScale = 0.f;
	float	m_retainTime = 0.f;

	Vector3	 m_axis;
};

