#pragma once

#ifndef __LIGHTMANAGER_H__
#define __LIGHTMANAGER_H__

#include "Nalmak_Include.h"
class DirectionalLight;
class GameObject;
class PointLight;

class LightManager
{
	DECLARE_SINGLETON(LightManager)
private:
	LightManager();
	~LightManager();
public:
	void SetSkyBox(const wstring& _skyBoxName);
	void SetDirectionalLightInfo(DirectionalLight* _light);
	void DeleteDirectionalLight();
	void DeletePointLight(PointLight* _light);
	void AddPointLight(PointLight* _light);
	bool GetDirectionalLightInfo(DirectionalLightInfo& _info);
	const vector<PointLight*>& GetPointLights() { return m_pointLights; }
	PointLight* GetPointLight(int _index) { return m_pointLights[_index]; }
	size_t GetPointLightCount() { return m_pointLights.size(); }
private:
	GameObject* m_skyBox = nullptr;

private:
	DirectionalLight* m_directionalLigth = nullptr;
	vector<PointLight*> m_pointLights;
};
#endif

