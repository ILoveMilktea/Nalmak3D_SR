#include "stdafx.h"
#include "..\Include\EnemyManager.h"

#include "DogFightState.h"
#include "ShootingState.h"
#include "BossState.h"

#include "Enemy.h"

EnemyManager* EnemyManager::m_Instance = nullptr;


EnemyManager::EnemyManager(Desc * _Desc)
{//유니티의 어웨이크

	/* 현재 전투 상황 3가지를 스테이트로 관리 할 에정이다 이거야. */
	m_gameObject->AddComponent<StateControl>(); 
	//component의 m_gameObject => 해당 컴포넌트를 가지고 있는 게임옵줵
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
	{//업데이트를 쓰기 위해서 야를 Component를 상속받은 컴포넌트 객체루다가 만듦.
		
		auto Instance = INSTANTIATE();
		Instance->AddComponent<EnemyManager>();
		m_Instance = Instance->GetComponent<EnemyManager>();
		
		Instance->SetDontDestroy(true);//씬 넘어가도 지우지마라 이거야.
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
{//유니티의 스따뜨
}

void EnemyManager::Update()
{
}

int EnemyManager::Get_EnemyCount() const
{
	return 0;// TODO: 여기에 반환 구문을 삽입합니다.
}

void EnemyManager::Enemy_Spawn(Vector3 _pos)
{
	GameObject* Enemy_obj = INSTANTIATE(0, L"Enemy");
	Enemy_obj->SetPosition(_pos);

	Enemy::Desc Enemy_desc;
	/*desc 세팅*/
	Enemy_obj->AddComponent<Enemy>(&Enemy_desc);
	
	MeshRenderer::Desc Enemy_Mesh;
	Enemy_Mesh.meshName = L"box";
	Enemy_Mesh.mtrlName = L"default";
	Enemy_obj->AddComponent<MeshRenderer>(&Enemy_Mesh);

	//list_Enemies.emplace_back(Enemy_obj);

	

}

