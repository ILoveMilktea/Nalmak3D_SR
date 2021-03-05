#pragma once
#include "IRenderer.h"
class NALMAK_DLL TrailRenderer :
	public IRenderer
{
public:
	struct Desc
	{
		wstring mtrlName = L"default";
		Material* mtrl = nullptr;

		int layer = 0;
	};
public:
	TrailRenderer(Desc* _desc);
	~TrailRenderer();
private:
	// IRenderer을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;
	virtual void Render(Shader * _shader, int _index) override;
private:
	virtual void BindingStreamSource() override;
public:
	virtual int GetMaterialCount() override;
	virtual Material * GetMaterial(int _index = 0) override;
	virtual void SetMaterial(Material * _material, int _index = 0) override;
	virtual void SetMaterial(const wstring & _mtrlName, int _index = 0) override;

private:
	VIBuffer* m_viBuffer;
	Material* m_material;
	class DynamicInstanceBuffer* m_instanceBuffer;
private:
	int m_currentCount;
};

