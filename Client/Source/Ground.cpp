#include "stdafx.h"
#include "..\Include\Ground.h"



Ground::Ground(Desc * _desc)
{
}

Ground::~Ground()
{
}

void Ground::Initialize()
{

	m_groundMtrl = ResourceManager::GetInstance()->GetResource<Material>(L"mtrl_ground");

	AddComponent<MeshRenderer>();
}

void Ground::Update()
{
}
