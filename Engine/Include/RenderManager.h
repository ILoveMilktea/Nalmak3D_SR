#pragma once

#ifndef  __RENDERMANAGER_H__
#define __RENDERMANAGER_H__

#include "Nalmak_Include.h"
#include "Camera.h"

class IRenderer;
class GameObject;
class Material;
class Shader;
class VIBuffer;
class Text;
class Camera;
class DebugManager;
class MeshRenderer;
class LightManager;
BEGIN(Nalmak)

// ���� ��� 
// IRenderer�� ��ӹ��� ������Ʈ���� �� �Ŵ������� ���������� �Ѱ��ְ�
// �Ŵ����� ������ �������� �������� �ǽ��Ѵ�

// ������ �� �� ������ ��ȭ�� ������ ��ȭ�� �ִٸ� ����̽��� ������ �ٲ��ش�

// �ΰ� ���� . ȭ���ػ� ����, ī�޶� ����Ʈ


// ������ ������ ���׸��󿡼� ���� ���� �ϴ� (0 ~ 5000)������ ���� 
// �⺻ ���� 
//#define RENDER_QUEUE_BACKGROUND 1000
//#define RENDER_QUEUE_GEOMETRY 2000
//#define RENDER_QUEUE_TRANSPARENT 3000
//#define RENDER_QUEUE_OVERLAY 4000


//http://ozlael.egloos.com/2423070 ���۵� ������ �ڷ�
//https://portsnake.tistory.com/253

//https://lindenreid.wordpress.com/2017/12/15/simple-water-shader-in-unity/ �� ī�� ������

//https://aker.tistory.com/549 ����ȭ ���߿� �����غ���
//https://www.slideshare.net/cagetu/kgc2012-deferred-forward �����ÿ����� �����ڷ� 
// Texture coverage 

//http://ogldev.atspace.co.uk/www/tutorial21/tutorial21.html  deferred ����!
class RenderManager
{
	DECLARE_SINGLETON(RenderManager)
public:
	RenderManager();
	~RenderManager();

public:
	void Release();
	void Initialize();
	void Render();
	void Render(Camera* _cam);
	void RenderText();
	void Reset();
private:
	void DeferredRender(Camera * _cam, ConstantBuffer& _cBuffer);
	void GBufferPass(Camera * _cam, ConstantBuffer& _cBuffer);
	void ShadingPass(Camera * _cam, ConstantBuffer& _cBuffer);
	void LightingPass(Camera * _cam, ConstantBuffer& _cBuffer);
	void TransparentPass(Camera * _cam, ConstantBuffer& _cBuffer);
private:
	void RenderByMaterial(const wstring& _materialName, ConstantBuffer& _cBuffer);
	void RenderImageToScreen(IDirect3DBaseTexture9* _tex, ConstantBuffer& _cBuffer);
private:
	VIBuffer* m_imageVIBuffer;
private:
	map<int, vector<IRenderer*>> m_renderOpaqueLists;
	map<int, vector<IRenderer*>> m_renderTransparentLists;
	vector<Text*> m_textRenderList;
public:
	void RenderRequest(IRenderer* _render);
	void RenderRequest(Text* _text);
public:
	void AddCamera(Camera* _cam);
	void AddCamera(GameObject* _cam);

private:
	list<Camera*> m_cameraList;
	PDIRECT3DDEVICE9 m_device = nullptr;

private:
	Material* m_currentMaterial; // ����ȭ.. Material���� �׸��� ������ �ּ�ȭ
	VIBuffer* m_currentVIBuffer; // Mesh�� �׸��� �ּ�ȭ
	Shader* m_currentShader; // Shader���� �׸��� ���� �ּ�ȭ
	RENDERING_MODE m_renderingMode;
	BLENDING_MODE m_blendingMode;
	FILL_MODE m_fillMode;

private:
	Material* m_currentUIMaterial;
private:
	void UpdateMaterial(Material* _material);
	void UpdateRenderingMode(Material * _material);
	void UpdateBlendingMode(Material * _material);
	void UpdateFillMode(Material* _material);
	void UpdateVIBuffer(IRenderer* _renderer);
	void UpdateShader(Shader* _shader, ConstantBuffer& _cBuffer);
private:
	void RecordRenderTarget(UINT _index, const wstring& _name);
	void EndRenderTarget(const wstring& _name);
public:
	void SetWindowSize(UINT _x, UINT _y);
public:
	UINT GetWindowWidth() { return m_wincx; }
	UINT GetWindowHeight() { return m_wincy; }

public:
	Camera* GetMainCamera();
	void DeleteCamera(Camera* _cam);

private:
	UINT m_wincx;
	UINT m_wincy;
	UINT m_halfWincx;
	UINT m_halfWincy;
private:
	DebugManager* m_debugManager;
	LightManager* m_lightManager;
	ResourceManager* m_resourceManager;

private:
	void ClearRenderTarget(const wstring& _targetName);

};

END
#endif // ! __RENDERMANAGER_H__
