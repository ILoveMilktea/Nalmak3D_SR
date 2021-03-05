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
	m_firstDir = Nalmak_Math::Lerp(m_firstDir, m_player->GetTransform()->GetForward(), dTime);
	m_transform->position += ((dir + m_firstDir)  * 45.f * dTime);

	float EnemyPlayerLenght = Nalmak_Math::Distance(m_player->GetTransform()->position, m_target->GetTransform()->position);
	float fromEnemyLenght = Nalmak_Math::Distance(m_target->GetTransform()->position, m_gameObject->GetTransform()->position);

	float ratioValue = fromEnemyLenght / EnemyPlayerLenght;

	DEBUG_LOG(L"∫Ò¿≤", ratioValue);
	if (ratioValue <= 0.5f)
	{
		DESTROY(m_gameObject);
		m_start = true;
	}

}

void ClusterBulletMove::Release()
{
	if (m_start)
	{
		VIBufferRenderer::Desc render;
		render.meshName = L"box";
		render.mtrlName = L"default";

		float angleInterval = PI2 / m_bulletCount;
		float length = 15.f;
		Matrix temproyWorldMatrix = m_target->GetTransform()->GetWorldMatrix();
		Vector3 offSetX = Vector3(temproyWorldMatrix._11, temproyWorldMatrix._12, temproyWorldMatrix._13) * length;
		Vector3 offSetY = Vector3(temproyWorldMatrix._21, temproyWorldMatrix._22, temproyWorldMatrix._23) * length;
		Vector3 offSetZ = Vector3(temproyWorldMatrix._31, temproyWorldMatrix._32, temproyWorldMatrix._33) * length;

		
		Player_NearGuideBullet::Desc guidebulletInfo;
		SphereCollider::Desc sphereColInfo;
		sphereColInfo.collisionLayer = COLLISION_LAYER_BULLET_PLAYER;
		guidebulletInfo.speed = m_speed;
		for (int i = 0; i < m_bulletCount; ++i)
		{
			auto child = INSTANTIATE(OBJECT_TAG_BULLET_PLAYER)->AddComponent<VIBufferRenderer>(&render);
			child->AddComponent<SphereCollider>(&sphereColInfo);

			float x = m_transform->position.x + cosf(D3DXToRadian(i * angleInterval)) * length;
			float y = m_transform->position.y - sinf(D3DXToRadian(i * angleInterval)) * length;
			float z = m_transform->position.z - cosf(D3DXToRadian(i * angleInterval)) * length;
			guidebulletInfo.firstTarget = { x,y,z };

			child->AddComponent<Player_NearGuideBullet>(&guidebulletInfo);
			child->SetPosition(m_transform->position);
			child->SetScale(1.f, 1.f, 3.f);
			child->GetTransform()->rotation = m_transform->rotation;
		}
		m_start = false;
	}
	m_gameObject = nullptr;
}

