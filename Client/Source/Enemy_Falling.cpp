#include "stdafx.h"
#include "..\Include\Enemy_Falling.h"
#include "Enemy.h"


Enemy_Falling::Enemy_Falling()
{
}


Enemy_Falling::~Enemy_Falling()
{
}

void Enemy_Falling::Initialize()
{
	
}

void Enemy_Falling::EnterState()
{
	m_pEnemy = m_gameObject->GetComponent<Enemy>();

	assert(L"아 ㅋㅋ 에너미 못 찾은거 같다고 ㅋㅋ" && m_pEnemy);
	
	m_pEnemy->Target_Setting(false);
}

void Enemy_Falling::UpdateState()
{

	m_fFallDelta += dTime;

	Accelerate();
	//1. flight ahead ground
	//Dot forward and (0,-1,0);
	Vector3 vYaxis = { 0.f, -1.f, 0.f };
	float fInner = D3DXVec3Dot(&m_transform->GetForward(), &vYaxis);

	if (fInner <= 0.95f)
	{
		Quaternion qToGround = m_transform->RotateAxis(m_transform->GetRight(), dTime*2.f);
		m_transform->rotation *= qToGround;
		m_transform->RotateX(dTime * 5.f);

		m_pEnemy->Go_Straight();
	}
	else {
		//2. turn slowly to ZAxis for turn
		//Quaternion qTemp = m_transform->RotateAxis(m_transform->GetForward(), dTime * 2.f);
		Quaternion qTemp = m_transform->RotateAxis(Vector3(0, 1, 0), m_fTurnSpd * dTime);
		m_transform->rotation *= qTemp;
		

		//3. faliing
		m_transform->position.y -= dTime * m_fFallingSpd;
	}


	if (m_fFallDelta >= 5.f)
	{
		m_gameObject->GetComponent<StateControl>()->SetState(L"Death");
		//m_gameObject->GetComponent<StateControl>()->SetState(Nalmak_Math::Random<wstring>(L"Explosion", L"Death"));
	}
	DEBUG_LOG(L"Enemy State", L"Falling");
}

void Enemy_Falling::ExitState()
{

}

void Enemy_Falling::Accelerate()
{
	if (m_fFallingSpd <= 50.f)
	{
		m_fFallingSpd += dTime * 10.f;
	}

	if (m_fTurnSpd <= 4.f)
	{
		m_fTurnSpd += dTime *0.8f;
	}

}

