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
	
	currentShader->CommitChanges();				   // BeginPass ȣ��� �ݵ�� �׸��� ���� ȣ��
												   ////////////////////////////////////////////////////////////////////////////////////
												   // DrawPrimitive (index ��� x)
												   // Type, �̹��� �̿�� �ε���, �ּ� ��������, ȣ��� ���ؽ� ��, �ε��� ���۳����� �б� ������ �ε���, �׸��� ���� ��
	ThrowIfFailed(m_device->DrawIndexedPrimitive(currentShader->GetPrimitiveType(), 0, 0, m_viBuffer->GetVertexCount(), 0, m_viBuffer->GetFigureCount()));

}

void CanvasRenderer::BindingStreamSource()
{
	// ��� ���� �ѹ� //  �ּ�               // ������  // ������
	ThrowIfFailed(m_device->SetStreamSource(0, m_viBuffer->GetVertexBuffer(), 0, m_material->GetShader()->GetInputLayoutSize()));
	ThrowIfFailed(m_device->SetIndices(m_viBuffer->GetIndexBuffer()));

	// �����Լ� ���������ο� �ʿ�!
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
