#pragma once
#include "Component.h"
class Enemy :
	public Component
{
public:
	struct Desc 
	{
		float fMaxSpd = 20.f;
		float fLookSpd = 1.f;
		float fFov = 90.f;

		float fFpm = 300.f;
		int	iRound = 50;

		float fFpm_Missile = 30.f;
		int iRound_Missile = 5; 

	};

	enum ePattern { RUSH, IDLE, CHASE, DROP, HOLD };
public:
	Enemy(Desc* _Desc);
	virtual ~Enemy();

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void OnTriggerEnter(Collisions& _collision)override;
	virtual void OnTriggerStay(Collisions& _collision)override;
	virtual void OnTriggerExit(Collisions& _collision)override;

public:
	void Target_Setting(bool _onoff);
	void Target_Update(); 
	void Look_Target();
	
	bool Fov_Check();

public: /* Affect Status */
	void Damaged(const int& _playerDmg);
	

public: /* Get */
	const ENEMY_STATUS& Get_Status() const; 
	const int&		Get_FullHp() const;
	const int&		Get_CurHp() const;
	
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
	void Set_OriginForward(const Vector3& _forward);

public: /* Move */
	void Go_ToPos(Vector3 _pos);
	void Go_Straight(); 
	void Lean();
	void Horizontally(); 
	void Turn(); //Like Screw
	
	bool Dive(); //급 하강
	bool Soar(); //급 상승

	void Create_RandPos();

	bool Shoot();
	void Reloading();

	bool Missile();
	bool Missile_Reloading();

	void Decelerate();
	void Accelerate();

public: /* pattern*/
	void Chase();
	void Drop();
	void Hold();

private:
	GameObject* m_pTarget = nullptr;
	bool bTarget = false;

	ENEMY_STATUS m_tStatus;

	int	m_iAtt = 0;
	int m_iFullHp = 0;
	int m_iCurHp = 1240;
	
	float m_fFpm = 0; //Fire per minute 연사력
	float m_fFpmDelta = 0;
	int m_iFullRound = 100;
	int m_iCurRound = 0;
	float m_fRoundDelta = 0.f;

	float m_fFpm_Missile = 0;
	float m_fFpmDelta_Missile = 0;
	int m_iFullRound_Missile = 5;
	int m_iCurRound_Missile = 0;
	float m_fRoundDelta_Missile = 0.f;

	float m_fMaxSpd = 0.f;
	float m_fSpd = 20.f;
	float m_fLookSpd = 0.5f;
	//Spd : LookSpd = 20 : 1

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

	float m_fUpInner = 0.f;
	float m_fUpAngle = 0.f;

	float m_fQuartRotX = 0.f;
	float m_fQuartRotY = 0.f;
	float m_fQuartRotZ = 0.f;
	Quaternion m_QuartRot = { 0.f, 0.f, 0.f, 0.f };
	
	//enum ePattern { RUSH, IDLE, CHASE, DROP, HOLD };
	
	float	m_fChaseDelta = 0.f;
	bool	m_bChaseMove = false;

	
	float	m_fHoldDelta = 0.f;
	bool	m_bHoldMove = false;

	float	m_fDropDelta = 0.f;
	bool	m_bDropMove = false;

#pragma region ForLean
	float m_fTurnDeltaTime = 0.f;
	float m_fTurnUpdateTime = 0.01f;
	float m_fTurnSpd = 1.f; //클 수록 회전 폭 큼
	//UpdateTime : Spd = 1 : 20

	float m_fInner_First = 0.f;
	const float m_fInner_Goal = 1.f;
#pragma endregion

};

