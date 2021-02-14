#pragma once
#include "VIBuffer.h"
class Plane :
	public VIBuffer
{
public:
	Plane(int _width = 100, int _depth = 100, float _interval = 1);
	~Plane();

	// VIBuffer을(를) 통해 상속됨
	virtual void Initialize(wstring _fp = L"") override;

private:
	virtual void CreateVertexBuffer();
	virtual void CreateIndexBuffer();

	int m_width = 0;
	int m_depth = 0;
	float m_interval = 0;
public:
	void UpdateInstanceBuffer(INPUT_LAYOUT_POSITION_NORMAL_UV* _instanceList, int _count);

};
