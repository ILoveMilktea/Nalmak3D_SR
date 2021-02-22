#pragma once
#include "Component.h"
class Enemy :
	public Component
{
public:
	struct Desc 
	{
		float fSpd = 10.f;
		float fLookSpd = 0.5f;
		float fFpm = 120.f;
	};
public:
	Enemy(Desc* _Desc);
	virtual ~Enemy();

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;


public:
	void Target_Setting(bool _onoff);
	void Target_Update(); 
	void Look_Target();
	
	bool Fov_Check();

public: /* Affect Status */
	void Damaged(const int& _playerDmg);
	

public: /* Get */
	const int& Get_Damage();
	const int& Get_FullHp();
	const int& Get_CurHp();

public: /* Set */
	void Set_Damage(const int& _dmg);


public: /* Move */
	void Go_Straight(); 
	void Lean();
	void Horizontally(); 
	void Turn(); //Like Screw
	
	void Dive(); //급 하강
	void Soar(); //급 상승

	void Shoot();
	void Misile();

public: /* pattern*/
	void Rush();
	void Chase();
	void Drop();
	void Hold();

private:
	GameObject* m_pTarget = nullptr;
	bool bTarget = false;

	int	m_iAtt = 0;
	int m_iFullHp = 0;
	int m_iCurHp = 0;
	float m_fFpm = 0; //Fire per minute 연사력
	float m_fFpmDelta = 0;

	float m_fSpd = 10.f;
	float m_fLookSpd = 0.5f;
	//Spd : LookSpd = 20 : 1

	float m_fHorizonSpd = 10.f;

	float	m_fDist_Target = 0.f;
	float	m_fFov = 90.f;
	bool	m_bFov = false;

	float m_fInner = 0.f;//CurInner 

	float m_fUpInner = 0.f;
	float m_fUpAngle = 0.f;

	float m_fQuartRotX = 0.f;
	float m_fQuartRotY = 0.f;
	float m_fQuartRotZ = 0.f;
	Quaternion m_QuartRot = { 0.f, 0.f, 0.f, 0.f };
	
	enum ePattern { RUSH, IDLE, CHASE, DROP, HOLD};

#pragma region ForLean
	float m_fTurnDeltaTime = 0.f;
	float m_fTurnUpdateTime = 0.01f;
	float m_fTurnSpd = 1.f; //클 수록 회전 폭 큼
	//UpdateTime : Spd = 1 : 20

	float m_fInner_First = 0.f;
	const float m_fInner_Goal = 1.f;
#pragma endregion

#pragma region forTest
	//float m_fRotX = 0.f;
	//float m_fRotY = 0.f;
	//float m_fRotZ = 0.f;
	//
	//float fRotZ = 0.f;

	//float m_fForwardRot = 0.f;
	//float m_fRightRot = 0.f;
	//float m_fUpRot = 0.f;

	//Quaternion qForwardRot = { 0,0,0,0 };
	//Quaternion qUpRot = { 0,0,0,0 };
	//Quaternion qRightRot = { 0,0,0,0 };
	//Quaternion ResultQuater = { 0,0,0,0 };
#pragma endregion
};

