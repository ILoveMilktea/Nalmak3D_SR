#pragma once
#include "Component.h"
class SmoothFollow :
	public Component
{
public:
	struct Desc
	{
		GameObject* toTarget = nullptr;
		float culDistance = 20.f;
		float minDistance = 25.f;
		float maxDistance = 50.f;
		float followMoveSpeed = 5.f;
		float followRotationSpeed = 10.f;
		float ratioDamping = 0.3f; // 1미만
		float offSetY = 40.f;
	};

public:
	SmoothFollow(Desc* _desc);
	virtual ~SmoothFollow();

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;



private:
	GameObject* m_fromObject = nullptr;
private:
	GameObject* m_toTarget = nullptr;
	float		m_culDistance = 0;
	float		m_minDistance = 0;
	float		m_maxDistance = 0;
	float		m_followMoveSpeed = 0;
	float		m_followRotationSpeed = 0;
	float		m_Damping = 0;
	float		m_offSet = 0;

private:
	Vector3		m_followDirection;
	Quaternion	m_lookDirection;
	
private:
	class PlayerInfoManager* m_playerInfo;
	
};

