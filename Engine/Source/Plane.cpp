#include "..\Include\Plane.h"


Plane::Plane(int _width, int _depth, float _interval)
{
	m_width = _width;
	m_depth = _depth;
	m_interval = _interval;

	
}

Plane::~Plane()
{
}

void Plane::Initialize(wstring _fp/* = L""*/)
{
	CreateVertexBuffer();
	CreateIndexBuffer();

	SetFigureCount(m_width * m_depth * 2);
	SetVertexCount((m_width + 1) * (m_depth + 1));
}

void Plane::CreateVertexBuffer()
{
	ThrowIfFailed(m_device->CreateVertexBuffer(
		sizeof(INPUT_LAYOUT_POSITION_NORMAL_UV) * (m_width + 1) * (m_depth + 1),
		D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY,
		NULL,
		D3DPOOL_DEFAULT,
		&m_vBuffer,
		nullptr
	));

	INPUT_LAYOUT_POSITION_NORMAL_UV* vertices = nullptr;


	m_vBuffer->Lock(0, 0, (void**)&vertices, 0);

	for (int row = 0; row < m_depth + 1; ++row)
	{
		for (int col = 0; col < m_width + 1; ++col)
		{
			int index = row * (m_width + 1) + col;
			vertices[index].position = Vector3(m_interval * col,0.f, m_interval * row);
			vertices[index].uv = Vector2(col / (float)m_width, row / (float)m_depth);
			vertices[index].normal = Vector3(0.f, 1.f, 0.f);
		}
	}

	m_vBuffer->Unlock();

	D3DXComputeBoundingSphere(&vertices[0].position, (m_width + 1) * (m_depth + 1), sizeof(INPUT_LAYOUT_POSITION_NORMAL_UV), &m_boundingSphereCenter, &m_boundingSphereRadius);

}

void Plane::CreateIndexBuffer()
{
	ThrowIfFailed(m_device->CreateIndexBuffer(
		sizeof(short) * m_width * m_depth * 6,
		0,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_iBuffer,
		nullptr));

	short* indices = nullptr;

	m_iBuffer->Lock(0, 0, (void**)&indices, 0);

	int index = 0;
	for (int row = 0; row < m_depth; ++row)
	{
		for (int col = 0; col < m_width; ++col)
		{
			indices[index] = row * (m_width + 1) + col;
			indices[index + 2] = row * (m_width + 1) + col + 1;
			indices[index + 1] = (row + 1) * (m_width + 1) + col;

			indices[index + 3] = (row + 1) * (m_width + 1) + col;   // index + 2
			indices[index + 5] = row * (m_width + 1) + col + 1;   // index + 1
			indices[index + 4] = (row + 1) * (m_width + 1) + col + 1;

			index += 6; // next quad
		}
	}
	m_iBuffer->Unlock();
}

void Plane::UpdateInstanceBuffer(INPUT_LAYOUT_POSITION_NORMAL_UV * _instanceList, int _count)
{
	INPUT_LAYOUT_POSITION_NORMAL_UV* planeData;

	m_vBuffer->Lock(0, 0, (void**)&planeData, D3DLOCK_DISCARD);
	memcpy(planeData, _instanceList, sizeof(INPUT_LAYOUT_POSITION_NORMAL_UV)* _count);
	m_vBuffer->Unlock();
}
