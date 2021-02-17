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
#include "MeshRenderer.h"
#include "LightManager.h"
#include "PointLight.h"
#include "Transform.h"

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

void RenderManager::Initialize()
{
	m_device = DeviceManager::GetInstance()->GetDevice();
	m_debugManager = DebugManager::GetInstance();
	m_lightManager = LightManager::GetInstance();
	m_resourceManager = ResourceManager::GetInstance();

	m_renderingMode = RENDERING_MODE_MAX;
	m_blendingMode = BLENDING_MODE_MAX;
	
	m_currentMaterial = nullptr;
	m_currentShader = nullptr;
	m_currentVIBuffer = nullptr;

	m_cameraList.clear();

	m_halfWincx = (UINT)(m_wincx * 0.5f);
	m_halfWincy = (UINT)(m_wincy * 0.5f);

	D3DVIEWPORT9 vp = { 0,0,m_wincx,m_wincy,0,1 };
	m_device->SetViewport(&vp);

	m_imageVIBuffer = ResourceManager::GetInstance()->GetResource<VIBuffer>(L"quadNoneNormal");
	m_currentUIMaterial = ResourceManager::GetInstance()->GetResource<Material>(L"defaultUI");
}

void RenderManager::Render()
{

	ThrowIfFailed(m_device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, m_cameraList.front()->m_clearColor, 1, 0));

	for (auto& cam : m_cameraList)
	{
		if (cam->GetActive())
		{
			Render(cam);

		}
	}
	RenderText();
	ThrowIfFailed(m_device->Present(nullptr, nullptr, 0, nullptr));

	for (auto& renderList : m_renderOpaqueLists)
		renderList.second.clear();

}

void RenderManager::Render(Camera * _cam)
{
	
	///////////////////////////////////////////////////////
	// 공용 상수버퍼
	ConstantBuffer cBuffer;

	cBuffer.viewProj = _cam->GetViewMatrix() * _cam->GetProjMatrix();
	cBuffer.worldCamPos = _cam->GetTransform()->GetWorldPosition();
	cBuffer.wincx = m_wincx;
	cBuffer.wincy = m_wincy;

	DirectionalLightInfo info;
	if (m_lightManager->GetDirectionalLightInfo(info))
	{
		cBuffer.isDirectionalLight = 1;
		cBuffer.directionalLight = info;
	}
	else
	{
		cBuffer.isDirectionalLight = 0;
	}
	////////////////////////////////////////////////////////
	DeferredRender(_cam, cBuffer);


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
	for (auto& renderList : m_renderOpaqueLists)
		renderList.second.clear();
	for (auto& renderList : m_renderTransparentLists)
		renderList.second.clear();
}

void RenderManager::DeferredRender(Camera * _cam, ConstantBuffer& _cBuffer)
{
	GBufferPass(_cam, _cBuffer);
	LightingPass(_cam, _cBuffer);
	ShadingPass(_cam, _cBuffer);

	RenderImageToScreen(m_resourceManager->GetResource<RenderTarget>(L"GBuffer_light")->GetTexture(), _cBuffer);

	TransparentPass(_cam, _cBuffer);
}

void RenderManager::GBufferPass(Camera * _cam, ConstantBuffer& _cBuffer)
{
	ClearRenderTarget(L"GBuffer_diffuse");
	ClearRenderTarget(L"GBuffer_normal");
	ClearRenderTarget(L"GBuffer_position");
	ClearRenderTarget(L"GBuffer_depthStencil");


	m_currentShader = nullptr;
	m_currentMaterial = nullptr;

	ThrowIfFailed(m_device->BeginScene());
	RecordRenderTarget(0, L"GBuffer_diffuse");
	RecordRenderTarget(1, L"GBuffer_normal");
	RecordRenderTarget(2, L"GBuffer_depthStencil");
	RecordRenderTarget(3, L"GBuffer_position");

	for (auto& MeshRendererList : m_renderOpaqueLists)
	{
		for (auto& renderer : MeshRendererList.second)
		{
			if (_cam->CompareLayer(renderer->GetLayer()))
			{
				if (_cam->IsInFrustumCulling(renderer))
				{
					Material* material = renderer->GetMaterial();
					UpdateMaterial(material);
					UpdateShader(material->GetShader(), _cBuffer);
					UpdateVIBuffer(renderer);

					renderer->Render();
				}
			}
		}
	}

	if (m_currentShader)
		m_currentShader->EndPass();


	EndRenderTarget(L"GBuffer_diffuse");
	EndRenderTarget(L"GBuffer_normal");
	EndRenderTarget(L"GBuffer_depthStencil");
	EndRenderTarget(L"GBuffer_position");

	ThrowIfFailed(m_device->EndScene());
}


void RenderManager::LightingPass(Camera * _cam, ConstantBuffer& _cBuffer)
{

	m_currentShader = nullptr;
	m_currentMaterial = nullptr;
	Material* material = m_resourceManager->GetResource<Material>(L"pointLight");
	VIBuffer* viBuffer = m_resourceManager->GetResource<VIBuffer>(L"sphere");

	ClearRenderTarget(L"GBuffer_light");
	RecordRenderTarget(0, L"GBuffer_light");

	ThrowIfFailed(m_device->BeginScene());

	UpdateMaterial(material);
	UpdateShader(material->GetShader(), _cBuffer);

	ThrowIfFailed(m_device->SetStreamSource(0, viBuffer->GetVertexBuffer(), 0, m_currentShader->GetInputLayoutSize()));
	ThrowIfFailed(m_device->SetIndices(viBuffer->GetIndexBuffer()));

	for (auto& pointLight : m_lightManager->GetPointLights())
	{
		Vector3 pos = pointLight->GetTransform()->GetWorldPosition();
		float scale = pointLight->GetRadius();
		Matrix matTrs, matScale;
		D3DXMatrixTranslation(&matTrs, pos.x, pos.y, pos.z);
		D3DXMatrixScaling(&matScale, scale, scale, scale);

		m_currentShader->SetMatrix("g_world", matScale * matTrs);

		m_currentShader->CommitChanges();
		ThrowIfFailed(m_device->DrawIndexedPrimitive(m_currentShader->GetPrimitiveType(), 0, 0, viBuffer->GetVertexCount(), 0, viBuffer->GetFigureCount()));

	}
	if (m_currentShader)
		m_currentShader->EndPass();

	EndRenderTarget(L"GBuffer_light");
	ThrowIfFailed(m_device->EndScene());

}

void RenderManager::ShadingPass(Camera * _cam, ConstantBuffer & _cBuffer)
{
	ClearRenderTarget(L"GBuffer_final");

	RecordRenderTarget(0, L"GBuffer_final");

	RenderByMaterial(L"GBuffer_final",_cBuffer);

	EndRenderTarget(L"GBuffer_final");
}

void RenderManager::TransparentPass(Camera * _cam, ConstantBuffer& _cBuffer)
{
}


void RenderManager::RenderByMaterial(const wstring & _materialName, ConstantBuffer & _cBuffer)
{
	Material* material = m_resourceManager->GetResource<Material>(_materialName);

	ThrowIfFailed(m_device->BeginScene());

	m_currentShader = nullptr;
	m_currentMaterial = nullptr;

	UpdateMaterial(material);
	UpdateShader(material->GetShader(), _cBuffer);

	Matrix mat;
	D3DXMatrixScaling(&mat, 2, 2, 2);
	m_currentShader->SetMatrix("g_world", mat);

	ThrowIfFailed(m_device->SetStreamSource(0, m_imageVIBuffer->GetVertexBuffer(), 0, m_currentShader->GetInputLayoutSize()));
	ThrowIfFailed(m_device->SetIndices(m_imageVIBuffer->GetIndexBuffer()));

	m_currentShader->CommitChanges();
	ThrowIfFailed(m_device->DrawIndexedPrimitive(m_currentShader->GetPrimitiveType(), 0, 0, m_imageVIBuffer->GetVertexCount(), 0, m_imageVIBuffer->GetFigureCount()));

	if (m_currentShader)
		m_currentShader->EndPass();

	ThrowIfFailed(m_device->EndScene());
}

void RenderManager::RenderImageToScreen(IDirect3DBaseTexture9 * _tex, ConstantBuffer & _cBuffer)
{
	m_currentShader = nullptr;
	m_currentMaterial = nullptr;

	
	ThrowIfFailed(m_device->BeginScene());

	UpdateMaterial(m_currentUIMaterial);
	UpdateShader(m_currentUIMaterial->GetShader(), _cBuffer);
	m_currentShader->SetTexture("g_mainTex", _tex);
	Matrix mat;
	D3DXMatrixScaling(&mat, 2, 2, 2);
	m_currentShader->SetMatrix("g_world", mat);

	ThrowIfFailed(m_device->SetStreamSource(0, m_imageVIBuffer->GetVertexBuffer(), 0, m_currentShader->GetInputLayoutSize()));
	ThrowIfFailed(m_device->SetIndices(m_imageVIBuffer->GetIndexBuffer()));

	m_currentShader->CommitChanges();
	ThrowIfFailed(m_device->DrawIndexedPrimitive(m_currentShader->GetPrimitiveType(), 0, 0, m_imageVIBuffer->GetVertexCount(), 0, m_imageVIBuffer->GetFigureCount()));

	if (m_currentShader)
		m_currentShader->EndPass();

	ThrowIfFailed(m_device->EndScene());
}



void RenderManager::RenderRequest(IRenderer * _render)
{
	auto mtrl = _render->GetMaterial();
	if(mtrl->GetRenderingMode() != RENDERING_MODE_TRANSPARENT)
		m_renderOpaqueLists[mtrl->GetRenderQueue()].emplace_back(_render);
	else
		m_renderTransparentLists[mtrl->GetRenderQueue()].emplace_back(_render);

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

void RenderManager::UpdateMaterial(Material * _material)
{
	if (m_currentMaterial != _material)
	{
		m_currentMaterial = _material;

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

void RenderManager::UpdateShader(Shader * _shader,ConstantBuffer& _cBuffer)
{
	if (m_currentShader != _shader)
	{
		if (m_currentShader)
			m_currentShader->EndPass();

		m_currentShader = _shader;
		m_currentShader->SetValue("g_cBuffer", &_cBuffer, sizeof(ConstantBuffer));
		m_currentShader->BeginPass();

		ThrowIfFailed(m_device->SetVertexDeclaration(m_currentShader->GetDeclartion()));

	}
}

void RenderManager::RecordRenderTarget(UINT _index, const wstring & _name)
{
	m_resourceManager->GetResource<RenderTarget>(_name)->StartRecord(_index);
}

void RenderManager::EndRenderTarget(const wstring & _name)
{
	m_resourceManager->GetResource<RenderTarget>(_name)->EndRecord();
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

void RenderManager::ClearRenderTarget(const wstring & _targetName)
{
	RenderTarget* rt = m_resourceManager->GetResource<RenderTarget>(_targetName);
	rt->StartRecord(0);
	IDirect3DSurface9* surface[3];
	for (int i = 0; i < 3; ++i)
	{
		m_device->GetRenderTarget(i + 1, &surface[i]);
		m_device->SetRenderTarget(i + 1, nullptr);
	}
	m_device->Clear(0, nullptr, D3DCLEAR_TARGET, D3DCOLOR_RGBA(0, 0, 0, 1), 0, 1);
	
	for (int i = 0; i < 3; ++i)
	{
		m_device->SetRenderTarget(i + 1, surface[i]);
	}

	rt->EndRecord();
}
