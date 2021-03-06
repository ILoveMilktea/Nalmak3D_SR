#include "VIBufferRenderer.h"
#include "ResourceManager.h"
#include "Transform.h"


VIBufferRenderer::VIBufferRenderer(struct Desc* _desc)
{
	m_viBuffer = ResourceManager::GetInstance()->GetResource<VIBuffer>(_desc->meshName);
	if (!_desc->mtrl)
	{
		m_material = ResourceManager::GetInstance()->GetResource<Material>(_desc->mtrlName);
	}
	else
	{
		m_material = _desc->mtrl;

	}

	m_layer = _desc->layer;

	m_type = RENDERER_TYPE_VIBUFFER;
}


VIBufferRenderer::~VIBufferRenderer()
{
}

void VIBufferRenderer::Initialize()
{
}

void VIBufferRenderer::Update()
{
}

void VIBufferRenderer::LateUpdate()
{
}

void VIBufferRenderer::Release()
{
}

void VIBufferRenderer::Render(Shader * _shader)
{

	Shader* currentShader = m_material->GetShader();
	assert("Current Shader is nullptr! " && currentShader);

	currentShader->SetMatrix("g_world", m_transform->GetWorldMatrix());



	currentShader->CommitChanges();				   // BeginPass 호출시 반드시 그리기 전에 호출
												   ////////////////////////////////////////////////////////////////////////////////////
												   // DrawPrimitive (index 사용 x)
												   // Type, 이번에 이용될 인데스, 최소 참조갯수, 호출될 버텍스 수, 인덱스 버퍼내에서 읽기 시작할 인덱스, 그리는 도형 수
	ThrowIfFailed(m_device->DrawIndexedPrimitive(currentShader->GetPrimitiveType(), 0, 0, m_viBuffer->GetVertexCount(), 0, m_viBuffer->GetFigureCount()));

}

int VIBufferRenderer::GetMaterialCount()
{
	return 1;
}

Material * VIBufferRenderer::GetMaterial(int _index)
{
	return m_material;
}

void VIBufferRenderer::SetMaterial(Material * _material, int _index)
{
	m_material = _material;
}

void VIBufferRenderer::SetMaterial(const wstring & _mtrlName, int _index)
{
	m_material = ResourceManager::GetInstance()->GetResource<Material>(_mtrlName);
}

void VIBufferRenderer::SetVIBuffer(const wstring & _meshName)
{
	m_viBuffer = ResourceManager::GetInstance()->GetResource<VIBuffer>(_meshName);
}

void VIBufferRenderer::BindingStreamSource()
{
	ThrowIfFailed(m_device->SetStreamSource(0, m_viBuffer->GetVertexBuffer(), 0, m_material->GetShader()->GetInputLayoutSize()));
	ThrowIfFailed(m_device->SetIndices(m_viBuffer->GetIndexBuffer()));
}

float VIBufferRenderer::GetBoundingRadius()
{
	return m_viBuffer->GetBoundingSphereRadius();
}
Vector3 VIBufferRenderer::GetBoundingCenter()
{
	return m_viBuffer->GetBoundingSphereCenter();
}
