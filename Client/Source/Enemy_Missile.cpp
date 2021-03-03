#include "stdafx.h"
#include "..\Include\Enemy_Missile.h"



// Missile's Initial rotate valvue must be given like bullet.

Missile::Missile(Desc * _desc)
{
	m_iMinDmg = _desc->iMinDmg;
	m_iMaxDmg = _desc->iMaxDmg;

	m_fMaxSpd = _desc->fMaxSpd;
}

Missile::~Missile()
{

}

void Missile::Initialize()
{
	
	
}

void Missile::Update()
{
	m_fMissileDelta += dTime;

	if (m_fMissileDelta < 0.5f)
	{
		//�ణ ������ ������ ������
		m_transform->position.y -= dTime * 5.f;
		if (m_bEffect == false)
		{
			m_bEffect = true;
		}
	}

	if (m_fMissileDelta >= 0.5f)
	{//�߻��ϰ� ���ӵ�
		if (m_bEffect)
		{/*Effect Setting Here*/
			
			m_bEffect = false;
		}
		Accelerate(m_fMaxSpd);
		m_transform->position += m_transform->GetForward() * m_fCurSpd * dTime;
	}

	Boom();
	DEBUG_LOG(L"�̻��� ���� ��ġ", m_transform->position);
	DEBUG_LOG(L"�̻��� �ӵ�", m_fCurSpd);
}

void Missile::OnTriggerEnter(Collisions & _collision)
{
	for (auto& obj : _collision)
	{
		if (obj.GetGameObject()->GetTag() == OBJECT_TAG_PLAYER)
		{
			DESTROY(m_gameObject);
		}
	}
}

void Missile::OnTriggerStay(Collisions & _collision)
{
}

void Missile::OnTriggerExit(Collisions & _collision)
{
}

void Missile::Accelerate(float _maxSpd)
{
	if (m_fMaxSpd >= m_fCurSpd)
	{
		//m_fCurSpd += dTime * 50.f;
		m_fCurSpd = Nalmak_Math::Lerp(m_fCurSpd, m_fMaxSpd, dTime);
		//Lerp : ù��° ������ ���� �޾ƿͼ� MaxSpd�� �������� DTime��ŭ ������
		//		=> �׳� += dTime ���� �ϸ� �ӵ��� Ȯ ����, Ȯ ���� �ϴµ�
		//			Lerp�� �ϸ� ���������� �������� �Ź� �޾ƿͼ� �� �ȿ��� ������ �����ϴ°Ŷ� ��ӵ��� ��.

	}
}


void Missile::Boom()
{
	if (m_fMissileDelta >= 10.f)
	{
		DESTROY(m_gameObject);
	}
	
}
