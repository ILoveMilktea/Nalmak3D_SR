#include "stdafx.h"
#include "..\Include\Enemy_CrossFire_Evasion.h"
#include "Enemy_Bullet_Manager.h"


CrossFire_Evasion::CrossFire_Evasion()
{
}


CrossFire_Evasion::~CrossFire_Evasion()
{
}

void CrossFire_Evasion::Initialize()
{

}

void CrossFire_Evasion::EnterState()
{
}

void CrossFire_Evasion::UpdateState()
{
	m_fFpmDelta += dTime;

	if (60.f / m_fFpm <= m_fFpmDelta)
	{
		Vector3 vPos = m_transform->GetTransform()->position;

		Quaternion qRot = m_transform->GetTransform()->rotation;
		D3DXQuaternionIdentity(&qRot);
		D3DXQuaternionRotationAxis(&qRot, &Vector3(0.f, 1.f, 0.f), D3DXToRadian(m_fShootAngle));

		//right Shoot
		Vector3 vRight = { vPos.x + 2.5f, 0, vPos.z };

		Bullet_Manager::GetInstance()->Gun_Evasion(vRight, qRot);

		//left Shoot
		qRot = m_transform->GetTransform()->rotation;
		D3DXQuaternionIdentity(&qRot);
		D3DXQuaternionRotationAxis(&qRot, &Vector3(0.f, 1.f, 0.f), D3DXToRadian(360.f - m_fShootAngle));
		Vector3 vLeft = { vPos.x - 2.5f, 0.f, vPos.z };
		Bullet_Manager::GetInstance()->Gun_Evasion(vLeft, qRot);

		++m_iCount;

		if (m_iCount >= 3)
		{
			m_fFpmDelta = 0.f;
			m_iCount = 0;
		}

	}

	if (m_fShootAngle <= 90.f)
	{
		m_bAngleAdd = false;
	}
	if (m_fShootAngle >= 225.f)
	{
		m_bAngleAdd = true;
	}

	if (m_bAngleAdd)
	{
		m_fShootAngle -= dTime * 20.f;
	}
	else { m_fShootAngle += dTime * 20.f; }


	//DEBUG_LOG(L"Shoot Angle", m_fShootAngle);
	//DEBUG_LOG(L"Angle Bool", m_bAngleAdd);

	Exit();
}

void CrossFire_Evasion::ExitState()
{
}
