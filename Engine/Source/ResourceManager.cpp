#include "..\Include\ResourceManager.h"
#include "Quad.h"
#include "Triangle.h"
#include "LineVI.h"
#include "QuadNoneNormal.h"
#include "Box.h"
#include "Sphere.h"
#include "Plane.h"
#include "ObjMesh.h"
#include "SkyBox.h"
#include "DepthStencil.h"
#include "RenderManager.h"
#include "GroundVIBuffer.h"
#include "ParticleInfo.h"
#include "TBox.h"
#include "Core.h"
#include "StaticMesh.h"
#include "ScreenQuad.h"
#include "AudioClip.h"

USING(Nalmak)
IMPLEMENT_SINGLETON(ResourceManager)
ResourceManager::ResourceManager()
{
}


ResourceManager::~ResourceManager()
{
	Release();
}

HRESULT ResourceManager::Initialize(const wstring& _path)
{
	m_directoryPath = _path;

	//LoadMeshes<FBXLoader>(L"fbx");

	LoadResources<VIBuffer,ObjMesh>(L"obj");
	LoadResources<StaticMesh, StaticMesh>(L"X");
	LoadResources<AudioClip, AudioClip>(L"aud");

	LoadTextures(L"jpg");
	LoadTextures(L"png");
	LoadTextures(L"dds");

	LoadResources<RenderTarget, RenderTarget>(L"rtd");
	LoadResources<DepthStencil, DepthStencil>(L"dsd");
	LoadResources<Shader, Shader>(L"sd");
	LoadResources<Material, Material>(L"mtrl");
	LoadResources<ParticleInfo, ParticleInfo>(L"ptd");

	// Font
	AddFontResource(L"../../Resource/Font/Selected/Astrolab.ttf");

	AddFontResource(L"../../Resource/Font/Selected/Optimus.otf");
	AddFontResource(L"../../Resource/Font/Selected/earthorbiter.ttf");

	//AddFontResource(L"../../Resource/Font/Selected/bladesingercond.ttf");
	//AddFontResource(L"../../Resource/Font/Selected/DS-DIGI.otf");
	//AddFontResource(L"../../Resource/Font/Selected/PCap Terminal Condensed.TTF");
	return S_OK;
}

HRESULT ResourceManager::Release()
{
	for (auto& resources : m_resoucreContainers)
	{
		for (auto& resource : resources.second)
		{
			resource.second->Release();
			SAFE_DELETE(resource.second);
		}
		resources.second.clear();
	}
	m_resoucreContainers.clear();


	// Font
	RemoveFontResource(L"../../Resource/Font/Selected/Astrolab.ttf");
	//RemoveFontResource(L"../../Resource/Font/Selected/bladesingercond.ttf");
	//RemoveFontResource(L"../../Resource/Font/Selected/DS-DIGI.otf");
	//RemoveFontResource(L"../../Resource/Font/Selected/PCap Terminal Condensed.TTF");
	return S_OK;
}

void ResourceManager::SetShaderInfo(const wstring& _shaderName, D3DPRIMITIVETYPE _primitive, D3DVERTEXELEMENT9 * _decl, UINT _inputLayoutSize)
{
	Shader* shader = GetResource<Shader>(_shaderName);
	shader->SetInputLayout(_primitive, _decl, _inputLayoutSize);
}



void ResourceManager::CreateDefaultResource()
{
	CreateDefaultMesh();
}





void ResourceManager::CreateDefaultMesh()
{
	{
		VIBuffer* mesh = new Quad();
		assert("Fail to Create Mesh!" && mesh);
		mesh->OnInitialize();
		m_resoucreContainers[typeid(VIBuffer).name()][L"quad"] = mesh;
	}
	{
		VIBuffer* mesh = new ScreenQuad();
		assert("Fail to Create Mesh!" && mesh);
		mesh->OnInitialize();
		m_resoucreContainers[typeid(VIBuffer).name()][L"screenQuad"] = mesh;
	}
	{
		VIBuffer* mesh = new GroundVIBuffer();
		assert("Fail to Create Mesh!" && mesh);
		mesh->OnInitialize();
		m_resoucreContainers[typeid(VIBuffer).name()][L"ground"] = mesh;
	}
	{
		VIBuffer* mesh = new Triangle();
		assert("Fail to Create Mesh!" && mesh);
		mesh->OnInitialize();
		m_resoucreContainers[typeid(VIBuffer).name()][L"triangle"] = mesh;
	}
	{
		VIBuffer* mesh = new SkyBox();
		assert("Fail to Create Mesh!" && mesh);
		mesh->OnInitialize();
		m_resoucreContainers[typeid(VIBuffer).name()][L"skyBox"] = mesh;
	}

	{
		VIBuffer* mesh = new LineVI();
		assert("Fail to Create Mesh!" && mesh);
		mesh->OnInitialize();
		m_resoucreContainers[typeid(VIBuffer).name()][L"line"] = mesh;
	}
	{
		VIBuffer* mesh = new QuadNoneNormal();
		assert("Fail to Create Mesh!" && mesh);
		mesh->OnInitialize();
		m_resoucreContainers[typeid(VIBuffer).name()][L"quadNoneNormal"] = mesh;
	}
	{
		VIBuffer* mesh = new Box();
		assert("Fail to Create Mesh!" && mesh);
		mesh->OnInitialize();
		m_resoucreContainers[typeid(VIBuffer).name()][L"box"] = mesh;
	}
	{
		VIBuffer* mesh = new TBox();
		assert("Fail to Create Mesh!" && mesh);
		mesh->OnInitialize();
		m_resoucreContainers[typeid(VIBuffer).name()][L"Tbox"] = mesh;
	}
	{
		VIBuffer* mesh = new Sphere();
		assert("Fail to Create Mesh!" && mesh);
		mesh->OnInitialize();
		m_resoucreContainers[typeid(VIBuffer).name()][L"sphere"] = mesh;
	}
	{
		VIBuffer* mesh = new Plane();
		assert("Fail to Create Mesh!" && mesh);
		mesh->OnInitialize();
		m_resoucreContainers[typeid(VIBuffer).name()][L"plane"] = mesh;
	}

}

void ResourceManager::CreateDefaultShader()
{
	
}






void ResourceManager::UpdateMaterial()
{

	list<wstring> filePaths;
	FileIO::SearchingDir(&filePaths, m_directoryPath.c_str(), L"mtrl");

	for (auto& file : filePaths)
	{
		wstring filePath = file;
		wstring fileName = filePath.substr(filePath.find_last_of(L"/") + 1);
		size_t targetNum = fileName.find_last_of(L".");
		fileName = fileName.substr(0, targetNum);

		if (m_resoucreContainers[typeid(Material).name()][fileName])
		{
			Material material;
			material.Initialize(filePath);
			Material* existingMtrl = (Material*)m_resoucreContainers[typeid(Material).name()][fileName];
			*existingMtrl = material;
			existingMtrl->m_name = fileName;
		}
		else
		{
			Material* resource = new Material();

			assert("Fail to Create Resource!" && resource);
			resource->Initialize(filePath);
			m_resoucreContainers[typeid(Material).name()][fileName] = resource;
			((IResource*)resource)->m_name = fileName;
		}


	}
}

void ResourceManager::LoadTextures(const TCHAR * _extention)
{

	list<wstring> filePaths;
	FileIO::SearchingDir(&filePaths, m_directoryPath.c_str(), _extention);

	for (auto& file : filePaths)
	{
		wstring filePath = file;
		wstring fileName = filePath.substr(filePath.find_last_of(L"/") + 1);
		size_t targetNum = fileName.find_last_of(L".");
		fileName = fileName.substr(0, targetNum);



		targetNum = fileName.find_last_of(L"_");
		if (targetNum != -1)
		{
			wstring fileIndex = fileName.substr(targetNum + 1, fileName.length());

			int texIndex = 0;
			if (Nalmak_String::IsDigitString(&texIndex, fileIndex))
			{
				fileName = fileName.substr(0, targetNum);

				Texture* tex = (Texture*)m_resoucreContainers[typeid(Texture).name()][fileName];
				if (!tex)
				{
					tex = new Texture;
					m_resoucreContainers[typeid(Texture).name()][fileName] = tex;
				}
				tex->Initialize(filePath.c_str());

			}
			else
			{
				if (m_resoucreContainers[typeid(Texture).name()][fileName])
				{
					MessageBox(NULL, (L"Resource is already exist! " + filePath).c_str(), NULL, MB_OK);
				}
				Texture* tex = new Texture();
				assert("Fail to Create Resource!" && tex);
				tex->Initialize(filePath.c_str());
				m_resoucreContainers[typeid(Texture).name()][fileName] = tex;
			}
		}
		else
		{
			if (m_resoucreContainers[typeid(Texture).name()][fileName])
			{
				MessageBox(NULL, (L"Resource is already exist! " + filePath).c_str(), NULL, MB_OK);
			}
			Texture* tex = new Texture();
			assert("Fail to Create Resource!" && tex);
			tex->Initialize(filePath.c_str());
			m_resoucreContainers[typeid(Texture).name()][fileName] = tex;
		}


	}
}

