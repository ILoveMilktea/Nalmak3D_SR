#pragma once
#include "VIBuffer.h"
class ObjLoader :
	public VIBuffer
{
public:
	ObjLoader();
	~ObjLoader();

	// VIBuffer��(��) ���� ��ӵ�
	virtual void Initialize(wstring _fp = L"") override;
};

