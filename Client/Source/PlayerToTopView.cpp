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
		assert(L"�÷��̾� �������� �������� ����;;");
	}

	m_MainCamera = Core::GetInstance()->FindFirstObject(OBJECT_TAG_CAMERA);

	if (m_MainCamera == nullptr)
	{
		assert(L"�� ���� ����ī�޶� �������� Ȯ���� ����� ����;");
	}

	
}

void PlayerToTopView::Update()
{

	////DEBUG_LOG(L"SmoothFollow Pos", Core::GetInstance()->FindObjectByName(0, L"SmoothFollow")->GetTransform()->position);
	////DEBUG_LOG(L"SmoothFollow Rot", Core::GetInstance()->FindObjectByName(0, L"SmoothFollow")->GetTransform()->rotation);
	//DEBUG_LOG(L"MainCam Pos", m_MainCamera->GetTransform()->position);
	////DEBUG_LOG(L"MainCam Rot", m_MainCamera->GetTransform()->rotation);

	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_F2))
	{
		//���⼭ �ٷ� followSmooth �������� ���� FadeOut�Ǹ� �غ���.

		 PosTemp = Core::GetInstance()->FindObjectByName(0, L"SmoothFollow")->GetTransform()->position;
		 RotTemp = Core::GetInstance()->FindObjectByName(0, L"SmoothFollow")->GetTransform()->rotation;

		 //PosTemp_camera = m_MainCamera->GetTransform()->position;
		 //RotTemp_camera = m_MainCamera->GetTransform()->rotation;

		 DESTROY(Core::GetInstance()->FindObjectByName(0, L"SmoothFollow"));

		//Core::GetInstance()->FindObjectByName(0, L"SmoothFollow")->GetTransform()->SetActive(false);
		
		m_MainCamera->GetTransform()->position = PosTemp;
		m_MainCamera->GetTransform()->rotation = RotTemp;

		//PosTemp_camera = m_MainCamera->GetTransform()->position;
		//RotTemp_camera = m_MainCamera->GetTransform()->rotation;


		//Vector3 PosTemp = Core::GetInstance()->FindObjectByName(0, L"SmoothFollow")->GetTransform()->position;
		//Quaternion RotTemp = Core::GetInstance()->FindObjectByName(0, L"SmoothFollow")->GetTransform()->rotation;

		//PosTemp += m_MainCamera->GetTransform()->position;
		//RotTemp -= m_MainCamera->GetTransform()->rotation;
		////������ ����

		//m_MainCamera->GetTransform()->position = PosTemp;
		//m_MainCamera->GetTransform()->rotation = RotTemp;


		//DESTROY(Core::GetInstance()->FindObjectByName(0, L"SmoothFollow"));
		
		//if (m_Player->GetComponent<SmoothFollow>() != nullptr)
		//{
		//	m_Player->DeleteComponent<SmoothFollow>();
		//}

		//if (Core::GetInstance()->FindObjectByName(OBJECT_TAG_CAMERA, L"mainCamera") == nullptr)
		//{
		//	assert(L"������.");
		//}
		//else {
		//	assert(L"���� ���� ����.");
		//}
		//���� smoothFollow������ ȸ��, ��ġ ���� �س��� ���� -�� �ȸ�����,,,
		
		Create_Fade();

		m_bProduce = true;
	}

	if (m_bProduce)
	{	
		Accelerate();
		Player_Far();

		//Fade_Out();
		/*
			if(�÷��̾� ��ġ 1000�Ѿ�� or Fade Out ��)
			{
				MainCamera��ġ Y�࿡ ����ǰ� ����.
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

	m_Fade->AddComponent<CanvasRenderer>();
	SingleImage::Desc Fade_Desc;
	Fade_Desc.textureName = L"UIBlack";

	m_Fade->AddComponent<SingleImage>(&Fade_Desc);
	
	//auto image = UIFactory::CreateFade();
	m_Fade->GetTransform()->scale.x = 500.f;
}

void PlayerToTopView::Accelerate()
{
	m_fSpd = Nalmak_Math::Lerp(m_fSpd, 50.f, dTime);
}

bool PlayerToTopView::Fade_In()
{
	return false;
}

bool PlayerToTopView::Fade_Out()
{
	return false;
}
