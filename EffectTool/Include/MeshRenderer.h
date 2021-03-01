#pragma once

#ifndef __MESHRENDERER_H__
#define __MESHRENDERER_H__

#include "IRenderer.h"

class Animator;

class NALMAK_DLL MeshRenderer :
	public IRenderer
{
public:
	struct Desc
	{
		wstring mtrlName = L"default";
		Material* mtrl = nullptr;

		wstring meshName = L"quad";
		int layer = 0;
	};
	MeshRenderer(Desc* _desc);
private:
	// MeshRenderer을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;
public:
	virtual void Render(Shader* _shader, int _index) override;
	virtual void BindingStreamSource() override;

	// IRenderer을(를) 통해 상속됨
	void AddMaterial(const wstring& _mtrl);
	virtual int GetMaterialCount() override;
	virtual Material * GetMaterial(int _index = 0) override;
	virtual void SetMaterial(Material * _material, int _index = 0) override;
	virtual void SetMaterial(const wstring& _mtrlName, int _index = 0) override;
private:
	vector<Material*> m_materials;
	class Mesh* m_mesh;




};

#endif // !__MESHRENDERER_H__
