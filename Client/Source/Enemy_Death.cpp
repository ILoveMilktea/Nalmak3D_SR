#include "stdafx.h"
#include "..\Include\Enemy_Death.h"

#include "EnemyManager.h"

Enemy_Death::Enemy_Death()
{
}


Enemy_Death::~Enemy_Death()
{
}

void Enemy_Death::Initialize()
{
	//this state only destory Instance.

}

void Enemy_Death::EnterState()
{
	//m_pEnemy = m_gameObject->GetComponent<Enemy>();

	//assert(L"아 ㅋㅋ 에너미 못 찾은거 같다고 ㅋㅋ" && m_pEnemy);

	//m_pEnemy->Target_Setting(false);
	
	EnemyManager::GetInstance()->Add_EnemyCount(-1);



	//파티클 삭제//
	//삭제하면 나왔던거 다 사라짐.
	//죽으면 파티클 재생만 정지했다가
	//다 사라지면 없어지게.
	//-> 그래서 준비했다. ParticleDead_IfCount0
	//-> 파티클을 들고있는 Enemy랑 상관없이
	// 파티클 GameObject 객체에 달아놓고
	// Enemy가 죽을때 재생 정지만 시켜주면, 알아서 파티클 개수 세다가 0되면 터침.


	DESTROY(m_gameObject); //컽!
	


}

void Enemy_Death::UpdateState()
{
	DEBUG_LOG(L"Enemy State", L"Death");
}

void Enemy_Death::ExitState()
{
}




