#include "stdafx.h"
#include "../Include/EnemyManager.h"

#include "DogFightState.h"
#include "ShootingState.h"
#include "BossState.h"

#include "Enemy.h"

EnemyManager* EnemyManager::m_Instance = nullptr;


EnemyManager::EnemyManager(Desc * _Desc)
{
	//m_gameObject->AddComponent<StateControl>(); 
	////component의 m_gameObject => 해당 컴포넌트를 가지고 있는 게임옵h
	//GetComponent<StateControl>()->AddState<DogFightState>(L"dogFight");
	//GetComponent<StateControl>()->AddState<ShootingState>(L"shoot");
	//GetComponent<StateControl>()->AddState<BossState>(L"boss");

	//GetComponent<StateControl>()->InitState(L"dogFight");
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
	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_F1))
	{
		//int x, y, z;
		//x = rand() % 300 - 150;
		//y = rand() % 300 - 150;
		//z = rand() % 300 - 150;
		//Enemy_Spawn(Vector3((float)x, (float)y, (float)z));
		Enemy_Spawn(Vector3(150.f, 150.f, 150.f));
	}
}

//const int & EnemyManager::Get_EnemyCount() const
//{
//	// TODO: 여기에 반환 구문을 삽입합니다.
//	return 0;
//}

void EnemyManager::Enemy_Spawn(Vector3 _pos)
{
	GameObject* Enemy_obj = INSTANTIATE(0, L"Enemy");
	Enemy_obj->SetPosition(_pos);
	Enemy_obj->SetScale(0.1f,0.1f,0.1f);

	//Enemy_obj->AddComponent<StateControl>();
	

	Enemy::Desc Enemy_desc;
	/*desc 세팅*/
	Enemy_obj->AddComponent<Enemy>(&Enemy_desc);
	
	
	MeshRenderer::Desc Enemy_Mesh;
	Enemy_Mesh.mtrlName = L"default";
	Enemy_Mesh.meshName = L"flight";
	Enemy_obj->AddComponent<MeshRenderer>(&Enemy_Mesh);
}

void EnemyManager::Spawn_Rush()
{
	GameObject* Enemy_obj = INSTANTIATE(0, L"Enemy");
	//Enemy_obj->SetPosition(_pos);
	Enemy_obj->SetScale(0.1f, 0.1f, 0.1f);

	Enemy_obj->AddComponent<StateControl>();


	Enemy::Desc Enemy_desc;
	/*desc 세팅*/
	Enemy_obj->AddComponent<Enemy>(&Enemy_desc);


	MeshRenderer::Desc Enemy_Mesh;
	Enemy_Mesh.mtrlName = L"default";
	Enemy_Mesh.meshName = L"flight";
	Enemy_obj->AddComponent<MeshRenderer>(&Enemy_Mesh);
}

void EnemyManager::Spawn_Chase()
{
	GameObject* Enemy_obj = INSTANTIATE(0, L"Enemy");
	Enemy_obj->SetPosition(0,0,0);
	Enemy_obj->SetScale(0.1f, 0.1f, 0.1f);

	Enemy_obj->AddComponent<StateControl>();


	Enemy::Desc Enemy_desc;
	/*desc 세팅*/
	Enemy_obj->AddComponent<Enemy>(&Enemy_desc);


	MeshRenderer::Desc Enemy_Mesh;
	Enemy_Mesh.mtrlName = L"default";
	Enemy_Mesh.meshName = L"flight";
	Enemy_obj->AddComponent<MeshRenderer>(&Enemy_Mesh);
}

