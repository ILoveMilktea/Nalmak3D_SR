#pragma once

#ifndef __ICYCLE_H__
#define __ICYCLE_H__

#include "Nalmak_Include.h"
#include "Collision.h"

BEGIN(Nalmak)

typedef vector<Collision> Collisions;
class NALMAK_DLL ICycle
{
public:
	ICycle();
	virtual ~ICycle();
protected:
	virtual void Initialize() = 0;
	virtual void OnEnable();
	virtual void OnDisable();
	virtual void Update();
	virtual void LateUpdate();
	virtual void PreRender();
	virtual void PostRender();
	virtual void OnTriggerEnter(Collisions& _col);
	virtual void OnTriggerStay(Collisions& _col);
	virtual void OnTriggerExit(Collisions& _col);
	virtual void Release() = 0;
};
END
#endif // !__ICYCLE_H__
