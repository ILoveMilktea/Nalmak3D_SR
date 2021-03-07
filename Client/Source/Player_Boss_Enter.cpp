#include "stdafx.h"
#include "..\Include\Player_Boss_Enter.h"
#include "EnemyManager.h"


Player_Boss_Enter::Player_Boss_Enter()
{
}


Player_Boss_Enter::~Player_Boss_Enter()
{
}

void Player_Boss_Enter::Initialize()
{
}

void Player_Boss_Enter::EnterState()
{
	int i = 0;
}

void Player_Boss_Enter::UpdateState()
{
	if (!m_bBackStep)
	{ 
		if (EnemyManager::GetInstance()->Get_Boss()->GetComponent<StateControl>()->GetCurStateString()
			== L"Boss_Enter")
		{
			m_bBackStep = true;
			
		}
	}
	else 
	{
		m_transform->position.z -= dTime * 5.f;

		if (EnemyManager::GetInstance()->Get_Boss()->GetComponent<StateControl>()->GetCurStateString()
			== L"Boss_Interrupt")
		{
			m_gameObject->GetComponent<StateControl>()->SetState(L"playerBoss_Move");
		}
	
	}
}

void Player_Boss_Enter::ExitState()
{
}
