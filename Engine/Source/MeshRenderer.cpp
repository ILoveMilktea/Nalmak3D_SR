#include "..\Include\MeshRenderer.h"
#include "ResourceManager.h"
#include "Transform.h"
#include "Animator.h"
#include "StaticMesh.h"


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
	m_mesh = ResourceManager::GetInstance()->GetResource<StaticMesh>(_desc->meshName);

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

void MeshRenderer::Render(Shader* _shader)
{
	assert("Current Shader is nullptr! " && _shader);

	_shader->SetMatrix("g_world", m_transform->GetWorldMatrix());


	_shader->CommitChanges();				   // BeginPass 호출시 반드시 그리기 전에 호출
												   ////////////////////////////////////////////////////////////////////////////////////
												   // DrawPrimitive (index 사용 x)
												   // Type, 이번에 이용될 인데스, 최소 참조갯수, 호출될 버텍스 수, 인덱스 버퍼내에서 읽기 시작할 인덱스, 그리는 도형 수
	int subCount = m_mesh->GetSubsetCount();

	for (int i = 0; i < subCount; ++i)
	{
		m_mesh->Draw(i);
	}
}

void MeshRenderer::BindingStreamSource()
{
}

float MeshRenderer::GetBoundingRadius()
{
	return m_mesh->GetBoundingSphereRadius();
}

Vector3 MeshRenderer::GetBoundingCenter()
{
	return m_mesh->GetBoundingSphereCenter();
}

//void MeshRenderer::BindingStreamSource()
//{
//	//								 // 통로 소켓 넘버 //  주소               // 시작점  // 사이즈
//	//ThrowIfFailed(m_device->SetStreamSource(0, m_viBuffer->GetVertexBuffer(), 0, m_material->GetShader()->GetInputLayoutSize()));
//	//ThrowIfFailed(m_device->SetIndices(m_viBuffer->GetIndexBuffer()));
//
//	//// 고정함수 파이프라인에 필요!
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

unsigned long MeshRenderer::GetSubsetCount()
{
	return m_mesh->GetSubsetCount();
}

int MeshRenderer::GetMaterialCount()
{
	return (int)m_materials.size();
}
