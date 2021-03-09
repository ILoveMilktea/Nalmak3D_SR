#include "stdafx.h"
#include "..\Include\MidBoss_RotateAccel.h"

#include "MidBoss_Define.h"
#include "Enemy_MidBoss.h"


MidBoss_RotateAccel::MidBoss_RotateAccel()
{
}


MidBoss_RotateAccel::~MidBoss_RotateAccel()
{
}

void MidBoss_RotateAccel::Initialize()
{
}

void MidBoss_RotateAccel::EnterState()
{
	GetComponent<Enemy_MidBoss>()->SetRotateSpeed(_SPEED_HIGH);
	
	m_timer = 0.f;
	m_duration = 3.f;
}

void MidBoss_RotateAccel::UpdateState()
{
	//m_timer += dTime;

	//if (m_timer >= m_duration)
	//{
	//	SetState(_sn_idle);
	//	return;
	//}
	SetState(_sn_idle);

#ifdef _DEBUG
	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_F9))
	{
		SetState(_sn_idle);
		return;
	}
#endif // _DEBUG
}

void MidBoss_RotateAccel::ExitState()
{
	//GetComponent<Enemy_MidBoss>()->SetRotateSpeed(_SPEED_MID);
}
