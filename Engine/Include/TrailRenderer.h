#pragma once
#include "IRenderer.h"
class TrailRenderer :
	public IRenderer
{
public:
	struct Desc
	{

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
	virtual void BindingStreamSource() override;
	virtual int GetMaterialCount() override;
	virtual Material * GetMaterial(int _index = 0) override;
	virtual void SetMaterial(Material * _material, int _index = 0) override;
	virtual void SetMaterial(const wstring & _mtrlName, int _index = 0) override;
};

