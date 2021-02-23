#pragma once
#ifndef __CANVASGROUP_H__
#define __CANVASGROUP_H__

#include "Nalmak_Include.h"

class CanvasRenderer;
class NALMAK_DLL CanvasGroup
{
	DECLARE_SINGLETON(CanvasGroup)
public:
	CanvasGroup();
	~CanvasGroup();

public:
	void Initialize(_CANVAS_GROUP _group);
	void Release();

	// fade 0 ~ 1.f
	void SetGroupFade(_CANVAS_GROUP _group, float _fade);
	// interactable (button, toggle, slider)
	void SetGroupInteractive(_CANVAS_GROUP _group, bool _value);
	// block picking (ignore mouse click) bool
	void SetGroupBlockPicking(_CANVAS_GROUP _group, bool _value);
	// gameobject - setactive
	void SetObjectActive(_CANVAS_GROUP _group, bool _value);

public:
	void SetNonGroup(CanvasRenderer* _member);
	void AddGroupMember(CanvasRenderer* _member, _CANVAS_GROUP _group = 0);
	void ChangeGroup(CanvasRenderer* _member, _CANVAS_GROUP _groupToChange = 0);

public:
	const list<CanvasRenderer*>& GetGroup(_CANVAS_GROUP _group);
	CanvasRenderer* Find(const wstring& _name);
	CanvasRenderer* Find(_CANVAS_GROUP _group, const wstring& _name);
	CanvasRenderer* FindFirstObjectbyTag(_CANVAS_GROUP _group);

private:
	vector<list<CanvasRenderer*>> m_groupLists;
	
};



#endif // !__CANVASGROUP_H__

