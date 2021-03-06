#pragma once
#include "Mesh.h"
class StaticMesh :
	public Mesh
{
public:
	StaticMesh();
	~StaticMesh();

	virtual void Initialize(wstring _fp) override;
	virtual void Release() override;

private:
	LPD3DXMESH			m_originMesh;
	LPD3DXMESH			m_mesh;
	LPD3DXBUFFER		m_adjacency;
	LPD3DXBUFFER		m_subset;

	Vector3* m_vertexPositionData;
	unsigned int* m_indexData;


	unsigned long	 m_subsetCount;
	unsigned long	 m_stride;
	unsigned long	 m_vertexCount;
	unsigned long	 m_triCount;

	float m_boundingSphereRadius;
	Vector3 m_boundingSphereCenter;

public:
	virtual void Draw(unsigned int _subsetIndex) override;
	unsigned long GetSubsetCount() { return m_subsetCount; }
	float GetBoundingSphereRadius();
	Vector3 GetBoundingSphereCenter();
};
