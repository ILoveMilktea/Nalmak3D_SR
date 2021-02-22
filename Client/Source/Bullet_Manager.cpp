#include "stdafx.h"
#include "..\Include\Bullet_Manager.h"

#include "Bullet.h"

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
	Bullet_obj->SetScale(0.1f, 0.1f, 0.1f);
	
	Bullet::Desc Bullet_Desc;
	Bullet_Desc.fSpd = 50.f;
	Bullet_Desc.iDmg = 10;
	Bullet_obj->AddComponent<Bullet>(&Bullet_Desc);

	MeshRenderer::Desc Bullet_Mesh;
	Bullet_Mesh.mtrlName = L"default";
	Bullet_Mesh.meshName = L"sphere";
	Bullet_obj->AddComponent<MeshRenderer>(&Bullet_Mesh);


}
