#pragma once

#ifndef __IRENDERER_H__
#define __IRENDERER_H__

#include "Nalmak_Include.h"
#include "Component.h"
#include "Material.h"
#include "VIBuffer.h"
BEGIN(Nalmak)

class NALMAK_DLL IRenderer :
	public Component
{
public:
	IRenderer();
	virtual ~IRenderer() = default;
private:
	// Component을(를) 통해 상속됨
	virtual void Initialize() override = 0;
	virtual void Update() override = 0;
	virtual void LateUpdate() override = 0;
	virtual void PreRender() override;
	virtual void Release() override = 0;
public:
	virtual void Render(Shader* _shader,int _index) = 0;
	virtual void BindingStreamSource() = 0;
public:
	void RenderRequest();
public:
	// Only _index parameter is Valid in MeshRenderer 
	virtual int GetMaterialCount()  = 0;
	virtual Material* GetMaterial(int _index = 0) = 0;
	virtual void SetMaterial(Material* _material, int _index = 0) = 0;
	virtual void SetMaterial(const wstring& _mtrlName, int _index = 0) = 0;
	
protected:
	PDIRECT3DDEVICE9 m_device;
	RENDERER_TYPE  m_type;
	int m_layer;
	bool m_isFrustumCulling = true;
public:
	//PDIRECT3DVERTEXBUFFER9 GetVertexBuffer() const;
	//PDIRECT3DINDEXBUFFER9 GetIndexBuffer() const;

	int GetLayer() const { return m_layer; }
	bool IsFrustumCulling() { return m_isFrustumCulling; }
public:
	//UINT GetVertexCount();
	//UINT GetFigureCount();

	const RENDERER_TYPE& GetType() { return m_type; }
public:

	void SetLayer(int _layer) { m_layer = _layer; }
	//void SetMesh(wstring _meshName);
	void SetFrustumCulling(bool _culling) { m_isFrustumCulling = _culling; }




};

END
#endif
