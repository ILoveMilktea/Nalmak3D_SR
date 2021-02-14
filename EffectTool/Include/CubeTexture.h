#pragma once
#include "IResource.h"
class CubeTexture :
	public IResource
{
public:
	CubeTexture();
	~CubeTexture();

	// IResource을(를) 통해 상속됨
	virtual void Initialize(wstring _fp) override;
	virtual void Release() override;
};

