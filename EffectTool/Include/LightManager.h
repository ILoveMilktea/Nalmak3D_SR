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
private:
	GameObject* m_skyBox = nullptr;

private:
	DirectionalLight* m_directionalLigth = nullptr;
	vector<PointLight*> m_pointLights;
};
#endif

