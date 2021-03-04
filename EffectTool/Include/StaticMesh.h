#pragma once
#include "Mesh.h"
class StaticMesh :
	public Mesh
{
public:
	StaticMesh();
	~StaticMesh();

	// Mesh을(를) 통해 상속됨
	virtual void Initialize(wstring _fp) override;
	virtual void Release() override;

private:
	LPD3DXMESH			m_originMesh;
	LPD3DXMESH			m_mesh; // 서브셋의 모임
	LPD3DXBUFFER		m_adjacency;
	LPD3DXBUFFER		m_subset; // 폴리곤의 모임


	Vector3* m_vertexPositionData;
	unsigned int* m_indexData;


	unsigned long	 m_subsetCount;
	unsigned long	 m_stride;
	unsigned long	 m_vertexCount;
	unsigned long	 m_triCount;

public:
	virtual void Draw(unsigned int _subsetIndex) override;
	unsigned long GetSubsetCount() { return m_subsetCount; }
};

