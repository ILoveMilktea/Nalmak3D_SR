#include "..\Include\MeshRenderer.h"
#include "ResourceManager.h"
#include "Transform.h"
#include "Animator.h"


MeshRenderer::MeshRenderer(Desc * _desc)
{
	m_viBuffer = ResourceManager::GetInstance()->GetResource<VIBuffer>(_desc->meshName);
	if (!_desc->mtrl)
		m_material = ResourceManager::GetInstance()->GetResource<Material>(_desc->mtrlName);
	else
		m_material = _desc->mtrl;

	m_animator = nullptr;
	m_layer = _desc->layer;
}

void MeshRenderer::Initialize()
{
	m_animator = GetComponent<Animator>();
}

void MeshRenderer::Update()
{
}

void MeshRenderer::LateUpdate()
{
}

void MeshRenderer::Release()
{
}

void MeshRenderer::Render()
{

	Shader* currentShader = m_material->GetShader();
	assert("Current Shader is nullptr! " && currentShader);

	currentShader->SetMatrix("g_world", GetTransform()->GetWorldMatrix());

	if (m_animator)
		GetMaterial()->SetTexture(0, m_animator->GetDiffuseSprite());



	currentShader->CommitChanges();				   // BeginPass 호출시 반드시 그리기 전에 호출
												   ////////////////////////////////////////////////////////////////////////////////////
												   // DrawPrimitive (index 사용 x)
												   // Type, 이번에 이용될 인데스, 최소 참조갯수, 호출될 버텍스 수, 인덱스 버퍼내에서 읽기 시작할 인덱스, 그리는 도형 수
	ThrowIfFailed(m_device->DrawIndexedPrimitive(currentShader->GetPrimitiveType(), 0, 0, m_viBuffer->GetVertexCount(), 0, m_viBuffer->GetFigureCount()));


}

void MeshRenderer::BindingStreamSource()
{
									 // 통로 소켓 넘버 //  주소               // 시작점  // 사이즈
	ThrowIfFailed(m_device->SetStreamSource(0, m_viBuffer->GetVertexBuffer(), 0, m_material->GetShader()->GetInputLayoutSize()));
	ThrowIfFailed(m_device->SetIndices(m_viBuffer->GetIndexBuffer()));

	// 고정함수 파이프라인에 필요!
	// m_device->SetFVF()
	
}
