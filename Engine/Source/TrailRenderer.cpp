#include "TrailRenderer.h"
#include "Transform.h"

TrailRenderer::TrailRenderer(Desc * _desc)
{
	m_viBuffer = ResourceManager::GetInstance()->GetResource<VIBuffer>(L"quadNoneNormal");
	if (!_desc->mtrl)
	{
		m_material = ResourceManager::GetInstance()->GetResource<Material>(_desc->mtrlName);
	}
	else
	{
		m_material = _desc->mtrl;

	}

	m_layer = _desc->layer;

	m_type = RENDERER_TYPE_MESH;
}

TrailRenderer::~TrailRenderer()
{
}

void TrailRenderer::Initialize()
{
}

void TrailRenderer::Update()
{
}

void TrailRenderer::LateUpdate()
{
}

void TrailRenderer::Release()
{
}

void TrailRenderer::Render(Shader * _shader, int _index)
{
	if (m_currentCount == 0)
		return;

	assert("Current Shader is nullptr! " && _shader);

	_shader->CommitChanges();
	ThrowIfFailed(m_device->DrawIndexedPrimitive(_shader->GetPrimitiveType(), 0, 0, 4 * m_currentCount, 0, m_viBuffer->GetFigureCount()));
}

void TrailRenderer::BindingStreamSource()
{
	ThrowIfFailed(m_device->SetStreamSource(0, m_viBuffer->GetVertexBuffer(), 0, m_material->GetShader()->GetInputLayoutSize()));
	ThrowIfFailed(m_device->SetIndices(m_viBuffer->GetIndexBuffer()));
}

int TrailRenderer::GetMaterialCount()
{
	return 1;
}

Material * TrailRenderer::GetMaterial(int _index)
{
	return m_material;
}

void TrailRenderer::SetMaterial(Material * _material, int _index)
{
	m_material = _material;
}

void TrailRenderer::SetMaterial(const wstring & _mtrlName, int _index)
{
	m_material = ResourceManager::GetInstance()->GetResource<Material>(_mtrlName);

}
