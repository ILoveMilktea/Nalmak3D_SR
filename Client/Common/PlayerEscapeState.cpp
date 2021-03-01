#include "stdafx.h"
#include "PlayerEscapeState.h"
#include "PlayerSkillActor.h"
#include "PlayerItem.h"

PlayerEscapeState::PlayerEscapeState()
{
}


PlayerEscapeState::~PlayerEscapeState()
{
}

void PlayerEscapeState::Initialize()
{
}

void PlayerEscapeState::EnterState()
{
	m_skillActor = m_gameObject->GetComponent<PlayerSkillActor>();
	m_skillInfo = m_skillActor->GetSkillInfo();

	// test skill;
	// test defender skill; 
	m_dealy = m_skillInfo->GetItmeInfo().delay;

	

	int a = 10;
}

void PlayerEscapeState::UpdateState()
{
	
}

void PlayerEscapeState::ExitState()
{
}
