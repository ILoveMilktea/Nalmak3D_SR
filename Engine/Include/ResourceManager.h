#pragma once

#ifndef __RESOURCEMANAGER_H__
#define __RESOURCEMANAGER_H__

#include "Nalmak_Include.h"
#include "Shader.h"
#include "Texture.h"
#include "VIBuffer.h"
#include "Material.h"
#include "RenderTarget.h"
#include "IResource.h"

BEGIN(Nalmak)
class NALMAK_DLL ResourceManager
{
	DECLARE_SINGLETON(ResourceManager)
private:
	ResourceManager();
	~ResourceManager();
public:
	HRESULT Initialize(const wstring& _path);
	HRESULT Release();

	void SetShaderInfo(const wstring& _shaderName, D3DPRIMITIVETYPE _primitive, D3DVERTEXELEMENT9* _decl, UINT _inputLayoutSize);
	template<typename T>
	T* GetResource(const wstring& _name)
	{
		IResource* resource = m_resoucreContainers[typeid(T).name()][_name];
		
#ifdef _DEBUG
		if (!resource)
		{
			ERR_MSG((L"Resource with that name '" + _name + L"' does not exist").c_str());
			assert(0);
		}
#endif // DEBUG


		return (T*)resource;
	}

private:
	unordered_map<string, unordered_map<wstring, IResource*>> m_resoucreContainers;


	typedef unordered_map<string, unordered_map<wstring, IResource*>> RESOURCES;

private:
	wstring m_directoryPath;


public:
	void CreateDefaultResource();
private:
	void CreateDefaultMesh();
	void CreateDefaultShader();

public:
	void UpdateMaterial(); // Material 데이터 다시 쓰기
	void LoadTextures(const TCHAR* _extention);
private:

private:
	template <typename TYPE, typename T>
	void LoadResources(const TCHAR* _extention)
	{
		list<wstring> filePaths;
		FileIO::SearchingDir(&filePaths, m_directoryPath.c_str(), _extention);

		for (auto& file : filePaths)
		{
			wstring filePath = file;
			wstring fileName = filePath.substr(filePath.find_last_of(L"/") + 1);
			size_t targetNum = fileName.find_last_of(L".");
			fileName = fileName.substr(0, targetNum);

			if (m_resoucreContainers[typeid(TYPE).name()][fileName])
			{
				MessageBox(NULL, (L"Resource is already exist! " + filePath).c_str(), NULL, MB_OK);
				assert(0);
			}

			TYPE* resource = new T();

			assert("Fail to Create Resource!" && resource);
			resource->Initialize(filePath);
			m_resoucreContainers[typeid(TYPE).name()][fileName] = resource;
			((IResource*)resource)->m_name = fileName;

		}
	}
	
public:
	template<typename T>
	void AddResource(const wstring& _name, const T& _resource)
	{
		if (m_resoucreContainers[typeid(T).name()].find(_name) == m_resoucreContainers[typeid(T).name()].end())
		{
			T* resource = new T();
			*resource = _resource;
			m_resoucreContainers[typeid(T).name()][_name] = resource;
		}
		else
		{
			MessageBox(NULL, (L"Resource is already created by '" + _name + L"'").c_str(), NULL, MB_OK);
		}

	}
	template<typename T>
	void AddResource(const wstring& _name, T* _buffer)
	{
		if (m_resoucreContainers[typeid(T).name()].find(_name) == m_resoucreContainers[typeid(T).name()].end())
		{
			m_resoucreContainers[typeid(T).name()][_name] = _buffer;
		}
		else
		{
			MessageBox(NULL, (L"Resource is already created by '" + _name + L"'").c_str(), NULL, MB_OK);
		}
	}
public:
	template<typename T>
	unordered_map<wstring, IResource* >& GetAllResource()
	{
		return m_resoucreContainers[typeid(T).name()];
	}
public:
	const wstring& GetResourceDirectoryPath() { return m_directoryPath; }
};
END
#endif
