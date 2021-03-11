#include "stdafx.h"
#include "..\Include\MidBoss_Laser_Siege.h"

#include "MidBoss_Define.h"
#include "Enemy_MidBoss.h"

MidBoss_Laser_Siege::MidBoss_Laser_Siege()
{
}


MidBoss_Laser_Siege::~MidBoss_Laser_Siege()
{
}

void MidBoss_Laser_Siege::Initialize()
{
}

void MidBoss_Laser_Siege::EnterState()
{
	GetComponent<Enemy_MidBoss>()->PivotRotateOff();
	m_rotatePivot = GetComponent<Enemy_MidBoss>()->GetBulletproofPivot()->GetTransform();

	m_startPosition = m_transform->position;
	m_startRot = m_rotatePivot->rotation;
	m_siegeRot = _MIDBOSS_CENTERROT;

	g_siegeDuration = GetFloat(_g_laserSiegeDuration);

	m_timer = 0.f;

}

void MidBoss_Laser_Siege::UpdateState()
{
	float inverseRate = 1.f - m_timer / g_siegeDuration;
	float sLerpTimer = 1.f - inverseRate * inverseRate;
	m_transform->position = Nalmak_Math::Lerp(m_startPosition, _MIDBOSS_CENTERPOS, sLerpTimer);
	D3DXQuaternionSlerp(&m_rotatePivot->rotation, &m_startRot, &m_siegeRot, sLerpTimer);

	m_timer += dTime;

	if (m_timer >= g_siegeDuration)
	{
		m_transform->position = _MIDBOSS_CENTERPOS;
		m_rotatePivot->rotation = _MIDBOSS_CENTERROT;
		SetState(_sn_laserDetach);
		return;
	}

#ifdef _DEBUG
	if (InputManager::GetInstance()->GetKeyDown(_NEXT_STATE_KEY))
	{
		SetState(_sn_laserAttach);
		return;
	}
#endif // _DEBUG
}

void MidBoss_Laser_Siege::ExitState()
{
}
