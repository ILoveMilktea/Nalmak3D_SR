#include "stdafx.h"
#include "..\Include\Player_EmpMove.h"
#include "Player_EmpPulse.h"
#include "ParticleRenderer.h"
#include "ParticleDead_IfCount0.h"


Player_EmpMove::Player_EmpMove(Desc * _desc)
{
	m_fMaxSpd = _desc->fmaxSpd;
}

Player_EmpMove::~Player_EmpMove()
{
	if (m_smokeParticle)
	{
		m_smokeParticle->AddComponent<ParticleDead_IfCount0>();
		m_smokeParticle->StopEmit();
		m_smokeParticle = nullptr;
	}
}

void Player_EmpMove::Initialize()
{
	{
		ParticleRenderer::Desc render;
		render.particleDataName = L"missile_smoke";
		auto obj = INSTANTIATE()->AddComponent<ParticleRenderer>(&render);
		m_smokeParticle = obj->GetComponent<ParticleRenderer>();
		obj->SetParents(m_gameObject);
	}
}

void Player_EmpMove::Update()
{
	if (m_bGo)
	{	
		m_fEmpDelta += dTime;

		if (m_fEmpDelta < 0.5f)
		{
			m_transform->position.y -= dTime * 5.f;
			//m_transform->position -= m_transform->GetUp() * dTime * 5.f;
		}
		else 
		{
			Go_Straight();
		}
		
		
		if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_RIGHT_MOUSE))
		{
			Boom();
		}
	
	}


}

void Player_EmpMove::OnTriggerEnter(Collisions & _collision)
{
	for (auto& obj : _collision)
	{
		if (obj.GetGameObject()->GetTag() == OBJECT_TAG_ENEMY)
		{
			Boom();
		}
	}
	
}

void Player_EmpMove::OnTriggerStay(Collisions & _collision)
{
	
}

void Player_EmpMove::OnTriggerExit(Collisions & _collision)
{
	
}

void Player_EmpMove::Go_Straight()
{
	Accelerator();
	m_transform->position += m_transform->GetForward() * dTime * m_fMaxSpd;
}

void Player_EmpMove::Accelerator()
{
	if (m_fMaxSpd >= m_fCurSpd)
	{
		m_fCurSpd = Nalmak_Math::Lerp(m_fCurSpd, m_fMaxSpd, dTime);
	}
}

void Player_EmpMove::Boom()
{
	m_bGo = false;

	//m_gameObject->DeleteComponent<SphereCollider>();
	//m_gameObject->DeleteComponent<VIBufferRenderer>();

	Pulse = INSTANTIATE(OBJECT_TAG_BULLET_PLAYER, L"Pulse");
	Pulse->SetPosition(m_transform->position);

	Player_EmpPulse::Desc Pulse_desc;
	Pulse_desc.max_Radius = 50.f;
	Pulse->AddComponent<Player_EmpPulse>(&Pulse_desc);
	
	VIBufferRenderer::Desc Pulse_render;
	Pulse_render.meshName = L"screenQuad";
	Pulse_render.mtrlName = L"screenDistortion";
	Pulse->AddComponent<VIBufferRenderer>(&Pulse_render);

	SphereCollider::Desc Pulse_col;
	Pulse_col.collisionLayer = COLLISION_LAYER_BULLET_ENEMY;
	Pulse_col.radius = 0.5f;
	Pulse->AddComponent<SphereCollider>(&Pulse_col);

	DESTROY(m_gameObject);
	m_gameObject = nullptr;
}


