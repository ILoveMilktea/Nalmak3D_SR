#include "stdafx.h"
#include "..\Include\EnemyManager.h"

#include "DogFightState.h"
#include "ShootingState.h"
#include "BossState.h"

#include "Enemy.h"

EnemyManager* EnemyManager::m_Instance = nullptr;


EnemyManager::EnemyManager(Desc * _Desc)
{//����Ƽ�� �����ũ

	/* ���� ���� ��Ȳ 3������ ������Ʈ�� ���� �� �����̴� �̰ž�. */
	m_gameObject->AddComponent<StateControl>(); 
	//component�� m_gameObject => �ش� ������Ʈ�� ������ �ִ� ���ӿɢh
	GetComponent<StateControl>()->AddState<DogFightState>(L"dogFight");
	GetComponent<StateControl>()->AddState<ShootingState>(L"shoot");
	GetComponent<StateControl>()->AddState<BossState>(L"boss");
	
	GetComponent<StateControl>()->InitState(L"dogFight");

}

EnemyManager::~EnemyManager()
{
}

EnemyManager * EnemyManager::GetInstance()
{
	if (!m_Instance)
	{//������Ʈ�� ���� ���ؼ� �߸� Component�� ��ӹ��� ������Ʈ ��ü��ٰ� ����.
		
		auto Instance = INSTANTIATE();
		Instance->AddComponent<EnemyManager>();
		m_Instance = Instance->GetComponent<EnemyManager>();
		
		Instance->SetDontDestroy(true);//�� �Ѿ�� ���������� �̰ž�.
	}

	return m_Instance;
}

void EnemyManager::DeleteInstance()
{
	if (m_Instance)
	{
		DESTROY(m_Instance->GetGameObject());
	}

}

void EnemyManager::Initialize()
{//����Ƽ�� ������
}

void EnemyManager::Update()
{
}

int EnemyManager::Get_EnemyCount() const
{
	return 0;// TODO: ���⿡ ��ȯ ������ �����մϴ�.
}

void EnemyManager::Enemy_Spawn(Vector3 _pos)
{
	GameObject* Enemy_obj = INSTANTIATE(0, L"Enemy");
	Enemy_obj->SetPosition(_pos);

	Enemy::Desc Enemy_desc;
	/*desc ����*/
	Enemy_obj->AddComponent<Enemy>(&Enemy_desc);
	
	MeshRenderer::Desc Enemy_Mesh;
	Enemy_Mesh.meshName = L"box";
	Enemy_Mesh.mtrlName = L"default";
	Enemy_obj->AddComponent<MeshRenderer>(&Enemy_Mesh);

	//list_Enemies.emplace_back(Enemy_obj);

	

}

