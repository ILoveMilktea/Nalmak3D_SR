#include "stdafx.h"
#include "..\Include\Indicator_EnemyPos.h"
#include "PlayerInfoManager.h"

Indicator_EnemyPos::Indicator_EnemyPos(Desc * _desc)
{
	m_pTarget = _desc->Target;
}

Indicator_EnemyPos::~Indicator_EnemyPos()
{
}

void Indicator_EnemyPos::Initialize()
{
	assert(L"Can't find Target" && m_pTarget);

	m_pPlayer = PlayerInfoManager::GetInstance()->GetPlayer();
	assert(L"Cant' find Player" && m_pPlayer);

	m_pAlpha = GetComponent<MeshRenderer>()->GetMaterial();
	
	m_pMainCamera = Core::GetInstance()->GetMainCamera();

}

void Indicator_EnemyPos::Update()
{
//1. 3D Obejct로 띄울 경우 : 



	
	//if (targetPos.x > playerPos.x)
	//{//righter than player
	//	
	//}
	//else if (targetPos.x < playerPos.x)
	//{//leftter than player

	//}
	//
	///* Enemy Pos.y Calc */
	//if (targetPos.y > playerPos.y)
	//{//upper than player

	//}
	//else if (targetPos.y < playerPos.y)
	//{//lower than player 

	//}



}

void Indicator_EnemyPos::LateUpdate()
{
	Vector3 playerPos = m_pPlayer->GetTransform()->position;
	Vector3 targetPos = m_pTarget->GetTransform()->position;
	
	m_transform->position = playerPos;
	
	float GapX = targetPos.x - playerPos.x;
	float GapY = targetPos.y - playerPos.y;

	m_transform->position.x += GapX / 25.f;
	m_transform->position.y += GapY / 25.f;

	Vector3 Cam = m_pMainCamera->GetTransform()->position;
	float Z = m_transform->position.z - Cam.z;

	Vector2 vScreen = m_pMainCamera->WorldToScreenPos(m_transform->position);
	DEBUG_LOG(L"Cursor Screen Pos", vScreen);

	Vector2 vClampScreen;
	vClampScreen.x = Nalmak_Math::Clamp(vScreen.x, WINCX / 2.f * -1.f +160.f, WINCX / 2.f - 160.f);
	vClampScreen.y = Nalmak_Math::Clamp(vScreen.y, WINCY / 2.f * -1.f +140.f, WINCY / 2.f - 140.f);
	DEBUG_LOG(L"Cursor Screen Clamp Pos", vClampScreen);

	Vector3 vWolrd = m_pMainCamera->ScreenPosToWorld(vClampScreen, m_transform->position.z);
	DEBUG_LOG(L"Screen To World", vWolrd);

	////limit => first=min \ second=max
	////pair<float, float> Limit_Left;
	////Limit_Left.first = WINCX / 2.f * -1.f;
	////Limit_Left.second = TARGET_RANGE / 2.f * -1.f;
	//
	//pair<float, float> Limit_Right;
	//Limit_Right.first = WINCX / 2.f;
	//Limit_Right.second = TARGET_RANGE / 2.f;

	//pair <float, float> Limit_Up;
	//Limit_Up.first = WINCY / 2.f;
	//Limit_Up.second = TARGET_RANGE / 2.f;
	//
	///* for x Limit */
	//vScreen.x = Nalmak_Math::Clamp(vScreen.x, Limit_Right.first, Limit_Right.second);
	//vScreen.x = Nalmak_Math::Clamp(vScreen.x, Limit_Right.first * -1.f, Limit_Right.second * -1.f);
	///* for y Limit */
	//vScreen.y = Nalmak_Math::Clamp(vScreen.y, Limit_Up.first, Limit_Up.second);
	//vScreen.y = Nalmak_Math::Clamp(vScreen.y, Limit_Up.first * -1.f, Limit_Up.second * -1.f);



	//m_transform->position = vWolrd;

	m_transform->LookAt(m_pTarget, 1.f);
	//m_pAlpha->SetVector() 이걸로 투명도 조절가능. 사르륵 없어지게 해보자.

	DEBUG_LOG(L"Arrow Pos", m_transform->position);



	/* 정 안되면 그냥 락온 범위에다가 위, 아래만 판단해서 위치 정해주고 LookAt만 해주자*/
}

void Indicator_EnemyPos::Release_Target()
{
	m_pTarget = nullptr;
}
