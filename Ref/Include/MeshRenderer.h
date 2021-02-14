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
		wstring texName = L"default";
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
	virtual void Render() override;
	virtual void BindingStreamSource() override;

private:
	Animator* m_animator;
};

#endif // !__MESHRENDERER_H__
