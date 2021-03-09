#include "stdafx.h"
#include "..\Include\MidBoss_Laser_Fire.h"

#include "MidBoss_Define.h"
#include "Enemy_MidBoss.h"
#include "Enemy_BulletProof.h"
#include "DeadTimer.h"

MidBoss_Laser_Fire::MidBoss_Laser_Fire()
{
}


MidBoss_Laser_Fire::~MidBoss_Laser_Fire()
{
}

void MidBoss_Laser_Fire::Initialize()
{
}

void MidBoss_Laser_Fire::EnterState()
{
	g_fireDuration = GetFloat(_g_laserFireDuration);

	m_timer = 0.f;

	auto pivotTr = GetComponent<Enemy_MidBoss>()->GetBulletproofPivot()->GetTransform();

	for (int i = 0; i < 4; ++i)
	{
		m_bulletproof[i] = pivotTr->GetChild(i);
	}

	// temp laser
	CreateLaser(m_transform->GetWorldPosition(), m_transform->GetWorldPosition() + Vector3(0.f, 0.f, -500.f), 10.f);

	for (int i = 0; i < 4; ++i)
	{
		CreateLaser(m_bulletproof[i]->GetWorldPosition(), m_bulletproof[i]->GetWorldPosition() + Vector3(0.f, 0.f, -500.f), 10.f);
	}
}

void MidBoss_Laser_Fire::UpdateState()
{
	// lazer fire
	m_timer += dTime;

	if (m_timer >= g_fireDuration)
	{
		SetState(_sn_laserDischarge);
		return;
	}
}

void MidBoss_Laser_Fire::ExitState()
{
	DESTROY(m_mainLaser);
	for (int i = 0; i < 4; ++i)
	{
		DESTROY(m_subLaser[i]);
	}
}

void MidBoss_Laser_Fire::CreateLaser(Vector3 _startPoint, Vector3 _endPoint, float width)
{
	GameObject* laser = INSTANTIATE(OBJECT_TAG_BULLET_ENEMY, L"Bullet_Laser");
	Vector3 laserDir = _endPoint - _startPoint;
	laser->SetPosition(_startPoint + laserDir * 0.5);
	laser->GetTransform()->RotateX(90.f);

	float len = D3DXVec3Length(&laserDir);
	laser->SetScale(width, len, width);


	VIBufferRenderer::Desc desc_renderer;
	desc_renderer.meshName = L"cylinder";
	desc_renderer.mtrlName = L"default_green";
	laser->AddComponent<VIBufferRenderer>(&desc_renderer);

	LineCollider::Desc desc_col;
	desc_col.collisionLayer = COLLISION_LAYER_BULLET_ENEMY;
	laser->AddComponent<LineCollider>(&desc_col);

	DeadTimer::Desc desc_timer;
	desc_timer.timer = 3.f;
	laser->AddComponent<DeadTimer>(&desc_timer);
}
