#include "stdafx.h"
#include "..\Include\AirFire_Evasion.h"
#include "Bullet_Manager.h"
#include "Enemy_AirFire_TargetPlane.h"


AirFire_Evasion::AirFire_Evasion()
{
}


AirFire_Evasion::~AirFire_Evasion()
{
}

void AirFire_Evasion::Initialize()
{
}

void AirFire_Evasion::EnterState()
{
	m_pPlayer = Core::GetInstance()->FindFirstObject(OBJECT_TAG_PLAYER);
	m_transform->SetPosition(Vector3(50.f, -100.f, 30.f));
}

void AirFire_Evasion::UpdateState()
{
	//대충 거 쏘기 전에 스크립트로 조심해라라고 띄워주기.

	m_transform->LookAt(m_pPlayer, 1.f);

	m_fShootDelta += dTime;

	if (m_fShootDelta >= 3.f)
	{
		m_fBrustDelta += dTime;

		if (m_fBrustDelta >= 0.1f)
		{
			m_vDestPos.x = m_pPlayer->GetTransform()->position.x + (float)(rand() % 11 - 5);
			m_vDestPos.y = m_pPlayer->GetTransform()->position.y;
			m_vDestPos.z = m_pPlayer->GetTransform()->position.z + (float)(rand() % 11 - 5);

			Bullet_Manager::GetInstance()->Fire_Dest(m_transform->position, m_vDestPos, 150.f);

			++m_iCount;
			m_fBrustDelta = 0.f;

			Show_TargetPos();
		}
		
		if (m_iCount > 5)
		{
			
			m_iCount = 0;
			m_fShootDelta = 0.f;
		}

	}


	
}

void AirFire_Evasion::ExitState()
{
}

void AirFire_Evasion::Show_TargetPos()
{
	GameObject* TargetPlane = INSTANTIATE();
	TargetPlane->SetPosition(m_vDestPos);
	TargetPlane->SetScale(0.05f, 0.05f, 0.05f);

	Enemy_AirFire_TargetPlane::Desc compoent;
	TargetPlane->AddComponent<Enemy_AirFire_TargetPlane>(&compoent);

	VIBufferRenderer::Desc Target_render;
	Target_render.meshName = L"plane";
	Target_render.mtrlName = L"AirTarget";
	TargetPlane->AddComponent<VIBufferRenderer>(&Target_render);

	//m_vTarget_Plane.emplace_back(TargetPlane);
}
