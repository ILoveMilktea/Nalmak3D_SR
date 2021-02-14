#include "..\Include\VIBuffer.h"

USING(Nalmak)


VIBuffer::VIBuffer()
{
	m_vertexCount = 0;
	m_figureCount = 0;
}


VIBuffer::~VIBuffer()
{
	Release();
}

void VIBuffer::OnInitialize(const TCHAR * _fp)
{
	Initialize(_fp);

	assert("Please Set vertex Count In Initialize!" && m_vertexCount);
	assert("Please Set figure Count In Initialize!" && m_figureCount);
}

void VIBuffer::Initialize(wstring _fp)
{
}

void VIBuffer::Release()
{
	SAFE_RELEASE(m_vBuffer);
	SAFE_RELEASE(m_iBuffer);
}
