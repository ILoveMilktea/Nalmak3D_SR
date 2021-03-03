#include "stdafx.h"
#include "..\Include\ClusterBulletMove.h"
#include "Player_NearGuideBullet.h"




ClusterBulletMove::ClusterBulletMove(Desc * _desc)
{
	m_speed = _desc->speed;
	m_bulletCount = _desc->bulletCount;
	m_screenPos = _desc->screenPos;
	m_target = _desc->target;
}

ClusterBulletMove::~ClusterBulletMove()
{
	Release();

}

void ClusterBulletMove::Initialize()
{
	m_player = Core::GetInstance()->FindFirstObject(OBJECT_TAG_PLAYER);

	Vector3 playerLook = m_player->GetTransform()->GetForward();
	Vector3 playerRight = m_player->GetTransform()->GetRight();
	Vector3 playerUp = m_player->GetTransform()->GetUp();

	Vector3 winDir = playerRight * m_screenPos.x + playerUp * m_screenPos.y;
	D3DXVec3Normalize(&winDir, &winDir);
	m_firstDir = playerLook + winDir;
	
}

void ClusterBulletMove::Update()
{

	
	Vector3 dir = m_target->GetTransform()->position - m_transform->position;
	D3DXVec3Normalize(&dir, &dir);
	
	m_transform->LookAt(dir + m_transform->position, 1.5f);

	m_transform->position += ((dir + m_firstDir)  * m_speed * dTime);

	float EnemyPlayerLenght = Nalmak_Math::Distance(m_player->GetTransform()->position, m_target->GetTransform()->position);
	float fromEnemyLenght = Nalmak_Math::Distance(m_target->GetTransform()->position, m_gameObject->GetTransform()->position);

	float ratioValue = fromEnemyLenght / EnemyPlayerLenght;

	/*DEBUG_LOG(L"∫Ò¿≤", ratioValue);
	if (ratioValue <= 0.2f)
	{
		DESTROY(m_gameObject);
		m_start = true;
	}
*/
}

void ClusterBulletMove::Release()
{
	if (m_start)
	{
		VIBufferRenderer::Desc render;
		render.meshName = L"box";
		render.mtrlName = L"default";

		float angleInterval = PI2 / m_bulletCount;

		for (int i = 0; i < m_bulletCount; ++i)
		{
			auto child = INSTANTIATE(OBJECT_TAG_BULLET_PLAYER, L"clusterChild")->AddComponent<VIBufferRenderer>(&render);
			//child->AddComponent<Player_NearGuideBullet>();

			float x = m_transform->position.x + cosf(D3DXToRadian(i * angleInterval)) * 5.f;
			float y = m_transform->position.y - sin(D3DXToRadian(i * angleInterval)) * 5.f;
			
			child->SetPosition(x, y, m_transform->position.z);
		}
		m_start = false;
	}
	m_gameObject = nullptr;
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
