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

// 렌더 담당 
// IRenderer를 상속받은 컴포넌트들은 이 매니저에게 렌더정보를 넘겨주고
// 매니저가 정보를 바탕으로 렌더링을 실시한다

// 렌더링 할 시 정보의 변화를 감지해 변화가 있다면 디바이스에 세팅을 바꿔준다

// 부가 정보 . 화면해상도 정보, 카메라 리스트


// 렌더링 순서는 메테리얼에서 설정 가능 하다 (0 ~ 5000)사이의 정수 
// 기본 정의 
//#define RENDER_QUEUE_BACKGROUND 1000
//#define RENDER_QUEUE_GEOMETRY 2000
//#define RENDER_QUEUE_TRANSPARENT 3000
//#define RENDER_QUEUE_OVERLAY 4000


//http://ozlael.egloos.com/2423070 디퍼드 렌더링 자료
//https://portsnake.tistory.com/253

//https://lindenreid.wordpress.com/2017/12/15/simple-water-shader-in-unity/ 물 카툰 렌더링

//https://aker.tistory.com/549 최적화 나중에 구현해보기
//https://www.slideshare.net/cagetu/kgc2012-deferred-forward 라이팅에관한 참고자료 
// Texture coverage 
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
	void ClearRT(Camera * _cam, ConstantBuffer& _cBuffer);
private:
	map<int, vector<IRenderer*>> m_renderLists;
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
	Material* m_currentMaterial; // 최적화.. Material별로 그리기 설정을 최소화
	VIBuffer* m_currentVIBuffer; // Mesh별 그리기 최소화
	Shader* m_currentShader; // Shader별로 그리기 설정 최소화
	RENDERING_MODE m_renderingMode;
	BLENDING_MODE m_blendingMode;
	FILL_MODE m_fillMode;

private:
	void UpdateMaterial(Material* _material);
	void UpdateRenderingMode(Material * _material);
	void UpdateBlendingMode(Material * _material);
	void UpdateFillMode(Material* _material);
	void UpdateVIBuffer(IRenderer* _renderer);
	void UpdateShader(Shader* _shader, ConstantBuffer& _cBuffer);
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
	Shader* m_clearRTShader;
	VIBuffer* m_viBuffer;
};

END
#endif // ! __RENDERMANAGER_H__
