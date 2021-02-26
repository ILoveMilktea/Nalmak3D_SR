#pragma once
#include "Component.h"
class Shooter :
	public Component
{



public:
	struct Desc
	{
		MOVE_PATTERN eMovePattern;
		Vector3 firePos;
		float speed;
	};

	Shooter(Desc * _desc);
	virtual ~Shooter();

	// Component��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update() override;


	void ShooterActive(bool _activeCheck);

private:
	MOVE_PATTERN m_eMovePattern;
	Vector3 m_firePos;
	float m_speed;
private:
	bool	m_fire;
	Vector3 m_desiredPos = {};
	Vector3 m_fireDirection = {};
private:
	Core*		m_core;
	Transform*  m_targetTransform;
};

