#pragma once
#include "Component.h"
class MachineGun :
	public Component
{
	
public:
	struct Desc
	{
		float	fSpd;
		int		iDmg;
		
		bool	bStraight = true;
		Vector3	vDest = { 0.f,0.f,0.f };
	};
	
public:
	MachineGun(Desc* _desc);
	virtual ~MachineGun();

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;

	virtual void OnTriggerEnter(Collisions& _collision)override;
	virtual void OnTriggerStay(Collisions& _collision)override;
	virtual void OnTriggerExit(Collisions& _collision)override;

public:
	void Go_Straight();

	
	void Straight_Shoot();

	void CalcDir();
	void Dest_Shoot();
	
private:
	Camera*	m_pMainCamera = nullptr;
	Material* m_pMaterial = nullptr;
	

	bool	m_bStraight = true;
	
	bool	m_bFirst = true;
	Vector3 m_vDest;
	Vector3	m_vDir;

	
	float m_strechRatio = 18.f;

	float m_fSpd = 150.f;
	int m_iDamage = 0;

	float m_fDeltaTime = 0.f;
};

