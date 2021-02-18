#pragma once
#include "Light.h"
class NALMAK_DLL DirectionalLight :
	public Light
{
public:
	struct Desc
	{
		Vector3 color = Vector3(0.97f, 0.95f, 0.8f);
		float intensity = 1.f;
	};
public:
	DirectionalLight(Desc* _desc);
	~DirectionalLight();

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Release() override;
public:
	DirectionalLightInfo GetDirectionalLightInfo();
private:
	Vector3 m_color;
	float m_intensity;
};

