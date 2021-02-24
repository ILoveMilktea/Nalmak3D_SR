#pragma once
#include "Component.h"
class NALMAK_DLL DrawGizmo_2D :
	public Component
{
public:
	struct Desc
	{

	};
public:
	DrawGizmo_2D(Desc* _desc);
	~DrawGizmo_2D();

public:
	void SetActiveHandles(bool _value);
	bool GetSelected() { return m_selected; }
	bool CheckHandlePicked();

	void ResetingHandlePosition();

private:
	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
private:
	LineManager* m_line;

	GameObject* m_rightHandle;
	GameObject* m_upHandle;

	bool m_selected;
};

