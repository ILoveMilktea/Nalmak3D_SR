#pragma once

#ifndef __DYNAMIC_INSTANCE_BUFFER_H__
#define  __DYNAMIC_INSTANCE_BUFFER_H__
#include "VIBuffer.h"
class DynamicInstanceBuffer :
	public VIBuffer
{
public:
	DynamicInstanceBuffer(int _maxCount);
	virtual void Initialize(wstring _fp = L"") override;

private:
	virtual void CreateVertexBuffer();
	virtual void CreateIndexBuffer();
public:
	void UpdateInstanceBuffer(INPUT_LAYOUT_PARTICLE* _instanceList, int _count);
};

#endif
