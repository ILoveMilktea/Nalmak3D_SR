#include "..\Include\MeshRenderer.h"
#include "ResourceManager.h"
#include "Transform.h"
#include "Animator.h"
#include "Mesh.h"


MeshRenderer::MeshRenderer(Desc * _desc)
{
	if (!_desc->mtrl)
	{
		m_materials.emplace_back(ResourceManager::GetInstance()->GetResource<Material>(_desc->mtrlName));
	}
	else
	{
		m_materials.emplace_back(_desc->mtrl);
	}
	m_mesh = ResourceManager::GetInstance()->GetResource<Mesh>(_desc->meshName);

	m_layer = _desc->layer;
	m_type = RENDERER_TYPE_MESH;
}

void MeshRenderer::Initialize()
{
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

void MeshRenderer::Render(Shader* _shader, int _index)
{
	assert("Current Shader is nullptr! " && _shader);

	_shader->SetMatrix("g_world", m_transform->GetWorldMatrix());


	_shader->CommitChanges();				   // BeginPass ȣ��� �ݵ�� �׸��� ���� ȣ��
												   ////////////////////////////////////////////////////////////////////////////////////
												   // DrawPrimitive (index ��� x)
												   // Type, �̹��� �̿�� �ε���, �ּ� ��������, ȣ��� ���ؽ� ��, �ε��� ���۳����� �б� ������ �ε���, �׸��� ���� ��
	m_mesh->Draw(_index);
}

void MeshRenderer::BindingStreamSource()
{
}

//void MeshRenderer::BindingStreamSource()
//{
//	//								 // ��� ���� �ѹ� //  �ּ�               // ������  // ������
//	//ThrowIfFailed(m_device->SetStreamSource(0, m_viBuffer->GetVertexBuffer(), 0, m_material->GetShader()->GetInputLayoutSize()));
//	//ThrowIfFailed(m_device->SetIndices(m_viBuffer->GetIndexBuffer()));
//
//	//// �����Լ� ���������ο� �ʿ�!
//	//// m_device->SetFVF()
//	
//}

void MeshRenderer::AddMaterial(const wstring & _mtrl)
{
	m_materials.emplace_back(ResourceManager::GetInstance()->GetResource<Material>(_mtrl));
}

Material * MeshRenderer::GetMaterial(int _index)
{
#ifdef _DEBUG
	if (_index >= m_materials.size())
	{
		assert(L"Index out of range! " && 0);
	}
#endif // _DEBUG

	return m_materials[_index];
}

void MeshRenderer::SetMaterial(Material * _material, int _index)
{
#ifdef _DEBUG
	if (_index >= m_materials.size())
	{
		assert(L"Index out of range! " && 0);
	}
#endif // _DEBUG
	m_materials[_index] = _material;
}

void MeshRenderer::SetMaterial(const wstring& _mtrlName, int _index)
{
#ifdef _DEBUG
	if (_index >= m_materials.size())
	{
		assert(L"Index out of range! " && 0);
	}
#endif // _DEBUG
	m_materials[_index] = ResourceManager::GetInstance()->GetResource<Material>(_mtrlName);
}

int MeshRenderer::GetMaterialCount()
{
	return (int)m_materials.size();
}
