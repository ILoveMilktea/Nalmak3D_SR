#pragma once
#include "Light.h"
class NALMAK_DLL PointLight : public Light
{
public:
	struct Desc
	{
		Vector3 color = Vector3(0.97f, 0.95f, 0.8f);
		float diffuseIntensity = 0.2f;
		float ambientIntensity = 0.05f;

		float radius = 1.f;
	};
public:
	PointLight(Desc* _desc);
	~PointLight();
private:
	// Light을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void PreRender() override;
	virtual void Release() override;

public:
	PointLightInfo GetLightInfo() { return m_lightInfo; }
	void SetLightPosition(const Vector3& _vec) { m_lightInfo.position = _vec; }
	float GetRadius();
private:
	PointLightInfo m_lightInfo;


};

