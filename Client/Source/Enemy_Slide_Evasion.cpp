#include "stdafx.h"
#include "..\Include\Enemy_Slide_Evasion.h"

#include "Enemy_Bullet_Manager.h"

Slide_Evasion::Slide_Evasion()
{
}


Slide_Evasion::~Slide_Evasion()
{
}

void Slide_Evasion::Initialize()
{
}

void Slide_Evasion::EnterState()
{
	int iRand = rand() % 2;
	
	switch (iRand)
	{
	case 0: //right -> left
	{
		m_iDirection = -1; 
	
		int z = rand() % 45;
		m_transform->SetPosition(Vector3(90.f, 0.f, (float)z));
	}
	break;

	case 1: // left -> right
	{
		m_iDirection = 1;

		int z = rand() % 45;
		m_transform->SetPosition(Vector3(-90.f, 0.f, (float)z));
		
	
	}
	break;

	default:
		break;
	}


}

void Slide_Evasion::UpdateState()
{
	m_transform->position.x += m_iDirection * dTime * m_fSpd;

	m_fFpmDelta += dTime;

	if (m_fFpmDelta >= 60.f / m_fFpm )
	{	
		Bullet_Manager::GetInstance()->Gun_Evasion(m_transform->position, m_transform->rotation);

		m_fFpmDelta = 0.f;
	}
}

void Slide_Evasion::ExitState()
{

}
