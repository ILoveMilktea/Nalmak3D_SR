#pragma once

#ifndef  __VIBUFFER_H__
#define __VIBUFFER_H__

#include "IResource.h"

BEGIN(Nalmak)
class NALMAK_DLL VIBuffer :
	public IResource
{
public:
	VIBuffer();
	virtual ~VIBuffer();
public:
	void OnInitialize(const TCHAR * _fp = L"");
private:
	// IResource을(를) 통해 상속됨
	virtual void Initialize(wstring _fp = L"") override = 0;
	virtual void Release() override;
public:
	virtual void SetVertexCount(UINT _count) { m_vertexCount = _count; }
	virtual void SetFigureCount(UINT _count) { m_figureCount = _count; }

protected:
	PDIRECT3DVERTEXBUFFER9	m_vBuffer = nullptr;
	PDIRECT3DINDEXBUFFER9	m_iBuffer = nullptr;

protected:
	UINT m_vertexCount;
	UINT m_figureCount;

	INPUT_LAYOUT_POSITION_NORMAL_UV* m_vertices = nullptr;
	short* m_indices = nullptr;
public:
	PDIRECT3DVERTEXBUFFER9 GetVertexBuffer() { assert("Vertex Buffer is Empty!" && m_vBuffer); return m_vBuffer; }
	PDIRECT3DINDEXBUFFER9 GetIndexBuffer() { assert("Index Buffer is Empty!" && m_iBuffer); return m_iBuffer; }

	UINT GetVertexCount() { return m_vertexCount; }
	UINT GetFigureCount() { return m_figureCount; }

	INPUT_LAYOUT_POSITION_NORMAL_UV* GetVertices() { return m_vertices; }
	short* GetIndices() { return m_indices; }
protected:
	Vector3 m_boundingSphereCenter;
	float m_boundingSphereRadius = 0;
public:
	Vector3 GetBoundingSphereCenter() { return m_boundingSphereCenter; }
	float GetBoundingSphereRadius() { return m_boundingSphereRadius; }
};

END
#endif // ! __VIBUFFER_H__
