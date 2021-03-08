#include "stdafx.h"
#include "..\Include\Boss_Enter.h"


Boss_Enter::Boss_Enter()
{
}


Boss_Enter::~Boss_Enter()
{
}

void Boss_Enter::Initialize()
{

}

void Boss_Enter::EnterState()
{
}

void Boss_Enter::UpdateState()
{
	if (m_transform->position.z >= 80.f)
	{
		m_transform->position.z -= dTime * 10.f;
	}
	else 
	{
		m_gameObject->GetComponent<StateControl>()->SetState(L"Boss_Interrupt");
	}
	

	DEBUG_LOG(L"Boss Pos", m_transform->position);
}

void Boss_Enter::ExitState()
{
}
