#include "..\Include\CanvasRenderer.h"

#include "RenderManager.h"
#include "CanvasGroup.h"
#include "ResourceManager.h"
#include "Transform.h"
#include "Animator.h"
#include "SingleImage.h"
#include "Texture.h"
#include "Text.h"
#include "Number.h"
CanvasRenderer::CanvasRenderer()
	:ICanvasGroup()
{
}
CanvasRenderer::CanvasRenderer(Desc * _desc)
	:ICanvasGroup()
{
	m_viBuffer = ResourceManager::GetInstance()->GetResource<VIBuffer>(L"quadNoneNormal");
	m_material = ResourceManager::GetInstance()->GetResource<Material>(_desc->mtrlName);

	m_type = RENDERER_TYPE_CANVAS;
	m_color = { 1.f,1.f,1.f,1.f };

	m_group = _desc->group;
}

void CanvasRenderer::Initialize()
{
	m_renderManager = RenderManager::GetInstance();
	m_input = InputManager::GetInstance();
	m_animator = GetComponent<Animator>();


	if (m_transform->scale.x == 1.f)
		m_transform->scale.x = 100.f;
	if (m_transform->scale.y == 1.f)
		m_transform->scale.y = 100.f;

	m_transform->scale.z = 0.f;

	UpdateBoundary();

	CanvasGroup::GetInstance()->AddGroupMember(this, m_group);
}

void CanvasRenderer::Update()
{
	UpdateBoundary();
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
	CanvasGroup::GetInstance()->RemoveGroupMember(this, m_group);

	
}

void CanvasRenderer::Render(Shader * _shader)
{
	
	Render_Image();
	Render_Text();
	Render_Number();
}

void CanvasRenderer::BindingStreamSource()
{
	ThrowIfFailed(m_device->SetStreamSource(0, m_viBuffer->GetVertexBuffer(), 0, m_material->GetShader()->GetInputLayoutSize()));
	ThrowIfFailed(m_device->SetIndices(m_viBuffer->GetIndexBuffer()));

}

void CanvasRenderer::Render_Image()
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

	currentShader->CommitChanges();

	ThrowIfFailed(m_device->DrawIndexedPrimitive(currentShader->GetPrimitiveType(), 0, 0, m_viBuffer->GetVertexCount(), 0, m_viBuffer->GetFigureCount()));

}

void CanvasRenderer::Render_Text()
{
	Text* text = GetComponent<Text>();

	if (text)
	{
		text->RenderText();
	}
}

void CanvasRenderer::Render_Number()
{
	Number* number = GetComponent<Number>();

	if (number)
	{
		number->RenderText();
	}
}

void CanvasRenderer::UpdateBoundary()
{
	if (m_transform->GetParents())
	{
		auto worldMatrix = m_transform->GetUIWorldMatrix();
		Vector3 position = { worldMatrix.m[3][0], worldMatrix.m[3][1], worldMatrix.m[3][2] };

		float half_wincx = (float)m_renderManager->GetWindowWidth() * 0.5f;
		float half_wincy = (float)m_renderManager->GetWindowHeight() * 0.5f;

		position.x = half_wincx + position.x * half_wincx;
		position.y = half_wincy - position.y * half_wincy;

		m_boundary.left = LONG(position.x - m_transform->scale.x * 0.5f);
		m_boundary.top = LONG(position.y - m_transform->scale.y * 0.5f);
		m_boundary.right = LONG(position.x + m_transform->scale.x * 0.5f);
		m_boundary.bottom = LONG(position.y + m_transform->scale.y * 0.5f);
	}
	else
	{
		m_boundary.left = LONG(m_transform->position.x - m_transform->scale.x * 0.5f);
		m_boundary.top = LONG(m_transform->position.y - m_transform->scale.y * 0.5f);
		m_boundary.right = LONG(m_transform->position.x + m_transform->scale.x * 0.5f);
		m_boundary.bottom = LONG(m_transform->position.y + m_transform->scale.y * 0.5f);
	}

}

bool CanvasRenderer::IsCursorOnRect()
{
	Vector2 mousePos = m_input->GetMouseScreenPos();

	if (m_boundary.left < mousePos.x &&
		m_boundary.right > mousePos.x &&
		m_boundary.top < mousePos.y &&
		m_boundary.bottom > mousePos.y)
	{
		return true;
	}
	return false;
}

void CanvasRenderer::SetColor(Vector4 _color)
{
	if (GetComponent<Text>())
		GetComponent<Text>()->SetColor(
			D3DCOLOR_RGBA(
				int(_color.x * 255),
				int(_color.y * 255),
				int(_color.z * 255),
				int(_color.w * 255)));
	else
		m_color = _color;
}

void CanvasRenderer::SetFade(float _alpha)
{
	ICanvasGroup::SetFade(_alpha);
	m_color.w = _alpha;
}

void CanvasRenderer::SetInteractive(bool _value)
{
	ICanvasGroup::SetInteractive(_value);
}

void CanvasRenderer::SetBlockPicking(bool _value)
{
	ICanvasGroup::SetBlockPicking(_value);
}

void CanvasRenderer::SetGroup(_CANVAS_GROUP _group)
{
	m_group = _group;
	CanvasGroup::GetInstance()->ChangeGroup(this, _group);
}

bool CanvasRenderer::MouseClickDown()
{
	if (m_input->GetKeyDown(KEY_STATE_LEFT_MOUSE))
	{
		if (IsCursorOnRect())
			return true;
	}

	return false;
}

bool CanvasRenderer::MouseClickPress()
{
	if (m_input->GetKeyPress(KEY_STATE_LEFT_MOUSE))
	{
		if (IsCursorOnRect())
			return true;
	}

	return false;
}

bool CanvasRenderer::MouseClickUp_InRect()
{
	if (m_input->GetKeyUp(KEY_STATE_LEFT_MOUSE))
	{
		if (IsCursorOnRect())
			return true;
	}

	return false;
}

bool CanvasRenderer::MouseClickUp_OutRect()
{
	if (m_input->GetKeyUp(KEY_STATE_LEFT_MOUSE))
	{
		if (!IsCursorOnRect())
			return true;
	}

	return false;
}


int CanvasRenderer::GetMaterialCount()
{
	return 1;
}

Material * CanvasRenderer::GetMaterial(int _index)
{
	return m_material;
}

void CanvasRenderer::SetMaterial(Material * _material, int _index)
{
	m_material = _material;
}

void CanvasRenderer::SetMaterial(const wstring& _mtrlName, int _index)
{
	m_material = ResourceManager::GetInstance()->GetResource<Material>(_mtrlName);
}
