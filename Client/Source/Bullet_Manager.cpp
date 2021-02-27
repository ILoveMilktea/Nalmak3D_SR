#include "stdafx.h"
#include "..\Include\Bullet_Manager.h"

#include "MachineGun.h"
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
	if (m_Instance == nullptr)
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

void Bullet_Manager::Fire_Gun(Vector3 _start, Quaternion _rot, int _dmg, float _spd)
{
		GameObject* Gun_obj = INSTANTIATE(OBJECT_TAG_BULLET_ENEMY, L"Bullet_Enemy");
		Gun_obj->SetPosition(_start);
		Gun_obj->GetTransform()->rotation = _rot;
		Gun_obj->SetScale(0.5f, 0.5f, 0.5f);

		MachineGun::Desc Gun_Desc;
		Gun_Desc.fSpd = _spd;
		Gun_Desc.iDmg = _dmg;
		Gun_obj->AddComponent<MachineGun>(&Gun_Desc);

		MeshRenderer::Desc Gun_Mesh;
		Gun_Mesh.mtrlName = L"default";
		Gun_Mesh.meshName = L"box";
		Gun_obj->AddComponent<MeshRenderer>(&Gun_Mesh);

		SphereCollider::Desc Gun_col;
		Gun_col.collisionLayer = COLLISION_LAYER_BULLET_ENEMY;
		Gun_obj->AddComponent<SphereCollider>(&Gun_col);

}

void Bullet_Manager::Fire_Missile(Vector3 _start, Quaternion _rot, 
	int _minDmg , int _maxDmg,
	float _maxSpd )
{
	GameObject* Missile_obj = INSTANTIATE(OBJECT_TAG_BULLET_ENEMY, L"Missile");
	Missile_obj->SetPosition(_start);
	Missile_obj->GetTransform()->rotation = _rot;
	Missile_obj->SetScale(0.5f, 0.5f, 2.5f);

	Missile::Desc Missile_Desc;
	Missile_Desc.iMinDmg = _minDmg;
	Missile_Desc.iMaxDmg = _maxDmg;
	Missile_Desc.fMaxSpd = _maxSpd;
	Missile_obj->AddComponent<Missile>(&Missile_Desc);

	MeshRenderer::Desc Missile_Mesh;	
	Missile_Mesh.mtrlName = L"default";
	Missile_Mesh.meshName = L"box";
	Missile_obj->AddComponent<MeshRenderer>(&Missile_Mesh);

	SphereCollider::Desc Missile_col;
	Missile_col.collisionLayer = COLLISION_LAYER_BULLET_ENEMY;
	Missile_obj->AddComponent<SphereCollider>(&Missile_col);

}

void Bullet_Manager::Fire_Homing()
{
}

void Bullet_Manager::Gun_Evasion(Vector2 _start)
{//_start.x => x //_start.y => z

	//Vector3 vStart = { _start.x, 0.f,_start.y };

	//GameObject* Bullet_obj = INSTANTIATE(OBJECT_TAG_BULLET_ENEMY, L"Bullet");
	//Bullet_obj->SetPosition(vStart);
	//Bullet_obj->SetScale(0.5f, 0.5f, 0.5f);

	//Bullet::Desc Bullet_Desc;
	//Bullet_Desc.fSpd = 50.f;
	//Bullet_Desc.iDmg = 10;
	//Bullet_obj->AddComponent<Bullet>(&Bullet_Desc);

	//MeshRenderer::Desc Bullet_Mesh;
	//Bullet_Mesh.mtrlName = L"default";
	//Bullet_Mesh.meshName = L"box";
	//Bullet_obj->AddComponent<MeshRenderer>(&Bullet_Mesh);
}

void Bullet_Manager::Missile_Evasion(Vector2 _start)
{
	//Vector3 vStart = { _start.x, 0.f,_start.y };

	//GameObject* Missile_obj = INSTANTIATE(OBJECT_TAG_BULLET_ENEMY, L"Missile");
	//Missile_obj->SetPosition(vStart);
	//Missile_obj->SetScale(0.5f, 0.5f, 2.5f);

	//Missile::Desc Missile_Desc;
	//Missile_obj->AddComponent<Missile>(&Missile_Desc);

	//MeshRenderer::Desc Missile_Mesh;
	//Missile_Mesh.mtrlName = L"default";
	//Missile_Mesh.meshName = L"box";
	//Missile_obj->AddComponent<MeshRenderer>(&Missile_Mesh);
}

void Bullet_Manager::Homing_Evasion(Vector2 _start, Vector2 _target)
{
}
