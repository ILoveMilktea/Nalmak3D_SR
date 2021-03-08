#pragma once
#include "Component.h"
class Enemy :
	public Component
{
public:
	struct Desc 
	{
		Desc(ENEMY_STATUS _status  = ENEMY_STATUS(),
			BULLET_STATUS _gun = BULLET_STATUS(), 
			BULLET_STATUS _missile = BULLET_STATUS(),
			BULLET_STATUS _homing = BULLET_STATUS())
		{
			tStatus = _status;
			tGun = _gun;
			tMissile = _missile;
			tHoming = _homing;
		}
		ENEMY_STATUS		tStatus;
		BULLET_STATUS		tGun;
		BULLET_STATUS		tMissile;
		BULLET_STATUS		tHoming;
	};

public:
	Enemy(Desc* _Desc);
	virtual ~Enemy();

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void OnTriggerEnter(Collisions& _collision)override;

public:
	void Target_Setting(bool _onoff);
	void Target_Update(); 
	void Look_Target();
	
	bool Fov_Check();

	void Death_Check();
	

public: /* Affect Status */
	void Damaged(const int& _playerDmg);
	void Emp();

public: /* Get */
	const ENEMY_STATUS& Get_Status() const; 
	const int&		Get_FullHp() const;
	const int&		Get_CurHp() const;
	
	const BULLET_STATUS&	Get_GunStatus() const;
	const BULLET_STATUS&	Get_MissileStatus() const;
	const BULLET_STATUS&	Get_HomingStatus() const;

	const int&		Get_GunDamage() const;
	const int&		Get_MissileDamage() const;
	const int&		Get_HomingDamage() const;

	const int&		Get_GunCurRound() const;
	const int&		Get_GunFullRound() const;

	const int&		Get_MissileCurRound() const;
	const int&		Get_MissileFullRound() const;

	const int&		Get_HomingCurRound() const;
	const int&		Get_HomingFullRound() const;
	
	const float&	Get_Distance() const;
	const float&	Get_Inner() const;
	const Vector3&	Get_RandPos() const;



public: /* Set */
	void Set_Damage(const int& _dmg);
	void Set_OriginForward();
	

public: /* Move */
	void Go_ToPos(Vector3 _pos);
	void Go_Straight(); 
	void Horizontally(); 
	void Turn(); //Like Screw
	
	bool Dive(); //급 하강
	bool Soar(); //급 상승

	void Accelerate();
	void Decelerate();
	
	void Create_RandPos();

	bool Fire_Gun();
	bool Reloading_Gun();

	bool Fire_Missile();
	bool Reloading_Missile();

private:
	GameObject* m_pTarget = nullptr;
	bool bTarget = false;

	ENEMY_STATUS m_tStatus;

	/* for machine gun*/
	BULLET_STATUS	m_tMachineGun;
	float			m_fGunFpmDelta = 0.f;
	float			m_fGunReload = 0.f;

	/* for straight missile */
	BULLET_STATUS	m_tMissile;
	float			m_fMissileFpmDelta = 0.f;
	float			m_fMissileReload = 0.f;

	/* for homing missile */
	BULLET_STATUS	m_tHoming;
	float			m_fHomingFpmDelta = 0.f;
	float			m_fHomingReload = 0.f;

	float m_fHorizonSpd = 10.f;

	bool	m_bRandMove = false;
	Vector3 m_vRandPos = { 0.f,0.f,0.f };

	Vector3 m_vOriginForward = { 0.f, 0.f, 0.f };
	bool	m_bDive = false;
	float	m_fDiveInner = 0.f;
	bool	m_bSoar = false;
	float	m_fSoarInner = 0.f;

	float	m_fDist_Target = 0.f;
	float	m_fFov = 90.f;
	bool	m_bFov = false;

	float m_fInner = 0.f;//CurInner 
	//Dot calc Enemy's forward and Distance that between Enemy and Player

	float m_fInner_First = 0.f;

	float m_fUpInner = 0.f;
	float m_fUpAngle = 0.f;

	float m_fQuartRotX = 0.f;
	float m_fQuartRotY = 0.f;
	float m_fQuartRotZ = 0.f;
	Quaternion m_QuartRot = { 0.f, 0.f, 0.f, 0.f }; // for
	

	GameObject* m_pSmokeParticle = nullptr;
};

