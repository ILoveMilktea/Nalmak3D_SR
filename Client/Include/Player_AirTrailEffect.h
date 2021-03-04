#pragma once
#include "Component.h"
class Player_AirTrailEffect :
	public Component
{
public:
	struct Desc
	{
		float thick = 0.2f;
		float lifeTime = 1.f;
		int interval = 1;
		bool startOnPlay = true;
		Vector3 posOffset = Vector3(0, 0, 0);
	};
public:
	Player_AirTrailEffect(Desc* _desc);
	~Player_AirTrailEffect();

private:
	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
private:
	void CreateMesh();

private:
	Vector3 m_prePosition;
	Vector3 m_curPosition;
	Vector3 m_offset;
	Material* m_material;

	int m_interval;
	float m_thick;
	float m_lifeTime;
	bool m_isPlay;
	Vector4 m_color;
};

