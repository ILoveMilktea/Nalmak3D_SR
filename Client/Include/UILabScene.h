#pragma once
#ifndef __UILABSCENE_H__
#define __UILABSCENE_H__

#include "Scene.h"
class UILabScene :
	public Scene
{

	// Scene��(��) ���� ��ӵ�
	virtual void Initialize() override;

public:
	void CreatePauseButton();

	void CreateRader();

	void CreateSplineCurve();

	void PlayerUIPatitial();

};



#endif // !__UILABSCENE_H__

