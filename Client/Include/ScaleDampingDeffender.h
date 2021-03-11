#pragma once
#include "Component.h"
class ScaleDampingDeffender :
	public Component
{
public:
	struct Desc
	{
	
	};

public:
	ScaleDampingDeffender(Desc* _desc);
	virtual ~ScaleDampingDeffender();

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate()override;

	virtual void OnTriggerEnter(Collisions& _collision)override;
	virtual void OnTriggerStay(Collisions& _collision)override;
	virtual void OnTriggerExit(Collisions& _collision)override;
public:
	void ActiveShield();
private:
	void ShakeShield();
private:
	float m_activeTimer;
	float m_currentScale;
	float m_targetScale;
private:
	SphereCollider* m_spherCollider;
	Material* m_material;

};

