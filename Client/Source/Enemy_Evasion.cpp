#include "stdafx.h"
#include "..\Include\Enemy_Evasion.h"


Enemy_Evasion::Enemy_Evasion()
	:m_fLifeTime(4.f)
{
}


Enemy_Evasion::~Enemy_Evasion()
{
}

void Enemy_Evasion::Initialize()
{
}

void Enemy_Evasion::EnterState()
{
	
}

void Enemy_Evasion::UpdateState()
{
	
}

void Enemy_Evasion::ExitState()
{
}

void Enemy_Evasion::Exit()
{
	m_fExitDelta += dTime;

	if (m_fExitDelta >= m_fLifeTime)
	{
		//m_gameObject->GetComponent<StateControl>()->SetState(L"Exit");
		SetState(L"Evasion_Disappear");
	}
}
