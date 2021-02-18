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

		// for attenuation
		float constant = 0;
		float linearRatio = 0;
		float exp = 0.3f;
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
	float GetRadius();
private:
	PointLightInfo m_lightInfo;


};

