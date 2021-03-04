#include "stdafx.h"
#include "..\Include\Enemy_Exit_Evasion.h"


Exit_Evasion::Exit_Evasion()
{
}


Exit_Evasion::~Exit_Evasion()
{
}

void Exit_Evasion::Initialize()
{
}

void Exit_Evasion::EnterState()
{
	m_iDir = rand() %2;
	m_iRotSpd = rand() % 50 ;
	m_fRotTime = rand() % 4 + ((rand() % 10 + 1) / 10.f);
	switch (m_iDir)
	{
	case 0:
	{
		m_iDir = -1;
	}
	break;

	default:
		break;
	}
}

void Exit_Evasion::UpdateState()
{
	m_fRotDelta += dTime;

	Turn();
	Accelerate();
	Go_Straight();


	DEBUG_LOG(L"살아있음", L"아직까지는");
	DEBUG_LOG(L"turn time", m_fRotTime);
	Destory();
}

void Exit_Evasion::ExitState()
{
}

void Exit_Evasion::Turn()
{
	if (m_fRotDelta <= m_fRotTime)
	{
		m_transform->RotateY(dTime*m_iRotSpd*m_iDir);
	}
		
}

void Exit_Evasion::Go_Straight()
{
	m_transform->position += m_transform->GetForward() * dTime * m_fSpd;
}

void Exit_Evasion::Accelerate()
{
	if (m_fSpd <= 30.f)
	{
		m_fSpd += dTime * 5.f;
	}
}

void Exit_Evasion::Destory()
{
	if (m_transform->position.x >= 95.f
		|| m_transform->position.x <= -95.f
		|| m_transform->position.z >= 60.f
		|| m_transform->position.z <= -60.f)
	{
		DESTROY(m_gameObject);
	}
}
