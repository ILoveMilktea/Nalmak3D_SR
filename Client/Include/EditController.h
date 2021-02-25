#pragma once
#include "Component.h"
class EditController :
	public Component
{
public:
	struct Desc
	{

	};

public:
	EditController(Desc* _desc);

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;

private:
	InputManager* m_input;
	bool m_editMode;
};

