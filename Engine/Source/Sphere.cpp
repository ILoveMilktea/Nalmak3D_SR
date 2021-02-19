#include "..\Include\Sphere.h"



Sphere::Sphere()
{
}


Sphere::~Sphere()
{
}

void Sphere::Initialize(wstring _fp)
{
	m_heightSliceCount = 50;
	m_widthSliceCount = 50;
	m_radius = 1.f;

	CreateVertexBuffer();
	CreateIndexBuffer();

	
	
}

void Sphere::CreateVertexBuffer()
{

	int totalCount = (m_heightSliceCount - 1) * (m_widthSliceCount + 1) + 2;
	ThrowIfFailed(m_device->CreateVertexBuffer(
		sizeof(INPUT_LAYOUT_POSITION_NORMAL_UV) *totalCount,
		0, // 파티클이나 각종 옵션 조절
		NULL, //D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 | D3DFVF_TEXCOORDSIZE2(0),
		D3DPOOL_MANAGED,
		&m_vBuffer,
		nullptr
	));

	INPUT_LAYOUT_POSITION_NORMAL_UV* vertices = nullptr;

	m_vBuffer->Lock(0, 0, (void**)&vertices, 0);

	int vertexCount = 0;
	float radius = m_radius * 0.5f;
	vertices[vertexCount].position = Vector3(0, radius, 0);
	vertices[vertexCount].normal = Vector3(0, 1, 0);
	vertices[vertexCount].uv = Vector2(1, 0);


	float phiStep = PI / m_heightSliceCount;
	float thetaStep = 2.0f * PI / m_widthSliceCount;

	for (int i = 1; i <= m_heightSliceCount - 1; ++i)
	{
		float phi = i * phiStep;

		for (int j = 0; j <= m_widthSliceCount; ++j)
		{
			++vertexCount;

			float theta = j * thetaStep;

			vertices[vertexCount].position = Vector3(radius * sinf(phi)* cosf(theta), radius * cosf(phi), radius * sinf(phi)*sinf(theta));
			vertices[vertexCount].normal = Vector::Normalize(vertices[vertexCount].position);
			vertices[vertexCount].uv = Vector2(theta / (2 * PI), phi / PI);
		}
	}
	++vertexCount;

	vertices[vertexCount].position = Vector3(0, -radius, 0);
	vertices[vertexCount].normal = Vector3(0, -1, 0);
	vertices[vertexCount].uv = Vector2(1, 0);

	SetVertexCount(vertexCount + 1);
	m_vBuffer->Unlock();

	D3DXComputeBoundingSphere(&vertices[0].position, vertexCount, sizeof(INPUT_LAYOUT_POSITION_NORMAL_UV), &m_boundingSphereCenter, &m_boundingSphereRadius);

}

void Sphere::CreateIndexBuffer()
{
	int totalCount = m_widthSliceCount * 3  + (m_heightSliceCount - 2) * (m_widthSliceCount) * 6 + m_widthSliceCount * 3 ;

	ThrowIfFailed(m_device->CreateIndexBuffer(
		sizeof(short) * totalCount,
		0,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_iBuffer,
		nullptr));

	short* indices = nullptr;

	m_iBuffer->Lock(0, 0, (void**)&indices, 0);

	int count = -1;
	for (int i = 1; i <= m_widthSliceCount; ++i)
	{
		++count;
		indices[count] = 0;
		++count;
		indices[count] = i + 1;
		++count;
		indices[count] = i;
	}

	int baseIndex = 1;
	int ringVertexCount = m_widthSliceCount + 1;
	for (int i = 0; i < m_heightSliceCount - 2; ++i)
	{
		for (int j = 0; j < m_widthSliceCount; ++j)
		{
			++count;
			indices[count] = baseIndex + i * ringVertexCount + j;
			++count;
			indices[count] = baseIndex + i * ringVertexCount + j + 1;
			++count;
			indices[count] = baseIndex + (i + 1) * ringVertexCount + j;

			++count;
			indices[count] = baseIndex + (i + 1) * ringVertexCount + j;
			++count;
			indices[count] = baseIndex + i * ringVertexCount + j + 1;
			++count;
			indices[count] = baseIndex + (i + 1) * ringVertexCount + j + 1;
		}
	}

	int southPoleIndex = (m_heightSliceCount - 1) * (m_widthSliceCount + 1) + 1;
	baseIndex = southPoleIndex - ringVertexCount;

	for (int i = 0; i < m_widthSliceCount; ++i)
	{
		++count;
		indices[count] = southPoleIndex;
		++count;
		indices[count] = baseIndex + i;
		++count;
		indices[count] = baseIndex + i + 1;
	}
	SetFigureCount((count + 1) / 3);
	m_iBuffer->Unlock();
}
