#pragma once

#ifndef __LIGHTMANAGER_H__
#define __LIGHTMANAGER_H__

#include "Nalmak_Include.h"
class GameObject;

class LightManager
{
	DECLARE_SINGLETON(LightManager)
private:
	LightManager();
	~LightManager();
public:
	void SetSkyBox(const wstring& _skyBoxName);
private:
	GameObject* m_skyBox = nullptr;
};
#endif

