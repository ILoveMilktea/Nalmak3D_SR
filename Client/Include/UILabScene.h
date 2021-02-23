#pragma once
#ifndef __UILABSCENE_H__
#define __UILABSCENE_H__

#include "Scene.h"
class UILabScene :
	public Scene
{

	// Scene을(를) 통해 상속됨
	virtual void Initialize() override;

private:
	void CreatePauseButton();

	void CreateRader();

	void CreateSplineCurve();
};



#endif // !__UILABSCENE_H__

