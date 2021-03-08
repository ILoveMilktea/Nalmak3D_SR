#include "stdafx.h"
#include "..\Include\Enemy_MachineGun.h"
#include "PlayerInfoManager.h"



MachineGun::MachineGun(Desc* _desc)
{
	m_fSpd = _desc->fSpd;
	m_iDamage = _desc->iDmg;

	m_bStraight = _desc->bStraight;
	m_vDest = _desc->vDest;
}


MachineGun::~MachineGun()
{
}

void MachineGun::Initialize()
{
	m_pMainCamera = Core::GetInstance()->GetMainCamera();
	m_transform->SetScale(Vector3(1, m_strechRatio, 1));
	m_pMaterial = GetComponent<VIBufferRenderer>()->GetMaterial();
	
	m_vForwardDir = m_transform->GetForward();

}

void MachineGun::Update()
{
	CalcDir();

	m_fDeltaTime += dTime;

	if (m_bStraight)
	{
		Straight_Shoot();
	}
	else 
	{
		Dest_Shoot();
	}

	{
		float angle = Nalmak_Math::Dot(Vector3(0, 1, 0), m_vForwardDir);

		Vector3 axis;
		D3DXVec3Cross(&axis, &Vector3(0, 1, 0), &m_vForwardDir);
		D3DXQuaternionRotationAxis(&m_transform->rotation, &axis, acos(angle));
		//m_transform->SetRotation(90,0,0);

		m_transform->position += m_vForwardDir * m_fSpd * dTime;

		Matrix view = m_pMainCamera->GetViewMatrix();
		Matrix billboard;
		D3DXMatrixIdentity(&billboard);
		memcpy(&billboard.m[0][0], &view.m[0][0], sizeof(Vector3));
		memcpy(&billboard.m[1][0], &view.m[1][0], sizeof(Vector3));
		memcpy(&billboard.m[2][0], &view.m[2][0], sizeof(Vector3));

		D3DXMatrixInverse(&billboard, 0, &billboard);

		m_pMaterial->SetMatrix("g_invViewForBillboard", billboard);
	}
	
	if (m_fDeltaTime >= 5.f) 
	{
		DESTROY(m_gameObject);
	}

}

void MachineGun::OnTriggerEnter(Collisions & _collision)
{
	//MainGame에서 충돌 확인할 Layer설정 해줘야함.
	//아님 안함
	for (auto& obj : _collision)
	{
		if (obj.GetGameObject()->GetTag() == OBJECT_TAG_PLAYER)
		{
			PlayerInfoManager::GetInstance()->SetDamage(m_iDamage);
			DESTROY(m_gameObject);
		}
	}
}

void MachineGun::OnTriggerStay(Collisions & _collision)
{
}

void MachineGun::OnTriggerExit(Collisions & _collision)
{
}

void MachineGun::Go_Straight()
{
	m_transform->position += m_transform->GetForward() * m_fSpd * dTime;
}

void MachineGun::Straight_Shoot()
{
	Go_Straight();
}

void MachineGun::CalcDir()
{
	if (m_bFirst == true && m_bStraight == false)
	{
		m_vDir = m_vDest - m_transform->position;
		D3DXVec3Normalize(&m_vDir, &m_vDir);

		m_bFirst = false;
	}
}

void MachineGun::Dest_Shoot()
{
	m_transform->position += m_vDir * m_fSpd * dTime;
}
