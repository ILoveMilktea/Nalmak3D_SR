#pragma once

#ifndef __DYNAMIC_INSTANCE_BUFFER_H__
#define  __DYNAMIC_INSTANCE_BUFFER_H__
#include "VIBuffer.h"
template <typename T>
class DynamicInstanceBuffer :
	public VIBuffer
{
public:
	DynamicInstanceBuffer(int _maxCount)
	{
		ThrowIfFailed(m_device->CreateVertexBuffer(
			sizeof(T) * _maxCount,
			D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY, // 파티클이나 각종 옵션 조절
			NULL,
			D3DPOOL_DEFAULT, // 동적 버텍스 버퍼는 관리 메모리풀에 보관 불가
			&m_vBuffer,
			nullptr
		));
	}
	virtual void Initialize(wstring _fp = L"") override;

private:
	virtual void CreateVertexBuffer();
	virtual void CreateIndexBuffer();
public:
	void UpdateInstanceBuffer(T* _instanceList, int _count)
	{
		T* instanceData = nullptr;

		m_vBuffer->Lock(0, 0, (void**)&instanceData, D3DLOCK_DISCARD);
		memcpy(instanceData, _instanceList, sizeof(T)* _count);
		m_vBuffer->Unlock();
	}

	void CreateIndexBufferUsedByTrail(int _catmullomMaxCount);
};

#endif

template<typename T>
inline void DynamicInstanceBuffer<T>::Initialize(wstring _fp)
{
}

template<typename T>
inline void DynamicInstanceBuffer<T>::CreateVertexBuffer()
{
}

template<typename T>
inline void DynamicInstanceBuffer<T>::CreateIndexBuffer()
{
}

template<typename T>
inline void DynamicInstanceBuffer<T>::CreateIndexBufferUsedByTrail(int _catmullomMaxCount)
{
	INDEX32*		indexBuffer = nullptr;

	m_iBuffer->Lock(0, 0, (void**)&indexBuffer, 0);

	int triCount = 0;
	int index  = 0;

	for (int i = 0; i < _catmullomMaxCount; ++i)
	{
		index = i * 4;

		indexBuffer[triCount]._0 = index + 0;
		indexBuffer[triCount]._1 = index + 1;
		indexBuffer[triCount]._2 = index + 2;
		++triCount;

		indexBuffer[triCount]._0 = index + 0;
		indexBuffer[triCount]._1 = index + 2;
		indexBuffer[triCount]._2 = index + 3;
		++triCount;
	}

	m_iBuffer->Unlock();

}
