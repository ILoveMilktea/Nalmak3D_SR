#include "stdafx.h"
#include "..\Include\ClusterBulletMove.h"





ClusterBulletMove::ClusterBulletMove(Desc * _desc)
{
	m_speed = _desc->speed;
}

ClusterBulletMove::~ClusterBulletMove()
{
}

void ClusterBulletMove::Initialize()
{
	m_player = Core::GetInstance()->FindFirstObject(OBJECT_TAG_PLAYER);
	m_firstDir = m_player->GetTransform()->GetForward();
}

void ClusterBulletMove::Update()
{

	GameObject* target = FindEnemy(OBJECT_TAG::OBJECT_TAG_ENEMY);
	Vector3 dir = target->GetTransform()->position - m_transform->position;
	D3DXVec3Normalize(&dir, &dir);

	m_transform->LookAt(dir + m_transform->position, 1.5f);
	m_transform->position += dir * 25 * dTime;

}

GameObject* ClusterBulletMove::FindEnemy(OBJECT_TAG _enum, float _mimDis)
{
	GameObject* target = nullptr; 
	float mindis = _mimDis;
	for (auto& value : Core::GetInstance()->GetObjectList(_enum))
	{
		float lenght =  Nalmak_Math::Distance(value->GetTransform()->position, m_gameObject->GetTransform()->position);
		//value->
	
		if (mindis > lenght || !target)
		{
			mindis = lenght;
			target = value;
			break;
		}
	}

	return target;

}
