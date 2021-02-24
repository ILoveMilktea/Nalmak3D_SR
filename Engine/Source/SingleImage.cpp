#include "..\Include\SingleImage.h"
#include "ResourceManager.h"
#include "CanvasRenderer.h"

SingleImage::SingleImage(Desc * _desc)
{
	m_image =
		ResourceManager::GetInstance()->
		GetResource<Texture>(_desc->textureName)->GetTexure(0);
}

void SingleImage::Initialize()
{
	m_renderer = GetComponent<CanvasRenderer>();
	m_renderer->SetImage(m_image);

}

void SingleImage::Update()
{

}

void SingleImage::SetTexture(wstring _name)
{
	m_image = ResourceManager::GetInstance()->GetResource<Texture>(_name)->GetTexure(0);
	if(m_renderer)
		m_renderer->SetImage(m_image);
}

void SingleImage::SetTexture(IDirect3DBaseTexture9 * _tex)
{
	m_image = _tex;
	if (m_renderer)
		m_renderer->SetImage(m_image);
}


IDirect3DBaseTexture9* SingleImage::GetTexture()
{
	return m_image;
}
