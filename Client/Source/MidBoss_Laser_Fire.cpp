#include "stdafx.h"
#include "..\Include\MidBoss_Laser_Fire.h"

#include "MidBoss_Define.h"
#include "Enemy_MidBoss.h"
#include "Enemy_BulletProof.h"

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
	m_mainLaser = INSTANTIATE();
	m_mainLaser->AddComponent<CanvasRenderer>();
	m_mainLaser->AddComponent<SingleImage>();
	m_mainLaser->GetComponent<CanvasRenderer>()->SetColor(Vector4(0.6f, 0.f, 0.2f, 0.8f));
	Camera* maincam = Core::GetInstance()->GetMainCamera();
	Vector3 winpos = maincam->WorldToScreenPos(m_transform->position);
	//winpos = Vector3(winpos.x + WINCX * 0.5f, )
	m_mainLaser->SetPosition(winpos.x, winpos.y + (WINCY - winpos.y) * 0.5f);
	Vector3 left = maincam->WorldToScreenPos(m_transform->position - Vector3(m_transform->scale.x * 0.5f, 0.f, 0.f));
	Vector3 right = maincam->WorldToScreenPos(m_transform->position + Vector3(m_transform->scale.x * 0.5f, 0.f, 0.f));
	m_mainLaser->SetScale(right.x - left.x, WINCY - winpos.y);

	for (int i = 0; i < 4; ++i)
	{
		m_subLaser[i] = INSTANTIATE();
		m_subLaser[i]->AddComponent<CanvasRenderer>();
		m_subLaser[i]->AddComponent<SingleImage>();
		m_subLaser[i]->GetComponent<CanvasRenderer>()->SetColor(Vector4(0.6f, 0.f, 0.2f, 0.8f));
		Camera* maincam = Core::GetInstance()->GetMainCamera();
		Vector3 winpos = maincam->WorldToScreenPos(m_subLaser[i]->GetTransform()->GetWorldPosition());
		m_subLaser[i]->SetPosition(winpos.x, winpos.y + (WINCY - winpos.y) * 0.5f);
		Vector3 left = maincam->WorldToScreenPos(m_subLaser[i]->GetTransform()->GetWorldPosition() - Vector3(m_subLaser[i]->GetTransform()->scale.x * 0.5f, 0.f, 0.f));
		Vector3 right = maincam->WorldToScreenPos(m_subLaser[i]->GetTransform()->GetWorldPosition() + Vector3(m_subLaser[i]->GetTransform()->scale.x * 0.5f, 0.f, 0.f));
		m_subLaser[i]->SetScale(right.x - left.x, WINCY - winpos.y);
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
