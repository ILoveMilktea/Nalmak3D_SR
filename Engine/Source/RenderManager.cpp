﻿#include "RenderManager.h"
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
#include "DepthStencil.h"
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

	m_blendingMode = BLENDING_MODE_MAX;

	m_currentMaterial = nullptr;
	m_currentShader = nullptr;

	m_cameraList.clear();

	for (int i = 0; i < 4; ++i)
		m_currentRenderTarget[i] = nullptr;

	D3DVIEWPORT9 vp = { 0,0,m_wincx,m_wincy,0,1 };
	m_device->SetViewport(&vp);

	m_imageVIBuffer = ResourceManager::GetInstance()->GetResource<VIBuffer>(L"quadNoneNormal");
	m_fullScreenMtrl = ResourceManager::GetInstance()->GetResource<Material>(L"FullScreen");
}

void RenderManager::Render()
{
	assert(L"Please Set Camera at least one" &&m_cameraList.size());

	ThrowIfFailed(m_device->Clear(0, NULL,  D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,0, 1, 0));

	for (auto& cam : m_cameraList)
	{
		if (cam->GetActive())
		{
			Render(cam);
		}
	}
	ThrowIfFailed(m_device->Present(nullptr, nullptr, 0, nullptr));


	Reset();
}

void RenderManager::Render(Camera * _cam)
{
	///////////////////////////////////////////////////////
	// public const buffer
	ConstantBuffer cBuffer;
	Matrix view = _cam->GetViewMatrix();
	Matrix proj = _cam->GetProjMatrix();
	Matrix invView;
	D3DXMatrixInverse(&invView, nullptr, &view);
	//D3DXMatrixTranspose(&invView, &invView);
	Matrix invProj;
	D3DXMatrixInverse(&invProj, nullptr, &proj);
	//D3DXMatrixTranspose(&invProj, &invProj);

	Matrix worldCamMatrix = _cam->GetTransform()->GetWorldMatrix();
	cBuffer.viewProj = view * proj;
	cBuffer.worldCamPos = Vector3(worldCamMatrix._41, worldCamMatrix._42, worldCamMatrix._43);
	cBuffer.worldCamLook = Vector3(worldCamMatrix._31, worldCamMatrix._32, worldCamMatrix._33);

	cBuffer.invView = invView;
	cBuffer.invProj = invProj;

	////////////////////////////////////////////////////////
	ThrowIfFailed(m_device->BeginScene());
	DeferredRender(_cam, cBuffer);
	ThrowIfFailed(m_device->EndScene());


}

void RenderManager::DeferredRender(Camera* _cam, ConstantBuffer& _cBuffer)
{
	ClearRenderTarget(L"GBuffer_Diffuse");
	ClearRenderTarget(L"GBuffer_Normal");
	ClearRenderTarget(L"GBuffer_Depth");
	ClearRenderTarget(L"GBuffer_CookTorrance");
	ClearRenderTarget(L"GBuffer_Light");
	ClearRenderTarget(L"GBuffer_Shade");
	ClearRenderTarget(L"GBuffer_Debug");
	ClearRenderTarget(L"GBuffer_Transparent");
	ClearDepthStencil(L"Stencil_Transparent");

	SkyboxPass(_cBuffer);

	GBufferPass(_cam, _cBuffer);


	LightPass(_cam,_cBuffer);

	ShadePass(_cBuffer);



	DebugPass(_cBuffer);

	RenderImageToScreen(m_resourceManager->GetResource<RenderTarget>(L"GBuffer_Shade")->GetTexture(), _cBuffer); // 원래화면에 띄워줌

	TransparentPass(_cam, _cBuffer);

	UIPass(_cam, _cBuffer);
}

void RenderManager::SkyboxPass(ConstantBuffer & _cBuffer)
{
	if (!m_lightManager->IsSkyBoxRender())
		return;

	ThrowIfFailed(m_device->SetRenderState(D3DRS_ALPHABLENDENABLE, false));
	ThrowIfFailed(m_device->SetRenderState(D3DRS_ALPHATESTENABLE, false));

	m_currentShader = nullptr;
	m_currentMaterial = nullptr;

	auto viBuffer = m_lightManager->GetSkyboxVIBuffer();

	UpdateMaterial(m_lightManager->GetSkyboxMaterial(), _cBuffer);
	UpdateRenderTarget();

	ThrowIfFailed(m_device->SetStreamSource(0, viBuffer->GetVertexBuffer(), 0, sizeof(INPUT_LAYOUT_SKYBOX)));
	ThrowIfFailed(m_device->SetIndices(viBuffer->GetIndexBuffer()));

	DirectionalLightInfo info;
	if (m_lightManager->GetDirectionalLightInfo(info))
	{
		m_currentShader->SetValue("g_directionalLight", &info, sizeof(DirectionalLightInfo));
	}
	else
	{
		m_currentShader->SetValue("g_directionalLight", &DirectionalLightInfo(), sizeof(DirectionalLightInfo));
	}

	m_currentShader->CommitChanges();
	ThrowIfFailed(m_device->DrawIndexedPrimitive(m_currentShader->GetPrimitiveType(), 0, 0, viBuffer->GetVertexCount(), 0, viBuffer->GetFigureCount()));

	if (m_currentShader)
	{
		m_currentShader->EndPass();
		EndRenderTarget();
	}
}

void RenderManager::GBufferPass(Camera * _cam, ConstantBuffer& _cBuffer)
{


	SkyboxPass(_cBuffer);

	ThrowIfFailed(m_device->SetRenderState(D3DRS_ZWRITEENABLE, false));

	RenderNoneAlpha(_cam, _cBuffer, RENDERING_MODE_BACKGROUND);

	ThrowIfFailed(m_device->SetRenderState(D3DRS_ZWRITEENABLE, true));

	RenderNoneAlpha(_cam, _cBuffer, RENDERING_MODE_OPAQUE);


	ThrowIfFailed(m_device->SetRenderState(D3DRS_ALPHATESTENABLE, true));
	ThrowIfFailed(m_device->SetRenderState(D3DRS_ALPHAREF, 50));
	ThrowIfFailed(m_device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER));

	RenderNoneAlpha(_cam, _cBuffer, RENDERING_MODE_CUTOUT);

	ThrowIfFailed(m_device->SetRenderState(D3DRS_ALPHATESTENABLE, false));


	EndRenderTarget();
}

void RenderManager::LightPass(Camera* _cam, ConstantBuffer& _cBuffer)
{

	DirectionalLightPass(_cBuffer);

	PointLightPass(_cam,_cBuffer);


}

void RenderManager::PointLightPass(Camera* _cam, ConstantBuffer & _cBuffer)
{
	int count = (int)m_lightManager->GetPointLightCount();
	if (count == 0)
		return;

	VIBuffer* viBuffer = m_resourceManager->GetResource<VIBuffer>(L"sphere");
	Material* mtrlStencilLight = m_resourceManager->GetResource<Material>(L"PointLight_Stencil");
	Material* mtrlLight = m_resourceManager->GetResource<Material>(L"PointLight");

	mtrlStencilLight->SetDataToShader();
	mtrlLight->SetDataToShader();

	ThrowIfFailed(m_device->SetRenderState(D3DRS_STENCILENABLE, true));
	ThrowIfFailed(m_device->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP::D3DSTENCILOP_KEEP));
	ThrowIfFailed(m_device->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP::D3DSTENCILOP_DECR));
	ThrowIfFailed(m_device->SetRenderState(D3DRS_CCW_STENCILPASS, D3DSTENCILOP::D3DSTENCILOP_KEEP));
	ThrowIfFailed(m_device->SetRenderState(D3DRS_CCW_STENCILZFAIL, D3DSTENCILOP::D3DSTENCILOP_INCR));

	ThrowIfFailed(m_device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP::D3DBLENDOP_ADD));
	ThrowIfFailed(m_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND::D3DBLEND_ONE));
	ThrowIfFailed(m_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND::D3DBLEND_ONE));

	ThrowIfFailed(m_device->SetRenderState(D3DRS_FILLMODE, D3DFILLMODE::D3DFILL_SOLID));

	ThrowIfFailed(m_device->SetStreamSource(0, viBuffer->GetVertexBuffer(), 0, sizeof(INPUT_LAYOUT_POSITION_NORMAL_UV)));
	ThrowIfFailed(m_device->SetIndices(viBuffer->GetIndexBuffer()));

	m_currentShader = nullptr;
	m_currentMaterial = nullptr;

	for (int i = 0; i < count; ++i)
	{
		auto pointLight = m_lightManager->GetPointLight(i);

		Matrix world;
		Vector3 pos = pointLight->GetTransform()->GetWorldPosition();
		float scale = pointLight->GetRadius() * 2;
		pointLight->SetLightPosition(pos);

		Matrix matTrs, matScale;
		D3DXMatrixTranslation(&matTrs, pos.x, pos.y, pos.z);
		D3DXMatrixScaling(&matScale, scale, scale, scale);
		world = matScale * matTrs;

		if (_cam->IsInFrustumCulling(pos, scale))
		{
			PointLightPass(world, pointLight->GetLightInfo(), viBuffer, _cBuffer, mtrlStencilLight, mtrlLight);
			m_device->Clear(0, nullptr, D3DCLEAR_STENCIL, 0, 1, 0);
		}
	}
	if(m_currentShader)
		m_currentShader->EndPass();

	ThrowIfFailed(m_device->SetRenderState(D3DRS_ALPHABLENDENABLE, false));
	ThrowIfFailed(m_device->SetRenderState(D3DRS_STENCILENABLE, false));
	ThrowIfFailed(m_device->SetRenderState(D3DRS_ZENABLE, true));
	ThrowIfFailed(m_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW));
}

void RenderManager::PointLightPass(const Matrix& _matWorld, PointLightInfo _lightInfo, VIBuffer* _viBuffer, ConstantBuffer & _cBuffer, Material* _mtrlStencilLight, Material* _mtrlLight)
{
	ThrowIfFailed(m_device->SetRenderState(D3DRS_ALPHABLENDENABLE, false));

	UpdateShader(_mtrlStencilLight->GetShader(), _cBuffer);

	UpdateRenderTarget();

	m_device->SetRenderState(D3DRS_ZENABLE, true);
	m_device->SetRenderState(D3DRS_ZWRITEENABLE, false);
	m_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	m_device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
	m_device->SetRenderState(D3DRS_TWOSIDEDSTENCILMODE, true);

	m_currentShader->SetMatrix("g_world", _matWorld);
	m_currentShader->CommitChanges();
	ThrowIfFailed(m_device->DrawIndexedPrimitive(m_currentShader->GetPrimitiveType(), 0, 0, _viBuffer->GetVertexCount(), 0, _viBuffer->GetFigureCount()));


	EndRenderTarget();

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	ThrowIfFailed(m_device->SetRenderState(D3DRS_ALPHABLENDENABLE, true));

	UpdateShader(_mtrlLight->GetShader(), _cBuffer);

	UpdateRenderTarget();

	m_device->SetRenderState(D3DRS_ZENABLE, false);
	m_device->SetRenderState(D3DRS_ZWRITEENABLE, true);
	m_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	m_device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_NOTEQUAL);
	m_device->SetRenderState(D3DRS_STENCILREF, 0);

	m_device->SetRenderState(D3DRS_TWOSIDEDSTENCILMODE, false);

	m_currentShader->SetValue("g_pointLight", &_lightInfo, sizeof(PointLightInfo));
	m_currentShader->SetMatrix("g_world", _matWorld);

	m_currentShader->CommitChanges();
	ThrowIfFailed(m_device->DrawIndexedPrimitive(m_currentShader->GetPrimitiveType(), 0, 0, _viBuffer->GetVertexCount(), 0, _viBuffer->GetFigureCount()));


	EndRenderTarget();
}

void RenderManager::ShadePass(ConstantBuffer & _cBuffer)
{

	//RecordDepthStencil(L"Stencil_Transparent");

	ThrowIfFailed(m_device->SetRenderState(D3DRS_STENCILENABLE, true));
	ThrowIfFailed(m_device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL));
	ThrowIfFailed(m_device->SetRenderState(D3DRS_STENCILREF, 0)); // 1과 같을때 통과

	Material* material = m_resourceManager->GetResource<Material>(L"GBuffer_Shade");
	RenderByMaterialToScreen(material, _cBuffer);

	ThrowIfFailed(m_device->SetRenderState(D3DRS_STENCILENABLE, false));
	ThrowIfFailed(m_device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS));

	//EndDepthStencil(L"Stencil_Transparent");
}

void RenderManager::DebugPass(ConstantBuffer & _cBuffer)
{
	Material* material = m_resourceManager->GetResource<Material>(L"GBuffer_Debug");
	RenderByMaterialToScreen(material, _cBuffer);
}


void RenderManager::DirectionalLightPass(ConstantBuffer& _cBuffer)
{
	DirectionalLightInfo info;
	if (!m_lightManager->GetDirectionalLightInfo(info))
		return;
	Material* material = m_resourceManager->GetResource<Material>(L"DirectionalLight");
	material->SetValue("g_directionalLight", &info, sizeof(DirectionalLightInfo));


	RenderByMaterialToScreen(material, _cBuffer);
}

void RenderManager::TransparentPass(Camera* _cam, ConstantBuffer& _cBuffer)
{
	m_currentShader = nullptr;
	m_currentMaterial = nullptr;

	//RecordRenderTarget(0, L"GBuffer_Transparent");

	ThrowIfFailed(m_device->SetRenderState(D3DRS_ALPHABLENDENABLE, true));
	ThrowIfFailed(m_device->SetRenderState(D3DRS_ZWRITEENABLE, false));
	ThrowIfFailed(m_device->SetRenderState(D3DRS_ZENABLE, true));


	for (auto& renderList : m_renderLists[RENDERING_MODE_TRANSPARENT])
	{
		for (auto& renderer : renderList.second)
		{
			if (_cam->CompareLayer(renderer->GetLayer()))
			{
				if (_cam->IsInFrustumCulling(renderer))
				{
					renderer->BindingStreamSource();
					for (int i = 0; i < renderer->GetMaterialCount(); ++i)
					{
						Material* material = renderer->GetMaterial(i);
						UpdateMaterial(material, _cBuffer);

						renderer->Render(m_currentShader, i);
					}
				}
			}
		}
	}

	if (m_currentShader)
	{
		m_currentShader->EndPass();
	}

	ThrowIfFailed(m_device->SetRenderState(D3DRS_ALPHABLENDENABLE, false));
	ThrowIfFailed(m_device->SetRenderState(D3DRS_ZWRITEENABLE, true));

	//EndRenderTarget(L"GBuffer_Transparent");
}

void RenderManager::UIPass(Camera * _cam, ConstantBuffer & _cBuffer)
{

	m_currentShader = nullptr;
	m_currentMaterial = nullptr;

	ThrowIfFailed(m_device->SetRenderState(D3DRS_ZENABLE, false));
	ThrowIfFailed(m_device->SetRenderState(D3DRS_ALPHABLENDENABLE, true));


	for (auto& renderer : m_renderUILists)
	{
		if (_cam->CompareLayer(renderer->GetLayer()))
		{
			if (_cam->IsInFrustumCulling(renderer))
			{
				renderer->BindingStreamSource();

				Material* material = renderer->GetMaterial();
				UpdateMaterial(material, _cBuffer);

				renderer->Render(m_currentShader, 0);
			}
		}
	}

	if (m_currentShader)
	{
		m_currentShader->EndPass();
	}

	ThrowIfFailed(m_device->SetRenderState(D3DRS_ALPHABLENDENABLE, false));
	ThrowIfFailed(m_device->SetRenderState(D3DRS_ZENABLE, true));
}

void RenderManager::RenderNoneAlpha(Camera * _cam, ConstantBuffer & _cBuffer, RENDERING_MODE _mode)
{
	m_currentShader = nullptr;
	m_currentMaterial = nullptr;

	for (auto& MeshRendererList : m_renderLists[_mode])
	{
		for (auto& renderer : MeshRendererList.second)
		{
			if (_cam->CompareLayer(renderer->GetLayer()))
			{
				if (_cam->IsInFrustumCulling(renderer))
				{
					renderer->BindingStreamSource();

					for (int i = 0; i < renderer->GetMaterialCount(); ++i)
					{
						Material* material = renderer->GetMaterial(i);
						UpdateMaterial(material, _cBuffer);
						UpdateRenderTarget();
						renderer->Render(m_currentShader, i);
					}
				}
			}
		}
	}

	if (m_currentShader)
	{
		m_currentShader->EndPass();
	}
}

void RenderManager::Reset()
{
	m_currentMaterial = nullptr;

	for(int i = 0 ; i < RENDERING_MODE_MAX; ++i)
	for (auto& renderList : m_renderLists[i])
	{
		renderList.second.clear();
	}
	m_renderUILists.clear();

	m_debugManager->EraseTheRecord();
}

void RenderManager::RenderByMaterialToScreen(Material* _mtrl, ConstantBuffer & _cBuffer)
{
	m_currentMaterial = nullptr;
	m_currentShader = nullptr;

	UpdateMaterial(_mtrl, _cBuffer);
	UpdateRenderTarget();

	Matrix mat;
	D3DXMatrixScaling(&mat, 2, 2, 2);
	m_currentShader->SetMatrix("g_world", mat);

	ThrowIfFailed(m_device->SetRenderState(D3DRS_ZWRITEENABLE, false));

	ThrowIfFailed(m_device->SetStreamSource(0, m_imageVIBuffer->GetVertexBuffer(), 0,  sizeof(INPUT_LAYOUT_POSITION_UV)));
	ThrowIfFailed(m_device->SetIndices(m_imageVIBuffer->GetIndexBuffer()));

	m_currentShader->CommitChanges();
	ThrowIfFailed(m_device->DrawIndexedPrimitive(m_currentShader->GetPrimitiveType(), 0, 0, m_imageVIBuffer->GetVertexCount(), 0, m_imageVIBuffer->GetFigureCount()));

	ThrowIfFailed(m_device->SetRenderState(D3DRS_ZWRITEENABLE, true));
	m_currentShader->EndPass();
	EndRenderTarget();


}


void RenderManager::RenderImageToScreen(IDirect3DBaseTexture9 * _tex, ConstantBuffer & _cBuffer)
{
	m_currentShader = nullptr;
	m_currentMaterial = nullptr;

	UpdateMaterial(m_fullScreenMtrl, _cBuffer);
	m_currentShader->SetTexture("g_mainTex", _tex);
	Matrix mat;
	D3DXMatrixScaling(&mat, 2, 2, 2);
	m_currentShader->SetMatrix("g_world", mat);

	ThrowIfFailed(m_device->SetRenderState(D3DRS_ZWRITEENABLE, false));

	ThrowIfFailed(m_device->SetStreamSource(0, m_imageVIBuffer->GetVertexBuffer(), 0, sizeof(INPUT_LAYOUT_POSITION_UV)));
	ThrowIfFailed(m_device->SetIndices(m_imageVIBuffer->GetIndexBuffer()));

	m_currentShader->CommitChanges();
	ThrowIfFailed(m_device->DrawIndexedPrimitive(m_currentShader->GetPrimitiveType(), 0, 0, m_imageVIBuffer->GetVertexCount(), 0, m_imageVIBuffer->GetFigureCount()));

	if (m_currentShader)
	{
		m_currentShader->EndPass();
	}
	ThrowIfFailed(m_device->SetRenderState(D3DRS_ZWRITEENABLE, true));

}



void RenderManager::RenderRequest(IRenderer * _render)
{
	auto mtrl = _render->GetMaterial();
	if (_render->GetType() == RENDERER_TYPE::RENDERER_TYPE_CANVAS)
		m_renderUILists.emplace_back(_render);
	else
		m_renderLists[mtrl->GetRenderingMode()][mtrl->GetRenderQueue()].emplace_back(_render);

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


void RenderManager::UpdateMaterial(Material * _material, ConstantBuffer & _cBuffer)
{
	if (m_currentMaterial != _material)
	{
		m_currentMaterial = _material;

		UpdateBlendingMode(_material);
		UpdateFillMode(_material);
		_material->SetDataToShader();

		UpdateShader(m_currentMaterial->GetShader(), _cBuffer);
	}
}

void RenderManager::UpdateNoneAlphaMaterial(Material * _material, ConstantBuffer & _cBuffer)
{
	if (m_currentMaterial != _material)
	{
		m_currentMaterial = _material;

		UpdateFillMode(_material);
		_material->SetDataToShader();

		UpdateShader(m_currentMaterial->GetShader(), _cBuffer);
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
			ThrowIfFailed(m_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND::D3DBLEND_SRCALPHA));
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
			ThrowIfFailed(m_device->SetRenderState(D3DRS_FILLMODE, D3DFILLMODE::D3DFILL_SOLID));
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



void RenderManager::UpdateRenderTarget()
{

	for (int i = 0; i < 4; ++i)
	{
		RenderTarget* newRendertarget = m_currentShader->GetRenderTarget(i);

		if (!newRendertarget)
			return;

		if (m_currentRenderTarget[i] != newRendertarget)
		{
			if (m_currentRenderTarget[i])
				m_currentRenderTarget[i]->EndRecord();

			m_currentRenderTarget[i] = newRendertarget;
			m_currentRenderTarget[i]->StartRecord(i);
		}
	}
}

void RenderManager::EndRenderTarget()
{
	for (int i = 0; i < 4; ++i)
	{
		if (m_currentRenderTarget[i])
		{
			m_currentRenderTarget[i]->EndRecord();
			m_currentRenderTarget[i] = nullptr;
		}
		else
		{
			return;
		}
	}
}

void RenderManager::UpdateShader(Shader * _shader, ConstantBuffer& _cBuffer)
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

void RenderManager::RecordDepthStencil(const wstring & _name)
{
	m_resourceManager->GetResource<DepthStencil>(_name)->StartRecord();
}

void RenderManager::EndDepthStencil(const wstring & _name)
{
	m_resourceManager->GetResource<DepthStencil>(_name)->EndRecord();
}

void RenderManager::SetWindowSize(UINT _x, UINT _y)
{
	m_wincx = _x;
	m_wincy = _y;

	m_halfWincx = (UINT)(m_wincx * 0.5f);
	m_halfWincy = (UINT)(m_wincy * 0.5f);
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
	m_resourceManager->GetResource<RenderTarget>(_targetName)->Clear();
}

void RenderManager::ClearDepthStencil(const wstring & _targetName)
{
	m_resourceManager->GetResource<DepthStencil>(_targetName)->Clear();
}
