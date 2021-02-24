#include "stdafx.h"
#include "..\Include\TopViewCamera.h"


TopViewCamera::TopViewCamera(Desc * _desc)
{
}

TopViewCamera::~TopViewCamera()
{
}

void TopViewCamera::Initialize()
{
	m_MainCamera = Core::GetInstance()->FindFirstObject(OBJECT_TAG_CAMERA);

	if (m_MainCamera == nullptr)
	{
		assert(L"아 ㅋㅋ 메인 카메라 못찾겠다고 ㅋㅋ");
	}
	m_MainCamera->SetPosition(0.f, 0.f, 0.f);
	m_MainCamera->SetRotation(0.f, 0.f, 0.f);
	m_MainCamera->SetParents(m_gameObject);
	
	m_transform->RotateX(90.f);
	m_transform->SetPosition(Vector3(0.f, 100.f, 0.f));
}

void TopViewCamera::Update()
{


}
