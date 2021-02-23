#include "stdafx.h"
#include "..\Include\PlayerToTopView.h"

#include "SmoothFollow.h"
#include "SingleImage.h"

#include "PlayerInfoManager.h"

PlayerToTopView::PlayerToTopView(Desc * _desc)
{
}

PlayerToTopView::~PlayerToTopView()
{
}

void PlayerToTopView::Initialize()
{
	m_Player = Core::GetInstance()->FindFirstObject(OBJECT_TAG_PLAYER);
	
	if (m_Player == nullptr)
	{
		assert(L"플레이어 못받은거 같은데여 ㅋㅋ;;");
	}

	
}

void PlayerToTopView::Update()
{
	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_F2))
	{
		DESTROY(Core::GetInstance()->FindObjectByName(0, L"SmoothFollow"));
		//지우면 안됨.
		
		//if (m_Player->GetComponent<SmoothFollow>() != nullptr)
		//{
		//	m_Player->DeleteComponent<SmoothFollow>();
		//}

		if (Core::GetInstance()->FindObjectByName(OBJECT_TAG_CAMERA, L"mainCamera") == nullptr)
		{
			assert(L"삭제됨.");
		}
		else {
			assert(L"삭제 되지 않음.");
		}
		//현재 smoothFollow에서의 회전, 위치 고정 해놓고 삭제.
		
		Create_Fade();

		m_bProduce = true;
	}

	if (m_bProduce)
	{	
		Accelerate();
		Player_Far();
		//Fade_Out();
		/*
			if(플레이어 위치 1000넘어가기 or Fade Out 끝)
			{
				MainCamera위치 Y축에 평행되게 세팅.
				FadeIn();
			}
		*/
	}

}

void PlayerToTopView::Player_Far()
{
	Vector3 forward = m_Player->GetTransform()->GetForward();

	m_Player->GetTransform()->position += forward * m_fSpd;
}

void PlayerToTopView::Create_Fade()
{
	m_Fade = INSTANTIATE();

	SingleImage::Desc Fade_Desc;
	Fade_Desc.textureName = L"UIWhite";

	m_Fade->AddComponent<SingleImage>(&Fade_Desc);
	
	//m_Fade->GetTransform()->scale.x = 500.f;
}

void PlayerToTopView::Accelerate()
{
	m_fSpd = Nalmak_Math::Lerp(m_fSpd, 5.f, dTime);
}

bool PlayerToTopView::Fade_In()
{
	return false;
}

bool PlayerToTopView::Fade_Out()
{
	return false;
}
