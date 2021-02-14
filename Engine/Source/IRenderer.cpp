#include "..\Include\IRenderer.h"
#include "DeviceManager.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "Transform.h"

USING(Nalmak)

IRenderer::IRenderer()
{
	m_device = DeviceManager::GetInstance()->GetDevice();
}


void IRenderer::PreRender()
{
	RenderRequest();
}

void IRenderer::RenderRequest()
{
	RenderManager::GetInstance()->RenderRequest(this);
}

PDIRECT3DVERTEXBUFFER9 IRenderer::GetVertexBuffer() const
{
	return m_viBuffer->GetVertexBuffer();
}

PDIRECT3DINDEXBUFFER9 IRenderer::GetIndexBuffer() const
{
	return m_viBuffer->GetIndexBuffer();
}

Material * IRenderer::GetMaterial() const
{
	return m_material;
}

VIBuffer * IRenderer::GetVIBuffer() const
{
	return m_viBuffer;
}

UINT IRenderer::GetVertexCount()
{
	return m_viBuffer->GetVertexCount();
}

UINT IRenderer::GetFigureCount()
{
	return m_viBuffer->GetFigureCount();
}

void IRenderer::SetMaterial(Material * _material)
{
	m_material = _material;

	assert("material is nullptr" && m_material);
}

void IRenderer::SetMaterial(wstring _mtrlName)
{
	auto newMaterial = ResourceManager::GetInstance()->GetResource<Material>(_mtrlName);

	m_material = newMaterial;

	assert("material is nullptr" && m_material);
}

void IRenderer::SetMesh(wstring _meshName)
{
	m_viBuffer = ResourceManager::GetInstance()->GetResource<VIBuffer>(_meshName);
}
