#include "TrailRenderer.h"
#include "Transform.h"

TrailRenderer::TrailRenderer(Desc * _desc)
{
	if (!_desc->mtrl)
	{
		m_material = ResourceManager::GetInstance()->GetResource<Material>(_desc->mtrlName);
	}
	else
	{
		m_material = _desc->mtrl;

	}


	m_layer = _desc->layer;

	m_maxTrailCount = _desc->maxTrailCount;
	m_catmullrom_divideCount = _desc->detailCount;
	m_maxCatmullrom_TrailCount = m_maxTrailCount * m_catmullrom_divideCount;

	m_currentTrailCount = 0;
	m_currentCatmullrom_TrailCount = 0;


	m_secPerTrail = 1.f / _desc->trailCountPerSec;
	m_timer = 0;

	m_type = RENDERER_TYPE_MESH;
}

TrailRenderer::~TrailRenderer()
{
}

void TrailRenderer::Initialize()
{
	CreateDynamicBuffer();
}

void TrailRenderer::Update()
{
	
	m_timer += dTime;

	if (m_timer < m_secPerTrail) // 업데이트 주기 확인
		return;

	Vector3 worldPos = m_transform->GetWorldPosition();

	m_timer -= m_secPerTrail;

	if(m_currentTrailCount <= m_maxTrailCount)
		++m_currentTrailCount;


	Vector3 currentRect[4];
	Vector3 nextRect[4];

	for (int i = 0; i < m_currentTrailCount; ++i)
	{
		int index = i * 4;

		// 첫번째 사각형
		if (i == 0)
		{
			for (int j = 0; j < 4; ++j)
			{
				nextRect[j] = m_trailData[index + j].position;
				m_trailData[index + j].position = worldPos;
			}
		}
		else
		{
			for (int j = 0; j < 4; ++j)
			{

				currentRect[j] = nextRect[j];

				nextRect[j] = m_trailData[index + j].position;

				m_trailData[index + j].position = currentRect[j];
			}
		}
	}

	for (int i = 0; i < m_currentCatmullrom_TrailCount; ++i)
	{
		int index = i * 4;

		if( i / (float)m_catmullrom_divideCount < 1)
			continue;

		if(i / (float)m_catmullrom_divideCount >= m_currentTrailCount - 2)
			continue;

		D3DXVec3CatmullRom(&m_trailCatmullromData[index + 0].position,
			&m_trailData[(i / m_maxTrailCount - 1) * 4 + 0].position,
			&m_trailData[(i / m_maxTrailCount + 0) * 4 + 0].position,
			&m_trailData[(i / m_maxTrailCount + 1) * 4 + 0].position,
			&m_trailData[(i / m_maxTrailCount + 2) * 4 + 0].position,
			float(i % m_maxTrailCount) / float(m_maxTrailCount));
		

		D3DXVec3CatmullRom(&m_trailCatmullromData[index + 1].position,
			&m_trailData[(i / m_maxTrailCount - 1) * 4 + 0].position,
			&m_trailData[(i / m_maxTrailCount + 0) * 4 + 0].position,
			&m_trailData[(i / m_maxTrailCount + 1) * 4 + 0].position,
			&m_trailData[(i / m_maxTrailCount + 2) * 4 + 0].position,
			float(i % m_maxTrailCount + 1) / float(m_maxTrailCount));

		D3DXVec3CatmullRom(&m_trailCatmullromData[index + 2].position,
			&m_trailData[(i / m_maxTrailCount - 1) * 4 + 3].position,
			&m_trailData[(i / m_maxTrailCount + 0) * 4 + 3].position,
			&m_trailData[(i / m_maxTrailCount + 1) * 4 + 3].position,
			&m_trailData[(i / m_maxTrailCount + 2) * 4 + 3].position,
			float(i % m_maxTrailCount + 1) / float(m_maxTrailCount));

		D3DXVec3CatmullRom(&m_trailCatmullromData[index + 3].position,
			&m_trailData[(i / m_maxTrailCount - 1) * 4 + 3].position,
			&m_trailData[(i / m_maxTrailCount + 0) * 4 + 3].position,
			&m_trailData[(i / m_maxTrailCount + 1) * 4 + 3].position,
			&m_trailData[(i / m_maxTrailCount + 2) * 4 + 3].position,
			float(i % m_maxTrailCount) / float(m_maxTrailCount));
	}


}

void TrailRenderer::LateUpdate()
{
	if (m_currentTrailCount < 3)
		return;

	m_instanceBuffer->UpdateInstanceBuffer(m_trailData, m_currentTrailCount);
}

void TrailRenderer::Release()
{
	SAFE_DELETE(m_instanceBuffer);
	SAFE_DELETE_ARR(m_trailData);
	SAFE_DELETE_ARR(m_trailCatmullromData);
}

void TrailRenderer::Render(Shader * _shader, int _index)
{
	if (m_currentTrailCount < 3)
		return;

	assert("Current Shader is nullptr! " && _shader);

	_shader->CommitChanges();
	ThrowIfFailed(m_device->DrawIndexedPrimitive(_shader->GetPrimitiveType(), 0, 0, 4 * m_currentTrailCount, 0, m_instanceBuffer->GetFigureCount()));
}

void TrailRenderer::BindingStreamSource()
{
	ThrowIfFailed(m_device->SetStreamSource(0, m_instanceBuffer->GetVertexBuffer(), 0, m_material->GetShader()->GetInputLayoutSize()));
	ThrowIfFailed(m_device->SetIndices(m_instanceBuffer->GetIndexBuffer()));
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

void TrailRenderer::CreateDynamicBuffer()
{
	m_instanceBuffer = new DynamicInstanceBuffer<INPUT_LAYOUT_POSITION_UV>(m_maxCatmullrom_TrailCount);
	m_instanceBuffer->CreateIndexBufferUsedByTrail(m_maxCatmullrom_TrailCount);

	m_trailData = new INPUT_LAYOUT_POSITION_UV[m_maxTrailCount * 4];
	m_trailCatmullromData = new INPUT_LAYOUT_POSITION_UV[m_maxCatmullrom_TrailCount * 4];

}
