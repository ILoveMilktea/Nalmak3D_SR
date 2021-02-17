#pragma once
#include "Light.h"
class NALMAK_DLL PointLight : public Light
{
public:
	struct Desc
	{
		Vector3 color = Vector3(0.97f, 0.95f, 0.8f);
		float intensity = 1.f;
		float radius = 1.f;
	};
public:
	PointLight(Desc* _desc);
	~PointLight();
private:
	// Light을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Release() override;
public:
	float GetRadius() { return m_radius; }
private:
	float m_radius;

};

