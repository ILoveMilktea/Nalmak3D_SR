#include "RenderManager.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "DeviceManager.h"
#include "IRenderer.h"
#include "Camera.h"
#include "Transform.h"
#include "Material.h"
#include "RenderTarget.h"
#include "Shader.h"
#include "VIBuffer.h"
#include "GameObject.h"
#include "Text.h"
#include "DebugManager.h"
USING(Nalmak)
IMPLEMENT_SINGLETON(RenderManager)
RenderManager::RenderManager()
{
}


RenderManager::~RenderManager()
{
	Release();
}

void RenderManager::Release()
{
	m_device = nullptr;
	m_cameraList.clear();
}

void RenderManager::Initialize(UINT _wincx, UINT _wincy)
{
	m_device = DeviceManager::GetInstance()->GetDevice();
	m_debugManager = DebugManager::GetInstance();
	m_renderingMode = RENDERING_MODE_MAX;
	m_blendingMode = BLENDING_MODE_MAX;

	m_currentMaterial = nullptr;
	m_currentShader = nullptr;
	m_currentVIBuffer = nullptr;

	m_cameraList.clear();
	m_wincx = _wincx;
	m_wincy = _wincy;
	m_halfWincx = (UINT)(m_wincx * 0.5f);
	m_halfWincy = (UINT)(m_wincy * 0.5f);

	D3DVIEWPORT9 vp = { 0,0,m_wincx,m_wincy,0,1 };
	m_device->SetViewport(&vp);

}

void RenderManager::Render()
{

	ThrowIfFailed(m_device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, m_cameraList.front()->m_clearColor, 1, 0));

	for (auto& cam : m_cameraList)
	{
		if (cam->GetActive())
			Render(cam);
	}
	RenderText();
	ThrowIfFailed(m_device->Present(nullptr, nullptr, 0, nullptr));

	for (auto& renderList : m_renderLists)
		renderList.second.clear();

}

void RenderManager::Render(Camera * _cam)
{
	
	m_currentShader = nullptr;
	m_currentMaterial = nullptr;

	Matrix matViewProj = _cam->GetViewMatrix() * _cam->GetProjMatrix();
	Matrix worldMat = _cam->GetTransform()->GetWorldMatrix();
	Vector4 camWorldPos = Vector4(worldMat._41, worldMat._42, worldMat._43,1);
	_cam->RecordRenderTarget();
	
	ThrowIfFailed(m_device->BeginScene());



	for (auto& MeshRendererList : m_renderLists)
	{
		for (auto& renderer : MeshRendererList.second)
		{
			if (_cam->CompareLayer(renderer->GetLayer()))
			{
				if (_cam->IsInFrustumCulling(renderer))
				{

					Material* material = renderer->GetMaterial();
					UpdateMaterial(material, matViewProj, worldMat);
					UpdateShader(material->GetShader());
					UpdateVIBuffer(renderer);

					renderer->Render();
				}
			}
		}
	}

	if (m_currentShader)
		m_currentShader->EndPass();




	ThrowIfFailed(m_device->EndScene());
	_cam->EndRenderTarget();

}

void RenderManager::RenderText()
{
	for (auto& text : m_textRenderList)
	{
		RECT newRect = text->m_textBoundary;
		newRect.left += (LONG)(m_halfWincx + text->GetTransform()->GetNoneScaleWorldMatrix()._41);
		newRect.right += (LONG)(m_halfWincx + text->GetTransform()->GetNoneScaleWorldMatrix()._41);
		newRect.top += (LONG)(m_halfWincy - text->GetTransform()->GetNoneScaleWorldMatrix()._42);
		newRect.bottom += (LONG)(m_halfWincy - text->GetTransform()->GetNoneScaleWorldMatrix()._42);

		text->m_font->DrawTextW(
			nullptr,
			text->m_text.c_str(),
			-1,
			&newRect,
			text->m_option,
			text->m_color
		);
	}
	m_textRenderList.clear();
	m_debugManager->EraseTheRecord();
}

void RenderManager::Reset()
{
	m_currentMaterial = nullptr;

	m_cameraList.clear();
	for (auto& renderList : m_renderLists)
		renderList.second.clear();
}

void RenderManager::RenderRequest(IRenderer * _render)
{
	m_renderLists[_render->GetMaterial()->GetRenderQueue()].emplace_back(_render);
}

void RenderManager::RenderRequest(Text * _text)
{
	assert("text is nullptr!" && _text);
	m_textRenderList.emplace_back(_text);
}

void RenderManager::AddCamera(Camera * _cam)
{
	assert("Camera is nullptr " && _cam);
	m_cameraList.emplace_back(_cam);
}

void RenderManager::AddCamera(GameObject * _cam)
{
	AddCamera(_cam->GetComponent<Camera>());
}

void RenderManager::UpdateMaterial(Material * _material, const Matrix & _viewProj,const Matrix& _camPos)
{
	if (m_currentMaterial != _material)
	{
		m_currentMaterial = _material;
		_material->SetMatrix("g_viewProj", _viewProj);
		_material->SetMatrix("g_cameraMatrix", _camPos);

		UpdateRenderingMode(_material);
		UpdateBlendingMode(_material);
		UpdateFillMode(_material);
		_material->SetDataToShader();


	}
}

void RenderManager::UpdateRenderingMode(Material * _material)
{
	auto mode = _material->GetRenderingMode();
	if (m_renderingMode != mode)
	{
		m_renderingMode = mode;

		switch (mode)
		{
		case RENDERING_MODE_OPAQUE:
			ThrowIfFailed(m_device->SetRenderState(D3DRS_ALPHABLENDENABLE, false));
			ThrowIfFailed(m_device->SetRenderState(D3DRS_ALPHATESTENABLE, false));
			break;
		case RENDERING_MODE_CUTOUT:
			ThrowIfFailed(m_device->SetRenderState(D3DRS_ALPHABLENDENABLE, false));
			ThrowIfFailed(m_device->SetRenderState(D3DRS_ALPHATESTENABLE, true));
			ThrowIfFailed(m_device->SetRenderState(D3DRS_ALPHAREF, 50));
			break;
		case RENDERING_MODE_TRANSPARENT:
			ThrowIfFailed(m_device->SetRenderState(D3DRS_ALPHABLENDENABLE, true));
			ThrowIfFailed(m_device->SetRenderState(D3DRS_ALPHATESTENABLE, false));
			break;
		default:
			break;
		}
	}
}

void RenderManager::UpdateBlendingMode(Material * _material)
{

	auto mode = _material->GetBlendingMode();
	if (m_blendingMode != mode)
	{
		m_blendingMode = mode;
		switch (mode)
		{
		case BLENDING_MODE_DEFAULT:
			ThrowIfFailed(m_device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP::D3DBLENDOP_ADD));
			ThrowIfFailed(m_device->SetRenderState(D3DRS_SRCBLEND,D3DBLEND::D3DBLEND_SRCALPHA));
			ThrowIfFailed(m_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND::D3DBLEND_INVSRCALPHA));
	
			break;
		case BLENDING_MODE_ADDITIVE:
			ThrowIfFailed(m_device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP::D3DBLENDOP_ADD));
			ThrowIfFailed(m_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND::D3DBLEND_ONE));
			ThrowIfFailed(m_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND::D3DBLEND_ONE));
			break;
		case BLENDING_MODE_SUBTRACTIVE:
			ThrowIfFailed(m_device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP::D3DBLENDOP_REVSUBTRACT));
			ThrowIfFailed(m_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND::D3DBLEND_ONE));
			ThrowIfFailed(m_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND::D3DBLEND_ONE));
			break;
		case BLENDING_MODE_MULTIPLY:
			ThrowIfFailed(m_device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP::D3DBLENDOP_ADD));
			ThrowIfFailed(m_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND::D3DBLEND_SRCCOLOR));
			ThrowIfFailed(m_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND::D3DBLEND_DESTCOLOR));
			break;
		default:
			break;
		}
	}
}

void RenderManager::UpdateFillMode(Material * _material)
{
	auto fillMode = _material->GetFillMode();
	if (m_fillMode != fillMode)
	{
		m_fillMode = fillMode;

		switch (m_fillMode)
		{
		case FILL_MODE_SOLID:
			ThrowIfFailed(m_device->SetRenderState(D3DRS_FILLMODE,D3DFILLMODE::D3DFILL_SOLID));
			break;
		case FILL_MODE_WIREFRAME:
			ThrowIfFailed(m_device->SetRenderState(D3DRS_FILLMODE, D3DFILLMODE::D3DFILL_WIREFRAME));

			break;
		case FILL_MODE_POINT:
			ThrowIfFailed(m_device->SetRenderState(D3DRS_FILLMODE, D3DFILLMODE::D3DFILL_POINT));

			break;
		default:
			break;
		}
	}

}



void RenderManager::UpdateVIBuffer(IRenderer * _renderer)
{
	auto viBuffer = _renderer->GetVIBuffer();
	_renderer->BindingStreamSource();
}

void RenderManager::UpdateShader(Shader * _shader)
{
	if (m_currentShader != _shader)
	{
		if (m_currentShader)
			m_currentShader->EndPass();

		m_currentShader = _shader;
		m_currentShader->BeginPass();

		ThrowIfFailed(m_device->SetVertexDeclaration(m_currentShader->GetDeclartion()));

	}
}

void RenderManager::SetWindowSize(UINT _x, UINT _y)
{
	m_wincx = _x;
	m_wincy = _y;
}

Camera * RenderManager::GetMainCamera()
{
	if (m_cameraList.size() > 0)
		return m_cameraList.front();
	return nullptr;
}

void RenderManager::DeleteCamera(Camera * _cam)
{
	if (!m_device)
		return;

	if (m_cameraList.size() == 0)
		return;

	for (auto iter = m_cameraList.begin(); iter != m_cameraList.end(); ++iter)
	{
		if ((*iter) == _cam)
		{
			//(*iter) = nullptr;
			m_cameraList.erase(iter);
			return;
		}
	}
}
