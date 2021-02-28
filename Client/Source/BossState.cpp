#include "stdafx.h"
#include "..\Include\BossState.h"


BossState::BossState()
{
}


BossState::~BossState()
{
}

void BossState::Initialize()
{

}

void BossState::EnterState()
{


}

void BossState::UpdateState()
{
	DEBUG_LOG(L"Current Combat State : ", L"Boss State");

	m_fBossTime += dTime;
}

void BossState::ExitState()
{
}

float BossState::Get_Time() const
{
	return m_fBossTime;
}

float BossState::Get_Score() const
{
	return m_fBossScore;
}

void BossState::Set_Score(float _score)
{
	m_fBossScore = _score;
}

void BossState::Add_Score(float _score)
{
	m_fBossScore += _score;
}
