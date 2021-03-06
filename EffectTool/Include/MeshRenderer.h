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
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;
public:
	virtual void Render(Shader* _shader) override;
	virtual void BindingStreamSource() override;
public:
	virtual float GetBoundingRadius() override;
	virtual Vector3 GetBoundingCenter() override;
	// IRenderer��(��) ���� ���ӵ�
	void AddMaterial(const wstring& _mtrl);
	virtual int GetMaterialCount() override;
	virtual Material * GetMaterial(int _index = 0) override;
	virtual void SetMaterial(Material * _material, int _index = 0) override;
	virtual void SetMaterial(const wstring& _mtrlName, int _index = 0) override;
private:
	vector<Material*> m_materials;
	class StaticMesh* m_mesh;

	unsigned long GetSubsetCount();


};

#endif // !__MESHRENDERER_H__
