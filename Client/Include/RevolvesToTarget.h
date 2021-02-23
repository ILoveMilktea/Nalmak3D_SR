#pragma once
#include "Component.h"
class RevolvesToTarget :
	public Component
{
public:
	struct Desc
	{
		GameObject* target = nullptr;
		float roationSpeed = 5.f;
		float distanceLenght = 15.f;
		Vector3 addingPos = {};

	};
public:
	RevolvesToTarget(Desc* _desc);
	virtual ~RevolvesToTarget();


public:
	// Component��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;



private:
	float m_roationSpeed = 0.f;
	float m_distanceLenght = 0.f;
	Vector3 m_addingPos = {};

private:
	GameObject* m_target = nullptr;

private:
	Vector3		m_direction;

};

