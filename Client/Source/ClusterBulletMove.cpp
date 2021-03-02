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

	if (FindEnemy(OBJECT_TAG_ENEMY, 80))
	{
		
		int ia = 10;


	}

	m_transform->position += m_firstDir * dTime * 5;

	DEBUG_LOG(L"Near Enemy ", FindEnemy(OBJECT_TAG_ENEMY , 80));
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
