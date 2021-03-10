#include "stdafx.h"
#include "..\Include\Enemy_Falling.h"
#include "Enemy.h"
#include "ParticleDead_IfCount0.h"


Enemy_Falling::Enemy_Falling()
{
}


Enemy_Falling::~Enemy_Falling()
{
}

void Enemy_Falling::Initialize()
{
	
}

void Enemy_Falling::EnterState()
{
	m_pEnemy = m_gameObject->GetComponent<Enemy>();

	assert(L"�� ���� ���ʹ� �� ã���� ���ٰ� ����" && m_pEnemy);
	
	m_pEnemy->Target_Setting(false);

	//if (m_pSmokeParticle == nullptr)
	//{
	//	m_pSmokeParticle = INSTANTIATE(OBJECT_TAG_PARTICLE, L"enemy_falling_smoke");
	//
	//	ParticleRenderer::Desc smoke_desc;
	//	smoke_desc.particleDataName = L"enemy_smoke_0";
	//	smoke_desc.PlayOnAwake = true; //��ü ������ ���ÿ� ��ƼŬ on!

	//	if (m_pSmokeParticle != nullptr)
	//	{
	//		m_pSmokeParticle->AddComponent<ParticleRenderer>(&smoke_desc);
	//	}

	//	m_pSmokeParticle->AddComponent<ParticleDead_IfCount0>();
	//	//�̰� �޾Ƶθ� ���� �� ������Ű��
	//	//�� ������ �� ������� ���� �˾Ƽ� ������.
	//	//*����* ���⼭ �����ϴ� gameobject�� �� enemy�� �ƴ϶� particle�� gameobject��!!!
	//	
	//}
	
	
}

void Enemy_Falling::UpdateState()
{

	m_fFallDelta += dTime;

	Accelerate();
	//1. flight ahead ground
	//Dot forward and (0,-1,0);

	Vector3 vYaxis = { 0.f, -1.f, 0.f };
	float fInner = D3DXVec3Dot(&m_transform->GetForward(), &vYaxis);

	if (fInner <= 0.95f)
	{
		Quaternion qToGround = m_transform->RotateAxis(m_transform->GetRight(), dTime*2.f);
		m_transform->rotation *= qToGround;
	}

	
	//if(m_bFalling)
	//{
		//2. turn slowly to ZAxis for turn
		//Quaternion qTemp = m_transform->RotateAxis(Vector3(0, 1, 0), m_fTurnSpd * dTime);
	Quaternion qTemp = m_transform->RotateAxis(m_transform->GetForward(), m_fTurnSpd * dTime);
		m_transform->rotation *= qTemp;		
	//}

	//3. faliing
	m_transform->position.y -= dTime * m_fFallingSpd;
	//m_pSmokeParticle->GetTransform()->position = m_transform->position;

	//if (m_fFallDelta >= 5.f)
	//{
	//	if (m_pSmokeParticle != nullptr)
	//	{
	//		m_pSmokeParticle->GetComponent<ParticleRenderer>()->StopEmit();
	//		//�Ʊ� �޾Ƴ��� ���� ������ �ƶ� �����Ǹ� ������.
	//	}

		m_gameObject->GetComponent<StateControl>()->SetState(L"Explosion");
	//}

	DEBUG_LOG(L"Falling Inner", fInner);
	DEBUG_LOG(L"Enemy State", L"Falling");
}

void Enemy_Falling::ExitState()
{
	//m_gameObject->DeleteComponent<MeshRenderer>();
	// for .Use player nearGuidBullet
	

}

void Enemy_Falling::Accelerate()
{
	if (m_fFallingSpd <= 50.f)
	{
		m_fFallingSpd += dTime * 10.f;
	}

	if (m_fTurnSpd <= 4.f)
	{
		m_fTurnSpd += dTime *0.8f;
	}

}

