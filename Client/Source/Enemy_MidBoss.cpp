#include "stdafx.h"
#include "..\Include\Enemy_MidBoss.h"


Enemy_MidBoss::Enemy_MidBoss(Desc * _desc)
{
	m_status = _desc->tStatus;
	m_status.m_iCurHp = _desc->tStatus.m_iFullHp;

	m_mode = CONTROL;
	
	m_bulletproofPivot = _desc->pivot;
	m_pivotRotate = true;
}

Enemy_MidBoss::~Enemy_MidBoss()
{
}

void Enemy_MidBoss::Initialize()
{
}

void Enemy_MidBoss::Update()
{
	if (m_pivotRotate)
	{
		m_bulletproofPivot->GetTransform()->RotateY(5.f * dTime);
	}
}

void Enemy_MidBoss::Release()
{
	Component::Release();

	//if (!m_bulletproofPivot)
	//	return;

	//Transform* tr = m_bulletproofPivot->GetTransform();
	//
	//if (tr->GetChildCount() > 0)
	//{

	//	auto child1 = tr->GetChild(0);
	//	child1->DeleteParent();
	//	DESTROY(child1->GetGameObject());
	//	auto child2 = tr->GetChild(1);
	//	child2->DeleteParent();
	//	DESTROY(child2->GetGameObject());
	//	auto child3 = tr->GetChild(2);
	//	child3->DeleteParent();
	//	DESTROY(child3->GetGameObject());
	//	auto child4 = tr->GetChild(3);
	//	child4->DeleteParent();
	//	DESTROY(child4->GetGameObject());
	//}

	//m_bulletproofPivot->GetTransform()->DeleteParent();
	//DESTROY(m_bulletproofPivot);

}

void Enemy_MidBoss::OnTriggerEnter(Collisions & _collision)
{
	for (auto& obj : _collision)
	{
		if (obj.GetGameObject()->GetTag() == OBJECT_TAG_BULLET_PLAYER)
		{
			//m_tBossStatus.m_iCurHp -= 10;


		}
	}
}

void Enemy_MidBoss::OnTriggerStay(Collisions & _collision)
{
}

void Enemy_MidBoss::OnTriggerExit(Collisions & _collision)
{
}

int Enemy_MidBoss::Get_FullHp() const
{
	return m_status.m_iFullHp;
}

int Enemy_MidBoss::Get_CurHp() const
{
	return m_status.m_iCurHp;
}

void Enemy_MidBoss::Damaged(int _dmg)
{
	m_status.m_iCurHp -= _dmg;

	if (m_status.m_iCurHp < 0)
	{
		m_status.m_iCurHp = 0;
	}
}
