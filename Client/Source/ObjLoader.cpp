#include "stdafx.h"
#include "..\Include\ObjLoader.h"


ObjLoader::ObjLoader()
{
}


ObjLoader::~ObjLoader()
{
}

void ObjLoader::Initialize(wstring _fp)
{

	//ThrowIfFailed(m_device->CreateVertexBuffer(
	//	sizeof(INPUT_LAYOUT_POSITION_NORMAL_UV) * (UINT)vertex.size(),
	//	0, // 파티클이나 각종 옵션 조절
	//	NULL, //D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 | D3DFVF_TEXCOORDSIZE2(0),
	//	D3DPOOL_MANAGED,
	//	&m_vBuffer,
	//	nullptr
	//));

	//INPUT_LAYOUT_POSITION_NORMAL_UV* vertices = nullptr;
	//m_vBuffer->Lock(0, 0, (void**)&vertices, 0);


	//D3DXComputeBoundingSphere(&vertices[0].position, (DWORD)vertex.size(), sizeof(INPUT_LAYOUT_POSITION_NORMAL_UV), &m_boundingSphereCenter, &m_boundingSphereRadius);
	//m_vBuffer->Unlock();
	//SetVertexCount((UINT)vertex.size());
	//vertex.clear();



	//ThrowIfFailed(m_device->CreateIndexBuffer(
	//	sizeof(short) * (UINT)(faces.size()),
	//	0,
	//	D3DFMT_INDEX16,
	//	D3DPOOL_MANAGED,
	//	&m_iBuffer,
	//	nullptr));

	//short* test = nullptr;
	//m_iBuffer->Lock(0, 0, (void**)&test, 0);

	//for (size_t i = 0; i < faces.size(); ++i)
	//{
	//	if (i >= faces.size())
	//		break;

	//	test[i] = (short)faces[i] - 1;


	//}
	//m_iBuffer->Unlock();
	//SetFigureCount((UINT)faces.size());
	//faces.clear();

}
