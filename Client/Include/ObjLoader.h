#pragma once
#include "VIBuffer.h"
class ObjLoader :
	public VIBuffer
{
public:
	ObjLoader();
	~ObjLoader();

	// VIBuffer을(를) 통해 상속됨
	virtual void Initialize(wstring _fp = L"") override;
};

