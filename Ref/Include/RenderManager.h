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


// PBR ����  ggx
// http://filmicworlds.com/blog/optimizing-ggx-shaders-with-dotlh/ // PBR 

// https://holdimprovae.blogspot.com/2019/01/unityshaderstudy.html dissolve 

class RenderManager
{
	DECLARE_SINGLETON(RenderManager)

	typedef int RenderQueue;
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
	void SkyboxPass(ConstantBuffer& _cBuffer);
	void DeferredRender(Camera* _cam, ConstantBuffer& _cBuffer);
	void GBufferPass(Camera* _cam, ConstantBuffer& _cBuffer);
	void ShadePass(ConstantBuffer& _cBuffer);
	void DebugPass(ConstantBuffer& _cBuffer);
	void LightPass(Camera* _cam, ConstantBuffer& _cBuffer);
	void PointLightPass(Camera* _cam, ConstantBuffer& _cBuffer);
	void PointLightPass(const Matrix& _matWorld, PointLightInfo _lightInfo, VIBuffer* _viBuffer, ConstantBuffer& _cBuffer, Material* _mtrlStencilLight, Material* _mtrlLight);
	void DirectionalLightPass(ConstantBuffer& _cBuffer);
	void TransparentPass(Camera* _cam, ConstantBuffer& _cBuffer);
	void UIPass(Camera* _cam, ConstantBuffer& _cBuffer);
private:
	void RenderNoneAlpha(Camera * _cam, ConstantBuffer& _cBuffer, RENDERING_MODE _mode);
private:
	// ���� ȭ�鿡 �ؽ��ĸ� �׷���
	void RenderByMaterialToScreen(Material* _mtrl, ConstantBuffer& _cBuffer);
	void RenderImageToScreen(IDirect3DBaseTexture9* _tex, ConstantBuffer& _cBuffer);
private:
	VIBuffer* m_imageVIBuffer;
private:
	map<RenderQueue, vector<IRenderer*>> m_renderLists[RENDERING_MODE::RENDERING_MODE_MAX];
	vector<IRenderer*> m_renderUILists;

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
	RenderTarget* m_currentRenderTarget[4]; // RenderTarget ���� �׸��� ���� �ּ�ȭ

	BLENDING_MODE m_blendingMode;
	FILL_MODE m_fillMode;

private:
	Material* m_fullScreenMtrl;
private:
	void UpdateMaterial(Material* _material, ConstantBuffer& _cBuffer);
	void UpdateNoneAlphaMaterial(Material* _material, ConstantBuffer& _cBuffer);
	void UpdateBlendingMode(Material * _material);
	void UpdateFillMode(Material* _material);
	void UpdateVIBuffer(IRenderer* _renderer);
	void UpdateRenderTarget();
	void EndRenderTarget();
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
