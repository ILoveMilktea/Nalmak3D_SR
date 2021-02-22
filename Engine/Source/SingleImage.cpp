#include "..\Include\SingleImage.h"
#include "ResourceManager.h"
#include "CanvasRenderer.h"

SingleImage::SingleImage(Desc * _desc)
{
	SetTexture(_desc->textureName);
}

void SingleImage::Initialize()
{
	if (!GetComponent<CanvasRenderer>())
		m_gameObject->AddComponent<CanvasRenderer>();
	m_renderer = GetComponent<CanvasRenderer>();
	m_renderer->SetImage(m_image);
}

void SingleImage::Update()
{
}

void SingleImage::SetTexture(wstring _name)
{
	m_image = ResourceManager::GetInstance()->GetResource<Texture>(_name);
}

IDirect3DBaseTexture9* SingleImage::GetTexture()
{ 
	return m_image->GetTexure(0);
}

RECT * SingleImage::GetBoundary()
{
	return m_renderer->GetBoundary();
}
