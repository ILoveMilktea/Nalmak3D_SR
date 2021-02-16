#pragma once

#ifndef __LIGHTMANAGER_H__
#define __LIGHTMANAGER_H__

#include "Nalmak_Include.h"
class DirectionalLight;
class GameObject;

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
	bool GetDirectionalLightInfo(DirectionalLightInfo& _info);
private:
	GameObject* m_skyBox = nullptr;

private:
	DirectionalLight* m_directionalLigth = nullptr;
};
#endif

