#include "stdafx.h"
#include "..\Include\Bullet_Manager.h"

#include "Bullet.h"
#include "Missile.h"

Bullet_Manager* Bullet_Manager::m_Instance = nullptr;

Bullet_Manager::Bullet_Manager(Desc * _desc)
{
}

Bullet_Manager::~Bullet_Manager()
{
}

Bullet_Manager * Bullet_Manager::GetInstance()
{
	if (m_Instance)
	{
		auto Instance = INSTANTIATE();
		Instance->AddComponent<Bullet_Manager>();
		m_Instance = Instance->GetComponent<Bullet_Manager>();

		Instance->SetDontDestroy(true);
	}
	return m_Instance;
}

void Bullet_Manager::DeleteInstance()
{
	if (m_Instance)
	{
		DESTROY(m_Instance->GetGameObject());
	}
}

void Bullet_Manager::Initialize()
{
}

void Bullet_Manager::Update()
{
	
}

void Bullet_Manager::Fire(Vector3 _pos, Quaternion _rot)
{
	GameObject* Bullet_obj = INSTANTIATE(OBJECT_TAG_BULLET, L"Bullet");
	Bullet_obj->SetPosition(_pos);
	Bullet_obj->GetTransform()->rotation = _rot;
	Bullet_obj->SetScale(0.5f, 0.5f, 0.5f);
	
	Bullet::Desc Bullet_Desc;
	Bullet_Desc.fSpd = 50.f;
	Bullet_Desc.iDmg = 10.f;
	Bullet_obj->AddComponent<Bullet>(&Bullet_Desc);

	MeshRenderer::Desc Bullet_Mesh;
	Bullet_Mesh.mtrlName = L"default";
	Bullet_Mesh.meshName = L"box";
	Bullet_obj->AddComponent<MeshRenderer>(&Bullet_Mesh);


}

void Bullet_Manager::Fire_Missile(Vector3 _start, Vector3 _dest)
{
	GameObject* Missile_obj = INSTANTIATE(OBJECT_TAG_BULLET, L"Missile");
	Missile_obj->SetPosition(_start);
	Missile_obj->SetScale(0.5f, 0.5f, 3.5f);

	Missile::Desc Missile_Desc;
	Missile_Desc.vDest = _dest;
	Missile_obj->AddComponent<Missile>(&Missile_Desc);

	MeshRenderer::Desc Missile_Mesh;
	Missile_Mesh.mtrlName = L"default";
	Missile_Mesh.meshName = L"box";
	Missile_obj->AddComponent<MeshRenderer>(&Missile_Mesh);

}