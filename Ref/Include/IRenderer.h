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
	virtual void Render() = 0;
	virtual void BindingStreamSource() = 0;

public:
	void RenderRequest();
protected:
	VIBuffer* m_viBuffer;
	Material* m_material;
	PDIRECT3DDEVICE9 m_device;
	int m_layer;
public:
	PDIRECT3DVERTEXBUFFER9 GetVertexBuffer() const;
	PDIRECT3DINDEXBUFFER9 GetIndexBuffer() const;
	Material* GetMaterial() const;
	VIBuffer* GetVIBuffer() const;
	int GetLayer() const { return m_layer; }
public:
	UINT GetVertexCount();
	UINT GetFigureCount();

public:
	void SetMaterial(Material* _material);
	void SetMaterial(wstring _mtrlName);
	void SetLayer(int _layer) { m_layer = _layer; }
	void SetMesh(wstring _meshName);





};

END
#endif
