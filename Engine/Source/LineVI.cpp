#include "..\Include\LineVI.h"



void LineVI::Initialize(wstring _fp)
{
	CreateVertexBuffer();
	CreateIndexBuffer();

	SetFigureCount(1);
	SetVertexCount(2);
}

void LineVI::CreateVertexBuffer()
{
	ThrowIfFailed(m_device->CreateVertexBuffer(
		sizeof(INPUT_LAYOUT_POSITION) * 2,
		0, // 파티클이나 각종 옵션 조절
		NULL,
		D3DPOOL_MANAGED,
		&m_vBuffer,
		nullptr
	));

	INPUT_LAYOUT_POSITION* vertices = nullptr;

	m_vBuffer->Lock(0, 0, (void**)&vertices, 0);

	vertices[0].position = Vector3(-0.5f, 0.f, 0.f);
	vertices[1].position = Vector3(0.5f, 0.f, 0.f);


	m_vBuffer->Unlock();

	D3DXComputeBoundingSphere(&vertices[0].position, 2, sizeof(INPUT_LAYOUT_POSITION), &m_boundingSphereCenter, &m_boundingSphereRadius);
}

void LineVI::CreateIndexBuffer()
{
	ThrowIfFailed(m_device->CreateIndexBuffer(
		sizeof(short) * 2,
		0,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_iBuffer,
		nullptr));

	short* indices = nullptr;

	m_iBuffer->Lock(0, 0, (void**)&indices, 0);

	indices[0] = 0;
	indices[1] = 1;

	m_iBuffer->Unlock();
}
