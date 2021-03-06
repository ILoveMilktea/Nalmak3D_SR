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
		wstring mtrlName = L"default";
		Material* mtrl = nullptr;

		wstring meshName = L"box";
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
	virtual void Render(Shader * _shader) override;
	virtual int GetMaterialCount() override;
	virtual Material * GetMaterial(int _index = 0) override;
	virtual void SetMaterial(Material * _material, int _index = 0) override;
	virtual void SetMaterial(const wstring & _mtrlName, int _index = 0) override;

	VIBuffer* GetVIBuffer() { return m_viBuffer; }
	void SetVIBuffer(const wstring& _meshName);
private:
	virtual void BindingStreamSource() override;
private:
	VIBuffer* m_viBuffer;
	Material* m_material;
};

#endif