#include "stdafx.h"
#include "..\Include\Diagonal_Evasion.h"
#include "Bullet_Manager.h"


Diagonal_Evasion::Diagonal_Evasion()
{
}

Diagonal_Evasion::~Diagonal_Evasion()
{
}

void Diagonal_Evasion::Initialize()
{
}

void Diagonal_Evasion::EnterState()
{
	int iRand = rand() % 2;

	switch (iRand)
	{
	case 0: //rightTop -> leftBottom
	{
		m_iDirection = -1;

		int z = rand() % 45 + 20;
		m_transform->SetPosition(Vector3(90.f, 0.f, (float)z));
		m_transform->SetRotationY(45.f);
	}
	break;

	case 1: //leftTop -> rightBottom
	{
		m_iDirection = 1;

		int z = rand() % 45 + 20;
		m_transform->SetPosition(Vector3(-90.f, 0.f, (float)z));
		m_transform->SetRotationY(-45.f);
	}
	break;

	default:
		break;
	}
}

void Diagonal_Evasion::UpdateState()
{
	m_transform->position += m_transform->GetForward() * m_fSpd * dTime;

	m_fFpmDelta += dTime;

	if (m_fFpmDelta >= 60.f / m_fFpm)
	{
		Bullet_Manager::GetInstance()->Gun_Evasion(m_transform->position, m_transform->rotation);

		m_fFpmDelta = 0.f;
	}
}

void Diagonal_Evasion::ExitState()
{
}
