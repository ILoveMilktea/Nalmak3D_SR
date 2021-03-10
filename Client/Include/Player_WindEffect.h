#include "Component.h"

class Player_WindEffect : public Component
{
public:
	struct Desc
	{
		Vector3 leftTrailPos = Vector3(-1.f, 0.f, -0.5f);
		Vector3 rightTrailPos = Vector3(1.f, 0.f, -0.5f);
		float trailThick = 0.2f;
	};
public:
	Player_WindEffect(Desc* _desc);
	~Player_WindEffect() = default;
private:
	virtual void Initialize() override;
	virtual void Release() override;
	virtual void Update() override;
private:
	class TrailRenderer* m_leftTrail;
	class TrailRenderer* m_rightTrail;
	Vector3 m_leftTrailPos;
	Vector3 m_rightTrailPos;
	float m_trailThick;
	float m_trailCurrentThick;
	float m_trailTargetThick;
	float m_timer;
};