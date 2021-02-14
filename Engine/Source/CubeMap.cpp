#include "..\Include\CubeMap.h"
#include "RenderManager.h"
#include "Transform.h"

CubeMap::CubeMap(Desc * _desc)
{
}

CubeMap::~CubeMap()
{
}

void CubeMap::Initialize()
{
	m_mainCam = RenderManager::GetInstance()->GetMainCamera()->GetTransform();
}

void CubeMap::Update()
{
	m_transform->position = m_mainCam->position;
}
