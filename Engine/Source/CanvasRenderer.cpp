#include "..\Include\CanvasRenderer.h"

#include "ResourceManager.h"
#include "Transform.h"
#include "Animator.h"
#include "SingleImage.h"
#include "Texture.h"
CanvasRenderer::CanvasRenderer(Desc * _desc)
{
	m_viBuffer = ResourceManager::GetInstance()->GetResource<VIBuffer>(L"quadNoneNormal");
	m_material = ResourceManager::GetInstance()->GetResource<Material>(L"defaultUI");

	m_type = RENDERER_TYPE_CANVAS;
	m_color = { 1.f,1.f,1.f,1.f };
}

void CanvasRenderer::Initialize()
{
	m_animator = GetComponent<Animator>();

	if(m_transform->scale == Vector3(1.f, 1.f, 1.f))
		m_transform->scale = Vector3(100.f, 100.f, 0.f);
	
	UpdateBoundary();
}

void CanvasRenderer::Update()
{
	if (m_observedPosition != m_transform->position)
	{
		UpdateBoundary();
		m_observedPosition = m_transform->position;
	}
	if (m_observedScale != m_transform->scale)
	{
		UpdateBoundary();
		m_observedScale = m_transform->scale;
	}
}

void CanvasRenderer::LateUpdate()
{
}

void CanvasRenderer::Release()
{
}

void CanvasRenderer::Render()
{

	Shader*	currentShader = m_material->GetShader();

	assert("Current Shader is nullptr! " && currentShader);

	if (m_animator)
		GetMaterial()->SetTexture(0, m_animator->GetDiffuseSprite());
	else if (m_targetImage)
		currentShader->SetTexture("g_mainTex", m_targetImage);
	else
		return;

	currentShader->SetVector("g_mainTexColor", m_color);

	currentShader->SetMatrix("g_world", GetTransform()->GetUIWorldMatrix());
	
	currentShader->CommitChanges();				   // BeginPass 호출시 반드시 그리기 전에 호출
												   ////////////////////////////////////////////////////////////////////////////////////
												   // DrawPrimitive (index 사용 x)
												   // Type, 이번에 이용될 인데스, 최소 참조갯수, 호출될 버텍스 수, 인덱스 버퍼내에서 읽기 시작할 인덱스, 그리는 도형 수
	ThrowIfFailed(m_device->DrawIndexedPrimitive(currentShader->GetPrimitiveType(), 0, 0, m_viBuffer->GetVertexCount(), 0, m_viBuffer->GetFigureCount()));

}

void CanvasRenderer::BindingStreamSource()
{
	// 통로 소켓 넘버 //  주소               // 시작점  // 사이즈
	ThrowIfFailed(m_device->SetStreamSource(0, m_viBuffer->GetVertexBuffer(), 0, m_material->GetShader()->GetInputLayoutSize()));
	ThrowIfFailed(m_device->SetIndices(m_viBuffer->GetIndexBuffer()));

	// 고정함수 파이프라인에 필요!
	// m_device->SetFVF()
}

void CanvasRenderer::UpdateBoundary()
{
	m_boundary.left = LONG(m_transform->position.x - m_transform->scale.x * 0.5f);
	m_boundary.top = LONG(m_transform->position.y - m_transform->scale.y * 0.5f);
	m_boundary.right = LONG(m_transform->position.x + m_transform->scale.x * 0.5f);
	m_boundary.bottom = LONG(m_transform->position.y + m_transform->scale.y * 0.5f);
}

RECT * CanvasRenderer::GetBoundary()
{
	return &m_boundary;
}
