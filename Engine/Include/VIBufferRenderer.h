#pragma once

#ifndef __VIBUFFERRENDERER_H__
#define __VIBUFFERRENDERER_H__

#include "IRenderer.h"
class NALMAK_DLL VIBufferRenderer :
	public IRenderer
{
public:
	struct Desc
	{
		wstring mtrlName = L"defulat";
		Material* mtrl = nullptr;

		wstring meshName = L"meshName";
		int layer = 0;
	};
public:
	VIBufferRenderer(Desc* _desc);
	~VIBufferRenderer();
private:
	// IRenderer을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;
public:
	virtual void Render(Shader * _shader, int _index) override;
	virtual int GetMaterialCount() override;
	virtual Material * GetMaterial(int _index = 0) override;
	virtual void SetMaterial(Material * _material, int _index = 0) override;
	virtual void SetMaterial(const wstring & _mtrlName, int _index = 0) override;
private:
	virtual void BindingStreamSource() override;
private:
	VIBuffer* m_viBuffer;
	Material* m_material;
};

#endif