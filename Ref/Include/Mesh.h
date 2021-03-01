#pragma once
#include "IResource.h"
class Mesh :
	public IResource
{
public:
	Mesh();
	~Mesh();

	// IResource��(��) ���� ��ӵ�
	virtual void Initialize(wstring _fp) override = 0;
	virtual void Release() override = 0;

public:
	virtual void Draw(unsigned int _subsetIndex) = 0;
};

